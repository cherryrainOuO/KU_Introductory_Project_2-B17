#pragma once
#include "Calender.h"
#include "Schedule.h"
#include <windows.h>
#include <conio.h>
#include <queue>
#include <regex>

class KeywordSearch
{
private:
	Calender* cal;
	string kwd;
	queue<Schedule> res;
	int isKeyRight();
	void search();
	void print();
	void removeSpace(string& s);

public:
	/*constructor*/
	KeywordSearch(Calender* c) { cal = c; };

	void prompt();
};

