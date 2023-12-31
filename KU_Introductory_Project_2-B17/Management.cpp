#include "Management.h"

void Management::Prompt() {
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
		if (cal->isValidDate(dateinfo) < 0) {
			Sleep(1000);
			system("cls");
			cout << "오류: 날짜를 형식에 맞게 입력해주세요.\n\n";

			cout << "아무 키나 눌러주세요.\n";
			cout << "_____________________________\n";
			cout << "> ";
			_getch();
			Prompt();
			return;
		}
		else {
			system("cls");
			printSchedule();
		}
	}
}

// Calender.h(.cpp) 로 이동하였습니다.
/*
int Management::isValidDate(string dateStr) {

	string y, m, d; // 각각 year, month, date{
	regex re("[0-9]{4}/[0-9]{2}/[0-9]{2}");	// 날짜 문법 형식


	// 문법 형식에 맞지 않을 때 -1 반환
	if (regex_match(dateStr, re)) {
		y = dateStr.substr(0, 4);
		m = dateStr.substr(5, 2);
		d = dateStr.substr(8, 2);

		// 의미 규칙에 맞지 않을 때 -2 반환
		if (stoi(y) >= 2000 && stoi(y) <= FINAL_YEAR
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
		return -2;
	}
	return -1;
}
*/

bool Management::is_digit(string str) {
	return atoi(str.c_str()) != 0 || str.compare("0") == 0;
}

void Management::printSchedule() {
	vector<Schedule*> sche; // 현재 날짜에 해당하는 스케줄
	string sd, ed;  // startDate, endDate

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
		else if (m.size() == 1) {
			if (m[0] == '1')
				addSchedule();
			else if (m[0] == '2')
				mod_or_delSchedule();
		}
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
		cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
		cout << "원하는 메뉴를 입력하세요\n";
		cout << "-------------------------------\n";
		cout << "> ";
		getline(cin, m);
		system("cls");
		if (m == "^C") {
			system("cls");
			Prompt();
		}
		else if (m.size() == 1 && m[0] == '1')
			addSchedule();
		else {
			cout << "오류: 1을 입력해주세요.\n\n";
			cout << "아무 키나 눌러주세요.\n";
			cout << "_____________________________\n";
			cout << "> ";
			if (_getch()) {
				system("cls");
				printSchedule();
			}
		}

	}
}

/* Zeller의 함수를 이용하여 year년 month월 day일의 요일을 계산한다. */
/* 일요일은 1,월요일은 2와 같은 식으로 리턴된다.                   */
int Management::zeller(int year, int month, int day) {
	int year_of_century, century, day_of_week;

	/* Zeller의 함수에 사용될 수 있도록 year와 month를 보정 */
	if (month == 1 || month == 2) year--;
	month = (month + 9) % 12 + 1;        /* Jan=11, Feb=12, Mar=1, ... */
	year_of_century = year % 100;    /* 예 : 91 of 1991            */
	century = year / 100;            /* 예 : 19 of 1991            */

	day_of_week = ((13 * month - 1) / 5 + day + year_of_century +
		year_of_century / 4 + century / 4 - 2 * century) % 7;
	if (day_of_week < 0) day_of_week = (day_of_week + 7) % 7;
	return(day_of_week + 1);
}

int Management::getDiffDate(string startDate, string endDate)
{
	int y1, m1, d1, y2, m2, d2;
	y1 = stoi(startDate.substr(0, 4));
	m1 = stoi(startDate.substr(5, 2));
	d1 = stoi(startDate.substr(8, 2));
	y2 = stoi(endDate.substr(0, 4));
	m2 = stoi(endDate.substr(5, 2));
	d2 = stoi(endDate.substr(8, 2));

	time_t start, end;
	struct tm startTime, endTime;
	int tm_day;
	double diff;

	startTime.tm_year = y1 - 1900; // 년도가 1900년부터 시작하기 때문
	startTime.tm_mon = m1 - 1; //월이 0부터 시작하기 때문
	startTime.tm_mday = d1;
	startTime.tm_hour = 0;
	startTime.tm_min = 0;
	startTime.tm_sec = 0;
	startTime.tm_isdst = 0; //썸머타임 사용안함

	endTime.tm_year = y2 - 1900; // 년도가 1900년부터 시작하기 때문
	endTime.tm_mon = m2 - 1; //월이 0부터 시작하기 때문
	endTime.tm_mday = d2;
	endTime.tm_hour = 0;
	endTime.tm_min = 0;
	endTime.tm_sec = 0;
	endTime.tm_isdst = 0; //썸머타임 사용안함

	start = mktime(&startTime);
	end = mktime(&endTime);

	diff = difftime(end, start);

	tm_day = diff / (60 * 60 * 24);

	return tm_day;
}

string Management::calcStartDate(string endDate, int diffDate)
{
	int y1, m1, d1, y2, m2, d2;
	y1 = stoi(endDate.substr(0, 4));
	m1 = stoi(endDate.substr(5, 2));
	d1 = stoi(endDate.substr(8, 2));

	time_t start, end;
	struct tm startTime, endTime;
	int tm_day;

	endTime.tm_year = y1 - 1900; // 년도가 1900년부터 시작하기 때문
	endTime.tm_mon = m1 - 1; //월이 0부터 시작하기 때문
	endTime.tm_mday = d1;
	endTime.tm_hour = 0;
	endTime.tm_min = 0;
	endTime.tm_sec = 0;
	endTime.tm_isdst = 0; //썸머타임 사용안함

	end = mktime(&endTime);

	start = end - (time_t)diffDate * (60 * 60 * 24);

	localtime_s(&startTime, &start);

	y2 = startTime.tm_year + 1900;
	m2 = startTime.tm_mon + 1;
	d2 = startTime.tm_mday;

	string m2_str = (m2 < 10) ? "0" + to_string(m2) : to_string(m2);
	string d2_str = (d2 < 10) ? "0" + to_string(d2) : to_string(d2);

	return to_string(y2) + "/" + m2_str + "/" + d2_str;
}

int Management::findLastDayofMonth(int endDateYear, int endDateMonth)
{
	switch (endDateMonth) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;

	case 4: case 6: case 9: case 11:
		return 30;

	case 2:
		if (endDateYear % 4) {
			return 28;
		}
		else {
			return 29;
		}
	default:
		return -1;
	}
}

// date1이 date2보다 빠르면(이전이면) true를 반환
bool Management::isPreviousDate(string date1, string date2) {
	// 시작일보다 종료일이 빠른 경우 
	int y1, m1, d1, y2, m2, d2;

	y1 = stoi(date1.substr(0, 4));
	m1 = stoi(date1.substr(5, 2));
	d1 = stoi(date1.substr(8, 2));
	y2 = stoi(date2.substr(0, 4));
	m2 = stoi(date2.substr(5, 2));
	d2 = stoi(date2.substr(8, 2));

	if ((y1 > y2) || ((y1 == y2) && (m1 > m2)) || ((y1 == y2) && (m1 == m2) && (d1 > d2)))
		return false;
	return true;
}

