#pragma once
#include <fstream>
#include <sstream>
#include "Calender.h"
#include <regex>
#include <Windows.h>
#include <atlconv.h>
#include <locale>
#include <codecvt>
#include <atlstr.h>

class ScheduleDataManager
{
public:
	ScheduleDataManager() {};
	bool loadDataFile(Calender& c);
	bool saveDataFile(Calender& c);
	friend class Management;

private:
	wstring s2ws(const string& str);
	string ws2s(const wstring& wstr);
	void trim(string& str);
	//검사
	bool isRight(vector<string> record);
	bool checkT(string data); //title
	bool checkC(string data); // category
	bool checkD(string s); //date
	bool checkD2(string sd, string ed);
	bool checkM(string data); //memo
};

