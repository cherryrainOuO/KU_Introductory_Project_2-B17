#pragma once
#include "Calender.h"
#include "Schedule.h"
#include "Classification.h"
#include "ScheduleDataManager.h"
#include "CategoryDataManager.h"
#include <windows.h>
#include <conio.h>
#include <regex>
#include <sstream>
#include <algorithm>
#include <ctime>

#define FINAL_YEAR 2030

using namespace std;
/* ## : 수정 필요, ctrl + f로 찾기 바람 */

class Management
{
private:
	Calender* cal;
	string dateinfo;
	ScheduleDataManager SDM;
	CategoryDataManager* CDM;
	Classification* CLS;
	Category* cate;

	void printSchedule();
	void addSchedule();
	void mod_or_delSchedule();
	// int isValidDate(string dateStr);
	bool is_digit(string str);
	int zeller(int year, int month, int day);
	int getDiffDate(string startDate, string endDate);
	string calcStartDate(string endDate, int diffDate);
	int findLastDayofMonth(int endDateYear, int endDateMonth);

public:
	Management(Calender* c, CategoryDataManager* _cateManager, Classification* _class, Category* _cate) { cal = c; CDM = _cateManager; CLS = _class; cate = _cate; };
	void Prompt();
};

