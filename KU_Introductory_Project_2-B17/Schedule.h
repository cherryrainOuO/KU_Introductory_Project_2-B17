#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Schedule
{
private:
	string title;
	string startDate;
	string endDate;
	vector<string> category;
	string memo;
	int key; 
	int cycle; //0: x, 1: 매년, 2: 매달, 3: 매주
	string rptEndDate; //반복종료일
	int rptK; //대체 일정 구분

public:
	Schedule();
	Schedule(string t, string sd, string ed, vector<string> ca, string me, string rED, int cy, int k, int rptK);
	void print();
	//getter & setter
	string getTitle() { return title; };
	void setTitle(string t) { title = t; };
	string getStartDate() { return startDate; };
	void setStartDate(string date) { startDate = date; };
	string getEndDate() { return endDate; };
	void setEndDate(string date) { endDate = date; };
	vector<string> getCategory() { return category; };
	void setCategory(vector<string> cat) { category = cat; };
	string getMemo() { return memo; };
	void setMemo(string mm) { memo = mm; };
	int getKey() { return key; };
	void setKey(int k) { key = k; };
	int getCycle() { return cycle; };
	void setCycle(int c) { cycle = c; };
	string getRptEndDate() { return rptEndDate; };
	void setRptEndDate(string rd) { rptEndDate = rd; };
	int getRptK() { return rptK; }
	int setRptK(int _rptK) { rptK = _rptK; }

	bool operator < (Schedule& schedule) {
		return this->startDate < schedule.startDate;
	}
};

