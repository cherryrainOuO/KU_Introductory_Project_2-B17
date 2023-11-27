#include "Classification.h"


void Classification::Prompt_CategoryMenu()
{
	Sleep(100);
	system("cls"); // 화면 지우기

	cout << "카테고리 메뉴\n\n";

	cout << "1. 카테고리 추가\n";
	cout << "2. 카테고리 일정 보기\n";
	cout << "3. 카테고리 수정/삭제\n\n";

	cout << "원하는 번호를 입력하세요.\n";
	cout << "(취소를 원한다면 \"^C\"를 입력해주세요.)\n";
	cout << "-------------------------------------\n";
	cout << "> ";

	getline(cin, kwd); // 공백을 포함시키기 위해서 getline 을 사용했습니다.

	if (kwd == "^C") { // 취소
		return;
	}
	else {
		if (kwd.size() == 1) {
			switch (kwd[0])
			{
			case '1':
				CategoryAdd(); // 일정 추가
				Prompt_CategoryMenu();
				break;
			case '2':
				//test
				PrintSchedule_ByCategory(); // 일정 보기
				break;
			case '3':
				Prompt_PrintCategoryList_ForEditOrRemove(); // 수정/삭제
				break;
			default: // 오류 메세지
				system("cls"); // 화면 지우기

				cout << "오류 : 1, 2, 3 중 하나의 숫자를 입력해주세요.\n\n";
				cout << "아무 키나 눌러주세요.\n";
				cout << "-------------------------------------\n";
				cout << "> ";

				_getch(); // 아무 키나 입력 대기

				Prompt_CategoryMenu();
				break;
			}
		}
		else { // 오류 메세지
			system("cls"); // 화면 지우기

			cout << "오류 : 1, 2, 3 중 하나의 숫자를 입력해주세요.\n\n";
			cout << "아무 키나 눌러주세요.\n";
			cout << "-------------------------------------\n";
			cout << "> ";

			_getch(); // 아무 키나 입력 대기

			Prompt_CategoryMenu();
		}
	}


}

void Classification::CategoryAdd()
{
	Sleep(100);
	system("cls"); // 화면 지우기

	cout << "카테고리 추가" << endl << endl;
	cout << "새로 추가하길 원하는 카테고리명을 입력해주세요." << endl;
	cout << "(취소를 원한다면 \"^C\"를 입력해주세요.)\n";
	cout << "-------------------------------------\n";
	cout << "> ";

	getline(cin, kwd);

	if (kwd == "^C") {
		return;
	}
	else if (!(CDM->SyntaxCheck(kwd))) {
		system("cls"); // 화면 지우기

		cout << "오류 : 해당 입력은 카테고리명으로 사용할 수 없습니다." << endl << endl;
		cout << "아무 키나 눌러주세요." << endl;
		cout << "-------------------------------------" << endl;
		cout << "> ";

		_getch();
		CategoryAdd();
	}
	else if (!(CDM->DuplicationCheck(kwd))) {	//벡터 내에 kwd가 존재하지 않을 경우
		system("cls"); // 화면 지우기

		cout << "오류 : 해당 카테고리명이 이미 존재합니다." << endl << endl;
		cout << "아무 키나 눌러주세요." << endl;
		cout << "-------------------------------------" << endl;
		cout << "> ";

		_getch();
		CategoryAdd();
	}
	else {
		Sleep(100);
		system("cls");

		CDM->CategoryAdd(kwd);

		cout << "카테고리 추가 완료" << endl << endl;

		cout << "아무 키나 눌러주세요.\n";
		cout << "-------------------------------------\n";
		cout << "> ";

		_getch(); // 아무 키나 입력 대기


	}



}


