#pragma once
#include <iostream>
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
	void print();
	//getter & setter
	string getTitle() { return title; };
	void setTitle(string t) { title = t; };
	string getStartDate() { return startDate; };
	void setStartDate(string date) { startDate = date; };
	string getEndDate() { return endDate; };
	void setEndDate(string date) { endDate = date; };
	string getCategory() { return category; };
	void setCategory(string cat) { category = cat; };
	string getMemo() { return memo; };
	void setMemo(string mm) { memo = mm; };
};

