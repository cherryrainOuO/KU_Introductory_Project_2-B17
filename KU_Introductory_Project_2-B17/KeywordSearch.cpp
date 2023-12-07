#include "KeywordSearch.h"

void KeywordSearch::prompt()
{
    int res = -1;
    while (res < 0) {
        try
        {
            system("cls");
            cout << "검색어 입력 (^C 입력 시 이전 화면으로 돌아갑니다): ";
            getline(cin, kwd);
            res = isKeyRight();
        }
        catch (exception& e)
        {
            system("cls");
            cout << "[오류] " << e.what() << "\n(*아무 키 입력 시 이전 화면으로 돌아갑니다.)";
            Sleep(100);
            _getch();
        }
    }

    if (res == 0) return; //주 프롬프트로 복귀
    if (res == 1) search();
}

int KeywordSearch::isKeyRight()
{
    regex re("[\\^\\n\\t]"); 

    if (kwd.empty() || kwd.find_first_not_of(' ') == string::npos) {
        exception e("검색 시 한 글자 이상 입력되어야 합니다.");
        throw e;
    }
    if (kwd.compare("^C") == 0 || kwd.compare("^c") == 0)
        return 0;
    else if (regex_search(kwd, re)) {
        exception e("^, [tab], [Enter]는 포함될 수 없습니다.");
        throw e;
    }
    else
        return 1;
}

void KeywordSearch::search()
{
    string tempKey = kwd;
    removeSpace(tempKey);

    sort(cal->allSchs.begin(), cal->allSchs.end());

    for (Schedule s : cal->allSchs) {
        string title = s.getTitle();
        string memo = s.getMemo();
        removeSpace(title);
        removeSpace(memo);

        if (title.find(tempKey) != string::npos || memo.find(tempKey) != string::npos)
            res.push(s);
    }
    print();
}

void KeywordSearch::print()
{
	system("cls");
	/*cout << "키워드 \"" << kwd << "\"(으)로 검색한 결과입니다.\n";
	cout << "---------------------------------------------\n";
	if (res.empty())
		cout << "해당 키워드를 포함하고 있는 일정이 없습니다.\n";
	else {
		while (!res.empty()) {
			res.front().print();
			res.pop();
		}
		cout << "---------------------------------------------\n";
	}*/
	Prompt_after_or_before_When(kwd);
	cout << "(*메인 화면으로 돌아가려면 아무 키나 입력하세요.)\n";
	Sleep(100);
	_getch();
}



void KeywordSearch::removeSpace(string& s)
{
	s.erase(remove(s.begin(), s.end(), ' '), s.end());
}


