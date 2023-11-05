#include "ScheduleDataManager.h"

bool ScheduleDataManager::loadDataFile(Calender& c, Category& cat)
{
    string fileName = "Calendar-schedule.txt";
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
            cout << "오류: 데이터 파일 생성을 실패하였습니다. 프로그램을 종료합니다.\n\n";
            cout << "아무 키나 눌러주세요.\n";
            cout << "-------------------------------------\n";
            cout << "> ";

            _getch(); // 아무 키나 입력 대기

            exit(0);

            return false; //false가 리턴되면 프로그램이 종료되도록
        }
        else {
            fout.close();
            cout << "파일 생성 성공\n";
            Sleep(1000);

            return true;
        }
    }

    //파일이 존재하는 경우
    c.allSchs.clear(); //일정 생성 전 벡터 초기화
    vector<string>* categories = cat.GetCategories();
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
            //cout << temptkn;
            if (!temptkn.empty()) record.push_back(temptkn); //연속된 tab 무시
        }
        //메모가 비워진 경우 4번 인덱스에 빈 문자열 삽입
        if (record.size() == SIZE - 1) record.insert(record.begin() + 4, "");

        if (record.size() != SIZE || !isRight(record, categories)) {
            //cout << record.size(); //test
            cerr << "오류: 데이터 파일의 형식이 잘못되었습니다.\n";
            cout << "---------------------------------------------------------------------------------------\n";
            cout << ws2s(line) << "\n";
            cout << "---------------------------------------------------------------------------------------\n프로그램을 종료합니다.\n";
            return false;
        }

        //title, sd, ed, cate, memo, rED, cy, k 순서
        string ti = record[0];
        string sd = record[2];
        string ed = record[3];
        string cat = record[1];
        string me = record[4];
        string rED = record[5];
        int cy = stoi(record[6]);
        int k = stoi(record[7]);

        Schedule s(ti, sd, ed, cat, me, rED, cy, k);

        if (!checkCont(s)) {
            cerr << "오류: 데이터 파일의 형식이 잘못되었습니다.\n";
            cout << "---------------------------------------------------------------------------------------\n";
            cout << ws2s(line) << "\n";
            cout << "---------------------------------------------------------------------------------------\n프로그램을 종료합니다.\n";
            return false;
        }
        dupKeySches[k] = s; //키가 중복될 때 검사하기 위해

        int period = calcPeriod(sd, ed); //일정의 기간

        //반복 종료일까지 추가

        if (cy >= 1) {
            int endday = stoi(ed.substr(8, 2));
            while (checkD2(ed, rED)) {
                Schedule s(ti, sd, ed, cat, me, rED, cy, k);
                c.allSchs.push_back(s);
                ed = addDate(ed, cy, endday);
                sd = calcSD(ed, period);
            }
        }
        else {
            Schedule s(ti, sd, ed, cat, me, rED, cy, k);
            c.allSchs.push_back(s);
        }

        record.clear();
    }
    dupKeySches.clear();
    file.close();
    return true;
}

bool ScheduleDataManager::saveDataFile(Calender& c)
{
    //이 함수를 호출하기 전 일정 추가 프롬프트에서 모든 문법 검사를 마치기 때문에 따로 검사를 하지 않습니다
    
    sort(c.allSchs.begin(), c.allSchs.end());//일정 시작일 순으로 정렬 필요

    string fileName = "Calendar-schedule.txt";
    wofstream file;

    file.open(fileName, ios::out);
    file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));

    map<int, Schedule> prev;

    for (Schedule s : c.allSchs) {

        int key = s.getKey();
        if (dupKeySches.find(key) != dupKeySches.end()) {
            Schedule prevS = prev[key];
            Schedule first = dupKeySches[key];
            string standard = addDate(first.getEndDate(), first.getCycle(), 0);
            standard = calcSD(standard, 1);
            
            if (s.getCycle() == 1) {
                //매년
                int em1 = stoi(prevS.getEndDate().substr(5, 2)), em2 = stoi(s.getEndDate().substr(5, 2));
                int ed1 = stoi(prevS.getEndDate().substr(8, 2)), ed2 = stoi(s.getEndDate().substr(8, 2));
                if (!checkD2(s.getEndDate(), standard) && ed1 - ed2 >= 0) continue;
                else if (ed1 - ed2 < 0) {
                    prev[key] = s;
                }
            }
            else if (s.getCycle() == 2) {
                //매월
                int ed1 = stoi(prevS.getEndDate().substr(8, 2)), ed2 = stoi(s.getEndDate().substr(8, 2));
                if (ed1 - ed2 >= 0 && !checkD2(s.getEndDate(), standard))
                    continue;
                else
                    prev[key] = s;
            }
            else if (s.getCycle() == 3) {
                //매주: key 값이 같은 경우 해당 일정의 종료일이 가장 빠른 종료일에서 주기 내에 존재하는 경우에만 파일에 추가
                if (!checkD2(s.getEndDate(), standard))
                    continue;
            }
        }
        else {
            dupKeySches[key] = s;
            prev[key] = s;
        }
        c.setHighestKey();

        wstring t = s2ws(s.getTitle());
        wstring c = s2ws(s.getCategory());
        wstring sD = s2ws(s.getStartDate());
        wstring eD = s2ws(s.getEndDate());
        wstring m = s2ws(s.getMemo());
        wstring rED = s2ws(s.getRptEndDate());
        wstring cy = s2ws(to_string(s.getCycle()));
        wstring k = s2ws(to_string(s.getKey()));
        
        file << t << L"\t" << c << L"\t" << sD << L"\t" << eD << L"\t" << m << L"\t" << rED << L"\t" << cy << L"\t"<< k << L"\n";
    }

    file.close();

    if (file.fail()) {
        cerr << "파일 저장에 실패했습니다.";
        return false;
    }
    prev.clear();
    dupKeySches.clear();
    return true;
}

