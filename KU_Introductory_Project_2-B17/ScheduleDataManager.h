#pragma once
#include <fstream>
#include <sstream>
#include "Calender.h"
#include <regex>
#include <Windows.h>
#include <atlconv.h>

class ScheduleDataManager
{
public:
	ScheduleDataManager() {};
	bool loadDataFile(Calender& c);
private:
	//검사
	bool isRight(vector<string> record);
	bool checkT(string data); //title
	bool checkC(string data); // category
	bool checkD(string s); //date
	bool checkM(string data); //memo
};

