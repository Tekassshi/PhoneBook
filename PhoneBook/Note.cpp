#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

#include "List.h"
# define JSON_DIAGNOSTICS 1;
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

bool Note::isExist(string phone_number) {
	NOTE* temp = list;

	while (temp != nullptr) {
		if (phone_number == temp->phone_number)
			return true;

		temp = temp->next;
	}

	return false;
}

void Note::push(NOTE* elem) {
	if (list == nullptr) {
		list = elem;
		return;
	}

	NOTE* ptr = list;

	while (ptr->next != nullptr)
		ptr = ptr->next;

	ptr->next = elem;

	return;
}

void Note::add() {
	cout << "\n--- Новая запись ---\n";

	NOTE* new_note = new NOTE;
	NOTE* temp = list;

	if (length != 0)
		while (temp->next != nullptr)
			temp = temp->next;

	string input;

	int* date = new int[3]{0, 0, 0};

	bool should_brake;

	for (int i = 0; i < 4; i++) {

		should_brake = 0;

		while (!should_brake) {
			cin.clear();
			switch (i)
			{
			case 0:
			{
				cout << "\nВведите имя: "; cin >> input;
				if (!isNameValid(input)) {
					cout << "\nНеверные данные (имя должно содержать только буквы).\n";
					cout << "Повторите ввод.\n";
					cin.clear();

					continue;
				}

				new_note->firstname = formatName(input);
				should_brake = 1;
				break;
			}
			case 1:
			{
				cout << "\nВведите фамилию: "; cin >> input;
				if (!isNameValid(input)) {
					cout << "\nНеверные данные (фамилия должна содержать только буквы).\n";
					cout << "Повторите ввод.\n";
					cin.clear();

					continue;
				}

				new_note->lastname = formatName(input);
				should_brake = 1;
				break;
			}
			case 2:
			{
				cout << "\nВведите номер телефона (формат +7XXXXXXXXX): "; cin >> input;
				if (!isNumValid(input)) {
					cout << "\nНеверные данные (номер телефона должен соответствовать формату ";
					cout << "и не должен содержать лишних символов).\n";
					cout << "Повторите ввод.\n";
					cin.clear();

					continue;
				}

				string edited = formatNumber(input);

				if (isExist(edited)) {
					cout << "\nЧеловек с таким номером телефона уже существует!\n";
					cout << "Повторите ввод.\n";

					cin.clear();
					continue;
				}

				new_note->phone_number = edited;
				should_brake = 1;
				break;
			}
			case 3:
			{
				string day; string month; string year;

				cout << "\nВведите дату рождения (формат ДД ММ ГГГГ): ";

				cin >> day >> month >> year;

				if (!isNumeric(day) || !isNumeric(month) || !isNumeric(year)
					|| day.length() > 2 || month.length() > 2 || year.length() > 4) {
					cout << "\nНекорректные данные (дата должна состоять из цифр и иметь верный формат).\n";
					cout << "Повторите ввод.\n";
					cin.clear();

					continue;
				}

				date[0] = stoi(day);
				date[1] = stoi(month);
				date[2] = stoi(year);

				if (!isDateValid(date)) {
					cout << "\nДата рождения введена некорректно.\n";
					cout << "Повторите ввод.\n";
					cin.clear();

					continue;
				}

				new_note->birth_date = date;

				should_brake = 1;
				break;
			}
			}
		}
	}

	if (length == 0)
		list = new_note;
	else
		temp->next = new_note;

	length++;

	cout << "\033[32m" << "\nЗапись добавлена успешно!\n\n" << "\033[0m";
}

void Note::show(NOTE* person) {
	if (person == nullptr)
		return;

	cout << "\nИмя: " << person->firstname << "\n";
	cout << "Фамилия: " << person->lastname << "\n";
	cout << "Номер телефона: " << person->phone_number << "\n";
	cout << "Дата рождения: ";

	if (to_string((person->birth_date)[0]).length() > 1)
		cout << (person->birth_date)[0] << ".";
	else {
		cout << "0" << (person->birth_date)[0] << ".";
	}

	if (to_string((person->birth_date)[1]).length() > 1)
		cout << (person->birth_date)[1] << ".";
	else {
		cout << "0" << (person->birth_date)[1] << ".";
	}

	cout << (person->birth_date)[2] << "\n";
}

