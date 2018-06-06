#include <ctime>
#include "SerialPort.h"

const int TIMEOUT_MS = 1000;

bool connect(HANDLE & hComm, const char *pcCommPort) {
    //  Open a handle to the specified com port.
    hComm = CreateFile(pcCommPort,
            GENERIC_READ | GENERIC_WRITE,
            0,              //  must be opened with exclusive-access
            NULL,           //  default security attributes
            OPEN_EXISTING,  //  must use OPEN_EXISTING
            0,              //  not overlapped I/O
            NULL);          //  hTemplate must be NULL for comm devices

    if (hComm == INVALID_HANDLE_VALUE) {
        //  Handle the error.
        //printf("CreateFile failed with error %d.\n", (uint32_t) GetLastError());
        return false;
    }

    DCB dcb;
    /*Secure*/ZeroMemory(&dcb, sizeof (DCB)); //  Initialize the DCB structure.
    dcb.DCBlength = sizeof (DCB);

    //  Build on the current configuration by first retrieving all current settings.
    if (!GetCommState(hComm, &dcb)) {
        //  Handle the error.
        //printf("GetCommState failed with error %d.\n", (uint32_t) GetLastError());
        return false;
    }

    //  Fill in DCB values and set the com state: 
    dcb.BaudRate = CBR_9600;    //  baud rate
    dcb.ByteSize = 8;           //  data size, xmit and rcv
    dcb.Parity = NOPARITY;      //  parity bit
    dcb.StopBits = ONESTOPBIT;  //  stop bit

    if (!SetCommState(hComm, &dcb)) {
        //  Handle the error.
        //printf("SetCommState failed with error %d.\n", (int) GetLastError());
        return false;
    }

    COMMTIMEOUTS commtimeouts;
    commtimeouts.ReadIntervalTimeout = 100;
    commtimeouts.ReadTotalTimeoutConstant = 100;
    commtimeouts.ReadTotalTimeoutMultiplier = 1;
    if ( !SetCommTimeouts(hComm, &commtimeouts) ) {
        std::cout << "[ERR] Unable to set timeouts." << std::endl;
        return false;
    }

    return true;
}

void writeLine(HANDLE & handle, std::string line) throw (std::exception) {
    line += '\n';
    bool errorFlag = false;
    DWORD len = line.size();
    DWORD off = 0;
    errorFlag = (bool) WriteFile(handle, line.c_str(), len, &off, NULL);
    if (!errorFlag) throw std::exception();
}

std::string readLine(HANDLE &handle) throw (std::exception) {
    const clock_t startTime = std::clock();
    DWORD bytesRead, errors;
    COMSTAT status;
    ClearCommError(handle, &errors, &status);
    std::string str;
    while (true) {
        char buf = 0;
        if (!ReadFile(handle, &buf, 1, &bytesRead, NULL) || !buf) {
            throw std::exception();
        }
        str += buf;
        if (buf == '\n') return str;
        const clock_t runTime = ( std::clock () - startTime ) /  CLOCKS_PER_SEC;
        if (runTime > TIMEOUT_MS) {
            std::cerr << "Timeout ";
            throw std::exception();
        }
    }
}

std::string readUntil(HANDLE &handle, char c) throw (std::exception) {
    const clock_t startTime = std::clock();
    DWORD bytesRead, errors;
    COMSTAT status;
    ClearCommError(handle, &errors, &status);
    std::string str;
    while (true) {
        char buf = 0;
        if (!ReadFile(handle, &buf, 1, &bytesRead, NULL) || !buf) {
            throw std::exception();
        }
        //str += buf;
        if (buf == c) return str;
        else str += buf;
        const clock_t runTime = ( std::clock () - startTime ) /  CLOCKS_PER_SEC;
        if (runTime > TIMEOUT_MS) {
            std::cerr << "Timeout ";
            std::cerr.flush();
            throw std::exception();
        }
    }
}

void flush(HANDLE & handle) {
    DWORD bytesRead, toRead, errors;
    COMSTAT status;

    ClearCommError(handle, &errors, &status); //Use the ClearCommError function to get status info on the Serial port
    toRead = status.cbInQue;
    char * buf = new char[toRead];

    if (!ReadFile(handle, buf, toRead, &bytesRead, NULL)) {
        //  Handle the error.
        std::cerr << "Terminal failure: Unable to read from file.\n GetLastError=" << GetLastError() << std::endl;
        delete [] buf;
        return;
    }

    delete [] buf;
    return;
}
