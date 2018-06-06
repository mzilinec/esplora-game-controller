#include <Esplora.h>
#include <HID.h>
#include <SPI.h>
#include <SD.h>
#include <ArduinoJson.h>

#include "game_controller.h"

DynamicJsonBuffer *buf = NULL;
JsonObject *config = NULL;

String serialIn;
bool serialComplete;
long lastSerial;
long lastUpdate = 0;

long update_interval = 25;

float oldAccel[3], currAccel[3];
int joyCenterX, joyCenterY;
int accelCenterX, accelCenterY;

void setup() {

  Serial.begin(9600);
  if (!SD.begin(8)) {
    Esplora.writeRGB(255,0,0);
    // continue without SD card
    //exit(1);
  }

  HID().AppendDescriptor(&descriptor);
  if (!loadConfig()) createDefaultConfig();

  if (config->containsKey("update_interval")) {
    update_interval = (*config)["update_interval"];
  }

  joyCenterX = Esplora.readJoystickX();
  joyCenterY = Esplora.readJoystickY();
}

bool loadConfig() {
  buf = new DynamicJsonBuffer(128);
  File cfgFile = SD.open(CONFIG_FILE_NAME);
  if (cfgFile) {
    JsonObject &json = buf->parseObject(cfgFile);
    if (json.success()) {
      config = &json;
      cfgFile.close();
      return true;
    }
    cfgFile.close();
  }
  return false;
}

void writeConfig() {
  SD.remove(CONFIG_FILE_NAME);
  File cfgFile = SD.open(CONFIG_FILE_NAME, FILE_WRITE);
  config->printTo(cfgFile);
  cfgFile.close();
}

void createDefaultConfig() {
  delete buf;
  buf = new DynamicJsonBuffer(128);
  JsonObject &json = buf->createObject();
  config = &json;

  json["buttons"] = buf->createObject();
  json["joystick"] = buf->createObject();
  json["accelerometer"] = buf->createObject();
  json["joybtn"] = buf->createObject();

  json["buttons"]["mapping"] = "gamepad";
  json["joystick"]["mapping"] = "joystick";

  writeConfig();
}

void writeKeyboard (const bool (& isDown)[4], const JsonObject &cfg, report_t &report) {
  for (uint8_t i = 0; i < 4; i++) {
    if (isDown[i]) {
      uint8_t key = cfg["keys"].as<char*>()[i];
      if (report.keyOffset > 6) report.keyboard[0] = 0x01; // keyboard overflow
      else report.keyboard[report.keyOffset++] = key; // the-other-endian
    }
  }
}

void writeGamepad (const bool (& isDown)[4], int btnOff, report_t &report) {
  for (uint8_t i = 0; i < 4; i++) // TODO button offset config key
    if (isDown[i]) report.gamepad |= 1 << i + btnOff;
}

// Normalizes an integer to range [-to; to]
int normalize (int what, int to) {
  if (abs(what) > abs(to)) {
    return what > 0 ? to : -to;
  }
  return what;
}

void applyDeadzoneAndSensitivity(int &x, int &y, const int max, const JsonObject &cfg) {
  if (cfg.containsKey("deadzone")) {
    int deadzone = cfg["deadzone"];
    if (abs(x) < deadzone) x = 0;
    if (abs(y) < deadzone) y = 0;
  }
  if (cfg.containsKey("sensitivityX")) {
    x *= cfg["sensitivityX"].as<float>();
  }
  if (cfg.containsKey("sensitivityY")) {
    y *= cfg["sensitivityY"].as<float>();
  }
  x = normalize(x, max);
  y = normalize(y, max);
}

void sendButtons (report_t &report, const JsonObject& cfg) {
  bool btn[4];
  for (uint8_t i = 0; i < 4; i++) btn[i] = Esplora.readButton(i + 1) == LOW;
  String mapping = cfg["mapping"];
  if (mapping == "keyboard") {
    writeKeyboard(btn, cfg, report);
  } else if (mapping == "mouse" || mapping == "joystick") {
    float sensitivity = cfg.containsKey("repeat_rate") ? cfg["repeat_rate"].as<float>() : 10.0f;
    int dx = btn[0] == btn[2] ? 0 : (btn[0] ? sensitivity : -sensitivity);
    int dy = btn[1] == btn[3] ? 0 : (btn[3] ? sensitivity : -sensitivity);
    if (mapping == "mouse") {
      report.mouse[0] = dy;
      report.mouse[1] = dx;
    } else {
      report.joystick[0] = dy;
      report.joystick[1] = dx;
    }
  } else if (mapping == "gamepad") {
    //int btnOff = cfg.containsKey("first_button") ? cfg["first_button"] : 0;
    writeGamepad(btn, 0, report);
  }
}

