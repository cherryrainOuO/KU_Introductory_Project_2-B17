#pragma once
#include "Calender.h"
#include "Schedule.h"
#include <windows.h>
#include <conio.h>
#include <regex>

class Management
{
private:
	Calender* cal;
	string dateinfo;

	void printSchedule();
	void addSchedule();
	void modifySchedule();
	bool isValidDate();

public:
	Management(Calender* c) { cal = c; };
	void Prompt();
};

