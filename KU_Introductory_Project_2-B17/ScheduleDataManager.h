#pragma once
#include <fstream>
#include <sstream>
#include "Calender.h"

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
	bool checkD(string s, string e); //date
	bool checkM(string data); //memo
};

