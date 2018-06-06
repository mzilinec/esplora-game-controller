#include <iostream>
#include <vector>
#include <sstream>
#include <regex>
#include <string>
#include "SerialPort.h"
#include "gen_keymap.h"

std::map<const std::string, unsigned char> keymap;

const char ASCII_SOH = 0x01;
const char ASCII_EOT = 0x04;
const char ASCII_STX = 0x02;
const char ASCII_ETX = 0x03;
const char ASCII_ACK = 0x6;
const char ASCII_NAK = 0x15;
const char ASCII_BEL = 0x7;

std::string PromptUserForPort() {
    std::cout << "Controller not detected automatically!" << std::endl;
    std::cout << "Enter port with esplora:" << std::endl;
    std::string port;
    std::cin >> port;
    // todo check format
    return "\\\\.\\" + port;
}

bool Ping(HANDLE &h) {
    std::cout << "Pinging" << std::endl;
    std::string line;
    line += ASCII_BEL;
    line += '\n';
    writeLine(h,  line);
    std::string response = readLine(h);
    return response[0] == ASCII_ACK;
}

std::vector<std::string> SplitToWords(const std::string & str) {
    std::vector<std::string> words;
    bool isSpace = true;
    std::string word;
    for (auto &&item : str) {
        if (item == ' ' || item == '\t') {
            if (!isSpace && !word.empty()) {
                words.push_back(word);
            }
            isSpace = true;
        } else {
            if (isSpace) {
                word = std::string();
            }
            word += item;
            isSpace = false;
        }
    }
    if (!isSpace && !word.empty()) {
        words.push_back(word);
    }
    return words;
}

void ConvertKeyCodes (std::string &str) {
    std::regex r ("KEY_[A-Za-z_]+ *");
    std::smatch match;

    while (std::regex_search(str, match, r)) {
        std::string keyname = match.str();
        // erase spaces
        keyname.erase(std::remove(keyname.begin(), keyname.end(), ' '), keyname.end());
        // convert to keycode
        auto it = keymap.find(keyname);
        if (it == keymap.end()) {
            std::cout << "Warning: invalid keycode" << std::endl;
            return;
        }
        unsigned char keycode = it->second;
        std::string repl; repl += keycode;
        str = std::regex_replace(str, r, repl, std::regex_constants::format_first_only);
    }

    #ifdef DEBUG
    for (int i = 0; i < str.length(); i++)
        std::cout << (int) str[i] << " ";
    std::cout << std::endl;
    std::cout << str << std::endl;
    #endif
}

void ProcessLine (HANDLE &h, std::string &line) {
    std::vector<std::string> words = SplitToWords(line);

    if (!words.empty()) {
        std::string cmd = words[0];
        if (cmd.find("get") == 0) {
            writeLine(h, line);
            try {
                std::cout << readUntil(h, ASCII_ACK) << std::endl;
            } catch (std::exception &e) {
                std::cerr << "Read error" << std::endl;
            }
        } else if (cmd.find("set") == 0 || cmd.find("defaults") == 0) {
            ConvertKeyCodes(line);
            writeLine(h, line);
            try {
                std::string response = readLine(h);
                if (response[0] == ASCII_ACK) {
                        std::cout << "OK" << std::endl;
                } else throw std::exception();
            } catch (std::exception &e) {
                std::cerr << "Write error" << std::endl;
            }
        } else {
            std::cout << "Invalid command" << std::endl;
        }
    }
}

bool tryConnect(HANDLE &h) {
    for (int i = 1; i < 100; i++) {
        std::string port = "\\\\.\\COM";
        char arr[3];
        itoa(i, arr, 10);
        port += arr;
        if (connect(h, port.data()) && Ping(h))
            return true;
    }
    return false;
}

int main() {
    //std::cout << "Esplora Game Controller Config Tool" << std::endl << std::endl;

    fillKeymap(keymap); // name to keycode mappings, e.g. KEY_ENTER
    HANDLE h;
    bool flag = tryConnect(h);
    if (!flag) {
        std::string port = PromptUserForPort();
        flag = connect(h, port.data()) && Ping(h);
    }
    if (flag) {
        std::cout << ">> Connection successful" << std::endl;
    } else {
        std::cout << ">> Connection failed!" << std::endl;
        char c;
        std::cin >> c;
        CloseHandle(h);
        return 1;
    }
    while (1) {
        std::string line;
        getline(std::cin, line);
        if (line == "exit" || line == "quit") {
            break;
        } else {
            flush(h);
            ProcessLine(h, line);
            flush(h);
        }
    }
    CloseHandle(h);
    return 0;
}