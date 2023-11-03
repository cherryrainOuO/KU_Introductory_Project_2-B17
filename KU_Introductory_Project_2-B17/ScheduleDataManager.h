#pragma once
#include <fstream>
#include <sstream>
#include "Calender.h"
#include <ctime>
#include <regex>
#include <Windows.h>
#include <atlconv.h>
#include <map>
#include <locale>
#include <codecvt>
#include <atlstr.h>
#include "Category.h"
#include <stack>


#define SIZE 8 //데이터 요소
#define CYMAX 3 //주기 0~3

class ScheduleDataManager
{
public:
	ScheduleDataManager() {};
	bool loadDataFile(Calender& c, Category& cat);
	bool saveDataFile(Calender& c);
	friend class Management;
	friend class CategoryDataManager;

private:
	map<int, Schedule> dupKeySches;

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
	bool checkCy(string data, string sd, string ed); //cycle
	bool checkKey(string data); //key
	bool checkCont(Schedule s);
	bool isSameSch(Schedule s1, Schedule s2);
	
	//날짜 관련 연산
	void initTime(struct tm& date, int y, int m, int d);
	int calcPeriod(string d1, string d2);
	string addDate(string date, int cy, int endday);
	string calcSD(string ed, int pe);
};

