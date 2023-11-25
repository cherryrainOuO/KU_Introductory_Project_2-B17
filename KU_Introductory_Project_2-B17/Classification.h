#pragma once
#include "Calender.h"
#include "Schedule.h"
#include "Category.h"
#include "CategoryDataManager.h"
#include <windows.h>
#include <conio.h>
#include <regex>
#include <string>
#include <queue>
#include <sstream>

class Classification
{
private:
	Calender* cal;
	string kwd; // 키보드 입력 용
	queue<Schedule> res; // 스케줄
	CategoryDataManager* CDM; // 카테고리 매니저

	void CategoryAdd();
	void PrintSchedule_ByCategory();
	void Caculate_ByOperators();
	void makeQueueForPrint(string str);
	void makeQueueForPrint(vector<string> cate, vector<string> block);

	void Prompt_CategoryEdit(int _cateNum);
	void Prompt_CategoryRemove(int _cateNum);
	void Prompt_PrintCategoryList_ForEditOrRemove();
	void Prompt_CategoryEditOrRemove(int _cateNum);
	void Prompt_after_or_before_When(queue<Schedule> res, string cateKwd);

	friend class Management;

public:
	/*constructor*/
	Classification() {};
	Classification(Calender* _caln, CategoryDataManager* _cateManager) { cal = _caln; CDM = _cateManager; };

	void Prompt_CategoryMenu();
};

