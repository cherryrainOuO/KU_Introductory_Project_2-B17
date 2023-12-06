#include "Calender.h"

Calender::Calender()
{
}

void Calender::setHighestKey()
{
	for (Schedule sch : allSchs) {
		int currSchKey = sch.getKey();
		if (highestKey < currSchKey) {
			highestKey = currSchKey;
		}
	}
}

int Calender::getHighestKey()
{
	return highestKey;
}

// 유효한 날짜면 0 반환
int Calender::isValidDate(string dateStr) {

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