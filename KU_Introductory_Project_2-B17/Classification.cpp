#include "Classification.h"


void Classification::Prompt_CategoryMenu()
{
	Sleep(100);
	system("cls"); // 화면 지우기

	cout << "카테고리 메뉴\n\n";

	cout << "1. 카테고리 추가\n";
	cout << "2. 카테고리 일정 보기\n";
	cout << "3. 카테고리 수정/삭제\n\n";

	cout << "원하는 번호를 입력하세요.\n";
	cout << "(취소를 원한다면 \"^C\"를 입력해주세요.)\n";
	cout << "-------------------------------------\n";
	cout << "> ";

	getline(cin, kwd); // 공백을 포함시키기 위해서 getline 을 사용했습니다.

	if (kwd == "^C") { // 취소
		return;
	}
	else {
		switch (kwd[0])
		{
		case '1':
			CategoryAdd(); // 일정 추가
			break;
		case '2':
			//test
			PrintSchedule_ByCategory(); // 일정 보기
			break;
		case '3':
			Prompt_PrintCategoryList_ForEditOrRemove(); // 수정/삭제
			break;
		default: // 오류 메세지
			system("cls"); // 화면 지우기

			cout << "오류 : 1, 2, 3 중 하나의 숫자를 입력해주세요.\n\n";
			cout << "아무 키나 눌러주세요.\n";
			cout << "-------------------------------------\n";
			cout << "> ";

			_getch(); // 아무 키나 입력 대기
			
			Prompt_CategoryMenu();
			break;
		}
	}
	

}

void Classification::CategoryAdd()
{
	Sleep(100);
	system("cls"); // 화면 지우기

	cout << "카테고리 추가" << endl << endl;
	cout << "새로 추가하길 원하는 카테고리명을 입력해주세요." << endl;
	cout << "(취소를 원한다면 \"^C\"를 입력해주세요.)\n";
	cout << "-------------------------------------\n";
	cout << "> ";

	getline(cin, kwd);

	if (kwd == "^C") {
		return;
	}
	else if (kwd.length() < 1 || kwd.length() > 30) {
		system("cls"); // 화면 지우기

		cout << "오류 : 해당 입력은 카테고리명으로 사용할 수 없습니다." << endl << endl;
		cout << "아무 키나 눌러주세요." << endl;
		cout << "-------------------------------------" << endl;
		cout << "> ";

		_getch();
		CategoryAdd();
	}
	else if (find(CDM->GetCategory()->begin(), CDM->GetCategory()->end(), kwd) != CDM->GetCategory()->end()) {	//벡터 내에 kwd가 존재하지 않을 경우
		system("cls"); // 화면 지우기

		cout << "오류 : 해당 카테고리명이 이미 존재합니다." << endl << endl;
		cout << "아무 키나 눌러주세요." << endl;
		cout << "-------------------------------------" << endl;
		cout << "> ";

		_getch();
		CategoryAdd();
	}
	else {
		Sleep(100);
		system("cls");

		CDM->CategoryAdd(kwd);

		cout << "카테고리 추가 완료" << endl << endl;

		cout << "아무 키나 눌러주세요.\n";
		cout << "-------------------------------------\n";
		cout << "> ";

		_getch(); // 아무 키나 입력 대기

		return;
	}



}

void Classification::PrintSchedule_ByCategory()
{
	Sleep(100);
	system("cls"); // 화면 지우기

	cout << "카테고리 일정 보기" << endl << endl;
	cout << "0. 기본" << endl;
	CDM->CategoryPrint();
	cout << "원하는 카테고리를 선택하세요." << endl;
	cout << "(취소를 원한다면 \"^C\"를 입력해주세요.)\n";
	cout << "-------------------------------------\n";
	cout << "> ";

	getline(cin, kwd);

	if (kwd == "^C") { // 취소
		Prompt_CategoryMenu();
	}

	else if (stoi(kwd) > CDM->GetSize() || stoi(kwd) < 0) { // 오류 메세지
		system("cls"); // 화면 지우기

		cout << "오류 : 해당 카테고리는 존재하지 않습니다.\n\n";
		cout << "아무 키나 눌러주세요.\n";
		cout << "-------------------------------------\n";
		cout << "> ";

		_getch(); // 아무 키나 입력 대기

		PrintSchedule_ByCategory();
	}
	else {
		Sleep(100);
		system("cls");

		string cateKwd;

		if (stoi(kwd) == 0) {
			cateKwd = "기본";
		}
		else {
			cateKwd = CDM->GetValue(stoi(kwd) - 1);
		}
		
		makeQueueForPrint(cateKwd);

		if (res.empty())
			cout << "\"" << cateKwd << "\" 카테고리를 포함하고 있는 일정이 없습니다." << endl << endl;
		else {
			cout << "카테고리 \"" << cateKwd << "\"에 해당되는 일정들입니다." << endl << endl;
			while (!res.empty()) {
				res.front().print();
				res.pop();
			}
		}
		
		cout << "아무 키나 눌러주세요.\n";
		cout << "-------------------------------------\n";
		cout << "> ";
		_getch(); // 아무 키나 입력 대기

		Prompt_CategoryMenu();
	}

}

void Classification::makeQueueForPrint(string str) {
	for (Schedule s : cal->allSchs) {
		if (s.getCategory().compare(str) == 0) {
			res.push(s);
		}
	}
}