void Note::show() {

	cout << "\n\n--- Список контактов ---\n\n";

	if (length == 0) {
		cout << "      Список пуст!\n\n";
		return;
	}

	NOTE* temp = list;

	while (temp != nullptr) {
		
		cout << "Имя: " << temp->firstname << "\n";
		cout << "Фамилия: " << temp->lastname << "\n";
		cout << "Номер телефона: " << temp->phone_number << "\n";
		cout << "Дата рождения: ";

		if (to_string((temp->birth_date)[0]).length() > 1)
			cout << (temp->birth_date)[0] << ".";
		else {
			cout << "0" << (temp->birth_date)[0] << ".";
		}

		if (to_string((temp->birth_date)[1]).length() > 1)
			cout << (temp->birth_date)[1] << ".";
		else {
			cout << "0" << (temp->birth_date)[1] << ".";
		}

		cout << (temp->birth_date)[2] << "\n";

		temp = temp->next;

		cout << "------------------------";
		cout << "\n\n";
	}
	cout << "\n\n";
}

bool Note::compDates(NOTE* ptr1, NOTE* ptr2) {
	if (ptr1->birth_date[2] > ptr2->birth_date[2])
		return true;

	if (ptr1->birth_date[1] > ptr2->birth_date[1]  && 
		(ptr1->birth_date[2] == ptr2->birth_date[2]))
		return true;

	if (ptr1->birth_date[0] > ptr2->birth_date[0]  &&
	    ptr1->birth_date[1] == ptr2->birth_date[1] &&
		ptr1->birth_date[2] == ptr2->birth_date[2])
		return true;

	return false;
}

NOTE* Note::getTail(NOTE* head) {
	NOTE* temp = head;

	if (list == nullptr)
		return nullptr;

	while (temp->next != nullptr)
		temp = temp->next;

	return temp;
}

NOTE* Note::divide(NOTE* head, NOTE* end, NOTE** newhead, NOTE** newend, int key, int reverse_key) {

	NOTE* pivot = end, * prev = nullptr, * cur = head, * tail = pivot;

	const char* str1 = nullptr;
	const char* str2 = nullptr;

	if (key == 0) {
		str1 = (cur->firstname).c_str();
		str2 = (pivot->firstname).c_str();
	}
	else if (key == 1) {
		str1 = (cur->lastname).c_str();
		str2 = (pivot->lastname).c_str();
	}

	while (cur != pivot) {
		if (
			((key == 0 || key == 1) &&
			((reverse_key == 0 && strcmp(str1, str2) < 0) ||
			(reverse_key == 1 && strcmp(str1, str2) > 0)))
			||
			(key == 2 && 
			((reverse_key == 0 && !compDates(cur, pivot)) ||
			(reverse_key == 1 && compDates(cur, pivot)))
			)) {

			if (*newhead == nullptr)
				*newhead = cur;

			prev = cur;
			cur = cur->next;
		}
		else {
			if (prev)
				prev->next = cur->next;

			NOTE* temp = cur->next;
			tail->next = cur;
			cur->next = nullptr;
			tail = cur;
			cur = temp;
		}

		if (key == 0)
			str1 = (cur->firstname).c_str();
		else if (key == 1)
			str1 = (cur->lastname).c_str();
	}

	if (*newhead == nullptr)
		*newhead = pivot;

	*newend = tail;

	return pivot;
}

NOTE* Note::quickSort(NOTE* head, NOTE* end, int key, int reverse_key) {
	if (!head || head == end)
		return head;

	NOTE* newHead = nullptr;
	NOTE* newEnd = nullptr;

	NOTE* pivot = divide(head, end, &newHead, &newEnd, key, reverse_key);

	if (newHead != pivot) {
		NOTE* temp = newHead;
		
		while (temp->next != pivot)
			temp = temp->next;
		
		temp->next = nullptr;

		newHead = quickSort(newHead, temp, key, reverse_key);

		temp = getTail(newHead);
		temp->next = pivot;
	}

	pivot->next = quickSort(pivot->next, newEnd, key, reverse_key);

	return newHead;
}

//	key 0 - by firstname
//	key 1 - by lastname
//	key 2 - by birth date
// 
//	reverse_key 0 - ascending 
//	reverse_key 1 - descending

void Note::sort(int key, int reverse_key) {
	list = quickSort(list, getTail(list), key, reverse_key);
}

