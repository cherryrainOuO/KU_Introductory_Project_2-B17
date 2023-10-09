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
		if (isValidDate(dateinfo) < 0) {
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
int Management::isValidDate(string dateStr) {

	string y, m, d; // 각각 year, month, date{
	regex re("[0-9]{4}/[0-9]{2}/[0-9]{2}");	// 날짜 문법 형식


	// 문법 형식에 맞지 않을 때 -1 반환
	if (regex_match(dateStr, re)) {
		y = dateStr.substr(0, 4);
		m = dateStr.substr(5, 2);
		d = dateStr.substr(8, 2);

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

bool Management::is_digit(string str) {
	return atoi(str.c_str()) != 0 || str.compare("0") == 0;
}

void Management::printSchedule(){
	string sd, ed;  // startDate, endDate
	vector<Schedule*> sche; // 현재 날짜에 해당하는 스케줄
	
	// 현재 날짜의 스케줄을 캘린더에서 하나씩 추가
	for (int i = 0; i < cal->allSchs.size(); i++) {

		sd = cal->allSchs[i].getStartDate();
		ed = cal->allSchs[i].getEndDate();

		if (dateinfo >= sd && dateinfo <= ed)
			sche.push_back(&(cal->allSchs[i]));
	}

	string m; // 메뉴 선택 (일정 추가, 일정 수정/삭제)
	// 선택한 날짜의 일정이 1개 이상인 경우
	if (sche.size() > 0) {
		cout << "<" << dateinfo << "의 일정>\n\n";

		// 사용자가 입력한 날짜의 일정 목록
		for (int i = 0; i < sche.size(); i++)
			sche[i]->print();

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
			mod_or_delSchedule();
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
	int cateCount = 0;
	string menu;
	
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
				switch (isValidDate(startDate)) {
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
				switch (isValidDate(endDate)) {
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
				wregex wrx(L"([ㄱ-ㅣ가-힣a-zA-Z0-9 ]{1,30})");
				wsmatch wideMatch;
				wstring wtitle = SDM.s2ws(title);
				if (regex_match(wtitle.cbegin(), wtitle.cend(), wideMatch, wrx) &&
					title[0] != ' ' && title.back() != ' ') {
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
			cout << "<일정 추가(4/5)>\n\n";
			cout << "카테고리 선택\n\n";
			cout << "0. 기본\n";
			CDM->CategoryPrint();
			cateCount = CDM->GetSize();
			cout << cateCount + 1 << ". 새 카테고리 추가\n\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "일정의 새로운 카테고리를 선택하세요.\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, menu);
			system("cls");
			if (menu == "^C") {
				system("cls");
				flag = 2; // 이전 프롬프트(제목 입력 프롬프트)로 이동
			}
			else if (is_digit(menu) && 0 == stoi(menu)) {
				category = "기본"; // 기본 카테고리
				flag = 4; // 메모 입력 프롬프트로 이동
			}
			else if (is_digit(menu) && 1 <= stoi(menu) && stoi(menu) <= cateCount) {
				category = CDM->GetCategory()->at(stoi(menu) - 1); // 사용자 지정 카테고리
				flag = 4; // 메모 입력 프롬프트로 이동
			}
			else if (is_digit(menu) && stoi(menu) == cateCount + 1) {
				CLS->CategoryAdd(); // 카테고리 추가
				if (cateCount != CDM->GetSize()) { // 카데고리가 정상적으로 추가된 경우
					category = CDM->GetCategory()->at(CDM->GetSize() - 1); // 새로 추가한 카테고리
					flag = 4; // 메모 입력 프롬프트로 이동
				}
				else {
					flag = 3;//현재 프롬프트 반복
				}
			}
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
				wregex wrx(L"([ㄱ-ㅣ가-힣a-zA-Z0-9 ]+)");
				wsmatch wideMatch;
				wstring wmemo = SDM.s2ws(memo);
				if (memo.size() != 0) {
					if (regex_match(wmemo.cbegin(), wmemo.cend(), wideMatch, wrx) &&
						memo[0] != ' ' && memo.back() != ' ') {
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
				else {
					flag = 5;
				}
			}
			break;
		}
	}
	Schedule* newDate = new Schedule(title, startDate, endDate, category, memo);
	cal->allSchs.push_back(*newDate);	// 데이터 파일에 해당 스케줄 추가
	SDM.saveDataFile(*cal);	// 데이터 파일에 저장
	
	system("cls");
	printSchedule();
}

void Management::mod_or_delSchedule()
{
	vector<Schedule*> sche; // 현재 날짜에 해당하는 스케줄
	vector<int> scheNum; // 현재 날짜에 해당하는 스케줄의 번호

	string sd, ed;
	string startDate, endDate, title, category, memo;
	string y, m, d;
	string menu; // 메뉴 선택
	int selectedNum = 0; // 사용자가 선택한 일정의 번호
	int cateCount = 0;


	int flag = 0;// 부 프롬프트 간 이동을 위한 변수
	while (flag < 9) {
		system("cls");
		switch (flag) {
		case 0:
			// 현재 날짜의 스케줄을 캘린더에서 하나씩 추가
			sche.clear();
			for (int i = 0; i < cal->allSchs.size(); i++) {

				sd = cal->allSchs[i].getStartDate();
				ed = cal->allSchs[i].getEndDate();

				if (dateinfo >= sd && dateinfo <= ed) {
					sche.push_back(&(cal->allSchs[i]));
					scheNum.push_back(i);
				}
					
			}
			
			cout << "<일정 수정/삭제>\n\n";

			// 사용자가 입력한 날짜의 일정 목록
			for (int i = 0; i < sche.size(); i++) {
				cout << i + 1 << ". \n";
				sche[i]->print();
			}

			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "수정/삭제를 원하는 일정의 번호를 입력하세요.\n";
			cout << "------------------------------\n";
			cout << "> ";
			getline(cin, menu);
			system("cls");
			if (menu == "^C") {
				system("cls");
				flag = 9;
				printSchedule(); // 이전 프롬프트 (일정목록/메뉴선택)
			}
			else if (is_digit(menu) && (stoi(menu) >= 1 && stoi(menu) <= sche.size())) {
				selectedNum = stoi(menu) - 1;
				flag = 1; // 다음 프롬프트(수정/삭제 선택)
			}
			else {
				flag = 0; // 현재 프롬프트 다시 수행
				cout << "오류: 수정/삭제를 원하는 일정의 번호를 형식에 맞게 입력해주세요.\n";
				if (_getch()) {
					system("cls");
				}
			}
			break;
		case 1:
			cout << "<일정 수정/삭제>\n\n";
			cout << "수정/삭제 여부 선택\n\n";
			cout << "제목 : " << sche[selectedNum]->getTitle() << "\n\n";
			cout << "1. 수정\n";
			cout << "2. 삭제\n\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "선택한 일정에 대해 진행할 작업을 선택해주세요.\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, menu);
			system("cls");
			if (menu == "^C") {
				system("cls");
				flag = 0; // 이전 프롬프트 (일정 선택 프롬프트)
			}
			else if (is_digit(menu) && stoi(menu) == 1)
				flag = 2; // 수정 프롬프트로 이동
			else if (is_digit(menu) && stoi(menu) == 2)
				flag = 8; // 삭제 프롬프트로 이동
			else {
				cout << "오류: 1,2 중 하나의 숫자를 입력해주세요.\n";
				if (_getch()) {
					system("cls");
					flag = 1; // 현재 프롬프트 반복
				}
			}	
			break;
		case 2:
			cout << "<일정 수정>\n\n";
			cout << "변경할 요소 선택\n\n";
			
			sche[selectedNum]->print();

			cout << "1. 시작일\n";
			cout << "2. 종료일\n";
			cout << "3. 제목\n";
			cout << "4. 카테고리\n";
			cout << "5. 메모\n\n";

			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "선택한 일정에서 정보를 변경할 요소를 선택해주세요.\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, menu);
			system("cls");
			if (menu == "^C") {
				system("cls");
				flag = 1; // 이전 프롬프트 (수정/삭제 여부 선택 프롬프트)
			}
			else if (is_digit(menu) && stoi(menu) == 1)
				flag = 3; // 시작일 수젇 프롬프트로 이동
			else if (is_digit(menu) && stoi(menu) == 2)
				flag = 4; // 종료일 수정 프롬프트로 이동
			else if (is_digit(menu) && stoi(menu) == 3)
				flag = 5; // 제목 수정 프롬프트로 이동
			else if (is_digit(menu) && stoi(menu) == 4)
				flag = 6; // 카테고리 수정 프롬프트로 이동
			else if (is_digit(menu) && stoi(menu) == 5)
				flag = 7; // 메모 수정 프롬프트로 이동
			else {
				cout << "오류: 1,2,3,4,5 중 하나의 숫자를 입력해주세요.\n";
				if (_getch()) {
					system("cls");
					flag = 2; // 현재 프롬프트 반복
				}
			}
			break;
		case 3:
			cout << "<일정 수정>\n\n";
			cout << "시작일 입력\n\n";
			cout << "시작일 입력 형식 : yyyy/mm/dd\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "일정의 새로운 시작일을 입력하세요.\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, startDate);
			if (startDate == "^C") {
				system("cls");
				flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
			}
			else {
				switch (isValidDate(startDate)) {
				case 0:
					sche[selectedNum]->setStartDate(startDate);
					SDM.saveDataFile(*cal);	// 데이터 파일에 저장
					flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
					break;
				case -1:
					system("cls");
					cout << "오류: 시작일의 날짜를 형식에 맞게 입력해주세요.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
					flag = 3; // 현재 프롬프트를 반복
					break;
				case -2:
					system("cls");
					cout << "오류: " << dateinfo << "(은)는 존재하지 않는 날짜입니다.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
					flag = 3; // 현재 프롬프트를 반복
					break;
				}
			}
			break;
		case 4:
			cout << "<일정 수정>\n\n";
			cout << "종료일 입력\n\n";
			cout << "종료일 입력 형식 : yyyy/mm/dd\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "일정의 새로운 종료일을 입력하세요.\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, endDate);
			if (endDate == "^C") {
				system("cls");
				flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
			}
			else {
				switch (isValidDate(endDate)) {
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
						flag = 4; // 현재 프롬프트 반복
					}
					else {
						sche[selectedNum]->setEndDate(endDate);
						SDM.saveDataFile(*cal);	// 데이터 파일에 저장
						flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
					}
					break;
				case -1:
					system("cls");
					cout << "오류: 종료일의 날짜를 형식에 맞게 입력해주세요.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
					flag = 4; // 현재 프롬프트 반복
					break;
				case -2:
					system("cls");
					cout << "오류: " << dateinfo << "(은)는 존재하지 않는 날짜입니다.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
					flag = 4; // 현재 프롬프트 반복
					break;
				}
			}
			break;
		case 5:
			cout << "<일정 수정>\n\n";
			cout << "제목 입력\n\n";
			cout << "(제목 입력 형식 설명)\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "일정의 새로운 제목을 입력하세요.\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, title);
			if (title == "^C") {
				flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
			}
			else {
				wregex wrx(L"([ㄱ-ㅣ가-힣a-zA-Z0-9 ]{1,30})");
				wsmatch wideMatch;
				wstring wtitle = SDM.s2ws(title);
				if (regex_match(wtitle.cbegin(), wtitle.cend(), wideMatch, wrx) &&
					title[0] != ' ' && title.back() != ' ') {
					sche[selectedNum]->setTitle(title);
					SDM.saveDataFile(*cal);	// 데이터 파일에 저장
					flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
				}
				else {
					system("cls");
					cout << "오류: 제목을 형식에 맞게 입력해주세요.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
					flag = 5; // 현재 프롬프트 반복
				}
			}
			break;
		case 6:
			cout << "<일정 수정>\n\n";
			cout << "카테고리 선택\n\n";
			cout << "0. 기본\n";
			CDM->CategoryPrint();
			cateCount = CDM->GetSize();
			cout << cateCount + 1 << ". 새 카테고리 추가\n\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "일정의 새로운 카테고리를 선택하세요.\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, menu);
			system("cls");
			if (menu == "^C") {
				system("cls");
				flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
			}
			else if (is_digit(menu) && 0 == stoi(menu)) {
				sche[selectedNum]->setCategory("기본"); // 기본 카테고리
				SDM.saveDataFile(*cal);	// 데이터 파일에 저장
				flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
			}
			else if (is_digit(menu) && 1 <= stoi(menu) && stoi(menu) <= cateCount) {
				sche[selectedNum]->setCategory(CDM->GetCategory()->at(stoi(menu) - 1)); // 사용자 지정 카테고리
				SDM.saveDataFile(*cal);	// 데이터 파일에 저장
				flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
			}
			else if (is_digit(menu) && stoi(menu) == cateCount + 1) {
				CLS->CategoryAdd(); // 카테고리 추가
				if (cateCount != CDM->GetSize()) { // 카데고리가 정상적으로 추가된 경우
					sche[selectedNum]->setCategory(CDM->GetCategory()->at(CDM->GetSize() - 1)); // 새로 추가한 카테고리
					SDM.saveDataFile(*cal);	// 데이터 파일에 저장
					flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
				}
				else {
					flag = 6; // 현재 프롬프트 반복
				}
			}
			break;
		case 7:
			cout << "<일정 수정>\n\n";
			cout << "메모 입력\n\n";
			cout << "(메모 입력 형식 설명)\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "기존 일정의 새로운 메모를 입력하세요.\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, memo);
			if (memo == "^C") {
				flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
			}
			else {
				wregex wrx(L"([ㄱ-ㅣ가-힣a-zA-Z0-9 ]+)");
				wsmatch wideMatch;
				wstring wmemo = SDM.s2ws(memo);
				if (memo.size() != 0) {
					if (regex_match(wmemo.cbegin(), wmemo.cend(), wideMatch, wrx) &&
						memo[0] != ' ' && memo.back() != ' ') {
						sche[selectedNum]->setMemo(memo);
						SDM.saveDataFile(*cal);	// 데이터 파일에 저장
						flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
					}
					else {
						system("cls");
						cout << "오류: 메모를 형식에 맞게 입력해주세요.\n\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						_getch();
						flag = 7; // 현재 프롬프트 반복
					}
				}
			}
			break;
		case 8:
			cout << "<일정 삭제>\n\n";
			cout << "제목 : " << sche[selectedNum]->getTitle() << "\n\n";
			cout << "해당 일정을 정말로 삭제하시겠습니까?\n\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "1. 예\n";
			cout << "2. 아니요\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, menu);
			system("cls");
			if (menu == "^C") {
				system("cls");
			}
			else if (is_digit(menu) && stoi(menu) == 1) {
				cal->allSchs.erase(cal->allSchs.begin() + scheNum[selectedNum]);
				SDM.saveDataFile(*cal);	// 데이터 파일에 저장
			}
			else {
				cout << "오류: 1,2 중 하나의 숫자를 입력해주세요.\n";
				if (_getch()) {
					system("cls");
					flag = 8; // 현재 프롬프트 반복
				}
			}
			flag = 0; // 일정 선택 프롬프트로 이동
			break;
		}
	}
}
