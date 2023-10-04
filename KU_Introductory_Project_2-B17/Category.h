#pragma once
#include "Calender.h"
#include "Schedule.h"
#include <windows.h>
#include <conio.h>
#include <regex>
#include <string>

class Category
{
private:
	vector<string> categories;

public:
	Category() {};
	void print() {};

	//getter & setter
	vector<string>* GetCategories() { return &categories; }
	void SetCategories(vector<string> _cate) { categories = _cate; }

};