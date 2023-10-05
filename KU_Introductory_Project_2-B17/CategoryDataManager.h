#pragma once
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>
#include <regex>
#include <Windows.h>
#include <atlconv.h>
#include "Calender.h"
#include "Category.h"

class CategoryDataManager
{
public:
	CategoryDataManager(Category* _cate, Calender* _cale) { cate = _cate; cale = _cale; }
	bool loadDataFile(Category& _cate);
	bool SaveDataFile(); ///////////////////////////////////////////////////////////////////////////// 구현 필요!
	string ws2s(const std::wstring& wstr);
	void trim(string& str);

	bool UpdateCategoryToCalender(); ///////////////////////////////////////////////////////////////// 구현 필요!

	void CategoryAdd(string _str);
	void CategoryEdit(int _cateNum, string _newStr);
	void CategoryRemove(int _cateNum);

	void CategoryPrint();

	vector<string>* GetCategory() { return cate->GetCategories(); }
	int GetSize() { return cate->GetCategories()->size(); }
	string GetValue(int _index) { return cate->GetCategories()->at(_index); }

	bool SyntaxCheck(string _str);
	bool DuplicationCheck(string _str);

private:
	Category* cate;
	Calender* cale;

};

