#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;

void MainPrompt();
void ClassificationPrompt();
void SearchPrompt();
void MangementPrompt();
void ExitPrompt();

int main() {
	
	while (true) {

		MainPrompt();
	}

	
	

	return 0;
}

void MainPrompt() {
	Sleep(100);
	system("cls");

	cout << "Ķ���� Ȩ\n\n";

	cout << "1. ���� �з�\n";
	cout << "2. �˻�\n";
	cout << "3. ���� ����\n";
	cout << "4. ����\n\n";

	cout << "���ϴ� ��ȣ�� �Է��ϼ���.\n";
	cout << "-------------------------------------\n";
	cout << ">";

	string n;
	getline(cin, n);

	switch (n[0])
	{
	case '1':
		ClassificationPrompt();
		break;
	case '2':
		SearchPrompt();
		break;
	case '3':
		MangementPrompt();
		break;
	case '4':
		ExitPrompt();
		break;
	default:
		system("cls");

		cout << "���� : 1, 2, 3, 4 �� �ϳ��� ���ڸ� �Է����ּ���.\n\n";
		cout << "�ƹ� Ű�� �����ּ���.\n";
		cout << "-------------------------------------\n";
		cout << ">";
		
		_getch();

		break;
	}

}

void ClassificationPrompt() {
	system("cls");
}

void SearchPrompt() {
	system("cls");
}

void MangementPrompt() {
	system("cls");
}

void ExitPrompt() {
	system("cls");
	cout << "Ķ���� ���� �����մϴ�.\n";
	exit(0);
}