void Note::remove() {
	NOTE* temp = list;

	while (list != nullptr) {
		list = list->next;
		delete[] temp->birth_date;
		delete temp;
		temp = list;
	}
	length = 0;

	cout << "\033[32m" << "\nСписок очищен!\n\n" << "\033[0m";
}

void Note::remove(string phone_number) {

	if (list == nullptr) {
		cout << "\nСписок пуст!\n";
		return;
	}

	phone_number = formatNumber(phone_number);

	NOTE* ptr = list, *prev = nullptr;
	bool isExist = 0;

	if (length == 0) {
		cout << "\nСписок пуст\n";
		return;
	}

	while ((ptr != nullptr)) {
		if (ptr->phone_number == phone_number || ptr->phone_number == simpleNumber(phone_number)) {
			isExist = 1;
			break;
		}

		prev = ptr;
		ptr = ptr->next;
	}

	if (!isExist) {
		cout << "\nНомер телефона не существует!\n";
		return;
	}

	if (prev == nullptr)
		list = ptr->next;
	else
		prev->next = ptr->next;

	delete[] ptr->birth_date;
	delete ptr;
	length--;

	cout << "\033[32m" << "\nНомер телефона успешно удалён!\n\n" << "\033[0m";
}

void Note::get(string value, int key) {

	NOTE* ptr = list;
	bool isExist = 0;

	if (key == 0 || key == 1)
		value = formatName(value);
	else
		value = formatNumber(value);

	if (list == nullptr) {
		cout << "\nСписок пуст!\n";
		return;
	}

	while (ptr != nullptr) {
		if (key == 0 && ptr->firstname == value ||
			key == 1 && ptr->lastname == value ||
			key == 2 && ptr->phone_number == value) {
		
			isExist = 1;
			show(ptr);

			if (key == 2)
				break;
		}
		ptr = ptr->next;
	}

	if (isExist == 0)
		cout << "\nЭлементы не найден\n";
}

void Note::get(int birth_date[3]) {
	NOTE* ptr = list;
	bool isExist = 0;

	if (list == nullptr) {
		cout << "\nСписок пуст!\n";
		return;
	}

	while (ptr != nullptr) {
		if (ptr->birth_date[0] == birth_date[0] &&
			ptr->birth_date[1] == birth_date[1] &&
			ptr->birth_date[2] == birth_date[2]) {
			
			isExist = 1;
			show(ptr);
		}
		ptr = ptr->next;
	}

	if (isExist == 0)
		cout << "\nЭлементы не найден\n";
}

void Note::editAll(string phone_number) {
	phone_number = formatNumber(phone_number);

	NOTE* ptr = list;

	if (!isExist(phone_number)) {
		cout << "\nТакого номера телефона не существует!\n";
		return;
	}

	while (ptr->phone_number != phone_number)
		ptr = ptr->next;

	bool should_brake;
	string input;
	int date[3];

	for (int i = 0; i < 4; i++) {

		should_brake = 0;

		while (!should_brake) {
			cin.clear();
			switch (i)
			{
			case 0:
			{
				cout << "\nВведите имя: "; cin >> input;
				if (!isNameValid(input)) {
					cout << "\nНеверные данные (имя должно содержать только буквы).\n";
					cout << "Повторите ввод.\n";
					cin.clear();

					continue;
				}

				ptr->firstname = formatName(input);
				should_brake = 1;
				break;
			}
			case 1:
			{
				cout << "\nВведите фамилию: "; cin >> input;
				if (!isNameValid(input)) {
					cout << "\nНеверные данные (фамилия должна содержать только буквы).\n";
					cout << "Повторите ввод.\n";
					cin.clear();

					continue;
				}

				ptr->lastname = formatName(input);
				should_brake = 1;
				break;
			}
			case 2:
			{
				cout << "\nВведите номер телефона (формат +7XXXXXXXXX): "; cin >> input;
				if (!isNumValid(input)) {
					cout << "\nНеверные данные (номер телефона должен соответствовать формату ";
					cout << "и не должен содержать лишних символов).\n";
					cout << "Повторите ввод.\n";
					cin.clear();

					continue;
				}

				string edited = formatNumber(input);

				if (isExist(edited)) {
					cout << "\nЧеловек с таким номером телефона уже существует!\n";
					cout << "Повторите ввод.\n";

					cin.clear();
					continue;
				}

				ptr->phone_number = edited;
				should_brake = 1;
				break;
			}
			case 3:
			{
				string day; string month; string year;

				cout << "\nВведите дату рождения (формат ДД ММ ГГГГ): ";

				cin >> day >> month >> year;

				if (!isNumeric(day) || !isNumeric(month) || !isNumeric(year)
					|| day.length() > 2 || month.length() > 2 || year.length() > 4) {
					cout << "\nНекорректные данные (дата должна состоять из цифр и иметь верный формат).\n";
					cout << "Повторите ввод.\n";
					cin.clear();

					continue;
				}

				date[0] = stoi(day);
				date[1] = stoi(month);
				date[2] = stoi(year);

				if (!isDateValid(date)) {
					cout << "\nДата рождения введена некорректно.\n";
					cout << "Повторите ввод.\n";
					cin.clear();

					continue;
				}

				ptr->birth_date[0] = date[0];
				ptr->birth_date[1] = date[1];
				ptr->birth_date[2] = date[2];

				should_brake = 1;
				break;
			}
			}
		}
	}

	cout << "\nЗапись успешно изменена!\n";
}