void Classification::PrintSchedule_ByCategory(){
	Sleep(100);
	system("cls"); // 화면 지우기

	cout << "카테고리 일정 보기" << endl << endl;
	cout << "0. 기본" << endl;
	CDM->CategoryPrint();
	cout << "원하는 카테고리를 선택하세요." << endl;
	cout << "카테고리는 & | ~ 연산 기호를 조합하여 여러개 입력할 수도 있습니다.\n";
	cout << "연산의 우선순위 : not(~) > and(&) > or(|)\n";
	cout << "(취소를 원한다면 \"^C\"를 입력해주세요.)\n";
	cout << "-------------------------------------\n";
	cout << "> ";

	getline(cin, kwd);

	if (kwd == "^C") { // 취소
		Prompt_CategoryMenu();
	}
	else if (kwd.find('~') == string::npos
		&& kwd.find('&') == string::npos
		&& kwd.find('|') == string::npos)
	{ // 단일 번호의 경우
		try {
			int ikwd = stoi(kwd);
		}
		catch (exception e) {
			system("cls"); // 화면 지우기

			cout << "오류 : 해당 카테고리는 존재하지 않습니다.\n\n";
			cout << "아무 키나 눌러주세요.\n";
			cout << "-------------------------------------\n";
			cout << "> ";

			_getch(); // 아무 키나 입력 대기

			PrintSchedule_ByCategory();

		}

		if (stoi(kwd) > CDM->GetSize() || stoi(kwd) < 0) { // 오류 메세지
			system("cls"); // 화면 지우기

			cout << "오류 : 해당 카테고리는 존재하지 않습니다.\n\n";
			cout << "아무 키나 눌러주세요.\n";
			cout << "-------------------------------------\n";
			cout << "> ";

			_getch(); // 아무 키나 입력 대기

			PrintSchedule_ByCategory();
			
		}
		else {
			Sleep(100);
			system("cls");

			string cateKwd;

			if (stoi(kwd) == 0) {
				cateKwd = "기본";
			}
			else {
				cateKwd = CDM->GetValue(stoi(kwd) - 1);
			}

			makeQueueForPrint(cateKwd);

			if (res.empty())
				cout << "\"" << cateKwd << "\" 카테고리를 포함하고 있는 일정이 없습니다." << endl << endl;
			else {
				// 언제 이후만 이전만 입력 프롬프트
				// 아직 makeQueueForPrint랑 연동이 덜 돼서 실행 시에 여러 번 호출되면 반복 출력됩니다.
				Prompt_after_or_before_When(res, cateKwd);
			}

			/*cout << "아무 키나 눌러주세요.\n";
			cout << "-------------------------------------\n";
			cout << "> ";
			_getch(); // 아무 키나 입력 대기*/
			system("cls");
			Prompt_CategoryMenu();
		}
	}
	else {
		Caculate_ByOperators(); //? 피연산자와 연산자의 조합 계산 및 출력
	}
}


vector<string> Classification::split(string str, string delims)
{
	vector<string> result;

	string temp = "";
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '~') {
			if (temp != "") result.push_back(temp);
			temp = "";
			result.push_back("~");
		}
		else if (str[i] == '&') {
			if (temp != "") result.push_back(temp);
			temp = "";
			result.push_back("&");
		}
		else if (str[i] == '|') {
			if (temp != "") result.push_back(temp);
			temp = "";
			result.push_back("|");
		}
		else {
			temp += str[i];
		}
	}

	if (temp != "") result.push_back(temp);

	return result;
}

struct Classification::Oper {
public:
	int priority;
	string oper;

	Oper(int _prio, string _oper) {
		priority = _prio;
		oper = _oper;
	}
};

class Classification::CategoryComponent {
public:
	vector<string> cate; // 있어야 되는 카테고리
	vector<string> block; // 있으면 안되는 카테고리

	CategoryComponent(string str) { // 최초 피연산자 넣기
		cate.push_back(str);
	}

	CategoryComponent(CategoryComponent* left, CategoryComponent* right, string oper) { // 계산해서 컴포넌트 합치기
		if (oper == "~") {
			for (string s : right->cate) block.push_back(s);
			for (string s : right->block) cate.push_back(s);
		}
		else if (oper == "&") {
			for (string s : left->cate) cate.push_back(s);

			for (string s : left->block) block.push_back(s);

			for (string s : right->cate) cate.push_back(s);

			for (string s : right->block) block.push_back(s);
		}
		// 여러개의 컴포넌트 구분짓는 기준을 or 로 할거라서 따로 계산 안함. 
	}

};

