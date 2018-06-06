#define REPORT_MOUSE 2
#define REPORT_KEYBOARD 3
#define REPORT_GAMEPAD 4
#define REPORT_JOYSTICK 5
#define REPORT_ACCELEROMETER 6
#define REPORT_SLIDER 7

const char * CONFIG_FILE_NAME = "CONFIG.JSN";
const long SERIAL_TIMEOUT = 1000;

const char ASCII_SOH = 0x01;
const char ASCII_EOT = 0x04;
const char ASCII_STX = 0x02;
const char ASCII_ETX = 0x03;
const char ASCII_ACK = 0x6;
const char ASCII_NAK = 0x15;
const char ASCII_BEL = 0x7;

typedef struct report_t {
  uint8_t gamepad = 0;
  int16_t joystick[2] = {0};
  int8_t accelerometer[3] = {0};
  uint16_t slider = 0;
  int8_t click = 0;
  int16_t mouse[2] = {0};
  // one special, one reserved
  // and six key presses
  uint8_t keyboard[6] = {0};
  int8_t keyOffset = 0;

  void send() {
    HID().SendReport(REPORT_GAMEPAD, &gamepad, sizeof(gamepad));
    HID().SendReport(REPORT_JOYSTICK, &joystick, sizeof(joystick));
    HID().SendReport(REPORT_ACCELEROMETER, &accelerometer, sizeof(accelerometer));
    HID().SendReport(REPORT_SLIDER, &slider, sizeof(slider));
    HID().SendReport(REPORT_MOUSE, &click, sizeof(click) + sizeof(mouse));
    HID().SendReport(REPORT_KEYBOARD, &keyboard, sizeof(keyboard));
  }
} report_t;

const static uint8_t descriptorBytes[] PROGMEM = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x05,                    // USAGE (Game Pad)
    0xa1, 0x01,                    // COLLECTION (Application)
/** gamepad **/
    0xa1, 0x00,                    // COLLECTION (Physical)
	  0x05, 0x09,                    //   USAGE_PAGE (Button)
    0x19, 0x01,                    //   USAGE_MINIMUM (Button 1)
    0x29, 0x04,                    //   USAGE_MAXIMUM (Button 4)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x08,                    //   REPORT_COUNT (8)
	  0x85, REPORT_GAMEPAD,          //   REPORT_ID (gamepad)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0xc0,                          // END_COLLECTION
/** joystick **/
	  0xa1, 0x00,                    // COLLECTION (Physical)
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    // USAGE (X)
    0x09, 0x31,                    // USAGE (Y)
    0x16, 0x00, 0xfe,              // LOGICAL_MINIMUM (-512)
    0x26, 0x00, 0x02,              // LOGICAL_MAXIMUM (512)
    0x85, REPORT_JOYSTICK,         // REPORT_ID (2)
    0x75, 0x10,                    // REPORT_SIZE (16)
    0x95, 0x02,                    // REPORT_COUNT (2)
    0x81, 0x02,                    // INPUT (Data,Var,Abs)
    0xc0,                          // END_COLLECTION
/** accelerometer **/
	  0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x39,                    // USAGE (Hat switch)
    0xa1, 0x00,                    // COLLECTION (Physical)
    0x05, 0x01,                    //   USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //	USAGE (X)
    0x09, 0x31,                    // 	USAGE (Y)
    0x09, 0x32,                    // 	USAGE (Z)
    0x75, 0x08,                    // 	REPORT_SIZE (8)
    0x95, 0x03,                    // 	REPORT_COUNT (3)
    0x85, REPORT_ACCELEROMETER,    // 	REPORT_ID (4)
    0x15, 0x81,                    // 	LOGICAL_MINIMUM (-127)
    0x25, 0x7f,                    // 	LOGICAL_MAXIMUM (127)
    0x81, 0x02,                    // 	INPUT (Data,Var,Abs)
    0xc0,                          // END_COLLECTION
/** slider **/
	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0xa1, 0x00,                    // COLLECTION (Physical)
    0x09, 0x36,                    //   USAGE (Slider)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x03,              //   LOGICAL_MAXIMUM (1023)
    0x85, REPORT_SLIDER,           //   REPORT_ID (5)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x10,                    //   REPORT_SIZE (16)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0xc0,                          // END_COLLECTION
    0xc0,                           // END_COLLECTION

/** keyboard **/
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x00,                    // COLLECTION (Physical)
    0x85, REPORT_KEYBOARD,         // REPORT_ID
   // 0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
   
   // 0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
   // 0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
   // 0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
   // 0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    
   // 0x75, 0x01,                    //   REPORT_SIZE (1)
   // 0x95, 0x08,                    //   REPORT_COUNT (8)
   // 0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    
   // 0x95, 0x01,                    //   REPORT_COUNT (1)
   // 0x75, 0x08,                    //   REPORT_SIZE (8)
   // 0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
    
    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM
    0x25, 0xff,                     
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0x00,                    //   USAGE_MINIMUM
    0x29, 0xff,
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0,                          // END_COLLECTION

/** mouse **/
	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	0x09, 0x02,                    // USAGE (Mouse)
	0xa1, 0x01,                    // COLLECTION (Application)
	0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    // 	COLLECTION (Physical)
    0x85, REPORT_MOUSE,            //    REPORT_ID (6)
    // mouse button
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x09, 0x01,                    //     USAGE(Button 1)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    // padding
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x75, 0x07,                    //     REPORT_SIZE (7)
    0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
    // mouse motion
    0x05, 0x01,                    //    USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //  	 USAGE (X)
    0x09, 0x31,                    //  	 USAGE (Y)
    0x75, 0x10,                    //  	 REPORT_SIZE (16)
    0x95, 0x02,                    //  	 REPORT_COUNT (2)

    0x16, 0x00, 0xfe,              // LOGICAL_MINIMUM (-512)
    0x26, 0x00, 0x02,              // LOGICAL_MAXIMUM (512)
    0x81, 0x06,                    //    INPUT (Data,Var,Rel)

    0xc0,                          //   END_COLLECTION
	0xc0,                           // END_COLLECTION

  //0xc0                           // END_COLLECTION

};

const static HIDSubDescriptor descriptor = HIDSubDescriptor (&descriptorBytes, sizeof(descriptorBytes));