void Note::edit(string phone_number, int key) {
	phone_number = formatNumber(phone_number);

	NOTE* ptr = list;
	
	if (!isExist(phone_number)) {
		cout << "\nТакого номера телефона не существует!\n";
		return;
	}

	while (ptr->phone_number != phone_number)
		ptr = ptr->next;

	string input;

	while (true) {
		if (key == 0 || key == 1) {

			if (key == 0) {
				cout << "Введите новое имя: "; cin >> input;
			}
			if (key == 1) {
				cout << "Введите новую фамилию: "; cin >> input;
			}

			if (!isNameValid(input)) {
				cout << "\nНеверные данные (имя и фамилия должны содержать только буквы).\n";
				cout << "Повторите ввод.\n";
				cin.clear();

				continue;
			}

			if (key == 0) {
				ptr->firstname = input;
				cout << "\nИмя успешно изменено!\n";
			}
			if (key == 1) {
				ptr->lastname = input;
				cout << "\nФамилия успешно изменена!\n";
			}
			break;

		}
		else if (key == 2) {
			cout << "\nВведите новый номер телефона (формат +7XXXXXXXXX): "; cin >> input;

			if (!isNumValid(input)) {
				cout << "\nНеверные данные (номер телефона должен соответствовать формату ";
				cout << "и не должен содержать лишних символов).\n";
				cout << "Повторите ввод.\n";
				cin.clear();

				continue;
			}

			string edited = formatNumber(input);

			if (isExist(edited)) {
				cout << "\nЧеловек с таким номером телефона уже существует!\n";
				cout << "Повторите ввод.\n";

				cin.clear();
				continue;
			}

			ptr->phone_number = edited;
			cout << "\nНомер телефона успешно изменен!\n";
			break;
		}
		else if (key == 3) {
			int date[3];	
			string day; string month; string year;

			cout << "\nВведите новую дату рождения (формат ДД ММ ГГГГ): ";
			cin >> day >> month >> year;

			if (!isNumeric(day) || !isNumeric(month) || !isNumeric(year)
				|| day.length() > 2 || month.length() > 2 || year.length() > 4) {

				cout << "\nНекорректные данные (дата должна состоять из цифр и иметь верный формат).\n";
				cout << "Повторите ввод.\n";
				cin.clear();

				continue;
			}

			date[0] = stoi(day);
			date[1] = stoi(month);
			date[2] = stoi(year);

			if (!isDateValid(date)) {
				cout << "\nДата рождения введена некорректно.\n";
				cout << "Повторите ввод.\n";
				cin.clear();

				continue;
			}

			ptr->birth_date[0] = date[0];
			ptr->birth_date[1] = date[1];
			ptr->birth_date[2] = date[2];

			cout << "\nДата рождения изменена успешно!\n";
			break;
		}
	}
}

