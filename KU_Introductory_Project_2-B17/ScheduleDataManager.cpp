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
    c.cycle_per_keys.clear();
    vector<string>* categories = cat.GetCategories();
    vector<string> record;
    wstring line;
    int idx = 0;

    //파일 레코드 순서: 제목, 카테고리 개수, 카테고리, 시작일, 종료일, 메모, 반복 종료일, 반복 주기, 키, 반복 기준 구분용 키

    while (getline(file, line)) {
        wstringstream ss(line);
        wstring token;

        while (getline(ss, token, L'\t')) {
            string temptkn;
            temptkn = ws2s(token);
            trim(temptkn); // tkn의 앞 뒤 공백 제거

            if (!temptkn.empty()) {
                record.push_back(temptkn); //연속된 tab 무시
            }
        }

        if (checkCNum(record[1])) {
            //메모가 비워진 경우 (카테고리 개수 - 1) + 5번 인덱스에 빈 문자열 삽입
            if (record.size() == (SIZE + stoi(record[1]) - 1) - 1) record.insert(record.begin() + stoi(record[1]) - 1 + 5, "");

            //레코드 사이즈가 안 맞는 경우
            if (record.size() != (SIZE + stoi(record[1]) - 1)) {
                cerr << "오류: 데이터 파일의 형식이 잘못되었습니다.\n";
                cout << "---------------------------------------------------------------------------------------\n";
                cout << ws2s(line) << "\n";
                cout << "---------------------------------------------------------------------------------------\n프로그램을 종료합니다.\n";
                return false;
            }
        
        }//레코드 사이즈 계산이 되어야 함
        else {
            cerr << "오류: 데이터 파일의 형식이 잘못되었습니다.\n";
            cout << "---------------------------------------------------------------------------------------\n";
            cout << ws2s(line) << "\n";
            cout << "---------------------------------------------------------------------------------------\n프로그램을 종료합니다.\n";
            return false;
        }

        //title, sd, ed, cate(여러 개), memo, rED, cy, k, rk순서
        string ti = record[0];
        int catecnt = stoi(record[1]);
        vector<string> cates; //한 일정 여러개
        for (int i = 2; i < catecnt + 2; i++) {
            cates.push_back(record[i]);
        }
        string sd = record[catecnt + 2];
        string ed = record[catecnt + 3];
        string me = record[catecnt + 4];
        string rED = record[catecnt + 5];
        int cy = stoi(record[catecnt + 6]);
        int k = stoi(record[catecnt + 7]);
        int rptK = stoi(record[catecnt + 8]);

        sort(cates.begin(), cates.end()); //카테고리 비교를 위한 정렬

        Schedule s(ti, sd, ed, cates, me, rED, cy, k, rptK);

        if (!isRight(record, categories) || !checkCont(s)) {
            cerr << "오류: 데이터 파일의 형식이 잘못되었습니다.\n";
            cout << "---------------------------------------------------------------------------------------\n";
            cout << ws2s(line) << "\n";
            cout << "---------------------------------------------------------------------------------------\n프로그램을 종료합니다.\n";
            return false;
        }
        if (dupKeySches.find(k) != dupKeySches.end()) {
            c.cycle_per_keys[k] = max(c.cycle_per_keys[k], cy);
        }
        else {
            c.cycle_per_keys[k] = cy;
        }

        if (dupKeySches[k].find(rptK) != dupKeySches[k].end()) {
            if (dupKeySches[k][rptK].getCycle() == s.getCycle() && s.getCycle() != 0)
                record.clear();
                continue;
        } //key, rptK, 주기 동일하면 무시

        dupKeySches[k][rptK] = s; //키가 중복될 때 검사하기 위해

        int period = calcPeriod(sd, ed); //일정의 기간

        //반복 종료일까지 추가

        if (cy >= 1) {
            int endday = stoi(ed.substr(8, 2));
            while (checkD2(ed, rED)) {
                Schedule s(ti, sd, ed, cates, me, rED, cy, k, rptK);
                c.allSchs.push_back(s);
                ed = addDate(ed, cy, endday);
                sd = calcSD(ed, period);
            }
        }
        else {
            Schedule s(ti, sd, ed, cates, me, rED, cy, k, rptK);
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
            Schedule first = dupKeySches[key][0];
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
            dupKeySches[key][0] = s;
            prev[key] = s;
        }
        c.setHighestKey();

        wstring output = L"";
        wstring t = s2ws(s.getTitle()); //제목
        output += (t + L"\t");

        vector<string> temp = s.getCategory();
        wstring clen = s2ws(to_string(temp.size())); //카테고리개수
        output += (clen + L"\t");

        for (int i = 0; i < temp.size(); i++) {
            wstring c = s2ws(temp.at(i));
            output += (c + L"\t");
        } //카테고리

        wstring sD = s2ws(s.getStartDate()); //시작일
        output += (sD + L"\t");

        wstring eD = s2ws(s.getEndDate()); //종료일
        output += (eD + L"\t");

        wstring m = s2ws(s.getMemo()); //메모
        output += (m + L"\t");

        wstring rED = s2ws(s.getRptEndDate()); //반복종료일
        output += (rED + L"\t");

        wstring cy = s2ws(to_string(s.getCycle())); //주기
        output += (cy + L"\t");

        wstring k = s2ws(to_string(s.getKey())); //키
        output += (k + L"\t");

        wstring rptK = s2ws(to_string(s.getRptK())); //서브키

        output += rptK;
        //제목 카테고리개수 카테고리 시작일 종료일 메모 반복종료일 주기 키 반복날짜구분
        file << output << L"\n";
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
        if (!checkT(record[0])) return false; //title
        int nc = stoi(record[1]);
        vector<string> c;
        for (int i = 2; i < nc + 2; i++) {
            c.push_back(record[i]);
        }
        if (!checkC(c, cates)) return false; //category
        if (!checkD(record[nc + 2])) return false; //startDate
        if (!checkD(record[nc + 3])) return false; //endDate
        if (!checkD2(record[nc + 2], record[nc + 3])) return false; //startDate <= endDate
        if (!checkM(record[nc + 4])) return false; // memo
        if (!checkD(record[nc + 5])) return false; //repeat end Date
        if (!checkD2(record[nc + 3], record[nc + 5])) return false; //endDate <= repeatEndDate
        if (!checkCy(record[nc + 6])) return false; // cycle
        if (!checkKey(record[nc + 7])) return false; //key
        if (!checkRptK(record[nc + 8], record[nc + 6])) return false; //subKey
    }
    catch (const exception& e)
    {
        //nullpointerException
        return false;
    }
    cout << "이것이 뜬다면 맞는 일정이다앙";
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

