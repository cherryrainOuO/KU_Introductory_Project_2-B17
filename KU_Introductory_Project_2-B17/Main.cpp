#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include "KeywordSearch.h"

#include "Classification.h"
#include "Calender.h"
using namespace std;

void MainPrompt();
void ClassificationPrompt();
void SearchPrompt();
void ManagementPrompt();
void ExitPrompt();

Calender calender;
KeywordSearch ks(&calender); //test
Classification classification;

int main() {

	// 임의 데이터 (나중에 지울거임)
	Schedule s1 = Schedule("s1", "2023/04/28", "2023/05/02","c1", "m1");
	Schedule s2 = Schedule("s2", "2023/04/29", "2023/04/29", "c2", "m2");
	Schedule s3 = Schedule("s3", "2023/04/29", "2023/04/29", "c3", "m3");
	Schedule s4 = Schedule("s4", "2023/04/30", "2023/05/06", "c4", "m4");
	Schedule s5 = Schedule("s5", "2023/04/30", "2023/04/30", "c5", "m5");

	calender.allSchs.push_back(s1);
	calender.allSchs.push_back(s2);
	calender.allSchs.push_back(s3);
	calender.allSchs.push_back(s4);
	calender.allSchs.push_back(s5);

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
	cout << "> ";

	string n;
	getline(cin, n); // 공백을 포함시키기 위해서 getline 을 사용했습니다.

	switch (n[0])
	{
	case '1':
		classification.Prompt(); // 일정 분류
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
		cout << "> ";
		
		_getch(); // 아무 키나 입력 대기

		break;
	}

}

/*
void ClassificationPrompt() {
	system("cls");
}

void SearchPrompt() {
	system("cls");
}
*/

void ManagementPrompt() {
	system("cls");
	string dateinfo; // yyyy/mm/dd
	string y, m, d; // 각각 year, month, date
	bool b = false; // dateinfo가 입력 형식에 맞는지 확인하기 위한 변수

	cout << "날짜 입력\n\n";

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
					if (stoi(y) % 4) {
						if (stoi(d) <= 28)
							b = true;
					}
					else {
						if (stoi(d) <= 29)
							b = true;
					}
					break;
				}
			}
		}
		if(!b) {
			system("cls");
			cout << "오류: 날짜를 형식에 맞게 입력해주세요.\n\n";

			cout << "아무 키나 눌러주세요.\n";
			cout << "_____________________________\n";
			cout << "> ";
			_getch();
		}
		else {
			system("cls");
			string sd, ed;  // startDate, endDate
			vector<Schedule> sche; // 현재 날짜에 해당하는 스케줄
			
			for (int i = 0; i < calender.allSchs.size(); i++) {			
				sd = calender.allSchs[i].getStartDate();
				ed = calender.allSchs[i].getEndDate();
				
				if (dateinfo >= sd && dateinfo <= ed) 
					sche.push_back(calender.allSchs[i]);
			}
			if (sche.size() > 0) {
				cout << "<" << dateinfo << "의 일정>\n\n";
				
				// 사용자가 입력한 날짜의 일정 목록
				for (int i = 0; i < sche.size(); i++)
					sche[i].print();

				cout << "1. 일정 추가\n";
				cout << "2. 일정 수정/삭제\n\n";

				cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
				cout << "원하는 메뉴를 입력하세요.\n";
				cout << "------------------------------\n";
				cout << "> ";
				_getch();
			}

			else { // 날짜에 해당하는 스케줄이 존재하지 않음
				cout << "<(사용자가 입력한 날짜)의 일정>\n\n";
				cout << "일정이 없습니다.일정을 추가하세요.\n\n";
				cout << "1. 일정 추가\n\n";
				cout << "(^ C 입력 시 이전 화면으로 돌아갑니다)\n\n";
				cout << "원하는 메뉴를 입력하세요\n";
				cout << "-------------------------------\n";
				cout << "> ";
				_getch();
			}
		}
	}
}

void ExitPrompt() {
	system("cls");
	cout << "캘린더 앱을 종료합니다.\n";
	exit(0);
}