void Management::addSchedule()
{
	string startDate, endDate, title, memo, rptEndDate;
	vector<string> category;
	string yRptStr, mRptStr, wRptStr; //년, 월, 주별로 반복날짜 정보를 입력받을 문자열
	vector<string> yRptVec; //연도 별로 반복날짜 정보를 저장할 벡터
	vector<int> mRptVec, wRptVec;	//월, 주별로 반복날짜 정보를 저장할 벡터
	int cycle, key, rptK;
	string y, m, d;
	int cateCount = 0;
	string menu;

	int flag = 0;	// 부 프롬프트 간 이동을 위한 변수
	// int backup_flag = 0;
	while (flag < 10) {
		system("cls");
		switch (flag) {
		case 0:
			cout << "<일정 추가>\n\n";
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
				return;
			}
			else {
				switch (cal->isValidDate(startDate)) {
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
					cout << "오류: " << startDate << "(은)는 존재하지 않는 날짜입니다.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
					break;
				}
			}
			break;
		case 1:
			cout << "<일정 추가>\n\n";
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
				switch (cal->isValidDate(endDate)) {
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
					cout << "오류: " << endDate << "(은)는 존재하지 않는 날짜입니다.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
					break;
				}
			}
			break;
		case 2:
			cout << "<일정 추가>\n\n";
			cout << "제목 입력\n\n";
			cout << "제목 형식:\n";
			cout << "길이가 1 이상 30 이하이며 한글/영어/숫자와 공백의 조합\n";
			cout << "첫 문자와 마지막 문자는 한글/영어/숫자\n";
			cout << "탭, 줄바꿈 사용 불가\n\n";
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
			cout << "<일정 추가>\n\n";
			cout << "카테고리 선택\n\n";
			cout << "0. 기본\n";
			CDM->CategoryPrint();
			cateCount = CDM->GetSize();
			//cout << cateCount + 1 << ". 새 카테고리 추가\n\n";
			cout << "(여러 카테고리의 입력은 공백류로 구분합니다.)" << endl;
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "일정의 새로운 카테고리를 선택하세요.\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, menu);
			system("cls");
			if (menu == "^C") {
				system("cls");
				flag = 2; // 이전 프롬프트(제목 입력 프롬프트)로 이동
				break;
			}


			/******************************************************
			*******************************************************/
			else if (menu.size() >= 1) {
				int winput = 0;
				vector<int> cateTemp;
				istringstream ciss(menu);
				string cword;
				while (ciss >> cword) {
					if (is_digit(cword) && stoi(cword) >= 0 && stoi(cword) <= cateCount) {
						try {
							cateTemp.push_back(stoi(cword));
						}
						catch (exception e) {
							cout << "1" << e.what();
						}
					}
					else {
						cout << "오류: 0 혹은 1~" << cateCount << "까지의 자연수를 입력해주세요.\n\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						if (_getch()) {
							system("cls");
							winput = 1; // 현재 프롬프트 반복
						}
						break;
					}
				}
				if (winput == 1) {
					flag = 3;
					break;
				}
				else {
					try {
						sort(cateTemp.begin(), cateTemp.end());
						cateTemp.erase(unique(cateTemp.begin(), cateTemp.end()), cateTemp.end());
					}
					catch (exception e) {
						cout << "2" << e.what();
					}

					while (!cateTemp.empty()) {
						int cateTT = cateTemp.back();
						cateTemp.pop_back();
						if (0 == cateTT) {
							category.push_back("기본"); // 기본 카테고리
						}
						else if (1 <= cateTT && cateTT <= cateCount) {
							category.push_back(CDM->GetCategory()->at(cateTT - 1)); // 사용자 지정 카테고리
						}
					}
				}
			}
			else {
				cout << "오류: 0 혹은 1~" << cateCount << "까지의 자연수를 입력해주세요.\n\n";
				cout << "아무 키나 눌러주세요.\n";
				cout << "_____________________________\n";
				cout << "> ";
				if (_getch()) {
					system("cls");
					flag = 3; // 현재 프롬프트 반복
				}
				break;
			}
			flag = 4; // 메모 입력 프롬프트로 이동
			break;
		case 4:
			cout << "<일정 추가>\n\n";
			cout << "메모 입력\n\n";
			cout << "메모 형식:\n";
			cout << "길이가 0 이상이며 한글/영어/숫자와 공백의 조합\n";
			cout << "길이가 1 이상인 경우, 첫 문자와 마지막 문자는 한글/영어/숫자\n";
			cout << "탭, 줄바꿈 사용 불가\n\n";
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
		case 5:
			cout << "<일정 추가>\n\n";
			cout << "반복 여부 및 단위 선택\n\n";
			cout << "0. 반복하지 않음\n";
			cout << "1. 매년\n";
			cout << "2. 매월\n";
			cout << "3. 매주\n\n";
			cout << "원하는 반복 단위를 입력하세요.\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, menu);
			if (menu == "^C") {
				flag = 4;
				break;
			}
			else if (menu.size() == 1) {
				if (is_digit(menu) && stoi(menu) == 0) {
					cycle = stoi(menu);
					flag = 10; // 프롬프트 종료, 일정 추가/저장
					break;
				}
				else if (is_digit(menu) && stoi(menu) == 1) {
					cycle = stoi(menu);
					flag = 6; // 년 입력 프롬프트로 이동
					break;
				}
				else if (is_digit(menu) && stoi(menu) == 2) {
					cycle = stoi(menu);
					flag = 7; // 월 입력 프롬프트로 이동
					break;
				}
				else if (is_digit(menu) && stoi(menu) == 3) {
					cycle = stoi(menu);
					flag = 8; // 주 입력 프롬프트로 이동
					break;
				}
			}
			system("cls");
			cout << "오류: 0,1,2,3 중 하나의 숫자를 입력해주세요.\n\n";
			cout << "아무 키나 눌러주세요.\n";
			cout << "_____________________________\n";
			cout << "> ";
			if (_getch()) {
				system("cls");
				flag = 5; // 현재 프롬프트 반복
			}
			break;
		case 6:
			// backup_flag = 6;
			cout << "<일정 추가>\n\n";
			cout << "년 입력\n\n";
			cout << "반복할 날짜를 형식에 맞게 입력해주세요.\n";
			cout << "(mm/dd, 여러 날짜의 입력은 공백류로 구분합니다.)\n";
			cout << "예:  01/02 10/04 12/31  (매년 1월 2일, 10월 4일, 12월 31일 반복)\n\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, yRptStr);
			if (yRptStr == "^C") {
				flag = 5;
			}
			else {
				regex re("(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])([ ]+(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01]))*");	// 날짜 문법 형식
				if (!regex_match(yRptStr, re)) {
					system("cls");
					cout << "오류: 반복 날짜를 형식에 맞게 입력해주세요.\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					if (_getch()) {
						system("cls");
						flag = 6; // 현재 프롬프트 반복
						break;
					}
				}
				regex re2("(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])");
				regex re3("02/30|02/31|02/31|04/31|06/31|09/31|11/31");

				// 문법 형식에 맞지 않을 때 -1 반환
				if (regex_match(yRptStr, re)) {
					yRptVec.clear();

					istringstream iss(yRptStr);
					bool isExistDate = true, hasEndDate = false;
					do {
						std::string word;
						iss >> word;
						if (!word.empty()) {

							if (regex_match(word, re2) && !regex_match(word, re3)) {
								if (word == endDate.substr(5, 5)) {
									hasEndDate = true; // 반복날짜 중에 사용자가 입력한 종료일이 포함되어 있는지
								}
								yRptVec.push_back(word);
							}
							else {
								isExistDate = false; // 반복날짜들이 모두 존재하는 날짜인지
								break;
							}
						}
					} while (iss);

					if (!isExistDate) {
						system("cls");
						cout << "오류: 존재하지 않는 날짜가 포함되어 있습니다.\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						if (_getch()) {
							system("cls");
							flag = 6; // 현재 프롬프트 반복
							break;
						}
					}
					if (!hasEndDate) {
						system("cls");
						cout << "오류: 일정의 '종료일'이 반복 날짜에 포함되어야 합니다.\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						if (_getch()) {
							system("cls");
							flag = 6; // 현재 프롬프트 반복
							break;
						}
					}

					yRptVec.erase(unique(yRptVec.begin(), yRptVec.end()), yRptVec.end()); //중복 제거
					flag = 9; // 반복종료일 입력 프롬프트로 이동
				}
			}
			break;
		case 7:
			// backup_flag = 7;
			cout << "<일정 추가>\n\n";
			cout << "월 입력\n\n";
			cout << "반복할 날짜를 숫자만 입력해주세요.\n";
			cout << "(여러 날짜의 입력은 공백류로 구분합니다.)\n";
			cout << "예: 1 11 21 (매달 1일, 11일, 21일 반복)\n\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, mRptStr);
			if (mRptStr == "^C") {
				flag = 5;
			}
			else {
				// 00 입력 불가, 01~09 == 1~9
				regex re("(0?[1-9]|[12][0-9]|3[01])([ ]+(0?[1-9]|[12][0-9]|3[01]))*");
				if (regex_match(mRptStr, re)) {
					mRptVec.clear();	// 현재 프롬프트가 재시작되는 경우 고려

					istringstream iss(mRptStr);
					string word;

					while (iss >> word) {
						mRptVec.push_back(stoi(word));
					}
					sort(mRptVec.begin(), mRptVec.end());
					mRptVec.erase(unique(mRptVec.begin(), mRptVec.end()), mRptVec.end());

					vector<int>::iterator ptr;
					bool isExistDate = true;
					for (ptr = mRptVec.begin(); ptr != mRptVec.end(); ++ptr) {
						if (*ptr > 31) {
							isExistDate = false;
							break;
						}
					}
					if (!isExistDate) {
						system("cls");
						cout << "오류: 공백류로 구분되는 \"1부터 31까지의 자연수 숫자\" 1개 이상을 입력해주셔야 합니다.\n\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						_getch();
						break;
					}

					bool hasEndDate = false;
					int ed = stoi(endDate.substr(8, 2));
					for (ptr = mRptVec.begin(); ptr != mRptVec.end(); ++ptr) {
						if (*ptr == ed) {
							hasEndDate = true;
							break;
						}
					}
					if (!hasEndDate) {
						system("cls");
						cout << "오류: 일정의 '종료일'이 반복 날짜에 포함되어야 합니다.\n\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						_getch();
						break;
					}
					flag = 9;
				}
				else {
					system("cls");
					cout << "오류: 공백류로 구분되는 \"1부터 31까지의 자연수 숫자\" 1개 이상을 입력해주셔야 합니다.\n\n";					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
				}
			}
			break;
		case 8:
			// backup_flag = 8;
			cout << "<일정 추가>\n\n";
			cout << "주 입력\n\n";
			cout << "1. 일\n";
			cout << "2. 월\n";
			cout << "3. 화\n";
			cout << "4. 수\n";
			cout << "5. 목\n";
			cout << "6. 금\n";
			cout << "7. 토\n\n";
			cout << "반복할 요일의 번호를 입력하세요.\n";
			cout << "(여러 요일의 입력은 공백류로 구분합니다.)\n";
			cout << "예 : 1 2 3\n\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, wRptStr);
			if (wRptStr == "^C") {
				flag = 5;
			}
			else {
				regex re("[1-7]([ ]+[1-7])*");
				if (regex_match(wRptStr, re)) {
					wRptVec.clear();	// 현재 프롬프트가 재시작되는 경우 고려

					istringstream iss(wRptStr);
					string word;
					while (iss >> word) {
						wRptVec.push_back(stoi(word));
					}
					sort(wRptVec.begin(), wRptVec.end());
					wRptVec.erase(unique(wRptVec.begin(), wRptVec.end()), wRptVec.end());

					bool hasEndDate = false;
					int y = stoi(endDate.substr(0, 4));
					int m = stoi(endDate.substr(5, 2));
					int d = stoi(endDate.substr(8, 2));
					int edWhatday = zeller(y, m, d);	// 종료일이 무슨 요일인지

					vector<int>::iterator ptr;
					for (ptr = wRptVec.begin(); ptr != wRptVec.end(); ++ptr) {
						if (*ptr == edWhatday) {
							hasEndDate = true;
							break;
						}
					}
					if (!hasEndDate) {
						system("cls");
						cout << "오류: 일정의 '종료일'이 반복 날짜에 포함되어야 합니다.\n\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						_getch();
						break;
					}
					flag = 9;
				}
				else {
					system("cls");
					cout << "오류: 공백류로 구분되는 \"1부터 7까지의 자연수 숫자\" 1개 이상을 입력해주셔야 합니다.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
				}
			}
			break;
		case 9:
			cout << "<일정 추가>\n\n";
			cout << "반복 종료일 입력\n\n";
			cout << "반복 종료일을 입력해주세요.\n\n";
			cout << "반복 종료일 입력 형식 : yyyy/mm/dd\n";
			cout << "(지정하지 않을 경우 -1 을 입력해주세요.)\n\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, rptEndDate);
			if (rptEndDate == "^C") {
				flag = 5;
			}
			else if (rptEndDate == "-1") {
				rptEndDate = to_string(FINAL_YEAR) + "/12/31";
				flag = 10;
			}
			else {
				switch (cal->isValidDate(rptEndDate)) {
				case 0:
					// 종료일보다 반복종료일이 빠른 경우 
					int y1, m1, d1, y2, m2, d2;
					y1 = stoi(endDate.substr(0, 4));
					m1 = stoi(endDate.substr(5, 2));
					d1 = stoi(endDate.substr(8, 2));
					y2 = stoi(rptEndDate.substr(0, 4));
					m2 = stoi(rptEndDate.substr(5, 2));
					d2 = stoi(rptEndDate.substr(8, 2));

					if ((y1 > y2) || ((y1 == y2) && (m1 > m2))
						|| ((y1 == y2) && (m1 == m2) && (d1 > d2))) {
						system("cls");
						cout << "오류: 반복 종료일은 일정의 종료일과 같거나, 그 이후여야 합니다.\n\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						_getch();
						flag = 9;
					}
					else {
						flag = 10;
					}
					break;
				case -1:
					system("cls");
					cout << "오류: 반복 종료일의 날짜를 형식에 맞게 입력해주세요.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
					flag = 9;
					break;
				case -2:
					system("cls");
					cout << "오류: " << rptEndDate << "(은)는 존재하지 않는 날짜입니다.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
					flag = 9;
					break;
				}
			}
			break;
		}
	}

	int diffDate = 0;
	Schedule* newDate = nullptr;
	switch (cycle) {
	case 0:	// 반복 x
		newDate = new Schedule(title, startDate, endDate, category, memo, endDate, cycle, cal->getHighestKey() + 1, 0);
		cal->allSchs.push_back(*newDate);	// 데이터 파일에 해당 스케줄 추가
		break;
	case 1:	// 매년 반복
		// 1. startDate와 endDate의 날짜 차이를 알아야 함.
		// 2. yRptVec에서 종료일(10/04)을 꺼내와서 해당 날짜 차이를 가지고 시작일을 알아냄
		// 3. 알아낸 시작일과 yRptVec에서 꺼낸 종료일을 가지고 새로운 스케줄 객체 생성
		// 4. 2와 3을 yRptVec의 모든 객체에 대하여 반복
		diffDate = getDiffDate(startDate, endDate);
		for (int i = 0; i < yRptVec.size(); i++) {
			int m1, d1, m2, d2;
			m1 = stoi(endDate.substr(5, 2));
			d1 = stoi(endDate.substr(8, 2));
			m2 = stoi(yRptVec[i].substr(0, 2));
			d2 = stoi(yRptVec[i].substr(3, 2));

			int endDateYear = stoi(endDate.substr(0, 4));
			if ((m1 > m2) || ((m1 == m2) && (d1 > d2))) {	// endDate가 yRptVect보다 뒤에 있는 경우
				endDateYear++;
			}
			string anotherEndDate = to_string(endDateYear) + "/" + yRptVec[i];
			while (endDateYear <= FINAL_YEAR && cal->isValidDate(anotherEndDate)) {	// 2월 29일이 있는 연도까지 반복
				string possibleEndDate = anotherEndDate.substr(0, 8) + "28";
				if (!isPreviousDate(possibleEndDate, rptEndDate)) {
					anotherEndDate = possibleEndDate;
					break;
				}
				string possibleStartDate = calcStartDate(possibleEndDate, diffDate);
				newDate = new Schedule(title, possibleStartDate, possibleEndDate, category, memo, possibleEndDate, 0, cal->getHighestKey() + 1, i + 1);
				cal->allSchs.push_back(*newDate);	// 데이터 파일에 해당 스케줄 추가
				endDateYear++;
				anotherEndDate = to_string(endDateYear) + "/" + yRptVec[i];
			}

			if (endDateYear <= FINAL_YEAR && isPreviousDate(anotherEndDate, rptEndDate)) {	// 2월 29일이 있는 연도인 경우
				string anotherStartDate = calcStartDate(anotherEndDate, diffDate);
				newDate = new Schedule(title, anotherStartDate, anotherEndDate, category, memo, rptEndDate, cycle, cal->getHighestKey() + 1, i + 1);
				cal->allSchs.push_back(*newDate);	// 데이터 파일에 해당 스케줄 추가
			}
		}
		break;
	case 2:	// 매월 반복
		// 1. startDate와 endDate의 날짜 차이를 알아야 함.
		// 2. mRptVec에서 종료일(11)을 꺼내와서 해당 날짜 차이를 가지고 시작일을 알아냄
		// 3. 알아낸 시작일과 mRptVec에서 꺼낸 종료일을 가지고 새로운 스케줄 객체 생성
		// 4. 2와 3을 mRptVec의 모든 객체에 대하여 반복
		diffDate = getDiffDate(startDate, endDate);
		for (int i = 0; i < mRptVec.size(); i++) {
			int d1, d2;
			d1 = stoi(endDate.substr(8, 2));
			d2 = mRptVec[i];

			int endDateYear = stoi(endDate.substr(0, 4));
			int endDateMonth = stoi(endDate.substr(5, 2));
			if (d1 > d2) {	// endDate가 yRptVect보다 뒤에 있는 경우
				if (++endDateMonth > 12) {
					endDateYear++;
					endDateMonth -= 12;
				}
			}

			string eDMString = (endDateMonth < 10) ? "0" + to_string(endDateMonth) : to_string(endDateMonth);
			string eDDString = (mRptVec[i] < 10) ? "0" + to_string(mRptVec[i]) : to_string(mRptVec[i]);
			string anotherEndDate = to_string(endDateYear) + "/" + eDMString + "/" + eDDString;
			while (endDateYear <= FINAL_YEAR && cal->isValidDate(anotherEndDate)) {	// 해당 날짜가 있는 달이 나오기 전까지
				string possibleEndDate = anotherEndDate.substr(0, 8) + to_string(findLastDayofMonth(endDateYear, endDateMonth));
				if (!isPreviousDate(possibleEndDate, rptEndDate)) {
					anotherEndDate = possibleEndDate;
					break;
				}
				string possibleStartDate = calcStartDate(possibleEndDate, diffDate);
				newDate = new Schedule(title, possibleStartDate, possibleEndDate, category, memo, possibleEndDate, 0, cal->getHighestKey() + 1, i + 1);
				cal->allSchs.push_back(*newDate);	// 데이터 파일에 해당 스케줄 추가
				if (++endDateMonth > 12) {
					endDateYear++;
					endDateMonth -= 12;
				}
				eDMString = (endDateMonth < 10) ? "0" + to_string(endDateMonth) : to_string(endDateMonth);
				anotherEndDate = to_string(endDateYear) + "/" + eDMString + "/" + eDDString;
			}
			if (endDateYear <= FINAL_YEAR && isPreviousDate(anotherEndDate, rptEndDate)) {	// 해당 날짜가 있는 달인 경우
				string anotherStartDate = calcStartDate(anotherEndDate, diffDate);
				newDate = new Schedule(title, anotherStartDate, anotherEndDate, category, memo, rptEndDate, cycle, cal->getHighestKey() + 1, i + 1);
				cal->allSchs.push_back(*newDate);	// 데이터 파일에 해당 스케줄 추가
			}
		}
		break;
	case 3:	// 매주 반복
		// 1. startDate와 endDate의 날짜 차이를 알아야 함.
		// 2. wRptVec에서 종료일(5)을 꺼내와서 해당 날짜 차이를 가지고 시작일을 알아냄
		// 3. 알아낸 시작일과 wRptVec에서 꺼낸 종료일을 가지고 새로운 스케줄 객체 생성
		// 4. 2와 3을 wRptVec의 모든 객체에 대하여 반복
		diffDate = getDiffDate(startDate, endDate);
		for (int i = 0; i < wRptVec.size(); i++) {
			int endDateYear = stoi(endDate.substr(0, 4));
			int endDateMonth = stoi(endDate.substr(5, 2));
			int endDateDay = stoi(endDate.substr(8, 2));
			int edWhatday = zeller(endDateYear, endDateMonth, endDateDay);
			int anotherEndDateDay, extraDay;

			anotherEndDateDay = endDateDay + ((7 - (edWhatday - wRptVec[i])) % 7);
			if ((extraDay = (anotherEndDateDay - findLastDayofMonth(endDateYear, endDateMonth))) > 0) {	// 해당 달을 넘어서는 날짜인 경우
				if (++endDateMonth > 12) {
					endDateYear++;
					endDateMonth -= 12;
				}
				anotherEndDateDay = extraDay;
			}

			string eDMString = (endDateMonth < 10) ? "0" + to_string(endDateMonth) : to_string(endDateMonth);
			string eDDString = (anotherEndDateDay < 10) ? "0" + to_string(anotherEndDateDay) : to_string(anotherEndDateDay);
			string anotherEndDate = to_string(endDateYear) + "/" + eDMString + "/" + eDDString;
			if (endDateYear <= FINAL_YEAR && isPreviousDate(anotherEndDate, rptEndDate)) {
				string anotherStartDate = calcStartDate(anotherEndDate, diffDate);
				newDate = new Schedule(title, anotherStartDate, anotherEndDate, category, memo, rptEndDate, cycle, cal->getHighestKey() + 1, i + 1);
				cal->allSchs.push_back(*newDate);	// 데이터 파일에 해당 스케줄 추가
			}
		}
		break;
	}

	SDM.saveDataFile(*cal);	// 데이터 파일에 저장
	SDM.loadDataFile(*cal, *cate);
	CDM->loadDataFile(*cate);
	system("cls");
	printSchedule();
}

