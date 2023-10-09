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
#include "Category.h"

class ScheduleDataManager
{
public:
	ScheduleDataManager() {};
	bool loadDataFile(Calender& c, Category& cat);
	bool saveDataFile(Calender& c);
	friend class Management;
	friend class CategoryDataManager;

private:
	wstring s2ws(const string& str);
	string ws2s(const wstring& wstr);
	void trim(string& str);
	//검사
	bool isRight(vector<string> record, vector<string>* cates);
	bool checkT(string data); //title
	bool checkC(string data, vector<string>* cates); // category
	bool checkD(string s); //date
	bool checkD2(string sd, string ed);
	bool checkM(string data); //memo
};

