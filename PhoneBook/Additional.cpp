#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

#include <windows.h>
#include <stringapiset.h>

using namespace std;

bool isNumValid(string phone_number) {

	string temp;
	temp += phone_number[0];
	temp += phone_number[1];

	if ((phone_number.length() != 11 && phone_number[0] == '8') ||
		(phone_number.length() != 12 && phone_number[1] == '7') ||
		(phone_number[0] != '8' && temp != "+7"))

		return false;

	for (int i = 0; i < phone_number.length(); i++) {
		if (i == 0 && phone_number[i] == '+')
			continue;
		else if (!isdigit(phone_number[i]))
			return false;
	}

	return true;
}

string formatNumber(string number) {
	string formated("");

	int f = ((number[0] == '+' && number[1] == '7') ?  1 : 0);

	if (!f) {
		number = "+7" + number.substr(1);
	}

	for (int i = 0; i < number.length(); i++) {
		if (i == 2) {
			formated += ' '; formated += '(';
			formated += number[i];
		}
		else if (i == 4) {
			formated += number[i];
			formated += ')'; formated += ' ';
		}
		else if (i == 7) {
			formated += number[i];
			formated += ' ';
		}
		else if (i == 9) {
			formated += number[i];
			formated += '-';
		}
		else {
			formated += number[i];
		}
	}

	return formated;
}

bool isNameValid(string name) {
	if (name.length() < 1)
		return false;

	for (int i = 0; i < name.length(); i++) {
		if (!isalpha((unsigned char)name[i]))
			return false;
	}

	return true;
}

string formatName(string name) {
	name[0] = toupper(name[0]);

	if (name[0] == 'я')
		name[0] = 'Я';

	for (int i = 1; i < name.length(); i++) {
		name[i] = tolower(name[i]);
	}

	return name;
}

bool isDateValid(int date[3]) {

	auto now = chrono::system_clock::now();
	time_t tt = chrono::system_clock::to_time_t(now);
	tm loc_tm = *localtime(&tt);

	int day = loc_tm.tm_mday;
	int month = loc_tm.tm_mon + 1;
	int year = loc_tm.tm_year + 1900;

	if (date[1] > 12 || date[0] == 0 || date[1] == 0 || date[2] == 0 || date[2] < 1900)
		return false;

	if ((date[0] > day && date[1] >= month && date[2] >= year) ||
		(date[0] == day && date[1] > month && date[2] >= year) ||
		(date[1] > month && date[2] >= year) || (date[2] > year))
		return false;

	bool isLeap = (date[2] % 400 == 0) ||
		((date[2] % 4 == 0) && (date[2] % 100 != 0));

	if (date[0] > 31 && (date[1] == 1 || date[1] == 3 || date[1] == 5
		|| date[1] == 7 || date[1] == 8 || date[1] == 10 || date[1] == 12))
		return false;

	if (date[0] > 28 && date[1] == 2 && isLeap == 0)
		return false;

	if (date[0] > 29 && date[1] == 2 && isLeap == 1)
		return false;

	if (date[0] > 30 && (date[1] == 4 || date[1] == 6 || date[1] == 9 ||
		date[1] == 11))
		return false;

	return true;
}

bool isNumeric(string s) {
	if (s == "")
		return false;

	for (int i = 0; i < s.length(); i++) {
		if (!isdigit(s[i]))
			return false;
	}
	return true;
}

string readNumber() {
	string number;

	while (true) {
		cout << "\nВведите номер телефона (формат +7XXXXXXXXX): "; cin >> number;

		if (!isNumValid(number)) {
			cout << "\nНеверный номер (номер телефона должен соответствовать формату "
				"и не должен содержать лишних символов).\n";

			cout << "Повторите ввод.\n";
			cin.clear();

			continue;
		}
		break;
	}

	return number;
}

string cp1251_to_utf8(string input_str) {

	const char* str = input_str.c_str();

	string res;
	int result_u, result_c;

	result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);

	if (!result_u)
		return 0; 
	
	wchar_t* ures = new wchar_t[result_u];

	if (!MultiByteToWideChar(1251, 0, str, -1, ures, result_u)) {
		delete[] ures;
		return 0;
	}

	result_c = WideCharToMultiByte(65001, 0, ures, -1, 0, 0, 0, 0);
	if (!result_c) {
		delete[] ures;
		return 0;
	}

	char* cres = new char[result_c];

	if (!WideCharToMultiByte(65001, 0, ures, -1, cres, result_c, 0, 0)) {
		delete[] cres;
		return 0;
	}

	delete[] ures;
	res.append(cres);

	delete[] cres;
	return res;
}

bool is_valid_utf8(string input_str) {

	const char* string = input_str.c_str();

	if (!string) { return true; }
	const unsigned char* bytes = (const unsigned char*)string;
	unsigned int cp;
	int num;
	while (*bytes != 0x00) {
		if ((*bytes & 0x80) == 0x00) {
			// U+0000 to U+007F 
			cp = (*bytes & 0x7F);
			num = 1;
		}
		else if ((*bytes & 0xE0) == 0xC0) {
			// U+0080 to U+07FF 
			cp = (*bytes & 0x1F);
			num = 2;
		}
		else if ((*bytes & 0xF0) == 0xE0) {
			// U+0800 to U+FFFF 
			cp = (*bytes & 0x0F);
			num = 3;
		}
		else if ((*bytes & 0xF8) == 0xF0) {
			// U+10000 to U+10FFFF 
			cp = (*bytes & 0x07);
			num = 4;
		}
		else { return false; }
		bytes += 1;
		for (int i = 1; i < num; ++i) {
			if ((*bytes & 0xC0) != 0x80) { return false; }
			cp = (cp << 6) | (*bytes & 0x3F);
			bytes += 1;
		}
		if ((cp > 0x10FFFF) ||
			((cp <= 0x007F) && (num != 1)) ||
			((cp >= 0xD800) && (cp <= 0xDFFF)) ||
			((cp >= 0x0080) && (cp <= 0x07FF) && (num != 2)) ||
			((cp >= 0x0800) && (cp <= 0xFFFF) && (num != 3)) ||
			((cp >= 0x10000) && (cp <= 0x1FFFFF) && (num != 4))) {
			return false;
		}
	}
	return true;
}

string Utf8_to_cp1251(string input_string) {

	const char* str = input_string.c_str();

	string res;
	int result_u, result_c;

	result_u = MultiByteToWideChar(CP_UTF8, 0, str, -1, 0, 0);

	if (!result_u)
		return 0;

	wchar_t* ures = new wchar_t[result_u];

	if (!MultiByteToWideChar(CP_UTF8, 0, str, -1, ures, result_u)) {
		delete[] ures;
		return 0;
	}

	result_c = WideCharToMultiByte(1251, 0, ures, -1, 0, 0, 0, 0);

	if (!result_c) {
		delete[] ures;
		return 0;
	}

	char* cres = new char[result_c];

	if (!WideCharToMultiByte(1251, 0, ures, -1, cres, result_c, 0, 0)) {
		delete[] cres;
		return 0;
	}

	delete[] ures;
	res.append(cres);

	delete[] cres;
	return res;
}

string simpleNumber(string number) {
	string s = "";

	for (int i = 0; i < number.length(); i++) {
		if (number[i] != ' ' && number[i] != '-'
			&& number[i] != '(' && number[i] != ')')
			s += number[i];
	}

	return s;
}