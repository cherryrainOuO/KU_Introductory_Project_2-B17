#pragma once
#include <fstream>
#include <sstream>
#include "Calender.h"
#include "Category.h"

class CategoryDataManager
{
public:
	CategoryDataManager(Category* _cate) { cate = _cate; }
	bool loadDataFile();

	void CategoryAdd(string _str);
	void CategoryEdit(int _cateNum, string _newStr);
	void CategoryRemove(int _cateNum);

	void CategoryPrint();

	int GetSize() { return cate->GetCategories()->size(); }
	string GetValue(int _index) { return cate->GetCategories()->at(_index); }
private:
	Category* cate;
};