void KeywordSearch::Prompt_after_or_before_When(string kwd) {

	cout << "키워드 \"" << kwd << "\"(으)로 검색되는 일정 중\n";
	cout << "\"언제 이후만\" 과 \"언제 이전만\" 이 출력 되기를 원하신다면\n";
	cout << "해당하는 날짜를 공백 하나로 구분하여 입력해주세요.\n";
	cout << "원하지 않으신다면 각각 \'x\'를 입력해주세요.\n\n";

	cout << "입력 형식: yyyy/mm/dd yyyy/mm/dd\n\n";

	cout << "예 : 2010/01/01 2023/12/31  (2010/01/01 ~ 2023/12/31에 해당하는 일정 출력)\n";
	cout << "     2010/01/01 x           (2010/01/01 이후에 해당하는 일정 출력)\n";
	cout << "     x 2023/12/31           (2023/12/31 이전에 해당하는 일정 출력) \n";
	cout << "     x x                    (모든 일정 출력)\n\n";

	cout << "(^C 입력 시 이전 화면으로 돌아갑니다.)\n";
	cout << "----------------------------------------------\n";
	cout << "> ";

	string whendates;
	vector<string> dates;
	string afterDate, beforeDate;
	regex datesform(R"(\S+\s+\S+)");

	getline(cin, whendates);

	system("cls");
	if (whendates == "^C") {
		system("cls");
		prompt();
	}

	else if (regex_match(whendates, datesform)) {
		dates = split_by_space(whendates, ' ');
		afterDate = dates[0];
		beforeDate = dates[1];

		if (afterDate == "x")
			afterDate = "2000/01/01";
		if (beforeDate == "x")
			beforeDate = "2030/12/31";

		int y1, m1, d1, y2, m2, d2;
		bool b = true; // afterDate < beforeDate
		if (afterDate.length() == 10 && beforeDate.length() == 10) {
			y1 = stoi(afterDate.substr(0, 4));
			m1 = stoi(afterDate.substr(5, 2));
			d1 = stoi(afterDate.substr(8, 2));
			y2 = stoi(beforeDate.substr(0, 4));
			m2 = stoi(beforeDate.substr(5, 2));
			d2 = stoi(beforeDate.substr(8, 2));

			if ((y1 > y2) || ((y1 == y2) && (m1 > m2))
				|| ((y1 == y2) && (m1 == m2) && (d1 > d2)))
				b = false;
		}

		if ((cal->isValidDate(afterDate) == -1) || (cal->isValidDate(beforeDate) == -1)) {
			system("cls");
			cout << "오류: 입력 형식에 맞게 입력해주세요.\n";
			cout << "아무 키나 눌러주세요.\n";
			cout << "_____________________________\n";
			cout << "> ";
			if (_getch()) {
				system("cls");
				return;
				// Prompt_after_or_before_When(res, cateKwd);
			}
		}
		else if ((cal->isValidDate(afterDate) == -2) || (cal->isValidDate(beforeDate) == -2)) {
			system("cls");
			cout << "오류: 존재하지 않는 날짜가 포함되어 있습니다.\n";
			cout << "아무 키나 눌러주세요.\n";
			cout << "_____________________________\n";
			cout << "> ";
			if (_getch()) {
				system("cls");
				return;
				// Prompt_after_or_before_When(res, cateKwd);
			}
		}
		else if (b == false) {
			system("cls");
			cout << "오류: \"언제 이전만\"의 날짜가 \"언제 이후만\"의 날짜보다 앞서,\n      기간이 존재하지 않습니다.\n";
			cout << "아무 키나 눌러주세요.\n";
			cout << "_____________________________\n";
			cout << "> ";
			if (_getch()) {
				system("cls");
				return;
				// Prompt_after_or_before_When(res, cateKwd);
			}
		}
		else {
			// res는 size가 계속 변동됨
			int s = res.size();		
			for (int i = 0; i < s; i++) {
				if (res.front().getEndDate() >= afterDate
					&& res.front().getEndDate() <= beforeDate) {
					res.push(res.front());
				}
				res.pop();
			}
		}
	}
	else {
		system("cls");
		cout << "오류: 입력 형식에 맞게 입력해주세요.\n";
		cout << "아무 키나 눌러주세요.\n";
		cout << "_____________________________\n";
		cout << "> ";
		if (_getch()) {
			system("cls");
			Prompt_after_or_before_When(kwd);
			//return;
		}
	}
	if (res.empty())
		cout << "\"" << kwd << "\" 키워드로 검색되는 일정 중 " << afterDate << " ~ " << beforeDate << " 날짜에 해당하는 일정이 없습니다.\n\n";
	else {
		cout << "키워드 \"" << kwd << "\"에 해당되는 일정들입니다.\n";
		cout << afterDate << " ~ " << beforeDate << "\n\n";

		while (!res.empty()) {
			res.front().print();
			res.pop();
		}
	}
	while (!res.empty()) {
		res.pop();
	}
	cout << "아무 키나 눌러주세요.\n";
	cout << "_____________________________\n";
	cout << "> ";
	if (_getch()) {
		system("cls");
		return;
	}
}

vector<string> KeywordSearch::split_by_space(string str, char del) {
	istringstream iss(str);
	string buf;
	vector<string> result;

	while (getline(iss, buf, del))
		result.push_back(buf);

	return result;
}

