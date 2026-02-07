//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
//#include "bobtypes.h"
#include <mutex>

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

#if defined(__WINDOWS__)
#include "windows.h"
#endif

class Logger
{
public:
	string name = "";


#if defined(__WINDOWS__)
	static HANDLE hConsole;
#endif

	static ofstream outputFile;
	static bool outputFileInit;
	static mutex log_Mutex;

//	Logger();
//	Logger(const string& s);
//	static void initLogger();
//	void log(const string& s);
//	void info(const string& s);
//	void warn(const string& s);
//	void debug(const string& s);
//	void error(const string& s);
//
//	string currentDateTime();

	

	//=========================================================================================================================
	Logger()
	{//=========================================================================================================================


	}


	//=========================================================================================================================
	Logger(const string& s)
	{//=========================================================================================================================
		name = s;
	}


	//=========================================================================================================================
	static void initLogger()
	{//=========================================================================================================================

#if defined(__WINDOWS__)
		if (hConsole == nullptr)hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif


		if (!outputFileInit)
		{
			outputFileInit = true;

			string name = "log.html";
#ifdef ORBIS
			name = "/app0/" + name;
#endif

			outputFile.open(name, ofstream::out);

			outputFile << "<html><body>" << endl;
		}
	}



	//=========================================================================================================================
	static string currentDateTime()
	{//=========================================================================================================================
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
		// for more information about date/time format
		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

		return buf;
	}

	//#ifndef _COLORS_
	//#define _COLORS_
	//
	///* FOREGROUND */
	//#define RST  "\x1B[0m"
	//#define KRED  "\x1B[31m"
	//#define KGRN  "\x1B[32m"
	//#define KYEL  "\x1B[33m"
	//#define KBLU  "\x1B[34m"
	//#define KMAG  "\x1B[35m"
	//#define KCYN  "\x1B[36m"
	//#define KWHT  "\x1B[37m"
	//
	//#define FRED(x) KRED x RST
	//#define FGRN(x) KGRN x RST
	//#define FYEL(x) KYEL x RST
	//#define FBLU(x) KBLU x RST
	//#define FMAG(x) KMAG x RST
	//#define FCYN(x) KCYN x RST
	//#define FWHT(x) KWHT x RST
	//
	//#define BOLD(x) "\x1B[1m" x RST
	//#define UNDL(x) "\x1B[4m" x RST
	//
	//#endif  /* _COLORS_ */


	//=========================================================================================================================
	static void staticLog(const string& s)
	{//=========================================================================================================================
		cout << currentDateTime() << " | " << " | " << s << endl;

		outputFile << currentDateTime() << " <span style=\"color:black\">" << " LOG: " << s << "</span><br>" << endl;
	}

	//=========================================================================================================================
	void log(const string& s)
	{//=========================================================================================================================

		lock_guard<mutex> lock(log_Mutex);

#if defined(__WINDOWS__)
		FlushConsoleInputBuffer(hConsole);
		SetConsoleTextAttribute(hConsole, 15);
#endif

		cout << currentDateTime() << " | " << name << " | " << s << endl;

		outputFile << currentDateTime() << " <span style=\"color:black\">" << name << " LOG: " << s << "</span><br>" << endl;
	}

	//=========================================================================================================================
	void info(const string& s)
	{//=========================================================================================================================

		lock_guard<mutex> lock(log_Mutex);

#if defined(__WINDOWS__)
		FlushConsoleInputBuffer(hConsole);
		SetConsoleTextAttribute(hConsole, 15);
#endif


		cout << currentDateTime() << " | " << name << " | " << s << endl;


		outputFile << currentDateTime() << " <span style=\"color:black\">" << name << " INFO: " << s << "</span><br>" << endl;
	}



	// color your getText in Windows console mode
	// colors are 0=black 1=blue 2=green and so on to 15=white  
	// colorattribute = foreground + background * 16
	// to get red getText on yellow use 4 + 14*16 = 228
	// light red on yellow would be 12 + 14*16 = 236
	// DARKBLUE = 1, DARKGREEN 2, DARKTEAL 3, DARKRED 4, DARKPINK 5, DARKYELLOW 6, GRAY 7, DARKGRAY 8, BLUE 9, GREEN 10, TEAL 11, RED 12, PINK 13, YELLOW 14, WHITE 15


	//=========================================================================================================================
	void debug(const string& s)
	{//=========================================================================================================================
		lock_guard<mutex> lock(log_Mutex);

#if defined(__WINDOWS__) && defined(_DEBUG)
		FlushConsoleInputBuffer(hConsole);
		SetConsoleTextAttribute(hConsole, 10);//green
		cout << currentDateTime() << " | " << name << " | " << s << endl;
		SetConsoleTextAttribute(hConsole, 15);
#elif defined(_DEBUG)
		cout << "\x1B[32m" << currentDateTime() << " | " << name << " DEBUG: " << s << "\x1B[0m" << endl;
#endif

		outputFile << currentDateTime() << " | " << " <span style=\"color:darkgreen\">" << name << " DEBUG: " << s << "</span><br>" << endl;

	}

	//=========================================================================================================================
	void warn(const string& s)
	{//=========================================================================================================================

		lock_guard<mutex> lock(log_Mutex);

#if defined(__WINDOWS__)
		FlushConsoleInputBuffer(hConsole);
		SetConsoleTextAttribute(hConsole, 14);//yellow
		cout << currentDateTime() << " | " << name << " | " << s << endl;
		SetConsoleTextAttribute(hConsole, 15);
#else
		cout << "\x1B[33m" << currentDateTime() << " | " << name << " WARN: " << s << "\x1B[0m" << endl;
#endif

		outputFile << currentDateTime() << " | " << " <span style=\"color:gold\">" << name << " WARN: " << s << "</span><br>" << endl;

	}

	//=========================================================================================================================
	void error(const string& s)
	{//=========================================================================================================================

		lock_guard<mutex> lock(log_Mutex);

#if defined(__WINDOWS__)
		FlushConsoleInputBuffer(hConsole);
		SetConsoleTextAttribute(hConsole, 12);//red
		cout << currentDateTime() << " | " << name << " | " << s << endl;
		SetConsoleTextAttribute(hConsole, 15);
#else
		cout << "\x1B[31m" << currentDateTime() << " | " << name << " ERROR: " << s << "\x1B[0m" << endl;
#endif

		outputFile << currentDateTime() << " | " << " <span style=\"color:red\">" << name << " ERROR: " << s << "</span><br>" << endl;

#if defined(_DEBUG) && ! defined(ORBIS)
		throw new exception;
#endif
	}

};

