#include "ScheduleDataManager.h"

bool ScheduleDataManager::loadDataFile(Calender& c)
{
    //파일 경로 사용자 지정?
    string filePath;
    string fileName = "testSch.txt";
    ifstream file;
    file.open(fileName, ios::in | ios::binary);
    if (!file) {
        //파일이 존재하지 않음
        cout << "경고: 데이터 파일이 존재하지 않습니다. 빈 데이터 파일을 생성합니다.\n";
        ofstream fout;
        fout.open(fileName, ios::out | ios::binary);
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
    string line;
    int idx = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        while (getline(ss, token, '\t')) {
            cout << token; //test
            if (!token.empty()) record.push_back(token); //연속된 tab 무시
        }
        if (record.size() != 5 || !isRight(record)) {
            cerr << "오류: 데이터 파일의 형식이 잘못되었습니다. 프로그램을 종료합니다.\n";
            return false;
        }
        Schedule s(record[0], record[1], record[2], record[3], record[4]);
        c.allSchs.push_back(s);
    }
    file.close();
    cout << "데이터 로드 성공";
    return true;
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
    return false;
}

bool ScheduleDataManager::checkM(string data)
{
    /*메모 체크...*/
    return true;
}
