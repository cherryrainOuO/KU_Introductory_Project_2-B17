#pragma once
#include "Calender.h"
#include "Schedule.h"
#include "Classification.h"
#include "ScheduleDataManager.h"
#include "CategoryDataManager.h"
#include <windows.h>
#include <conio.h>
#include <regex>

/* ## : 수정 필요, ctrl + f로 찾기 바람 */

class Management
{
private:
	Calender* cal;
	string dateinfo;
	ScheduleDataManager SDM;
	CategoryDataManager* CDM;
	Classification* CLS;

	void printSchedule();
	void addSchedule();
	void mod_or_delSchedule();
	int isValidDate(string dateStr);
	bool is_digit(string str);

public:
	Management(Calender* c, CategoryDataManager* _cateManager, Classification* _class) { cal = c; CDM = _cateManager; CLS = _class; };
	void Prompt();
};

