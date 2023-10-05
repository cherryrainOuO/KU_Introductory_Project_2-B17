#include "CategoryDataManager.h"

bool CategoryDataManager::loadDataFile()
{
	return false;
}

void CategoryDataManager::CategoryAdd(string _str)
{
	cate->GetCategories()->push_back(_str);
	//////////////////////////////////////////////////////////////

		/* 파일에도 업데이트 필요 */

	//////////////////////////////////////////////////////////////
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
	regex re("[\\^\\n\\t]");

	if (_str.empty() || // 비어 있거나
		_str.find_first_not_of(' ') == string::npos ||  // 공백으로 시작하지 않고
		regex_search(_str, re) || // ^ \n \t 안들어 있고
		!(_str.size() >= 1 && _str.size() <= 30)) // 길이 1 이상 30 이하여야 한다.
	{
		return false;
	}
	else {
		return true;
	}
}

bool CategoryDataManager::DuplicationCheck(string _str)
{
	if (find(cate->GetCategories()->begin(), cate->GetCategories()->end(), _str) != cate->GetCategories()->end()) {
		return false;
	}
	else {
		return true;
	}
}
