#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Schedule.h"

using namespace std;

class Calender
{
public:
	Calender();
	map<string, vector<Schedule>> schsmap; //날짜별로 검색용
	vector<Schedule> allSchs; //keysearch
private:

};