void Classification::Prompt_CategoryEdit(int _cateNum)
{
	Sleep(100);
	system("cls"); // 화면 지우기

	cout << "이전 카테고리 명 : " << CDM->GetValue(_cateNum - 1) << "\n\n";

	cout << "새 카테고리명을 입력해주세요.\n";
	cout << "(취소를 원한다면 \"^C\"를 입력해주세요.)\n";
	cout << "-------------------------------------\n";
	cout << "> ";

	getline(cin, kwd); // 공백을 포함시키기 위해서 getline 을 사용했습니다.

	if (kwd == "^C") { // 취소
		Prompt_CategoryEditOrRemove(_cateNum);
	}
	else if (CDM->SyntaxCheck(kwd) == false) { // 문법 체크
		system("cls"); // 화면 지우기

		cout << "오류 : 해당 입력은 카테고리명으로 사용할 수 없습니다.\n\n";
		cout << "아무 키나 눌러주세요.\n";
		cout << "-------------------------------------\n";
		cout << "> ";

		_getch(); // 아무 키나 입력 대기

		Prompt_CategoryEdit(_cateNum);
	}
	else if (CDM->DuplicationCheck(kwd) == false) { // 중복 체크
		system("cls"); // 화면 지우기

		cout << "오류 : 해당 카테고리명이 이미 존재합니다.\n\n";
		cout << "아무 키나 눌러주세요.\n";
		cout << "-------------------------------------\n";
		cout << "> ";

		_getch(); // 아무 키나 입력 대기

		Prompt_CategoryEdit(_cateNum);
	}
	else {
		
		Sleep(100);	
		system("cls"); // 화면 지우기

		CDM->CategoryEdit(_cateNum - 1, kwd);


		cout << "카테고리 수정 완료\n\n";

		cout << "아무 키나 눌러주세요.\n";
		cout << "-------------------------------------\n";
		cout << "> ";

		_getch(); // 아무 키나 입력 대기

		return;
	}
}

void Classification::Prompt_CategoryRemove(int _cateNum)
{
	Sleep(100);
	system("cls"); // 화면 지우기

	CDM->CategoryRemove(_cateNum);

	cout << "카테고리 삭제 완료\n\n";

	cout << "아무 키나 눌러주세요.\n";
	cout << "-------------------------------------\n";
	cout << "> ";

	_getch(); // 아무 키나 입력 대기

	return;
}


void Classification::Prompt_PrintCategoryList_ForEditOrRemove()
{
	Sleep(100);
	system("cls"); // 화면 지우기

	cout << "카테고리 수정 삭제\n\n";

	cout << "0. 기본\n";
	CDM->CategoryPrint();

	cout << "\n수정 및 삭제하길 원하는 카테고리를 선택하세요.\n";
	cout << "(기본 카테고리는 수정 및 삭제 불가능)\n";
	cout << "(취소를 원한다면 \"^C\"를 입력해주세요.)\n";
	cout << "-------------------------------------\n";
	cout << "> ";

	getline(cin, kwd); // 공백을 포함시키기 위해서 getline 을 사용했습니다.


	if (kwd == "^C") { // 취소
		Prompt_CategoryMenu();
	}
	else if (stoi(kwd) > CDM->GetSize() || stoi(kwd) < 0) { // 오류 메세지
		system("cls"); // 화면 지우기

		cout << "오류 : 해당 카테고리는 존재하지 않습니다.\n\n";
		cout << "아무 키나 눌러주세요.\n";
		cout << "-------------------------------------\n";
		cout << "> ";

		_getch(); // 아무 키나 입력 대기

		Prompt_PrintCategoryList_ForEditOrRemove();
	}
	else {
		Prompt_CategoryEditOrRemove(stoi(kwd));
	}
}

void Classification::Prompt_CategoryEditOrRemove(int _cateNum)
{
	system("cls"); // 화면 지우기

	cout << "선택된 카테고리 : \"" << CDM->GetValue(_cateNum-1) << "\"\n\n";

	cout << "1. 수정하기\n";
	cout << "2. 삭제하기\n\n";

	cout << "원하는 번호를 선택하세요.\n";
	cout << "(취소를 원한다면 \"^C\"를 입력해주세요.)\n";
	cout << "-------------------------------------\n";
	cout << "> ";

	getline(cin, kwd); // 공백을 포함시키기 위해서 getline 을 사용했습니다.


	if (kwd == "^C") { // 취소
		Prompt_PrintCategoryList_ForEditOrRemove();
	}
	else {
		switch (kwd[0])
		{
		case '1':
			Prompt_CategoryEdit(_cateNum); // 일정 수정

			Prompt_CategoryMenu();
			break;
		case '2':
			//test
			Prompt_CategoryRemove(_cateNum); // 일정 삭제

			Prompt_CategoryMenu();
			break;
		default: // 오류 메세지
			system("cls"); // 화면 지우기

			cout << "오류 : 1, 2 중 하나의 숫자를 입력해주세요.\n\n";
			cout << "아무 키나 눌러주세요.\n";
			cout << "-------------------------------------\n";
			cout << "> ";

			_getch(); // 아무 키나 입력 대기

			Prompt_CategoryEditOrRemove(_cateNum);
			break;
		}
	}
}