void Classification::Caculate_ByOperators() {
	/* 피연산자와 연산자의 조합 */
	try {
		vector<Oper*> userOperators;
		vector<string> postfix;

		vector<string> splitedKwd = split(kwd, "~&|");

		for (string s : splitedKwd) cout << s << " ";
		cout << "\n";

		for (int i = 0; i < splitedKwd.size(); i++) {
			if (splitedKwd[i] == "~") {

				userOperators.push_back(new Oper(1, "~"));
			}
			else if (splitedKwd[i] == "&") {

				while (userOperators.size() > 0 && userOperators.back()->priority <= 1) {
					postfix.push_back(userOperators.back()->oper);
					userOperators.pop_back();
				}

				userOperators.push_back(new Oper(2, "&"));

			}
			else if (splitedKwd[i] == "|") {
				while (userOperators.size() > 0 && userOperators.back()->priority <= 2) {
					postfix.push_back(userOperators.back()->oper);
					userOperators.pop_back();
				}

				userOperators.push_back(new Oper(3, "|"));

			}
			else {
				postfix.push_back(splitedKwd[i]);
			}
		}

		while (userOperators.size() > 0) {
			postfix.push_back(userOperators.back()->oper);
			userOperators.pop_back();
		}

		for (string s : postfix) cout << s << " ";
		cout << "\n";

		vector<CategoryComponent*> stack;
		CategoryComponent* tempLeft;
		CategoryComponent* tempRight;

		int componentCount = 1;

		for (int i = 0; i < postfix.size(); i++) {
			if (postfix[i] == "~") {
				if (stack.size() == 0) throw out_of_range("잘못함");

				tempRight = stack.back();
				stack.pop_back();

				stack.push_back(new CategoryComponent(NULL, tempRight, "~"));
			}
			else if (postfix[i] == "&") {
				if (stack.size() == 0) throw out_of_range("잘못함");

				tempLeft = stack.back();
				stack.pop_back();

				if (stack.size() == 0) throw out_of_range("잘못함");

				tempRight = stack.back();
				stack.pop_back();

				stack.push_back(new CategoryComponent(tempLeft, tempRight, "&"));
			}
			else if (postfix[i] == "|") {
				// 어차피 이부분은 마지막에 하므로 아무것도 하지말고 
				// 그냥 stack에는 여러 컴포넌트들이 생기도록 하기.
				// = 여러개의 컴포넌트 구분짓는 기준을 or 로 할거라서 따로 계산 안함.
				// '|' 몇번나왔는지 계산해서 이거랑 컴포넌트 수랑 다르면 틀린걸로 계산해야함.
				componentCount++;
			}
			else {
				stack.push_back(new CategoryComponent(postfix[i]));
			}
		}

		// stack : 카테고리 컴포넌트들이 들어있는데 각 성분들은 or로 연결.

		if (componentCount != stack.size()) // | 개수랑 다르면 틀린거
		{
			throw out_of_range("잘못함");
		}


		for (int i = 0; i < stack.size(); i++) {
			/* test */
			cout << "test ok : ";
			for (string s : stack[i]->cate) cout << s << " ";
			cout << "\n";
			cout << "test block : ";
			for (string s : stack[i]->block) cout << s << " ";
			cout << "\n---------or---------\n";

			makeQueueForPrint2(stack[i]->cate, stack[i]->block);
		}

		for (Schedule s : cal->allSchs) { s.setRC(0); } // 레퍼런스 카운트 초기화

		if (res.empty())
			cout << "\"" << kwd << "\" 카테고리를 포함하고 있는 일정이 없습니다." << endl << endl;
		else {
			// 언제 이후만 이전만 입력 프롬프트
			// 아직 makeQueueForPrint랑 연동이 덜 돼서 실행 시에 여러 번 호출되면 반복 출력됩니다.
			Prompt_after_or_before_When(res, kwd);
		}

		cout << "아무 키나 눌러주세요.\n";
		cout << "-------------------------------------\n";
		cout << "> ";
		_getch(); // 아무 키나 입력 대기

		Prompt_CategoryMenu();
	}
	catch (exception& e) {
		system("cls"); // 화면 지우기

		cout << "오류 : 올바르지 못한 연산입니다.\n\n";
		cout << "아무 키나 눌러주세요.\n";
		cout << "-------------------------------------\n";
		cout << "> ";

		_getch(); // 아무 키나 입력 대기

		PrintSchedule_ByCategory();

	}
}