bool ScheduleDataManager::checkCNum(string data)
{
    regex r("[0-9]+");
    if (!regex_match(data.cbegin(), data.cend(), r))
        return false;
    else if (stoi(data) < 1)
        return false;
    return true;
}

bool ScheduleDataManager::checkC(vector<string> data, vector<string>* cates)
{
    //중복 카테고리?
    int n = data.size();
    sort(data.begin(), data.end());
    data.erase(unique(data.begin(), data.end()), data.end());
    if (data.size() != n) return false;

    //카테고리 데이터 파일에 해당 카테고리가 존재하는지
    for (string c : data) {
        if (c.compare("기본") != 0 && find(cates->begin(), cates->end(), c) == cates->end())
            return false;
        //문법 형식
        wregex wrx(L"([ㄱ-ㅣ가-힣a-zA-Z0-9 ]{1,30})");
        wsmatch wideMatch;
        wstring wstr = s2ws(c);
        if (!regex_match(wstr.cbegin(), wstr.cend(), wideMatch, wrx)) {
            return false;
        }
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

bool ScheduleDataManager::checkRptK(string k, string rk, string cy)
{
    regex r("[0-9]+");
    if (!regex_match(rk.cbegin(), rk.cend(), r))
        return false;
    if (stoi(cy) == 0 && stoi(rk) != 0)
        return false;
    else {
        if (stoi(rk) < 0)
            return false;
    }
    return true;
}

bool ScheduleDataManager::checkCont(Schedule s)
{
    //key값이 같은 경우 동일해야하는 요소: 제목, 카테고리 개수, 카테고리, 시작일~종료일 간격
    int key = s.getKey();
    if (dupKeySches.find(key) != dupKeySches.end()) {
        int rk;
        for (int i = 0; i < 367; i++) {
            if (dupKeySches[key].find(i) != dupKeySches[key].end()) {
                rk = i;
                break;
            }
        }
        Schedule s2 = dupKeySches[key][rk];
        if (s2.getTitle().compare(s.getTitle()) != 0) {
            return false;
        }
        if (s2.getCategory().size() != s.getCategory().size())
            return false;
        for (int i = 0; i < s.getCategory().size(); i++) {
            if (s.getCategory().at(i).compare(s2.getCategory().at(i)) != 0)
                return false;
        } //카테고리가 모두 동일?

        if (calcPeriod(s.getStartDate(), s.getEndDate()) != calcPeriod(s2.getStartDate(), s2.getEndDate()))
            return false;
        if (s2.getCycle() > 0 && s.getCycle() > 0) //반복 주기 > 0일 때 반복종료일 동일
            if (s2.getRptEndDate().compare(s.getRptEndDate()) != 0)
                return false;
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

