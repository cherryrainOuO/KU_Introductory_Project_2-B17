#pragma once
#include <fstream>
#include <sstream>
#include "Calender.h"
#include <regex>
#include <Windows.h>
#include <atlconv.h>
#include <locale>
#include <codecvt>

class ScheduleDataManager
{
public:
	ScheduleDataManager() {};
	bool loadDataFile(Calender& c);
private:
	string ws2s(const std::wstring& wstr);
	void trim(string& str);
	//검사
	bool isRight(vector<string> record);
	bool checkT(string data); //title
	bool checkC(string data); // category
	bool checkD(string s); //date
	bool checkM(string data); //memo
};

