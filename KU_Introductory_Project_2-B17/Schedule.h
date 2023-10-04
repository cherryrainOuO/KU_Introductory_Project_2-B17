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
	string getTitle() { return title; };
	string getStartDate() { return startDate; };
	string getEndDate() { return endDate; };
	string getCategory() { return category; };
	string getMemo() { return memo; };
};