void Management::mod_or_delSchedule() {
	vector<Schedule*> sche; // 현재 날짜에 해당하는 스케줄
	vector<int> scheNum; // 현재 날짜에 해당하는 스케줄의 번호 

	string sd, ed;
	string startDate, endDate, title, memo, rptEndDate;
	vector<string> category;
	string yRptStr, mRptStr, wRptStr; //년, 월, 주별로 반복날짜 정보를 입력받을 문자열
	vector<string> yRptVec; //연도 별로 반복날짜 정보를 저장할 벡터
	vector<int> mRptVec, wRptVec;	//월, 주별로 반복날짜 정보를 저장할 벡터
	int cycle, key, rptK;
	string y, m, d;
	int selectedNum = 0; // 사용자가 선택한 일정의 번호
	int cateCount = 0;
	string menu; // 메뉴 	int cateCount = 0;

	int flag = 0;// 부 프롬프트 간 이동을 위한 변수
	int backup_flag = 0;

	boolean rptKCheck = false;

	while (flag < 16) {
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
				flag = 16;
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
			else if (menu.size() == 1 && is_digit(menu) && stoi(menu) >= 1 && stoi(menu) <= 2) {
				if (stoi(menu) == 1)
					flag = 2; // 수정 프롬프트로 이동
				else if (stoi(menu) == 2)
					flag = 14; // 삭제 프롬프트로 이동
			}
			else {
				cout << "오류: 1,2 중 하나의 숫자를 입력해주세요.\n\n";
				cout << "아무키나 눌러주세요." << endl;
				cout << "----------------------------------------------" << endl;
				cout << ">";
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
			cout << "5. 메모\n";
			cout << "6. 반복 여부 / 반복 일자 / 반복 종료일\n\n";

			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "선택한 일정에서 정보를 변경할 요소를 선택해주세요.\n";
			cout << "(반복되는 일정일 시, “일괄 수정” 됩니다.)\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, menu);
			system("cls");
			if (menu == "^C") {
				system("cls");
				flag = 1; // 이전 프롬프트 (수정/삭제 여부 선택 프롬프트)
			}
			else if (menu.size() == 1 && is_digit(menu) && stoi(menu) >= 1 && stoi(menu) <= 6) {
				if (stoi(menu) == 1)
					flag = 3; // 시작일 수정 프롬프트로 이동
				else if (stoi(menu) == 2)
					flag = 4; // 종료일 수정 프롬프트로 이동
				else if (stoi(menu) == 3)
					flag = 5; // 제목 수정 프롬프트로 이동
				else if (stoi(menu) == 4)
					flag = 6; // 카테고리 수정 프롬프트로 이동
				else if (stoi(menu) == 5) {
					if (sche[selectedNum]->getCycle() == 0 && sche[selectedNum]->getRptK() == 0) {	//선택한 일정이 반복하지 않는 일정인 경우
						rptKCheck = false;
						flag = 8;//메모 수정 프롬프트로 이동
					}
					else {//선택한 일정이 반복하는 일정인 경우
						flag = 7;//메모 수정 범위 선택 프롬프트로 이동
					}
				}
				else if (stoi(menu) == 6)
					flag = 9; // 반복 관련 수정 프롬프트로 이동 
			}
			else {
				cout << "오류: 1,2,3,4,5,6 중 하나의 숫자를 입력해주세요.\n\n";
				cout << "아무키나 눌러주세요." << endl;
				cout << "----------------------------------------------" << endl;
				cout << ">";
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

			endDate = sche[selectedNum]->getEndDate();
			getline(cin, startDate);
			if (startDate == "^C") {
				system("cls");
				flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
			}
			else {
				switch (cal->isValidDate(startDate)) {
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
						cout << "오류: 시작일은 종료일과 같거나, 그 이전이어야 합니다.\n\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						_getch();
						flag = 3; // 현재 프롬프트 반복
					}
					else {
						key = sche[selectedNum]->getKey();
						string sD = startDate;
						string ssNsD = sche[selectedNum]->getStartDate();
						for (int i = 0; i < cal->allSchs.size(); i++) {
							if (cal->allSchs[i].getKey() == key) {
								cal->allSchs[i].setStartDate(SDM.calcSD(cal->allSchs[i].getStartDate(), getDiffDate(sD, ssNsD)));
							}
						}
						sche[selectedNum]->setStartDate(startDate);
						SDM.saveDataFile(*cal);	// 데이터 파일에 저장
						//SDM.loadDataFile(*cal, *cate);
						CDM->loadDataFile(*cate);
						flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
					}
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
					cout << "오류: " << startDate << "(은)는 존재하지 않는 날짜입니다.\n\n";
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

			startDate = sche[selectedNum]->getStartDate();
			getline(cin, endDate);
			if (endDate == "^C") {
				system("cls");
				flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
			}
			else {
				switch (cal->isValidDate(endDate)) {
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

						if (getDiffDate(sche[selectedNum]->getRptEndDate(), endDate) > 0) {
							system("cls");
							cout << "오류: 종료일은 반복종료일과 같거나, 그 이전이여야 합니다.\n\n";
							cout << "아무 키나 눌러주세요.\n";
							cout << "_____________________________\n";
							cout << "> ";
							_getch();
							flag = 4; // 현재 프롬프트 반복
						}
						else {
							key = sche[selectedNum]->getKey();
							string eD = endDate;
							string ssNeD = sche[selectedNum]->getEndDate();
							for (int i = 0; i < cal->allSchs.size(); i++) {
								if (cal->allSchs[i].getKey() == key) {
									cal->allSchs[i].setEndDate(SDM.calcSD(cal->allSchs[i].getEndDate(), getDiffDate(eD, ssNeD)));
								}
							}
							sche[selectedNum]->setEndDate(endDate);
							SDM.saveDataFile(*cal);	// 데이터 파일에 저장
							//SDM.loadDataFile(*cal, *cate);
							CDM->loadDataFile(*cate);

							flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
						}
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
					cout << "오류: " << endDate << "(은)는 존재하지 않는 날짜입니다.\n\n";
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
			cout << "제목 형식:\n";
			cout << "길이가 1 이상 30 이하이며 한글/영어/숫자와 공백의 조합\n";
			cout << "첫 문자와 마지막 문자는 한글/영어/숫자\n";
			cout << "탭, 줄바꿈 사용 불가\n\n";
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

					key = sche[selectedNum]->getKey();
					for (int i = 0; i < cal->allSchs.size(); i++) {
						if (cal->allSchs[i].getKey() == key) {
							cal->allSchs[i].setTitle(title);
						}
					}
					sche[selectedNum]->setTitle(title);
					SDM.saveDataFile(*cal);	// 데이터 파일에 저장
					//SDM.loadDataFile(*cal, *cate);
					CDM->loadDataFile(*cate);
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
			cout << "(여러 카테고리의 입력은 공백류로 구분합니다.)" << endl;
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
			else if (menu.size() >= 1) {
				int winput = 0;
				vector<int> cateTemp;
				istringstream ciss(menu);
				string cword;
				while (ciss >> cword) {
					if (is_digit(cword) && stoi(cword) >= 0 && stoi(cword) <= cateCount) {
						cateTemp.push_back(stoi(cword));
					}
					else {
						cout << "오류: 0 혹은 1~" << cateCount << "까지의 자연수를 입력해주세요.\n\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						if (_getch()) {
							system("cls");
							winput = 1;
						}
						break;
					}
				}
				if (winput == 1) {
					flag = 6;
					break;
				}
				sort(cateTemp.begin(), cateTemp.end());
				cateTemp.erase(unique(cateTemp.begin(), cateTemp.end()), cateTemp.end());
				category.clear();
				while (!cateTemp.empty()) {
					int cateTT = cateTemp.back();
					cateTemp.pop_back();

					if (0 == cateTT) {
						key = sche[selectedNum]->getKey();
						category.push_back("기본");
					}

					else if (1 <= cateTT && cateTT <= cateCount) {
						key = sche[selectedNum]->getKey();
						category.push_back(CDM->GetCategory()->at(cateTT - 1));
					}
					
				}
				for (int i = 0; i < cal->allSchs.size(); i++) {
					if (cal->allSchs[i].getKey() == key) {
						cal->allSchs[i].setCategory(category);
					}
				}

				sche[selectedNum]->setCategory(category); // 사용자 지정 카테고리
				SDM.saveDataFile(*cal);	// 데이터 파일에 저장
				SDM.loadDataFile(*cal, *cate);
				CDM->loadDataFile(*cate);
				flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
			}
			else {
				cout << "오류: 0 혹은 1~" << cateCount << "까지의 자연수를 입력해주세요.\n\n";
				cout << "아무 키나 눌러주세요.\n";
				cout << "_____________________________\n";
				cout << "> ";
				if (_getch()) {
					system("cls");
					flag = 6; // 현재 프롬프트 반복
				}
			}
			break;

		case 7:   // 메모 수정 범위 선택 프롬프트 추가
			cout << "<일정 수정>\n\n";
			cout << "메모 수정 범위\n\n";
			cout << "1. 같은 반복 기준에 대해서만 수정\n";
			cout << "2. 모든 반복 기준에 대해서 수정\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "메모를 수정할 일정의 범위를 입력하세요.\n";
			cout << "------------------------------------\n";
			cout << "> ";
			getline(cin, menu);
			system("cls");
			if (menu == "^C") {
				system("cls");
				flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
			}
			else if (menu == "1" || menu == "2") {
				if (menu == "1")
					rptKCheck = true;
				else if (menu == "2")
					rptKCheck = false;
				flag = 8; // 다음 프롬프트(메모 수정 프롬프트)로 이동
			}
			else {
				cout << "오류 : 1, 2 중 하나의 숫자를 입력해주세요.\n\n";
				cout << "아무 키나 눌러주세요.\n";
				cout << "_____________________________\n";
				cout << "> ";
				if (_getch()) {
					system("cls");
					flag = 7; // 현재 프롬프트 반복
				}
			}
			break;

		case 8:
			cout << "<일정 수정>\n\n";
			cout << "메모 입력\n\n";
			cout << "메모 형식:\n";
			cout << "길이가 0 이상이며 한글/영어/숫자와 공백의 조합\n";
			cout << "길이가 1 이상인 경우, 첫 문자와 마지막 문자는 한글/영어/숫자\n";
			cout << "탭, 줄바꿈 사용 불가\n\n";
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
				if ((memo.size() >= 0 && regex_match(wmemo.cbegin(), wmemo.cend(), wideMatch, wrx) &&
					memo[0] != ' ' && memo.back() != ' ') || memo.size() == 0) {
					//if (regex_match(wmemo.cbegin(), wmemo.cend(), wideMatch, wrx) &&
					//	memo[0] != ' ' && memo.back() != ' ') {

					key = sche[selectedNum]->getKey();
					rptK = sche[selectedNum]->getRptK();

					if (rptKCheck) { //rptK값까지 같아야 하는 경우(같은 반복 기준)
						for (int i = 0; i < cal->allSchs.size(); i++) {
							if (cal->allSchs[i].getKey() == key && cal->allSchs[i].getRptK() == rptK) {
								cal->allSchs[i].setMemo(memo);
							}
						}
					}
					else { // key값만 같아도 되는 경우(반복x or 모든 반복 기준)
						for (int i = 0; i < cal->allSchs.size(); i++) {
							if (cal->allSchs[i].getKey() == key) {
								cal->allSchs[i].setMemo(memo);
							}
						}
					}



					sche[selectedNum]->setMemo(memo);
					SDM.saveDataFile(*cal);	// 데이터 파일에 저장
					//SDM.loadDataFile(*cal, *cate);
					CDM->loadDataFile(*cate);
					flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
					//}
						/*
					else {
						system("cls");
						cout << "오류: 메모를 형식에 맞게 입력해주세요.\n\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						_getch();
						flag = 7; // 현재 프롬프트 반복
					}
					*/
				}
				else {
					system("cls");
					cout << "오류: 메모를 형식에 맞게 입력해주세요.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
					flag = 8; // 현재 프롬프트 반복
				}
			}
			break;
		case 9:
			cout << "<일정 수정>\n\n";
			cout << "반복 여부 및 단위 선택\n\n";
			cout << "0. 반복하지 않음\n";
			cout << "1. 매년 \n";
			cout << "2. 매월 \n";
			cout << "3. 매주 \n\n";
			cout << "원하는 반복 단위를 입력하세요.\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, menu);
			system("cls");
			if (menu == "^C") {
				system("cls");
				flag = 2; // 이전 프롬프트 (변경할 요소 선택 프롬프트)
			}
			else if (menu.size() == 1 && is_digit(menu) && stoi(menu) >= 0 && stoi(menu) <= 3) {
				if (stoi(menu) == 0) {
					// stoi(menu) == 0 : 반복되지 않는 일정으로 수정, 혹은 그대로 둠
					//sche[selectedNum]->setCycle(0);
					//sche[selectedNum]->setRptEndDate(sche[selectedNum]->getEndDate());
					//SDM.saveDataFile(*cal);	// 데이터 파일에 저장
					//flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
					startDate = sche[selectedNum]->getStartDate();
					endDate = sche[selectedNum]->getEndDate();
					title = sche[selectedNum]->getTitle();
					category = sche[selectedNum]->getCategory();
					memo = sche[selectedNum]->getMemo();
					key = sche[selectedNum]->getKey();
					Schedule* newDate = nullptr;

					for (int i = 0; i < cal->allSchs.size();) {
						if (cal->allSchs[i].getKey() == key) {
							cal->allSchs.erase(cal->allSchs.begin() + i);
						}
						else {
							i++; //? i= -1 되는 경우를 방지하기 위해 여기로 옮겼습니다!
						}
					}
					newDate = new Schedule(title, startDate, endDate, category, memo, endDate, 0, key, 0);
					cal->allSchs.push_back(*newDate);

					SDM.saveDataFile(*cal);	// 데이터 파일에 저장
					flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
				}
				else if (stoi(menu) == 1)
					flag = 10;
				else if (stoi(menu) == 2)
					flag = 11;
				else if (stoi(menu) == 3)
					flag = 12;
			}
			else {
				system("cls");
				cout << "오류: 0, 1, 2, 3 중 하나의 숫자를 입력해주세요.\n\n";
				cout << "아무 키나 눌러주세요.\n";
				cout << "--------------------------\n";
				cout << ">";
				if (_getch()) {
					system("cls");
					flag = 9; // 현재 프롬프트 반복
					break;
				};
			}
			break;

		case 10: // 년 단위
			backup_flag = 10;
			cout << "<일정 수정>\n\n";
			cout << "년 입력\n\n";
			cout << "반복할 날짜를 형식에 맞게 입력해주세요.\n";
			cout << "(mm/dd, 여러 날짜의 입력은 공백류로 구분합니다.)\n";
			cout << "예: 01/02 10/04 12/31  (매년 1월 2일, 10월 4일, 12월 31일 반복)\n\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n";
			cout << "------------------------------\n";
			cout << ">";

			getline(cin, yRptStr);
			if (yRptStr == "^C") {
				flag = 9;
			}
			else {
				regex re("(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])([ ]+(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01]))*");	// 날짜 문법 형식
				if (!regex_match(yRptStr, re)) {
					system("cls");
					cout << "오류: 반복 날짜를 형식에 맞게 입력해주세요.\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					if (_getch()) {
						system("cls");
						flag = 10; // 현재 프롬프트 반복
						break;
					}
				}
				regex re2("(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])");
				regex re3("02/30|02/31|02/31|04/31|06/31|09/31|11/31");

				// 문법 형식에 맞지 않을 때 -1 반환
				if (regex_match(yRptStr, re)) {
					yRptVec.clear();

					istringstream iss(yRptStr);
					bool isExistDate = true, hasEndDate = false;
					do {
						std::string word;
						iss >> word;
						if (!word.empty()) {
							endDate = sche[selectedNum]->getEndDate();
							if (regex_match(word, re2) && !regex_match(word, re3)) {
								if (word == endDate.substr(5, 5)) {
									hasEndDate = true; // 반복날짜 중에 사용자가 입력한 종료일이 포함되어 있는지
								}
								yRptVec.push_back(word);
							}
							else {
								isExistDate = false; // 반복날짜들이 모두 존재하는 날짜인지
								break;
							}
						}
					} while (iss);

					if (!isExistDate) {
						system("cls");
						cout << "오류: 존재하지 않는 날짜가 포함되어 있습니다.\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						if (_getch()) {
							system("cls");
							flag = 10; // 현재 프롬프트 반복
							break;
						}
					}
					if (!hasEndDate) {
						system("cls");
						cout << "오류: 일정의 '종료일'이 반복 날짜에 포함되어야 합니다.\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						if (_getch()) {
							system("cls");
							flag = 10; // 현재 프롬프트 반복
							break;
						}
					}

					yRptVec.erase(unique(yRptVec.begin(), yRptVec.end()), yRptVec.end()); //중복 제거
					flag = 13; // 반복종료일 입력 프롬프트로 이동
				}
			}
			break;
		case 11: // 월 단위
			backup_flag = 11;
			cout << "<일정 수정>\n\n";
			cout << "월 입력\n\n";
			cout << "반복할 날짜의 숫자만 입력해주세요.\n";
			cout << "(여러 날짜의 입력은 공백류로 구분됩니다.)\n";
			cout << "예 : 1 11 21 (매달 1일, 11일, 21일 반복)\n\n";
			cout << "(^ C 입력 시 이전 화면으로 돌아갑니다)\n";
			cout << "---------------------------\n";
			cout << ">";

			getline(cin, mRptStr);
			if (mRptStr == "^C") {
				system("cls");
				flag = 9;
			}
			else {
				// 00 입력 불가, 01~09 == 1~9
				regex re("(0?[1-9]|[12][0-9]|3[01])([ ]+(0?[1-9]|[12][0-9]|3[01]))*");
				if (regex_match(mRptStr, re)) {
					mRptVec.clear();	// 현재 프롬프트가 재시작되는 경우 고려

					istringstream iss(mRptStr);
					string word;
					while (getline(iss, word, ' ')) {
						mRptVec.push_back(stoi(word));
					}
					sort(mRptVec.begin(), mRptVec.end());
					mRptVec.erase(unique(mRptVec.begin(), mRptVec.end()), mRptVec.end());

					vector<int>::iterator ptr;
					bool isExistDate = true;
					for (ptr = mRptVec.begin(); ptr != mRptVec.end(); ++ptr) {
						if (*ptr > 31) {
							isExistDate = false;
							break;
						}
					}
					if (!isExistDate) {
						system("cls");
						cout << "오류: 공백류로 구분되는 \"1부터 31까지의 자연수 숫자\" 1개 이상을 입력해주셔야 합니다.\n\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						_getch();
						break;
					}

					endDate = sche[selectedNum]->getEndDate();
					bool hasEndDate = false;
					int ed = stoi(endDate.substr(8, 2));
					for (ptr = mRptVec.begin(); ptr != mRptVec.end(); ++ptr) {
						if (*ptr == ed) {
							hasEndDate = true;
							break;
						}
					}
					if (!hasEndDate) {
						system("cls");
						cout << "오류: 일정의 '종료일'이 반복 날짜에 포함되어야 합니다.\n\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						_getch();
						break;
					}

					flag = 13;
				}
				else {
					system("cls");
					cout << "오류: 반복할 날짜를 형식에 맞게 입력해주세요.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
				}
			}
			break;
		case 12: // 주 단위
			backup_flag = 12;
			cout << "<일정 수정>\n\n";
			cout << "주 입력\n\n";
			cout << "1. 일\n";
			cout << "2. 월\n";
			cout << "3. 화\n";
			cout << "4. 수\n";
			cout << "5. 목\n";
			cout << "6. 금\n";
			cout << "7. 토\n\n";
			cout << "반복할 요일의 번호를 입력하세요.\n";
			cout << "(여러 요일의 입력은 공백류로 구분합니다.)\n";
			cout << "예 : 1 2 3\n\n";
			cout << "(^ C 입력 시 이전 화면으로 돌아갑니다)\n";
			cout << "---------------------------\n";
			cout << ">";

			getline(cin, wRptStr);
			if (wRptStr == "^C") {
				flag = 9;
			}
			else {
				regex re("[1-7]([ ]+[1-7])*");
				if (regex_match(wRptStr, re)) {
					wRptVec.clear();	// 현재 프롬프트가 재시작되는 경우 고려

					istringstream iss(wRptStr);
					string word;
					while (getline(iss, word, ' ')) {
						wRptVec.push_back(stoi(word));
					}
					sort(wRptVec.begin(), wRptVec.end());
					wRptVec.erase(unique(wRptVec.begin(), wRptVec.end()), wRptVec.end());

					bool hasEndDate = false;
					endDate = sche[selectedNum]->getEndDate();
					int y = stoi(endDate.substr(0, 4));
					int m = stoi(endDate.substr(5, 2));
					int d = stoi(endDate.substr(8, 2));
					int edWhatday = zeller(y, m, d);	// 종료일이 무슨 요일인지

					vector<int>::iterator ptr;
					for (ptr = wRptVec.begin(); ptr != wRptVec.end(); ++ptr) {
						if (*ptr == edWhatday) {
							hasEndDate = true;
							break;
						}
					}
					if (!hasEndDate) {
						system("cls");
						cout << "오류: 일정의 '종료일'이 반복 날짜에 포함되어야 합니다.\n\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						_getch();
						break;
					}
					flag = 13;
				}
				else {
					system("cls");
					cout << "오류: 공백류로 구분되는 \"1부터 7까지의 자연수 숫자\" 1개 이상을 입력해주셔야 합니다.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
				}
			}
			break;
		case 13: // 반복 종료일
			cout << "<일정 수정>\n\n";
			cout << "반복 종료일 입력\n\n";
			cout << "반복 종료일을 입력해주세요.\n\n";
			cout << "반복 종료일 입력 형식 : yyyy/mm/dd\n";
			cout << "(지정하지 않을 경우 -1 을 입력해주세요.)\n\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n";
			cout << "------------------------------------\n";
			cout << "> ";

			getline(cin, rptEndDate);
			if (rptEndDate == "^C") {
				flag = 9;
			}
			else {
				if (rptEndDate == "-1") {
					rptEndDate = to_string(FINAL_YEAR) + "/12/31";
					sche[selectedNum]->setCycle(backup_flag - 9);
					sche[selectedNum]->setRptEndDate(rptEndDate);
					SDM.saveDataFile(*cal);	// 데이터 파일에 저장
				}

				switch (cal->isValidDate(rptEndDate)) {
				case 0:
					// 종료일보다 반복종료일이 빠른 경우 
					int y1, m1, d1, y2, m2, d2;
					y1 = stoi(endDate.substr(0, 4));
					m1 = stoi(endDate.substr(5, 2));
					d1 = stoi(endDate.substr(8, 2));
					y2 = stoi(rptEndDate.substr(0, 4));
					m2 = stoi(rptEndDate.substr(5, 2));
					d2 = stoi(rptEndDate.substr(8, 2));

					if ((y1 > y2) || ((y1 == y2) && (m1 > m2))
						|| ((y1 == y2) && (m1 == m2) && (d1 > d2))) {
						system("cls");
						cout << "오류: 반복 종료일은 일정의 종료일과 같거나, 그 이후여야 합니다.\n\n";
						cout << "아무 키나 눌러주세요.\n";
						cout << "_____________________________\n";
						cout << "> ";
						_getch();
						flag = 13;
					}
					else {
						// 수정된 일정 
						cycle = backup_flag - 9;
						startDate = sche[selectedNum]->getStartDate();
						endDate = sche[selectedNum]->getEndDate();
						title = sche[selectedNum]->getTitle();
						category = sche[selectedNum]->getCategory();
						memo = sche[selectedNum]->getMemo();
						key = sche[selectedNum]->getKey();
						//rptK = sche[selectedNum]->getRptK(); // ???
						int diffDate = 0;
						Schedule* newDate = nullptr;

						for (int i = 0; i < cal->allSchs.size();) {
							if (cal->allSchs[i].getKey() == key) {
								cal->allSchs.erase(cal->allSchs.begin() + i);
							}
							else {
								i++; //? i= -1 되는 경우를 방지하기 위해 여기로 옮겼습니다!
							}
						}

						string subEndDate;

						switch (cycle) {
							/*
							case 0:	// 반복 x
								newDate = new Schedule(title, startDate, endDate, category, memo, endDate, cycle, cal->getHighestKey() + 1);
								cal->allSchs.push_back(*newDate);	// 데이터 파일에 해당 스케줄 추가
								break;
							*/
						case 1:	// 매년 반복
							// 1. startDate와 endDate의 날짜 차이를 알아야 함.
							// 2. yRptVec에서 종료일(10/04)을 꺼내와서 해당 날짜 차이를 가지고 시작일을 알아냄
							// 3. 알아낸 시작일과 yRptVec에서 꺼낸 종료일을 가지고 새로운 스케줄 객체 생성
							// 4. 2와 3을 yRptVec의 모든 객체에 대하여 반복
							diffDate = getDiffDate(startDate, endDate);

							subEndDate = endDate.substr(5, 5);

							for (int i = 0; i < yRptVec.size(); i++) {
								if (yRptVec[i] == subEndDate) {
									rptK = i;
								}

								int m1, d1, m2, d2;
								m1 = stoi(endDate.substr(5, 2));
								d1 = stoi(endDate.substr(8, 2));
								m2 = stoi(yRptVec[i].substr(0, 2));
								d2 = stoi(yRptVec[i].substr(3, 2));

								int endDateYear = stoi(endDate.substr(0, 4));
								if ((m1 > m2) || ((m1 == m2) && (d1 > d2))) {	// endDate가 yRptVect보다 뒤에 있는 경우
									endDateYear++;
								}
								string anotherEndDate = to_string(endDateYear) + "/" + yRptVec[i];
								while (endDateYear <= FINAL_YEAR && cal->isValidDate(anotherEndDate)) {	// 2월 29일이 있는 연도까지 반복
									string possibleEndDate = anotherEndDate.substr(0, 8) + "28";
									if (!isPreviousDate(possibleEndDate, rptEndDate)) {
										anotherEndDate = possibleEndDate;
										break;
									}
									string possibleStartDate = calcStartDate(possibleEndDate, diffDate);
									newDate = new Schedule(title, possibleStartDate, possibleEndDate, category, memo, possibleEndDate, 0, key, i + 1);   //기존 key 값 유지
									cal->allSchs.push_back(*newDate);	// 데이터 파일에 해당 스케줄 추가
									endDateYear++;
									anotherEndDate = to_string(endDateYear) + "/" + yRptVec[i];
								}
								if (endDateYear <= FINAL_YEAR && isPreviousDate(anotherEndDate, rptEndDate)) {	// 2월 29일이 있는 연도인 경우
									string anotherStartDate = calcStartDate(anotherEndDate, diffDate);
									newDate = new Schedule(title, anotherStartDate, anotherEndDate, category, memo, rptEndDate, cycle, key, i + 1);   //기존 key 값 유지
									cal->allSchs.push_back(*newDate);	// 데이터 파일에 해당 스케줄 추가
								}
							}
							break;
						case 2:	// 매월 반복
							// 1. startDate와 endDate의 날짜 차이를 알아야 함.
							// 2. mRptVec에서 종료일(11)을 꺼내와서 해당 날짜 차이를 가지고 시작일을 알아냄
							// 3. 알아낸 시작일과 mRptVec에서 꺼낸 종료일을 가지고 새로운 스케줄 객체 생성
							// 4. 2와 3을 mRptVec의 모든 객체에 대하여 반복
							diffDate = getDiffDate(startDate, endDate);

							subEndDate = endDate.substr(8, 2);

							for (int i = 0; i < mRptVec.size(); i++) {
								if (mRptVec[i] == stoi(subEndDate)) {
									rptK = i;
								}

								int d1, d2;
								d1 = stoi(endDate.substr(8, 2));
								d2 = mRptVec[i];

								int endDateYear = stoi(endDate.substr(0, 4));
								int endDateMonth = stoi(endDate.substr(5, 2));
								if (d1 > d2) {	// endDate가 yRptVect보다 뒤에 있는 경우
									if (++endDateMonth > 12) {
										endDateYear++;
										endDateMonth -= 12;
									}
								}

								string eDMString = (endDateMonth < 10) ? "0" + to_string(endDateMonth) : to_string(endDateMonth);
								string eDDString = (mRptVec[i] < 10) ? "0" + to_string(mRptVec[i]) : to_string(mRptVec[i]);
								string anotherEndDate = to_string(endDateYear) + "/" + eDMString + "/" + eDDString;
								while (endDateYear <= FINAL_YEAR && cal->isValidDate(anotherEndDate)) {	// 해당 날짜가 있는 달이 나오기 전까지
									string possibleEndDate = anotherEndDate.substr(0, 8) + to_string(findLastDayofMonth(endDateYear, endDateMonth));
									if (!isPreviousDate(possibleEndDate, rptEndDate)) {
										anotherEndDate = possibleEndDate;
										break;
									}
									string possibleStartDate = calcStartDate(possibleEndDate, diffDate);
									newDate = new Schedule(title, possibleStartDate, possibleEndDate, category, memo, possibleEndDate, 0, key, i + 1);		//왜 cycle 0
									cal->allSchs.push_back(*newDate);	// 데이터 파일에 해당 스케줄 추가
									if (++endDateMonth > 12) {
										endDateYear++;
										endDateMonth -= 12;
									}
									eDMString = (endDateMonth < 10) ? "0" + to_string(endDateMonth) : to_string(endDateMonth);
									anotherEndDate = to_string(endDateYear) + "/" + eDMString + "/" + eDDString;
								}
								if (endDateYear <= FINAL_YEAR && isPreviousDate(anotherEndDate, rptEndDate)) {	// 해당 날짜가 있는 달인 경우
									string anotherStartDate = calcStartDate(anotherEndDate, diffDate);
									newDate = new Schedule(title, anotherStartDate, anotherEndDate, category, memo, rptEndDate, cycle, key, i + 1);   //기존 key 값 유지
									cal->allSchs.push_back(*newDate);	// 데이터 파일에 해당 스케줄 추가
								}
							}
							break;
						case 3:	// 매주 반복
							// 1. startDate와 endDate의 날짜 차이를 알아야 함.
							// 2. wRptVec에서 종료일(5)을 꺼내와서 해당 날짜 차이를 가지고 시작일을 알아냄
							// 3. 알아낸 시작일과 wRptVec에서 꺼낸 종료일을 가지고 새로운 스케줄 객체 생성
							// 4. 2와 3을 wRptVec의 모든 객체에 대하여 반복
							diffDate = getDiffDate(startDate, endDate);

							for (int i = 0; i < wRptVec.size(); i++) {
								int endDateYear = stoi(endDate.substr(0, 4));
								int endDateMonth = stoi(endDate.substr(5, 2));
								int endDateDay = stoi(endDate.substr(8, 2));
								int edWhatday = zeller(endDateYear, endDateMonth, endDateDay);

								if (edWhatday == wRptVec[i]) {
									rptK = i;
								}

								int anotherEndDateDay, extraDay;

								anotherEndDateDay = endDateDay + ((7 - (edWhatday - wRptVec[i])) % 7);
								if ((extraDay = (anotherEndDateDay - findLastDayofMonth(endDateYear, endDateMonth))) > 0) {	// 해당 달을 넘어서는 날짜인 경우
									if (++endDateMonth > 12) {
										endDateYear++;
										endDateMonth -= 12;
									}
									anotherEndDateDay = extraDay;
								}

								string eDMString = (endDateMonth < 10) ? "0" + to_string(endDateMonth) : to_string(endDateMonth);
								string eDDString = (anotherEndDateDay < 10) ? "0" + to_string(anotherEndDateDay) : to_string(anotherEndDateDay);
								string anotherEndDate = to_string(endDateYear) + "/" + eDMString + "/" + eDDString;
								if (endDateYear <= FINAL_YEAR && isPreviousDate(anotherEndDate, rptEndDate)) {
									string anotherStartDate = calcStartDate(anotherEndDate, diffDate);
									newDate = new Schedule(title, anotherStartDate, anotherEndDate, category, memo, rptEndDate, cycle, key, i + 1); //기존 key 값 유지
									cal->allSchs.push_back(*newDate);	// 데이터 파일에 해당 스케줄 추가
								}
							}
							break;
						}

						SDM.saveDataFile(*cal);	// 데이터 파일에 저장
						SDM.loadDataFile(*cal, *cate);
						CDM->loadDataFile(*cate);
						newDate = new Schedule(title, startDate, endDate, category, memo, rptEndDate, cycle, key, rptK);
						sche.insert(sche.begin() + selectedNum, newDate);
						flag = 2; // 이전 프롬프트(수정할 요소 선택 프롬프트)로 이동
					}
					break;
				case -1:
					system("cls");
					cout << "오류: 시작일의 날짜를 형식에 맞게 입력해주세요.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
					flag = 13;
					break;
				case -2:
					system("cls");
					cout << "오류: " << rptEndDate << "(은)는 존재하지 않는 날짜입니다.\n\n";
					cout << "아무 키나 눌러주세요.\n";
					cout << "_____________________________\n";
					cout << "> ";
					_getch();
					flag = 13;
					break;
				}
			}
			break;
		case 14:
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
				flag = 0; // 일정 선택 프롬프트로 이동
				system("cls");
			}
			else if (menu.size() == 1 && is_digit(menu) && stoi(menu) >= 1 && stoi(menu) <= 2) {
				/*
				if (is_digit(menu) && stoi(menu) == 1) {
					cal->allSchs.erase(cal->allSchs.begin() + scheNum[selectedNum]);
					SDM.saveDataFile(*cal);	// 데이터 파일에 저장
					flag = 0; // 일정 선택 프롬프트로 이동
				}
				*/
				if (stoi(menu) == 1) {
					if (cal->cycle_per_keys[sche[selectedNum]->getKey()] == 0) {
						cal->allSchs.erase(cal->allSchs.begin() + scheNum[selectedNum]);
						SDM.saveDataFile(*cal);	// 데이터 파일에 저장
						system("cls");
						flag = 0; // 일정 선택 프롬프트로 이동
					}
					else {
						system("cls");
						flag = 15;
					}
				}
				else if (stoi(menu) == 2) {
					flag = 0; // 일정 선택 프롬프트로 이동
				}
			}
			else {
				system("cls");
				cout << "오류: 1,2 중 하나의 숫자를 입력해주세요.\n\n";
				cout << "아무 키나 눌러주세요.\n";
				cout << "--------------------------------------\n";
				cout << ">";
				if (_getch()) {
					system("cls");
					flag = 14; // 현재 프롬프트 반복
				}
			}
			break;
		case 15:
			cout << "<일정 삭제>\n\n";
			cout << "제목 : " << sche[selectedNum]->getTitle() << "\n\n";

			cout << "해당 일정은 "; //? (반복 단위)는 cycle 에 따라서 아래 처럼 표시됩니다!
			switch (cal->cycle_per_keys[sche[selectedNum]->getKey()]) {
			case 1: cout << "년 단위"; break;
			case 2: cout << "월 단위"; break;
			case 3: cout << "주 단위"; break;
			}
			cout << "로 반복되는 일정입니다.\n";

			cout << "삭제할 경우 반복되는 일정 전체가 삭제됩니다.\n";
			cout << "삭제하시겠습니까?\n\n";
			cout << "(^C 입력 시 이전 화면으로 돌아갑니다)\n\n";
			cout << "1. 예\n";
			cout << "2. 아니요\n";
			cout << "------------------------------------\n";
			cout << "> ";
			getline(cin, menu);
			system("cls");
			if (menu == "^C") {
				flag = 14; // 일정 삭제 확인 프롬프트로 이동
				system("cls");
			}
			else if (menu.size() == 1 && is_digit(menu) && stoi(menu) >= 1 && stoi(menu) <= 2) {
				if (stoi(menu) == 1) {
					key = sche[selectedNum]->getKey();

					for (int i = 0; i < cal->allSchs.size();) {
						if (cal->allSchs[i].getKey() == key) {
							cal->allSchs.erase(cal->allSchs.begin() + i);
						}
						else {
							i++; //? i= -1 되는 경우를 방지하기 위해 여기로 옮겼습니다!
						}
					}

					SDM.saveDataFile(*cal);	// 데이터 파일에 저장
					cal->cycle_per_keys.erase(key);
					system("cls");
					flag = 0;
				}
				else if (stoi(menu) == 2) {
					system("cls");
					flag = 0; // 일정 선택 프롬프트로 이동
				}
			}
			else {
				system("cls");
				cout << "오류: 1,2 중 하나의 숫자를 입력해주세요.\n\n";
				cout << "아무 키나 눌러주세요.\n";
				cout << "--------------------------------------\n";
				cout << ">";
				if (_getch()) {
					system("cls");
					flag = 15; // 현재 프롬프트 반복
				}
			}
			break;
		}
	}
	SDM.loadDataFile(*cal, *cate);
}
