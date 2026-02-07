#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ctime>

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#if defined(__WINDOWS__)
#include "windows.h"
HANDLE Logger::hConsole = nullptr;
#endif

ofstream Logger::outputFile;
bool Logger::outputFileInit = false;

mutex Logger::log_Mutex;




