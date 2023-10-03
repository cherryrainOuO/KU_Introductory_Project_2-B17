#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;

void MainPrompt();
void ClassificationPrompt();
void SearchPrompt();
void MangementPrompt();
void ExitPrompt();

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
	getline(cin, n); // 공백을 포함시키기 위해서 getline 을 사용했습니다.

	switch (n[0])
	{
	case '1':
		ClassificationPrompt(); // 일정 분류
		break;
	case '2':
		SearchPrompt(); // 검색
		break;
	case '3':
		MangementPrompt(); // 일정 관리
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

void MangementPrompt() {
	system("cls");
}

void ExitPrompt() {
	system("cls");
	cout << "캘린더 앱을 종료합니다.\n";
	exit(0);
}

