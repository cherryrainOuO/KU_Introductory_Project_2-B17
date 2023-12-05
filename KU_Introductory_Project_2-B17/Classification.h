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
	vector<Schedule> res; // 스케줄
	CategoryDataManager* CDM; // 카테고리 매니저
	vector<int> dupCheck; // 연산 조합 출력에서 중복 체크용 

	void CategoryAdd();
	void PrintSchedule_ByCategory();
	void Caculate_ByOperators();
	void makeQueueForPrint(string str);
	void makeQueueForPrint2(vector<string> cate, vector<string> block);

	void Prompt_CategoryEdit(int _cateNum);
	void Prompt_CategoryRemove(int _cateNum);
	void Prompt_PrintCategoryList_ForEditOrRemove();
	void Prompt_CategoryEditOrRemove(int _cateNum);
	void Prompt_after_or_before_When(vector<Schedule> res, string cateKwd);

	friend class Management;

	vector<string> split(string str, string delims);
	vector<string> split_by_space(string str, char del);

	struct Oper;
	class CategoryComponent;

public:
	/*constructor*/
	Classification() {};
	Classification(Calender* _caln, CategoryDataManager* _cateManager) { cal = _caln; CDM = _cateManager; };

	void Prompt_CategoryMenu();
};

