#pragma once
#include <string>

using namespace std;

class Schedule
{
private:
	string title;
	string startDate;
	string endDate;
	string category;
	string memo;

public:
	Schedule(string t, string sd, string ed, string ca, string me);
};

