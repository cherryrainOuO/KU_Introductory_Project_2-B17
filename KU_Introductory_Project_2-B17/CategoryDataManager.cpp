#include "CategoryDataManager.h"

bool CategoryDataManager::loadDataFile(Category& _cate)
{
	string fileName = "Calendar-category.txt";
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
			cout << "오류: 데이터 파일 생성을 실패하였습니다. 프로그램을 종료합니다.\n\n";
			cout << "아무 키나 눌러주세요.\n";
			cout << "-------------------------------------\n";
			cout << "> ";

			_getch(); // 아무 키나 입력 대기

			exit(0);

			return false; //false가 리턴되면 프로그램이 종료되도록
		}
		else {
			fout.close();
			cout << "파일 생성 성공\n";
			Sleep(1000);

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
			//cout << temptkn << "\n";

			if (!temptkn.empty()) {
				if (SyntaxCheck(temptkn) == false) {
					cout << "오류 : 데이터 파일의 형식이 잘못되었습니다.\n";
					cout << "-------------------------------------\n";
					cout << ws2s(line) << "\n";
					cout << "-------------------------------------\n";

					cout << "프로그램을 종료합니다.\n";

					exit(0);

					return false;
				}
				else if (find(record.begin(), record.end(), temptkn) != record.end() || temptkn.compare("기본") == 0) { // 중복 체크
					cout << "오류 : 데이터 파일의 형식이 잘못되었습니다.\n";
					cout << "-------------------------------------\n";
					cout << ws2s(line) << "\n";
					cout << "-------------------------------------\n";

					cout << "프로그램을 종료합니다.\n";

					exit(0);

					return false;

				}
					
				record.push_back(temptkn); //연속된 tab 무시
			}

		}

	}

	_cate.SetCategories(record);
	record.clear();

	file.close();
	//cout << "데이터 로드 성공\n";
	return true;

}

bool CategoryDataManager::SaveDataFile()
{

	//////////////////////////////////////////////////////////////

		/* 세이브해서 파일로 옮겨 주세요~ */

	//////////////////////////////////////////////////////////////

	try {
		string fileName = "Calendar-category.txt";
		wofstream file;

		file.open(fileName, ios::out);
		file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));

		if (file.fail()) {
			cout << "파일 저장에 실패했습니다." << endl;
			return false;
		}
		else {
			for (int i = 0; i < GetSize(); i++) {
				wstring c = s2ws(GetValue(i));
				file << L"\t" << c;	//\t으로 구분
			}
		}

		file.close();

	}
	catch (exception e) {
		cout << "Save Data File" << endl;
		e.what();
	}

	return true;
}

wstring CategoryDataManager::s2ws(const string& str)
{
	static std::locale loc("");
	auto& facet = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);
	return std::wstring_convert<std::remove_reference<decltype(facet)>::type, wchar_t>(&facet).from_bytes(str);
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

bool CategoryDataManager::UpdateCategoryToCalender(int _cateNum, string _newStr)
{

	//////////////////////////////////////////////////////////////

		/* 캘린더의 스케줄들의 카테고리에도 바뀐내용 업데이트 해주세요 ~ ~ */


		/* 캘린더 파일에도 바뀐 카테고리 명으로 업데이트 필요 */
	// 캘린더 :: 세이브 데이터 파일?

	// SDM.SaveDataFile() 을 여기서 호출하면 되지 않을까요?? 

	//////////////////////////////////////////////////////////////

	string oldCate = GetValue(_cateNum);


	for (int i = 0; i < cale->allSchs.size(); i++) {
		if (cale->allSchs.at(i).getCategory().compare(oldCate) == 0) {
			cale->allSchs.at(i).setCategory(_newStr);
			//cale->allSchs.at(i).print();
		}
	}
	SDM.saveDataFile(*cale);

	return true;
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
	UpdateCategoryToCalender(_cateNum, _newStr); // 수정
	cate->GetCategories()->at(_cateNum) = _newStr;

	SaveDataFile();
}

void CategoryDataManager::CategoryRemove(int _cateNum)
{



	//////////////////////////////////////////////////////////////

		
	//	/* 스케줄에도 바뀐 카테고리 명으로 업데이트 필요 */
	UpdateCategoryToCalender(_cateNum - 1, "기본");
	cate->GetCategories()->erase(cate->GetCategories()->begin() + _cateNum - 1); // 삭제

	/* 카테고리 파일에도 업데이트 필요 */
	SaveDataFile();
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
	wregex wrx(L"([ㄱ-ㅣ가-힣a-zA-Z0-9 ]{1,30})");
	wsmatch wideMatch;
	wstring wstr = SDM.s2ws(_str);
	if (regex_match(wstr.cbegin(), wstr.cend(), wideMatch, wrx) &&
		_str[0] != ' ' && _str.back() != ' ') {
		return true;
	}
	else {
		return false;
	}
}

bool CategoryDataManager::DuplicationCheck(string _str)
{
	if (_str == "기본") { return false; }

	return !(find(cate->GetCategories()->begin(), cate->GetCategories()->end(), _str) != cate->GetCategories()->end());
}
