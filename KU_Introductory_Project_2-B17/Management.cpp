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
	if (dateinfo == "^C") {	// 취소 명령어
		system("cls");
		return;
	}
	else {
		if (isValidDate() < 0) {
			Sleep(1000);
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
int Management::isValidDate() {

	string y, m, d; // 각각 year, month, date{
	regex re("[0-9]{4}/[0-9]{2}/[0-9]{2}");	// 날짜 문법 형식


	// 문법 형식에 맞지 않을 때 -1 반환
	if (regex_match(dateinfo, re)) {
		y = dateinfo.substr(0, 4);
		m = dateinfo.substr(5, 2);
		d = dateinfo.substr(8, 2);

		// 의미 규칙에 맞지 않을 때 -2 반환
		if (stoi(y) >= 2000 && stoi(y) <= 2030
			&& stoi(m) >= 1 && stoi(m) <= 12 && stoi(d) >= 1) {

			// 유효한 날짜일 때 0 반환
			switch (stoi(m)) {

			case 1: case 3: case 5: case 7: case 8: case 10: case 12:
				if (stoi(d) <= 31)
					return 0;

			case 4: case 6: case 9: case 11:
				if (stoi(d) <= 30)
					return 0;

			case 2:
				if (stoi(y) % 4) {
					if (stoi(d) <= 28)
						return 0;
				}
				else {
					if (stoi(d) <= 29)
						return 0;
				}
			}
		}
		else {
			return -2;
		}
	}
	return -1;
}

void Management::printSchedule(){
	string sd, ed;  // startDate, endDate
	vector<Schedule> sche; // 현재 날짜에 해당하는 스케줄
	
	// 현재 날짜의 스케줄을 캘린더에서 하나씩 추가
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
		if (m == "^C") {
			system("cls");
			Prompt();
		}
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
		cout << "<" << dateinfo << "의 일정>\n\n";
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
	string startDate, endDate, title, category, memo;
	string y, m, d;
	
	int flag = 0;	// 부 프롬프트 간 이동을 위한 변수
	while (flag < 5) {
		system("cls");
		switch (flag) {
		case 0:
			cout << "<일정 추가(1/5)>\n\n";
			cout << "시작일 입력\n\n";
			cout << "시작일 입력 형식 : yyyy/mm/dd\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "추가할 일정의 시작일을 입력하세요.\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, startDate);
			if (startDate == "^C") {
				system("cls");
				printSchedule();
			}
			else {
				switch (isValidDate()) {
				case 0:
					flag = 1;
					break;
				case -1:
					system("cls");
					cout << "오류: 시작일의 날짜를 형식에 맞게 입력해주세요.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
					break;
				case -2:
					system("cls");
					cout << "오류: " << dateinfo << "(은)는 존재하지 않는 날짜입니다.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
					break;
				}
			}
			break;
		case 1:
			cout << "<일정 추가(2/5)>\n\n";
			cout << "종료일 입력\n\n";
			cout << "종료일 입력 형식 : yyyy/mm/dd\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "추가할 일정의 종료일을 입력하세요.\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, endDate);
			if (endDate == "^C") {
				flag = 0;
			}
			else {
				switch (isValidDate()) {
				case 0:
					// 시작일보다 종료일이 빠른 경우 
					int y1, m1, d1, y2, m2, d2;
					y1 = stoi(startDate.substr(0, 4));
					m1 = stoi(startDate.substr(5, 2));
					d1 = stoi(startDate.substr(8, 2));
					y2 = stoi(endDate.substr(0, 4));
					m2 = stoi(endDate.substr(5, 2));
					d2 = stoi(endDate.substr(8, 2));

					if ((y1 > y2) || ((y1 == y2) && (m1 > m2))
						|| ((y1 == y2) && (m1 == m2) && (d1 > d2))) {
						system("cls");
						cout << "오류: 종료일은 시작일과 같거나, 그 이후여야 합니다.\n\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						_getch();
					}
					else {
						flag = 2;
					}
					break;
				case -1:
					system("cls");
					cout << "오류: 종료일의 날짜를 형식에 맞게 입력해주세요.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
					break;
				case -2:
					system("cls");
					cout << "오류: " << dateinfo << "(은)는 존재하지 않는 날짜입니다.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
					break;
				}
			}
			break;
		case 2:
			cout << "<일정 추가(3/5)>\n\n";
			cout << "제목 입력\n\n";
			cout << "(제목 입력 형식 설명)\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "추가할 일정의 제목을 입력하세요.\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, title);
			if (title == "^C") {
				flag = 1;
			}
			else {
				// ## 정규 표현식 수정해야 함
				regex re("[ㄱ-ㅣ가-힣a-zA-Z0-9]");
				if (regex_match(title, re)) {
					flag = 3;
				}
				else {
					system("cls");
					cout << "오류: 제목을 형식에 맞게 입력해주세요.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
				}
			}
			break;
		case 3:
			// ## 카테고리 진행 이후
			flag = 4;
			break;
		case 4:
			cout << "<일정 추가(5/5)>\n\n";
			cout << "메모 입력\n\n";
			cout << "(메모 입력 형식 설명)\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "추가할 일정의 메모를 입력하세요.\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, memo);
			if (memo == "^C") {
				flag = 3;
			}
			else {
				// ## 정규 표현식 수정해야 함
				regex re("[ㄱ-ㅣ가-힣a-zA-Z0-9]");
				if (regex_match(title, re)) {
					flag = 5;
				}
				else {
					system("cls");
					cout << "오류: 메모를 형식에 맞게 입력해주세요.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
				}
			}
			break;
		}
	}
	Schedule* newDate = new Schedule(title, startDate, endDate, category, memo);
	// ## 데이터 파일에 해당 스케줄 추가
	system("cls");
	printSchedule();
}

void Management::modifySchedule()
{
}
