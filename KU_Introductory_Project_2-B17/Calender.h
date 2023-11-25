#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <regex>
#include "Schedule.h"

using namespace std;
#define FINAL_YEAR 2030

class Calender
{
public:
	Calender();
	map<string, vector<Schedule>> schsmap; //날짜별로 검색용
	vector<Schedule> allSchs; //keysearch
	map<int, int> cycle_per_keys;
	void setHighestKey();
	int getHighestKey();
	int isValidDate(string dateStr);

private:
	int highestKey = 0;
};

