#include "Management.h"

void Management::Prompt(){
	system("cls");

	cout << "날짜 입력\n\n";

	cout << "입력 형식 : yyyy/mm/dd\n";
	cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";

	cout << "원하는 날짜를 입력하세요.\n";
	cout << "------------------------------------\n";
	cout << "> ";

	//! cin >> dateinfo;
	getline(cin, dateinfo); // cin 말고 getline을 사용.
	if (dateinfo == "^C") // 취소 명령어
		return;
	else {
		if (!isValidDate()) {
			system("cls");
			cout << "오류: 날짜를 형식에 맞게 입력해주세요.\n\n";

			cout << "아무 키나 눌러주세요.\n";
			cout << "_____________________________\n";
			cout << "> ";
			_getch();
			return;
		}
		else {
			system("cls");
			printSchedule();
		}
	}
}
bool Management::isValidDate() {

	string y, m, d; // 각각 year, month, date{
	if (dateinfo.length() == 10 && dateinfo[4] == '/' && dateinfo[7] == '/') {
		y = dateinfo.substr(0, 4);
		m = dateinfo.substr(5, 2);
		d = dateinfo.substr(8, 2);

		if (stoi(y) >= 2000 && stoi(y) <= 2030
			&& stoi(m) >= 1 && stoi(m) <= 12 && stoi(d) >= 1) {

			switch (stoi(m)) {

			case 1: case 3: case 5: case 7: case 8: case 10: case 12:
				if (stoi(d) <= 31)
					return true;

			case 4: case 6: case 9: case 11:
				if (stoi(d) <= 30)
					return true;

			case 2:
				if (stoi(y) % 4) {
					if (stoi(d) <= 28)
						return true;
				}
				else {
					if (stoi(d) <= 29)
						return true;
				}
			}
		}
	}
	return false;
}

void Management::printSchedule(){
	string sd, ed;  // startDate, endDate
	vector<Schedule> sche; // 현재 날짜에 해당하는 스케줄
	
	for (int i = 0; i < cal->allSchs.size(); i++) {

		sd = cal->allSchs[i].getStartDate();
		ed = cal->allSchs[i].getEndDate();

		if (dateinfo >= sd && dateinfo <= ed)
			sche.push_back(cal->allSchs[i]);
	}

	string m; // 메뉴 선택 (일정 추가, 일정 수정/삭제)
	// 선택한 날짜의 일정이 1개 이상인 경우
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
		getline(cin, m);
		system("cls");
		if (m == "^C")
			return;
		else if (m[0] == '1')
			addSchedule();
		else if (m[0] == '2')
			modifySchedule();
		else {
			cout << "오류: 1,2 중 하나의 숫자를 입력해주세요.\n";
			if (_getch()) {
				system("cls");
				printSchedule();
			}
		}

	}
	// 선택한 날짜의 일정이 0개인 경우
	else {
		cout << "<(사용자가 입력한 날짜)의 일정>\n\n";
		cout << "일정이 없습니다.일정을 추가하세요.\n\n";
		cout << "1. 일정 추가\n\n";
		cout << "(^ C 입력 시 이전 화면으로 돌아갑니다)\n\n";
		cout << "원하는 메뉴를 입력하세요\n";
		cout << "-------------------------------\n";
		cout << "> ";
		getline(cin, m);
		system("cls");
		if (m == "^C")
			return;
		else if (m[0] == '1')
			addSchedule();
		else {
			cout << "오류: 1을 입력해주세요.\n";
			if (_getch()) {
				system("cls");
				printSchedule();
			}
		}
	}
}

void Management::addSchedule()
{
}

void Management::modifySchedule()
{
}
