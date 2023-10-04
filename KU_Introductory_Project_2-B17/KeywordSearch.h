#pragma once
#include "Calender.h"
#include "Schedule.h"
#include <windows.h>
#include <conio.h>
#include <regex>

class KeywordSearch
{
private:
	Calender* cal;
	string kwd;
	vector<Schedule> res;
	int isKeyRight();
	void search();
	void print();
	void removeSpace(string& s);

public:
	/*constructor*/
	KeywordSearch() {};
	KeywordSearch(Calender* c) { cal = c; };

	void prompt();
};

