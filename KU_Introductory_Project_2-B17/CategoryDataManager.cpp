#include "CategoryDataManager.h"

bool CategoryDataManager::loadDataFile(Category& _cate)
{
	//파일 경로 사용자 지정?
	string filePath;
	string fileName = "testCate.txt";
	ifstream file;
	file.open(fileName, ios::in | ios::binary);
	if (!file) {
		//파일이 존재하지 않음
		cout << "경고: 데이터 파일이 존재하지 않습니다. 빈 데이터 파일을 생성합니다.\n";
		ofstream fout;
		fout.open(fileName, ios::out | ios::binary);
		if (!fout.is_open()) {
			cout << "오류: 데이터 파일 생성을 실패하였습니다. 프로그램을 종료합니다.\n";
			return false; //false가 리턴되면 프로그램이 종료되도록
		}
		else {
			fout.close();
			return true;
		}
	}

	//파일이 존재하는 경우
	vector<string> record;
	string line;
	int idx = 0;
	while (getline(file, line)) {
		cout << line << "\n";

		if (SyntaxCheck(line) == false) { 
			//////////////////////////////////////////////////////////////
			//! 왜 \t \n ' ' 은 인식을 못할까요? ㅎㅎ
			//! 
			//! 
			//////////////////////////////////////////////////////////////
			cout << "오류 : 데이터 파일의 형식이 잘못되었습니다. 프로그램을 종료합니다.\n";

			return false;
		}
		
		record.push_back(line);
	}
	_cate.SetCategories(record);

	file.close();
	cout << "데이터 로드 성공";
	return true;
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
