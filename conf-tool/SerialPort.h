#ifndef SERIALPORT_H
#define	SERIALPORT_H

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

bool connect(HANDLE & hComm, const char *pcCommPort);
void flush(HANDLE &);
std::string readLine(HANDLE&) throw (std::exception);
std::string readUntil(HANDLE&, char c) throw (std::exception);
void writeLine(HANDLE&, std::string) throw(std::exception);

#endif