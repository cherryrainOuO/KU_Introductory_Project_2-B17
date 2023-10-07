#include "CategoryDataManager.h"

bool CategoryDataManager::loadDataFile(Category& _cate)
{
	string fileName = "testCate.txt";
	wifstream file;

	//setting locale handling UTF-8
	file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));
	wcout.imbue(locale(""));

	file.open(fileName);

	if (!file) {
		//파일이 존재하지 않음
		cout << "경고: 데이터 파일이 존재하지 않습니다. 빈 데이터 파일을 생성합니다.\n";
		ofstream fout;
		fout.open(fileName);
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
	wstring line;
	while (getline(file, line)) {

		wstringstream ss(line);

		//wcout << line << " "; //OK
		//wcout << ss.str() << " "; //OK
		wstring token;
		while (getline(ss, token, L'\t')) {
			//wcout << token;
			string temptkn;
			temptkn = ws2s(token);
			trim(temptkn); // tkn의 앞 뒤 공백 제거
			cout << temptkn << "\n";

			//////////////////////////////////////////////////////////////
			// 
			//! 왜 ' ' 은 인식을 못할까요? ㅎㅎ
			//! 
			//////////////////////////////////////////////////////////////

			if (!temptkn.empty()) {
				if (SyntaxCheck(temptkn) == false) {
					cout << "오류 : 데이터 파일의 형식이 잘못되었습니다. 프로그램을 종료합니다.\n";

					return false;
				}
				record.push_back(temptkn); //연속된 tab 무시
			}

		}
		
	}

	_cate.SetCategories(record);
	record.clear();

	file.close();
	cout << "데이터 로드 성공\n";
	return true;

}

bool CategoryDataManager::SaveDataFile()
{

	//////////////////////////////////////////////////////////////

		/* 세이브해서 파일로 옮겨 주세요~ */

	//////////////////////////////////////////////////////////////

	string fileName = "testCate.txt";
	ofstream file(fileName);

	if (file.fail()) {
		cout << "Error" << endl;
		return false;
	}
	else {
		for (int i = 0; i < GetSize(); i++) {
			//file << GetValue(i) << endl;	//개행으로 구분
			file << GetValue(i) << "\t";	//\t으로 구분
		}
	}

	return true;
}

string CategoryDataManager::ws2s(const std::wstring& wstr) {
	static std::locale loc("");
	auto& facet = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);
	return std::wstring_convert<std::remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(wstr);
}

void CategoryDataManager::trim(string& str) {
	int npos;
	//left
	npos = str.find_first_not_of(' ');
	str.erase(0, npos);
	//right
	npos = str.find_last_not_of(' ');
	str.erase(npos + 1);
}

bool CategoryDataManager::UpdateCategoryToCalender()
{

	//////////////////////////////////////////////////////////////

		/* 캘린더의 스케줄들의 카테고리에도 바뀐내용 업데이트 해주세요 ~ ~ */

	
		/* 캘린더 파일에도 바뀐 카테고리 명으로 업데이트 필요 */
	// 캘린더 :: 세이브 데이터 파일?

	// SDM.SaveDataFile() 을 여기서 호출하면 되지 않을까요?? 

	//////////////////////////////////////////////////////////////

	return false;
}

void CategoryDataManager::CategoryAdd(string _str)
{
	cate->GetCategories()->push_back(_str);

	//////////////////////////////////////////////////////////////

		/* 파일에도 업데이트 필요 */
	SaveDataFile();

	//////////////////////////////////////////////////////////////
}

void CategoryDataManager::CategoryEdit(int _cateNum, string _newStr)
{
	cate->GetCategories()->at(_cateNum) = _newStr; // 수정


	//////////////////////////////////////////////////////////////

		/* 카테고리 파일에도 업데이트 필요 */
	SaveDataFile();

		/* 스케줄에도 바뀐 카테고리 명으로 업데이트 필요 */
	UpdateCategoryToCalender();

		/* 캘린더 파일에도 바뀐 카테고리 명으로 업데이트 필요 */
	// 캘린더 :: 세이브 데이터 파일?

	//////////////////////////////////////////////////////////////
}

void CategoryDataManager::CategoryRemove(int _cateNum)
{
	cate->GetCategories()->erase(cate->GetCategories()->begin() + _cateNum - 1); // 삭제

	//////////////////////////////////////////////////////////////

		/* 카테고리 파일에도 업데이트 필요 */
	SaveDataFile();

		/* 스케줄에도 바뀐 카테고리 명으로 업데이트 필요 */
	UpdateCategoryToCalender();


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
