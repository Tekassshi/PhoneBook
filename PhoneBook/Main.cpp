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
		cout << "\nВведите комманду (help - для получения справки, exit - для выхода): ";
		cin >> command;

		if (command == "help") {
			cout << 
				"\n\n --- Доступные команды --- \n\n"
				"\"add\" - добавить номер в список\n"
				"\"show\" - вывести список\n"
				"\"remove\" - очистить список\n"
				"\"remove_by_number\"- удалить по номеру телефона\n"
				"\"find\" - найти (по номеру, имени, фамилии, дате рождения)\n"
				"\"extract\" - загрузить список из файла\n"
				"\"save\" - сохранить список в файл\n"
				"\"sort\" - отсортировать файл (по имени, фамилии, дате рождения)\n"
				"\"edit\" - отредактировать запись в списке по номеру телефона\n"
				"\"exit\" - завершить работы программы\n";
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
			cout << "\nСохранить список в файл (1 - сохранить и выйти, 0 - выход без сохранения)?: "; cin >> p;

			if (p != 1 && p != 0) {
				cout << "\033[31m" << "\nНекорректная комманда, повторите ввод.\n"
					"\033[0m";
			}
			else if (p == 1) {
				list.save();
			}

			break;
		}
		else {
			cout << "\033[31m" << "\nНекорректная комманда, повторите ввод(введите \"help\" для получения справки)\n"
					"\033[0m";
			cin.clear();
		}
	}

	list.remove();
	
	_CrtDumpMemoryLeaks();
}