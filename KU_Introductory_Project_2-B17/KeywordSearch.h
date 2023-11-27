#pragma once
#include "Calender.h"
#include "Schedule.h"
#include <windows.h>
#include <conio.h>
#include <queue>
#include <regex>
#include <sstream>

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
	vector<string> split_by_space(string str, char del);
	void Prompt_after_or_before_When(queue<Schedule> res, string cateKwd);

public:
	/*constructor*/
	KeywordSearch(Calender* c) { cal = c; };

	void prompt();
};

