#include "Classification.h"


void Classification::Prompt()
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

	string n;
	getline(cin, n); // 공백을 포함시키기 위해서 getline 을 사용했습니다.

	if (n == "^C") { // 취소
		return;
	}
	else {
		switch (n[0])
		{
		case '1':
			CategoryAdd(); // 일정 추가
			break;
		case '2':
			//test
			PrintSchedule_ByCategory(); // 일정 보기
			break;
		case '3':
			CategoryEditOrRemove_Prompt(); // 수정/삭제
			break;
		default: // 오류 메세지
			system("cls"); // 화면 지우기

			cout << "오류 : 1, 2, 3 중 하나의 숫자를 입력해주세요.\n\n";
			cout << "아무 키나 눌러주세요.\n";
			cout << "-------------------------------------\n";
			cout << "> ";

			_getch(); // 아무 키나 입력 대기
			
			return;
			
		}
	}
	

}

void Classification::CategoryAdd()
{
}

void Classification::PrintSchedule_ByCategory()
{
}

void Classification::CategoryEdit()
{
}

void Classification::CategoryRemove()
{
}

void Classification::CategoryEditOrRemove_Prompt()
{
	Sleep(100);
	system("cls"); // 화면 지우기

	cout << "카테고리 수정 삭제\n\n";

	cout << "0. 기본\n";
	while (1) {

	}

	cout << "수정 및 삭제하길 원하는 카테고리를 선택하세요.\n";
	cout << "(기본 카테고리는 수정 및 삭제 불가능)\n";
	cout << "(취소를 원한다면 \"^C\"를 입력해주세요.)\n";
	cout << "-------------------------------------\n";
	cout << "> ";

	string n;
	getline(cin, n); // 공백을 포함시키기 위해서 getline 을 사용했습니다.


	if (n == "^C") { // 취소
		return;
	}
	else {
		switch (n[0])
		{
		case '1':
			CategoryAdd(); // 일정 추가
			break;
		case '2':
			//test
			PrintSchedule_ByCategory(); // 일정 보기
			break;
		case '3':
			; // 수정/삭제
			break;
		default: // 오류 메세지
			system("cls"); // 화면 지우기

			cout << "오류 : 1, 2, 3 중 하나의 숫자를 입력해주세요.\n\n";
			cout << "아무 키나 눌러주세요.\n";
			cout << "-------------------------------------\n";
			cout << "> ";

			_getch(); // 아무 키나 입력 대기

			Prompt();
			break;
		}
	}
}