void sendJoystick (report_t &report, const JsonObject &cfg) {
  int x = - Esplora.readJoystickX() + joyCenterX;
  int y = Esplora.readJoystickY() - joyCenterY;

  applyDeadzoneAndSensitivity(x, y, 512, cfg);

  String mapping = cfg["mapping"];
  if (mapping == "keyboard" || mapping == "gamepad") {
    bool b [4] = { y > 0, x < 0, y < 0, x > 0 };
    if (mapping == "gamepad")
      writeGamepad(b, 4, report);
    else writeKeyboard(b, cfg, report);
  } else if (mapping == "mouse") {
    report.mouse[0] = x;
    report.mouse[1] = y;
  } else if (mapping == "joystick") {
    report.joystick[0] = x;
    report.joystick[1] = y;
  }
}

void sendAccelerometer (report_t &report, const JsonObject &cfg) {
  /* Filter */
  float alpha = cfg.containsKey("noise_filter") ? cfg["noise_filter"] : 0.85f;
  for (uint8_t i = 0; i < 3; i++) {
    oldAccel[i] = currAccel[i];
    currAccel[i] = alpha * oldAccel[i] + (1 - alpha) * Esplora.readAccelerometer(X_AXIS + i);
  }

  /* Translate to X (left/right), Y (up/down) */
  int x, y;
  if (currAccel[1] != 0) {
    y = 123 - currAccel[2];
    if (currAccel[1] < 0) y = -y;
  }
  x = currAccel[0];

  if ((*config)["joybtn"]["mapping"] == "calibrate") {
    if (Esplora.readJoystickButton() == LOW) {
      accelCenterX = x; accelCenterY = y;
    }
  }

  x -= accelCenterX;
  y -= accelCenterY;

  applyDeadzoneAndSensitivity(x, y, 127, cfg);

  report.accelerometer[0] = x;
  report.accelerometer[1] = y;
}

void loop() {
  // send report every 'update_interval' milliseconds
  if (lastUpdate + update_interval < millis()) {
    lastUpdate = millis();
    report_t report;
    sendButtons(report, (*config)["buttons"]);
    sendJoystick(report, (*config)["joystick"]);
    sendAccelerometer(report, (*config)["accelerometer"]);
    report.slider = Esplora.readSlider();
    // joystick button
    String s = (*config)["joybtn"]["mapping"];
    if (Esplora.readJoystickButton() == LOW) {
      if (s == "click") {
        report.click = true;
      } else if (s == "keyboard") {
        char key = (*config)["joybtn"]["key"].as<char*>()[0];
        if (report.keyOffset > 6) report.keyboard[0] = 0x01; // keyboard overflow
        else report.keyboard[report.keyOffset++] = key;
      }
    }

    report.send();
  }

  // possibly read config from serial
  serialReadLine();
  if (serialComplete) {
    if (serialIn[0] == ASCII_BEL) {
      Serial.write(ASCII_ACK);
      Serial.write('\n');
      Serial.flush();
    } else serialProcessLine();
    serialComplete = false;
  }
  if (!serialComplete || lastSerial + SERIAL_TIMEOUT < millis()) {
    serialIn = String();
  }
}

// Reads from serial buffer into global variable
// and sets serialComplete when end of line reached
void serialReadLine() {
  while (!serialComplete && Serial.available()) {
    lastSerial = millis();
    char c = (char) Serial.read();
    serialIn += c;
    if ((c == '\n' || c == '\r')) {
      serialComplete = true;
    }
  }
}

// Returns the corresponding JSON element
// from a String in format foo.(bar).(...)
JsonObject *stringToKey(String &word, String &key) {
  JsonObject *json = config;
  for (int i = 0; i < word.length(); i++) {
    if (word[i] == '.') {
        json = &((*json)[key].as<JsonObject>());
        // adding a new tree is forbidden
      key = "";
    } else key += word[i];
  }
  return json;
}

// Returns the next word from String 'line'
// starting at offset 'off' or an empty String,
// setting 'off' to (end of word) + 1
String nextWord (String &line, int &off) {
  String word = "";
  while (line[off] == ' ') {off++;}
  while (line[off] != ' ' && line [off] != '\n') { word += line[off++]; }
  return word;
}

void serialProcessLine() {
  String str; int off = 0;
  str = nextWord(serialIn, off);
  String key = nextWord(serialIn, off);
  if (str == "get") {
    JsonObject *json;
    if (key == "") json = config;
    else json = stringToKey(key, str = "");
    (*json)[key].prettyPrintTo(Serial);
    Serial.write(ASCII_ACK); Serial.write('\n');
  } else if (str == "set") {
    JsonObject *json = stringToKey(key, str = "");
    (*json)[str] = nextWord(serialIn, off);
    writeConfig();
    Serial.write(ASCII_ACK);
    Serial.write('\n');
  } else if (str == "defaults") {
    createDefaultConfig();
    Serial.write(ASCII_ACK); Serial.write('\n');
  } else {
    // unknown command
    Serial.write(ASCII_NAK); Serial.write('\n');
  }
  Serial.flush();
}