/*---------보조 기능---------*/

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


/*--------파일 무결성 검사----------*/

bool ScheduleDataManager::isRight(vector<string> record, vector<string>* cates)
{
    //파일 순서: 제목 카테고리 시작일 종료일 메모 반복종료일 반복주기 키
    try
    {
        if(!checkT(record[0])) return false; //title
        if(!checkC(record[1], cates)) return false; //category
        if(!checkD(record[2])) return false; //startDate
        if(!checkD(record[3])) return false; //endDate
        if (!checkD2(record[2], record[3])) return false; //startDate <= endDate
        if(!checkM(record[4])) return false; // memo
        if (!checkD(record[5])) return false; //repeat end Date
        if (!checkD2(record[3], record[5])) return false; //endDate <= repeatEndDate
        if (!checkCy(record[6])) return false; // cycle
        if (!checkKey(record[7])) return false; //key
    }
    catch (const exception& e)
    {
        //nullpointerException
        return false;
    }
    return true;
}

bool ScheduleDataManager::checkT(string data)
{
    wregex wrx(L"([ㄱ-ㅣ가-힣a-zA-Z0-9 ]{1,30})");
    wsmatch wideMatch;
    wstring wstr = s2ws(data);
    if (!regex_match(wstr.cbegin(), wstr.cend(), wideMatch, wrx)) {
        return false;
    }

    return true;
}

bool ScheduleDataManager::checkC(string data, vector<string>* cates)
{
    //카테고리 데이터 파일에 해당 카테고리가 존재하는지
    if (data.compare("기본") != 0 && find(cates->begin(), cates->end(), data) == cates->end())
        return false;
    //문법 형식
    wregex wrx(L"([ㄱ-ㅣ가-힣a-zA-Z0-9 ]{1,30})");
    wsmatch wideMatch;
    wstring wstr = s2ws(data);
    if (!regex_match(wstr.cbegin(), wstr.cend(), wideMatch, wrx)) {
        return false;
    }

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
    return false;
}

bool ScheduleDataManager::checkD2(string sdt, string edt) {
    //형식 검사는 checkD에서 선행되기 때문에 검사 x
    string sy = sdt.substr(0, 4), sm = sdt.substr(5, 2), sd = sdt.substr(8, 2); //startDate
    string ey = edt.substr(0, 4), em = edt.substr(5, 2), ed = edt.substr(8, 2); //endDate

    int start = stoi(sy) * 10000 + stoi(sm) * 100 + stoi(sd); //2xxxxxxx
    int end = stoi(ey) * 10000 + stoi(em) * 100 + stoi(ed);

    if (start > end) return false;

    return true;
}

bool ScheduleDataManager::checkM(string data)
{
    wregex wrx(L"([ㄱ-ㅣ가-힣a-zA-Z0-9 ]+)");
    wsmatch wideMatch;
    wstring wmemo = s2ws(data);
    if (!data.empty()) {
        if (!regex_match(wmemo.cbegin(), wmemo.cend(), wideMatch, wrx))
            return false;
    }
    return true;
}