void Note::find() {

	string input; string value;
	int date[3];

	cout << "\n--- Cпособы поиска записи ---\n"
		"0 - по имени\n1 - по фамилии\n"
		"2 - по номеру телефона\n3 - по дате рождения\n";

	while (true) {
		cout << "\nВведите способ поиска записи: "; cin >> input;

		if (input == "0" || input == "1") {
			cout << "\nВведите значение для поиска: "; cin >> value;
		
			if (!isNameValid(value)) {
				cout << "\nНеверные данные (имя и фамилия должны содержать только буквы).\n";
				cout << "Повторите ввод.\n";
				cin.clear();

				continue;
			}
		}
		else if (input == "2") {
			cout << "\nВведите значение для поиска: "; cin >> value;

			if (!isNumValid(value)) {
				cout << "\nНеверные данные (номер телефона должен соответствовать формату (+7XXXXXXXXX) ";
				cout << "и не должен содержать лишних символов).\n";
				cout << "Повторите ввод.\n";
				cin.clear();

				continue;
			}
		}
		else if (input == "3") {
			string day; string month; string year;

			cout << "\nВведите дату рождения (формат ДД ММ ГГГГ): ";

			cin >> day >> month >> year;

			if (!isNumeric(day) || !isNumeric(month) || !isNumeric(year)
				|| day.length() > 2 || month.length() > 2 || year.length() > 4) {
				cout << "\nНекорректные данные (дата должна состоять из цифр и иметь верный формат).\n";
				cout << "Повторите ввод.\n";
				cin.clear();

				continue;
			}

			date[0] = stoi(day);
			date[1] = stoi(month);
			date[2] = stoi(year);

			if (!isDateValid(date)) {
				cout << "\nДата рождения введена некорректно.\n";
				cout << "Повторите ввод.\n";
				cin.clear();

				continue;
			}

		}
		else {
			cout << "\nНекорректный ввод, повторите попытку.\n";
			continue;
		}

		if (input == "0" || input == "1" || input == "2")
			get(value, stoi(input));
		else
			get(date);

		break;
	}
}

void Note::sortManager() {
	cout << "\n--- Cпособы сортировки списка ---\n"
			"0 - по имени\n1 - по фамилии\n"
			"2 - по дате рождения\n";

	cout << "\n--- Дополнительные параметры ---\n"
			"0 - сортировка по возрастанию\n1 - сортировка по убыванию\n\n";

	string key, reverse_key;

	while (true) {
		cout << "Введите способ сортировки списка: "; cin >> key;
		cout << "Введите дополнительный параметр: "; cin >> reverse_key;

		if (!isNumeric(key) || !isNumeric(reverse_key) ||  stoi(key) > 3 || stoi(key) < 0 ||
			stoi(reverse_key) > 1 || stoi(reverse_key) < 0) {

			cout << "\nНекорректные данные, повторите ввод.\n";
			cin.clear();
			continue;
		}

		if (list == nullptr) {
			cout << "\nСписок пуст!\n";
			return;
		}

		sort(stoi(key), stoi(reverse_key));
		cout << "\nСписок успешно отсортирован!\n\n";
		break;
	}
}

void Note::editManager() {
	
	string phone_number, key;

	cout << "\n--- Отредактировать значение списка ---\n"
		"0 - имя\n1 - фамилию\n"
		"2 - номер телефона\n3 - дату рождения\n4 - все данные\n\n";

	while (true) {
		cout << "Введите параметр для редактирования: "; cin >> key;
		cout << "Введите номер телефона: "; cin >> phone_number;

		if (!isNumeric(key) || key.length() > 10) {
			cout << "\nНекорректные данные, повторите ввод.\n";
			cin.clear();
			continue;
		}
		if (stoi(key) > 4 || stoi(key) < 0) {
			cout << "\nНекорректные данные, повторите ввод.\n";
			cin.clear();

			continue;
		}

		if (!isNumValid(phone_number)) {
			cout << "\nНеверные данные (номер телефона должен соответствовать формату (+7XXXXXXXXX) ";
			cout << "и не должен содержать лишних символов).\n";
			cout << "Повторите ввод.\n";
			cin.clear();

			continue;
		}

		if (stoi(key) == 4) {
			editAll(phone_number);
		}
		else {
			edit(phone_number, stoi(key));
		}

		break;
	}
}

Note::~Note() {
	NOTE* ptr;

	while (list != nullptr) {
		ptr = list;
		list = list->next;

		delete[] ptr->birth_date;
		delete ptr;
	}
}

