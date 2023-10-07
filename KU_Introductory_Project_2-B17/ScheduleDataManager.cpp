#include "ScheduleDataManager.h"

bool ScheduleDataManager::loadDataFile(Calender& c)
{
    string fileName = "testSch.txt";
    wifstream file;

    //setting locale handling UTF-8
    file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));
    wcout.imbue(locale(""));

    file.open(fileName);

    if (!file) {
        //파일이 존재하지 않음
        cout << "경고: 데이터 파일이 존재하지 않습니다. 빈 데이터 파일을 생성합니다.\n";
        ofstream fout;
        fout.open(fileName);
        if (!fout.is_open()) {
            cout << "오류: 데이터 파일 생성을 실패하였습니다. 프로그램을 종료합니다.\n";
            return false; //false가 리턴되면 프로그램이 종료되도록
        }
        else {
            fout.close();
            return true;
        }
    }

    //파일이 존재하는 경우
    vector<string> record;
    wstring line;
    int idx = 0;
    while (getline(file, line)) {
        wstringstream ss(line);
        //wcout << line << " "; //OK
        //wcout << ss.str() << " "; //OK
        wstring token;
        while (getline(ss, token, L'\t')) {
            //wcout << token;
            string temptkn;
            temptkn = ws2s(token);
            trim(temptkn); // tkn의 앞 뒤 공백 제거
            cout << temptkn;
            if (!temptkn.empty()) record.push_back(temptkn); //연속된 tab 무시
        }
        if (record.size() != 5 || !isRight(record)) {
            cout << record.size(); //test
            cerr << "오류: 데이터 파일의 형식이 잘못되었습니다. 프로그램을 종료합니다.\n";
            return false;
        }
        //title, sd, ed, cate, memo 순서
        Schedule s(record[0], record[2], record[3], record[1], record[4]);
        c.allSchs.push_back(s);
        record.clear();
    }
    file.close();
    return true;
}

bool ScheduleDataManager::saveDataFile(Calender& c)
{
    //이 함수를 호출하기 전 일정 추가 프롬프트에서 모든 문법 검사를 마치기 때문에 따로 검사를 하지 않습니다
    string fileName = "testSch.txt";
    wofstream file;

    file.open(fileName, ios::app);
    file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));

    for (Schedule s : c.allSchs) {
        wstring t = s2ws(s.getTitle());
        wstring c = s2ws(s.getCategory());
        wstring sD = s2ws(s.getStartDate());
        wstring eD = s2ws(s.getEndDate());
        wstring m = s2ws(s.getMemo());
        file << t << L"\t" << c << L"\t" << sD << L"\t" << eD << L"\t" << m << L"\n";
        //string s = "감자\t감자\t2022/12/12\t2022/12/12\tㅋㅋㅋ\n";
        //wstring ws = s2ws(s);
        //file << ws;
    }

    file.close();

    if (file.fail()) {
        cerr << "파일 저장에 실패했습니다.";
        return false;
    }

    return true;
}

wstring ScheduleDataManager::s2ws(const string& str)
{
    static std::locale loc("");
    auto& facet = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);
    return std::wstring_convert<std::remove_reference<decltype(facet)>::type, wchar_t>(&facet).from_bytes(str);
}

string ScheduleDataManager::ws2s(const wstring& wstr) {
    static std::locale loc("");
    auto& facet = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);
    return std::wstring_convert<std::remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(wstr);
}

void ScheduleDataManager::trim(string& str) {
    int npos;
    //left
    npos = str.find_first_not_of(' ');
    str.erase(0, npos);
    //right
    npos = str.find_last_not_of(' ');
    str.erase(npos + 1);
}

bool ScheduleDataManager::isRight(vector<string> record)
{
    bool c1, c2, c3, c4, c5;
    try
    {
        c1 = checkT(record[0]);
        c2 = checkC(record[1]);
        c3 = checkD(record[2]);
        c4 = checkD(record[3]);
        c5 = checkM(record[4]);
    }
    catch (const exception& e)
    {
        //nullpointerException
        return false;
    }
    return (c1 && c2 && c3 && c4 && c5);
}

bool ScheduleDataManager::checkT(string data)
{
    if(data.length() <= 0 || data.length() > 30)
        return false;
    return true;
}

bool ScheduleDataManager::checkC(string data)
{
    /*카테고리 규칙*/
    return true;
}

bool ScheduleDataManager::checkD(string s)
{
    string y, m, d; // 각각 year, month, date{
    regex re("[0-9]{4}/[0-9]{2}/[0-9]{2}");	// 날짜 문법 형식

    if (regex_match(s, re)) {
        y = s.substr(0, 4);
        m = s.substr(5, 2);
        d = s.substr(8, 2);

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
        else {
            return false;
        }
    }
    cout << "날짜 o";
    return false;
}

bool ScheduleDataManager::checkM(string data)
{
    /*메모 체크...*/
    return true;
}