void Classification::makeQueueForPrint2(vector<string> cate, vector<string> block) {

	vector<Schedule> allSchs = cal->allSchs; //! 이거 포인터 사용해야 rc 바꾸는거 적용될지도? => rc 바뀌는지 테스트 필요
	vector<int> checkSchs(allSchs.size(), 0);

	int targetSize = cate.size(); // cate가 비어있을경우엔 0
	
	for (int i = 0; i < allSchs.size(); i++) {
		
					
		for (string c : cate) { 

			c = (c == "0") ? "기본" : CDM->GetValue(stoi(c) - 1); // 여기서 모든 cate가 정상인지 체크 => 숫자가 아닌 다른 이상한 거 들어있을 때 catch 되는지 테스트 필요

			for (string origin : allSchs[i].getCategory()) { // 해당 스케줄에는 cate가 전부 들어있어야 함.

				if (origin.compare(c) == 0) {
					checkSchs[i]++;
					break;
				}
				
			}
		}

		for (string b : block) {
			b = (b == "0") ? "기본" : CDM->GetValue(stoi(b) - 1); // 여기서 모든 block 정상인지 체크. 따라서 -1 미리 확인해도 break 하면 안됨!

			for (string origin : allSchs[i].getCategory()) {

				if (origin.compare(b) == 0) {
					checkSchs[i] = -1; // block을 하나라도 포함하고 있는 스케줄은 바로 -1
					break;
				}
			}
		}
		
	}

	for (int i = 0; i < allSchs.size(); i++) {
		if (checkSchs[i] == targetSize && allSchs[i].getRC() == 0) { // 스케줄에 cate가 다 들어있고, rc가 0인 경우에만 출력! 
			res.push(allSchs[i]);
			allSchs[i].setRC(1);
		}
	}

	
}

void Classification::makeQueueForPrint(string str) {
	for (Schedule s : cal->allSchs) {

		for (string origin : s.getCategory()) {
			if (origin.compare(str) == 0) {
				res.push(s);

				break;
			}
		}
			
	}
}

void Classification::Prompt_CategoryEdit(int _cateNum)
{
	Sleep(100);
	system("cls"); // 화면 지우기

	cout << "이전 카테고리 명 : " << CDM->GetValue(_cateNum - 1) << "\n\n";

	cout << "새 카테고리명을 입력해주세요.\n";
	cout << "(취소를 원한다면 \"^C\"를 입력해주세요.)\n";
	cout << "-------------------------------------\n";
	cout << "> ";

	getline(cin, kwd); // 공백을 포함시키기 위해서 getline 을 사용했습니다.

	if (kwd == "^C") { // 취소
		Prompt_CategoryEditOrRemove(_cateNum);
	}
	else if (CDM->SyntaxCheck(kwd) == false) { // 문법 체크
		system("cls"); // 화면 지우기

		cout << "오류 : 해당 입력은 카테고리명으로 사용할 수 없습니다.\n\n";
		cout << "아무 키나 눌러주세요.\n";
		cout << "-------------------------------------\n";
		cout << "> ";

		_getch(); // 아무 키나 입력 대기

		Prompt_CategoryEdit(_cateNum);
	}
	else if (CDM->DuplicationCheck(kwd) == false) { // 중복 체크
		system("cls"); // 화면 지우기

		cout << "오류 : 해당 카테고리명이 이미 존재합니다.\n\n";
		cout << "아무 키나 눌러주세요.\n";
		cout << "-------------------------------------\n";
		cout << "> ";

		_getch(); // 아무 키나 입력 대기

		Prompt_CategoryEdit(_cateNum);
	}
	else {

		Sleep(100);
		system("cls"); // 화면 지우기

		CDM->CategoryEdit(_cateNum - 1, kwd);


		cout << "카테고리 수정 완료\n\n";

		cout << "아무 키나 눌러주세요.\n";
		cout << "-------------------------------------\n";
		cout << "> ";

		_getch(); // 아무 키나 입력 대기

		return;
	}
}

