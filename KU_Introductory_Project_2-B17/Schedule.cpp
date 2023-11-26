#include "Schedule.h"

Schedule::Schedule() {
	// 깡통이 없으면 실행이 안돼요
}

Schedule::Schedule(string t, string sd, string ed, string ca, string me, string rED, int cy, int k)
{
	title = t;
	startDate = sd;
	endDate = ed;
	category = ca;
	memo = me;
	rptEndDate = rED;
	cycle = cy;
	key = k;
}

void Schedule::print()
{
	cout << "제목: " << title << "\n";
	cout << "카테고리: " << category << "\n";
	cout << "날짜: " << startDate << " ~ " << endDate << "\n";
	cout << "메모: " << memo << "\n";

	cout << "반복 주기: ";
	switch (cycle) {
	case 0: cout << "반복하지 않음\n"; break;
	case 1: cout << "매년 반복\n"; break;
	case 2: cout << "매월 반복\n"; break;
	case 3: cout << "매주 반복\n"; break;
	}

	cout << "반복 종료일: ";
	if (cycle == 0) {
		cout << "반복하지 않음\n\n";
	}
	else {
		cout << rptEndDate << "\n\n";
	}

}
