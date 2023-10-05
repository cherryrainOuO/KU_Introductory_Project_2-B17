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

		/* 카테고리 파일에도 업데이트 필요 */

		/* 스케줄에도 바뀐 카테고리 명으로 업데이트 필요 */

		/* 캘린더 파일에도 바뀐 카테고리 명으로 업데이트 필요 */

	//////////////////////////////////////////////////////////////
}

void CategoryDataManager::CategoryRemove(int _cateNum)
{
	cate->GetCategories()->erase(cate->GetCategories()->begin() + _cateNum - 1); // 삭제

	//////////////////////////////////////////////////////////////

		/* 카테고리 파일에도 업데이트 필요 */

		/* 스케줄에도 기존 카테고리 명 -> 기본 카테고리 명으로 업데이트 필요 */
		
		/* 캘린더 파일에도 기존 카테고리 명 -> 기본 카테고리 명으로 업데이트 필요 */

	//////////////////////////////////////////////////////////////
}

void CategoryDataManager::CategoryPrint()
{
	for (int i = 0; i < GetSize(); i++) {
		cout << i + 1 << ". " << GetValue(i) << "\n";
	}
}

bool CategoryDataManager::SyntaxCheck(string _str)
{
	//////////////////////////////////////////////////////////////

	/* 카테고리 문법 규칙 체크 : 통과하면 true 틀리면 false*/

	//////////////////////////////////////////////////////////////

	return false;
}

bool CategoryDataManager::DuplicationCheck(string _str)
{
	//////////////////////////////////////////////////////////////

	/* 카테고리 중복 체크 : 통과하면 true 틀리면 false*/

	//////////////////////////////////////////////////////////////

	return false;
}