void Classification::Prompt_CategoryRemove(int _cateNum)
{
	Sleep(100);
	system("cls"); // 화면 지우기

	CDM->CategoryRemove(_cateNum);

	cout << "카테고리 삭제 완료\n\n";

	cout << "아무 키나 눌러주세요.\n";
	cout << "-------------------------------------\n";
	cout << "> ";

	_getch(); // 아무 키나 입력 대기

	return;
}


void Classification::Prompt_PrintCategoryList_ForEditOrRemove()
{
	Sleep(100);
	system("cls"); // 화면 지우기

	cout << "카테고리 수정 삭제\n\n";

	cout << "0. 기본\n";
	CDM->CategoryPrint();

	cout << "\n수정 및 삭제하길 원하는 카테고리를 선택하세요.\n";
	cout << "(기본 카테고리는 수정 및 삭제 불가능)\n";
	cout << "(취소를 원한다면 \"^C\"를 입력해주세요.)\n";
	cout << "-------------------------------------\n";
	cout << "> ";

	getline(cin, kwd); // 공백을 포함시키기 위해서 getline 을 사용했습니다.


	if (kwd == "^C") { // 취소
		Prompt_CategoryMenu();
	}
	else {
		try {
			if (stoi(kwd) == 0) { // 기본 카테고리 수정 삭제 불가능
				system("cls"); // 화면 지우기

				cout << "오류 : 기본 카테고리는 수정/삭제 할 수 없습니다.\n\n";
				cout << "아무 키나 눌러주세요.\n";
				cout << "-------------------------------------\n";
				cout << "> ";

				_getch(); // 아무 키나 입력 대기

				Prompt_PrintCategoryList_ForEditOrRemove();
			}
			else if (stoi(kwd) > CDM->GetSize() || stoi(kwd) < 0) { // 오류 메세지
				system("cls"); // 화면 지우기

				cout << "오류 : 해당 카테고리는 존재하지 않습니다.\n\n";
				cout << "아무 키나 눌러주세요.\n";
				cout << "-------------------------------------\n";
				cout << "> ";

				_getch(); // 아무 키나 입력 대기

				Prompt_PrintCategoryList_ForEditOrRemove();
			}
			else {
				Prompt_CategoryEditOrRemove(stoi(kwd));
			}
		}
		catch (const std::exception& expn) {
			system("cls"); // 화면 지우기

			cout << "오류 : 해당 카테고리는 존재하지 않습니다.\n\n";
			cout << "아무 키나 눌러주세요.\n";
			cout << "-------------------------------------\n";
			cout << "> ";

			_getch(); // 아무 키나 입력 대기

			Prompt_PrintCategoryList_ForEditOrRemove();
		}
	}

}

void Classification::Prompt_CategoryEditOrRemove(int _cateNum)
{
	system("cls"); // 화면 지우기

	cout << "선택된 카테고리 : \"" << CDM->GetValue(_cateNum - 1) << "\"\n\n";

	cout << "1. 수정하기\n";
	cout << "2. 삭제하기\n\n";

	cout << "원하는 번호를 선택하세요.\n";
	cout << "(취소를 원한다면 \"^C\"를 입력해주세요.)\n";
	cout << "-------------------------------------\n";
	cout << "> ";

	getline(cin, kwd); // 공백을 포함시키기 위해서 getline 을 사용했습니다.


	if (kwd == "^C") { // 취소
		Prompt_PrintCategoryList_ForEditOrRemove();
	}
	else {
		if (kwd.size() == 1) {

			switch (kwd[0])
			{
			case '1':
				Prompt_CategoryEdit(_cateNum); // 일정 수정

				Prompt_CategoryMenu();
				break;
			case '2':
				//test
				Prompt_CategoryRemove(_cateNum); // 일정 삭제

				Prompt_CategoryMenu();
				break;
			default: // 오류 메세지
				system("cls"); // 화면 지우기

				cout << "오류 : 1, 2 중 하나의 숫자를 입력해주세요.\n\n";
				cout << "아무 키나 눌러주세요.\n";
				cout << "-------------------------------------\n";
				cout << "> ";

				_getch(); // 아무 키나 입력 대기

				Prompt_CategoryEditOrRemove(_cateNum);
				break;
			}
		}
		else {
			system("cls"); // 화면 지우기

			cout << "오류 : 1, 2 중 하나의 숫자를 입력해주세요.\n\n";
			cout << "아무 키나 눌러주세요.\n";
			cout << "-------------------------------------\n";
			cout << "> ";

			_getch(); // 아무 키나 입력 대기

			Prompt_CategoryEditOrRemove(_cateNum);
		}
	}
}

