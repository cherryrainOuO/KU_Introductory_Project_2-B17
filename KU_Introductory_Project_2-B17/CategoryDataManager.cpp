#include "CategoryDataManager.h"

bool CategoryDataManager::loadDataFile()
{
	return false;
}

void CategoryDataManager::CategoryAdd(string _str)
{
}

void CategoryDataManager::CategoryEdit(int _cateNum, string _newStr)
{
	cate->GetCategories()->at(_cateNum) = _newStr; // 수정


	//////////////////////////////////////////////////////////////

		/* 파일에도 업데이트 필요 */

	//////////////////////////////////////////////////////////////
}

void CategoryDataManager::CategoryRemove(int _cateNum)
{
	cate->GetCategories()->erase(cate->GetCategories()->begin() + _cateNum - 1); // 삭제

	//////////////////////////////////////////////////////////////

		/* 파일에도 업데이트 필요 */

	//////////////////////////////////////////////////////////////
}

void CategoryDataManager::CategoryPrint()
{
	for (int i = 0; i < GetSize(); i++) {
		cout << i + 1 << ". " << GetValue(i) << "\n";
	}
}
