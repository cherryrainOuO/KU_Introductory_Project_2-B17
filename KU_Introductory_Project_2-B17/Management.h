#pragma once
#include "Calender.h"
#include "Schedule.h"
#include <windows.h>
#include <conio.h>
#include <regex>

/* ## : 수정 필요, ctrl + f로 찾기 바람 */

class Management
{
private:
	Calender* cal;
	string dateinfo;

	void printSchedule();
	void addSchedule();
	void mod_or_delSchedule();
	int isValidDate();
	bool is_digit(string str);

public:
	Management(Calender* c) { cal = c; };
	void Prompt();
};

