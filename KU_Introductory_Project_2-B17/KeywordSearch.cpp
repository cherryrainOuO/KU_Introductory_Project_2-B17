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

    for (Schedule s : cal.allSchs) {
        string title = s.getTitle();
        string memo = s.getMemo();
        removeSpace(title);
        removeSpace(memo);

        if (title.find(tempKey) != string::npos || memo.find(tempKey) != string::npos)
            res.push_back(s);
    }
    print();
}

void KeywordSearch::print()
{
    system("cls");
    cout << "키워드 \"" << kwd << "\"(으)로 검색한 결과입니다.\n";
    cout << "---------------------------------------------\n";
    if (res.empty())
        cout << "해당 키워드를 포함하고 있는 일정이 없습니다.\n";
    else {
        for (Schedule s : res) {
            s.print();
            cout << "\n";
        }
        cout << "---------------------------------------------\n";
    }
    cout << "(*메인 화면으로 돌아가려면 아무 키나 입력하세요.)\n";
    Sleep(100);
    _getch();
}

void KeywordSearch::removeSpace(string& s)
{
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
}

