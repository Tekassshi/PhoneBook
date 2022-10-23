#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <string>
#include <Windows.h>
#include "List.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Note list;

	string command;

	while (true) {
		cout << "\n������� �������� (help - ��� ��������� �������, exit - ��� ������): ";
		cin >> command;

		if (command == "help") {
			cout << 
				"\n\n --- ��������� ������� --- \n\n"
				"\"add\" - �������� ����� � ������\n"
				"\"show\" - ������� ������\n"
				"\"remove\" - �������� ������\n"
				"\"remove_by_number\"- ������� �� ������ ��������\n"
				"\"find\" - ����� (�� ������, �����, �������, ���� ��������)\n"
				"\"extract\" - ��������� ������ �� �����\n"
				"\"save\" - ��������� ������ � ����\n"
				"\"sort\" - ������������� ���� (�� �����, �������, ���� ��������)\n"
				"\"edit\" - ��������������� ������ � ������ �� ������ ��������\n"
				"\"exit\" - ��������� ������ ���������\n";
		}
		else if (command == "add") {
			list.add();
		}
		else if (command == "show") {
			list.show();
		}
		else if (command == "remove") {
			list.remove();
		}
		else if (command == "remove_by_number") {
			list.remove(readNumber());
		}
		else if (command == "find") {
			list.find();
		}
		else if (command == "sort") {
			list.sortManager();
		}
		else if (command == "edit") {
			list.editManager();
		}
		else if (command == "extract") {
			list.extract();
		}
		else if (command == "save") {
			list.save();
		}
		else if (command == "exit") {
			int p;
			cout << "\n��������� ������ � ���� (1 - ��������� � �����, 0 - ����� ��� ����������)?: "; cin >> p;

			if (p != 1 && p != 0) {
				cout << "\033[31m" << "\n������������ ��������, ��������� ����.\n"
					"\033[0m";
			}
			else if (p == 1) {
				list.save();
			}

			break;
		}
		else {
			cout << "\033[31m" << "\n������������ ��������, ��������� ����(������� \"help\" ��� ��������� �������)\n"
					"\033[0m";
			cin.clear();
		}
	}

	list.remove();
	
	_CrtDumpMemoryLeaks();
}