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


#define SIZE 10 //기본 데이터 요소 개수(카테고리가 1개일 때)
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
	map<int, map<int, Schedule>> dupKeySches;
	map<int, int> max_cy_k;

	wstring s2ws(const string& str);
	string ws2s(const wstring& wstr);
	void trim(string& str);
	//검사
	bool isRight(vector<string> record, vector<string>* cates);
	bool checkT(string data); //title
	bool checkCNum(string data); //numOfCategories
	bool checkC(vector<string> data, vector<string>* cates); // category
	bool checkD(string s); //date
	bool checkD2(string sd, string ed);
	bool checkM(string data); //memo
	bool checkCy(string data); //cycle
	bool checkKey(string data); //key
	bool checkRptK(string data, string data2, string data3);
	bool checkCont(Schedule s);
	
	//날짜 관련 연산
	void initTime(struct tm& date, int y, int m, int d);
	int calcPeriod(string d1, string d2);
	string addDate(string date, int cy, int endday);
	string calcSD(string ed, int pe);
};