vector<string> split_by_space(string str, char del) {
	istringstream iss(str);
	string buf;
	vector<string> result;

	while (getline(iss, buf, del))
		result.push_back(buf);

	return result;
}

void Classification::Prompt_after_or_before_When(queue<Schedule> res, string cateKwd) {

	queue<Schedule> r = res;

	cout << "카테고리 \"" << cateKwd << "\"(으)로 검색되는 일정 중\n";
	cout << "\"언제 이후만\" 과 \"언제 이전만\" 이 출력 되기를 원하신다면\n";
	cout << "해당하는 날짜를 공백 하나로 구분하여 입력해주세요.\n";
	cout << "원하지 않으신다면 각각 \'x\'를 입력해주세요.\n\n";

	cout << "입력 형식: yyyy/mm/dd yyyy/mm/dd\n\n";

	cout << "예 : 2010/01/01 2023/12/31  (2010/01/01 ~ 2023/12/31에 해당하는 일정 출력)\n";
	cout << "     2010/01/01 x           (2010/01/01 이후에 해당하는 일정 출력)\n";
	cout << "     x 2023/12/31           (2023/12/31 이전에 해당하는 일정 출력) \n";
	cout << "     x                      (모든 일정 출력)\n\n";

	cout << "(^C 입력 시 이전 화면으로 돌아갑니다.)\n";
	cout << "----------------------------------------------\n";
	cout << "> ";

	string whendates;
	vector<string> dates;
	string afterDate, beforeDate;
	getline(cin, whendates);
	system("cls");
	if (whendates == "^C")
		PrintSchedule_ByCategory();
	else if (whendates.find(' ') != std::string::npos) {
		dates = split_by_space(whendates, ' ');
		afterDate = dates[0];
		beforeDate = dates[1];

		if (afterDate == "x")
			afterDate = "2000/01/01";
		if (beforeDate == "x")
			beforeDate = "2030/12/31";

		int y1, m1, d1, y2, m2, d2;
		bool b = true; // afterDate < beforeDate
		y1 = stoi(afterDate.substr(0, 4));
		m1 = stoi(afterDate.substr(5, 2));
		d1 = stoi(afterDate.substr(8, 2));
		y2 = stoi(beforeDate.substr(0, 4));
		m2 = stoi(beforeDate.substr(5, 2));
		d2 = stoi(beforeDate.substr(8, 2));

		if ((y1 > y2) || ((y1 == y2) && (m1 > m2))
			|| ((y1 == y2) && (m1 == m2) && (d1 > d2)))
			b = false;

		if ((cal->isValidDate(afterDate) == -1) || (cal->isValidDate(beforeDate) == -1) || b == false) {
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
		else {
			for (int i = 0; i < res.size(); i++) {
				if (r.front().getEndDate() >= afterDate
					&& r.front().getEndDate() <= beforeDate)
					r.push(r.front());
				r.pop();
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
			return;
			// Prompt_after_or_before_When(res, cateKwd);
		}
	}
	if (r.empty())
		cout << "\"" << cateKwd << "\" 카테고리에 "<<afterDate << " ~ " << beforeDate << " 날짜에 해당하는 일정이 없습니다.\n\n";
	else {
		cout << "카테고리 \"" << cateKwd << "\"에 해당되는 일정들입니다.\n\n";
		while (!r.empty()) {
			r.front().print();
			r.pop();
		}
	}
	cout << "아무 키나 눌러주세요.\n";
	cout << "_____________________________\n";
	cout << "> ";
	if (_getch()) {
		system("cls");
		return;
	}
}