bool ScheduleDataManager::checkCy(string data)
{
    regex r("[0-9]+");
    if (!regex_match(data.cbegin(), data.cend(), r))
        return false;
    int cycle = stoi(data);
    if (cycle < 0 || cycle > CYMAX)
        return false;
    return true;
}

bool ScheduleDataManager::checkKey(string data)
{
    regex r("[0-9]+");
    if (!regex_match(data.cbegin(), data.cend(), r))
        return false;
    if (stoi(data) < 0)
        return false;
    return true;
}

bool ScheduleDataManager::checkCont(Schedule s)
{
    //key값이 같은 경우 동일해야하는 요소: 제목, 카테고리, 메모, 시작일~종료일 간격
    int key = s.getKey();
    if (dupKeySches.find(key) != dupKeySches.end()) {
        Schedule s2(dupKeySches[key]);
        if (s2.getTitle().compare(s.getTitle()) != 0)
            return false;
        if (s2.getCategory().compare(s.getCategory()) != 0)
            return false;
        if (s2.getMemo().compare(s.getMemo()) != 0)
            return false;
        if (calcPeriod(s.getStartDate(), s.getEndDate()) != calcPeriod(s2.getStartDate(), s2.getEndDate()))
            return false;
        if (s2.getCycle() > 0 && s.getCycle() > 0) //반복 주기
            if (s2.getRptEndDate().compare(s.getRptEndDate()) != 0)
                return false;
        if (s2.getCycle() == 0 && s.getCycle() == 0) {
            if (s2.getStartDate().substr(5, 5).compare(s.getStartDate().substr(5, 5)) != 0
                || s2.getEndDate().substr(5, 5).compare(s.getEndDate().substr(5, 5)) != 0)
                return false;
        }
    }
    return true;
}

void ScheduleDataManager::initTime(tm& date, int y, int m, int d)
{
    date.tm_year = y - 1900;
    date.tm_mon = m - 1;
    date.tm_mday = d;
    date.tm_hour = 0;
    date.tm_min = 0;
    date.tm_sec = 0;
    date.tm_isdst = 0;
}

int ScheduleDataManager::calcPeriod(string d1, string d2)
{
    int sy = stoi(d1.substr(0, 4)), sm = stoi(d1.substr(5, 2)), sd = stoi(d1.substr(8, 2)); //startDate
    int ey = stoi(d2.substr(0, 4)), em = stoi(d2.substr(5, 2)), ed = stoi(d2.substr(8, 2)); //end

    struct tm start_date = {};
    struct tm end_date = {};

    initTime(start_date, sy, sm, sd);
    initTime(end_date, ey, em, ed);

    time_t start_time = mktime(&start_date);
    time_t end_time = mktime(&end_date);
    double diff_seconds = difftime(end_time, start_time);

    int period = static_cast<int>(diff_seconds / (60 * 60 * 24));

    return period;
}

//주기 별 종료일 계산
string ScheduleDataManager::addDate(string date, int cy, int endday)
{
    int year = stoi(date.substr(0, 4)), month = stoi(date.substr(5, 2)), day = stoi(date.substr(8, 2));
    int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    string res;

    if (cy == 1) {
        //year
        if (day < endday) day = endday;
        year += 1;
        if (year % 4 && month == 2 && day == 29)
            day = 28;
    }
    else if (cy == 2) {
        //month
        if (day < endday) day = endday;
        month += 1;
        if (month > 12) {
            year += 1;
            month = 1;
        }
        if (year % 4 == 0 && year % 100 != 0) days[1] = 29;

        if (day > days[month - 1]) day = days[month - 1];
    }
    else if (cy == 3) {
        //week
        if (year % 4 == 0 && year % 100 != 0) days[1] = 29;

        day += 7;
        if (day > days[month - 1]) {
            day = day - days[month - 1];
            month += 1;
        }
        if (month > 12) {
            year += 1;
            month = 1;
        }
    }

    //format
    string y = to_string(year);
    string m = to_string(month);
    string d = to_string(day);

    if (month <= 9) {
        m = "0" + m;
    }
    if (day <= 9) {
        d = "0" + d;
    }
    res = y + "/" + m + "/" + d;
    return res;
}

//종료일로 시작일 계산
string ScheduleDataManager::calcSD(string ed, int pe)
{
    int year = stoi(ed.substr(0, 4)), month = stoi(ed.substr(5, 2)), day = stoi(ed.substr(8, 2));
    struct tm date = {};
    initTime(date, year, month, day);

    date.tm_mday -= pe;
    mktime(&date);

    char result[11];
    strftime(result, sizeof(result), "%Y/%m/%d", &date);

    return result;
}

