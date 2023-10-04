#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include "KeywordSearch.h"

using namespace std;

void MainPrompt();
void ClassificationPrompt();
void SearchPrompt();
void ManagementPrompt();
void ExitPrompt();

KeywordSearch ks; //test

int main() {
	
	while (true) {

		MainPrompt();
	}

	return 0;
}

void MainPrompt() {
	Sleep(100); 
	system("cls"); // 화면 지우기

	cout << "캘린더 홈\n\n";

	cout << "1. 일정 분류\n";
	cout << "2. 검색\n";
	cout << "3. 일정 관리\n";
	cout << "4. 종료\n\n";

	cout << "원하는 번호를 입력하세요.\n";
	cout << "-------------------------------------\n";
	cout << ">";

	string n;
	//getline(cin, n); // 공백을 포함시키기 위해서 getline 을 사용했습니다.
	cin >> n;

	switch (n[0])
	{
	case '1':
		ClassificationPrompt(); // 일정 분류
		break;
	case '2':
		//test
		ks.prompt(); // 검색
		break;
	case '3':
		ManagementPrompt(); // 일정 관리
		break;
	case '4':
		ExitPrompt(); // 종료
		break;
	default: // 오류 메세지
		system("cls"); // 화면 지우기

		cout << "오류 : 1, 2, 3, 4 중 하나의 숫자를 입력해주세요.\n\n";
		cout << "아무 키나 눌러주세요.\n";
		cout << "-------------------------------------\n";
		cout << ">";
		
		_getch(); // 아무 키나 입력 대기

		break;
	}

}

void ClassificationPrompt() {
	system("cls");
}

void SearchPrompt() {
	system("cls");
}

void ManagementPrompt() {
	system("cls");
	string dateinfo; // yyyy/mm/dd
	string y, m, d; // 각각 year, month, date
	bool b = false; // dateinfo가 입력 형식에 맞는지 확인하기 위한 변수

	cout << "\n\n날짜 입력\n\n";

	cout << "입력 형식 : yyyy/mm/dd\n";
	cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";

	cout << "원하는 날짜를 입력하세요.\n";
	cout << "------------------------------------\n";
	cout << "> ";

	//! cin >> dateinfo;
	getline(cin, dateinfo); // cin 말고 getline을 사용.

	if (dateinfo == "^C") // 취소 명령어
		MainPrompt();
	else {
		if (dateinfo.length() == 10 && dateinfo[4] == '/' && dateinfo[7] == '/'){ 
			y = dateinfo.substr(0, 4);
			m = dateinfo.substr(5, 2);
			d = dateinfo.substr(8, 2);
			if (stoi(y) >= 2000 && stoi(y) <= 2030
				&& stoi(m)>=1&& stoi(m)<=12&&stoi(d)>=1) {
				switch (stoi(m)) {
				case 1: case 3: case 5: case 7: case 8: case 10: case 12:
					if (stoi(d) <= 31)
						b = true;
					break;
				case 4: case 6: case 9: case 11: 
					if (stoi(d) <= 30)
						b = true;
					break;
				case 2:
					if (stoi(d) <= 28)
						b = true;
					break;
				}
			}
		}
		if(!b) {
			system("cls");
			cout << "\n오류: 날짜를 형식에 맞게 입력해주세요.\n\n";

			cout << "아무 키나 눌러주세요.\n";
			cout << "_____________________________\n";
			cout << "> ";
			_getch();
		}
		else {
			system("cls");
			/******/
			_getch();
		}
	}
}

void ExitPrompt() {
	system("cls");
	cout << "캘린더 앱을 종료합니다.\n";
	exit(0);
}