void Note::save() {

	json data;
	NOTE* ptr = list;

	while (ptr != nullptr) {
		json elem;

		elem[u8"Имя"] = cp1251_to_utf8(ptr->firstname);
		elem[u8"Фамилия"] = cp1251_to_utf8(ptr->lastname);
		elem[u8"Номер телефона"] = cp1251_to_utf8(ptr->phone_number);

		elem[u8"Дата рождения"] = {
		cp1251_to_utf8(to_string(ptr->birth_date[0])),
		cp1251_to_utf8(to_string(ptr->birth_date[1])),
		cp1251_to_utf8(to_string(ptr->birth_date[2]))
		};

		data.push_back(elem);

		ptr = ptr->next;
	}

	ofstream f("D:\\Other\\C++ Scripts\\PhoneBook\\Data.json");
	f << setw(4) << data;
	f.close();

	cout << "\033[32m" << "\n\nДанные успешно записаны в файл \"Data.json\"!\n\n" << "\033[0m";
}

void Note::extract() {
	ifstream f("D:\\Other\\C++ Scripts\\PhoneBook\\Data.json");

	json data;

	try {
		data = json::parse(f);
		remove();

		for (auto elem : data) {
			NOTE* input = new NOTE;

			string value;

			value = Utf8_to_cp1251(elem[u8"Имя"]);

			if (!isNameValid(value)) {
				cout << "\nНеверные данные \"" << value <<"\" (имя и фамилия должны содержать только буквы).\n";
				cout << "Повторите ввод.\n";
				cin.clear();

				delete input;
				continue;
			}
			input->firstname = value;

			value = Utf8_to_cp1251(elem[u8"Фамилия"]);

			if (!isNameValid(value)) {
				cout << "\nНеверные данные \"" << value << "\" (имя и фамилия должны содержать только буквы).\n";
				cout << "Повторите ввод.\n";
				cin.clear();

				delete input;
				continue;
			}
			input->lastname = value;

			value = Utf8_to_cp1251(elem[u8"Номер телефона"]);
			value = simpleNumber(value);

			if (!isNumValid(value)) {
				cout << "\nНеверные данные \"" << value << "\" (номер телефона должен соответствовать"
					"формату (+7XXXXXXXXX)\n и не должен содержать лишних символов).\n";

				delete input;
				continue;
			}

			NOTE* temp = list;
			bool isExist = 0;

			while (temp != nullptr) {
				if (value == temp->phone_number) {
					cout << "\nЧеловек с таким номером телефона \"" << value << "\" уже существует!\n";
					isExist = 1;
					break;
				}
				temp = temp->next;
			}

			if (isExist == 1) {
				delete input;
				continue;
			}

			value = formatNumber(value);
			input->phone_number = value;

			// Парсинг даты !!!
			int date[3]{0, 0, 0};
			input->birth_date = new int[3];

			string day = Utf8_to_cp1251(elem[u8"Дата рождения"][0]);
			string month = Utf8_to_cp1251(elem[u8"Дата рождения"][1]);
			string year = Utf8_to_cp1251(elem[u8"Дата рождения"][2]);

			if (!isNumeric(day) || !isNumeric(month) || !isNumeric(year)
				|| day.length() > 2 || month.length() > 2 || year.length() > 4) {

				cout << "\nНекорректные данные\"" << day + "." + month + "." + year <<
					"\" (дата должна состоять из цифр и иметь верный формат).\n";

				delete[] input->birth_date;
				delete input;
				continue;
			}

			date[0] = stoi(day);
			date[1] = stoi(month);
			date[2] = stoi(year);

			if (!isDateValid(date)) {
				cout << "\nДата рождения " << day + "." + month + "." + year << "введена некорректно.\n";

				delete[] input->birth_date;
				delete input;
				continue;
			}

			input->birth_date[0] = date[0];
			input->birth_date[1] = date[1];
			input->birth_date[2] = date[2];

			push(input);
			length += 1;
		}
	}
	catch (json::exception& e) {
		cout << "\033[31m" << "\nОшибка чтения файла json! Проверьте корректность формата записи.\n"
			 <<"\033[0m";

		cout << "\nФормат JSON: \n\n[ ";
		cout << "\n { \n  \"Дата рождения\": [ \"...\", \"...\", \"...\" ],\n";
		cout << "  \"Имя\":" << "\"...\",\n";
		cout << "  \"Номер телефона\": \"...\",\n";
		cout << "  \"Фамилия\": \"...\" \n }, \n ... \n]\n\n";

		cout << "\n" << Utf8_to_cp1251(e.what()) << "\n";
		return;
	}

	cout << "\033[32m" << "\nДанные успешно считаны из файла \"Data.json\"!\n\n" << "\033[0m";

	f.close();
}