#pragma once
#include "Calender.h"
#include "Schedule.h"
#include <windows.h>
#include <conio.h>
#include <regex>

class Classification
{
private:
	Calender cal;
	string kwd;
	vector<Schedule> res;

	void CategoryAdd();
	void PrintSchedule_ByCategory();
	void CategoryEdit();
	void CategoryRemove();

public:
	/*constructor*/
	Classification() {};
	Classification(Calender c) { cal = c; };

	void Prompt();
};

