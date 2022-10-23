#pragma once

#include <iostream>
#include <string>

using namespace std;

bool isNumValid(string phone_number);
bool isNameValid(string name);
bool isDateValid(int date[3]);
bool isNumeric(string s);

bool is_valid_utf8(string input_str);
wstring string_to_wstring(string str);
string cp1251_to_utf8(string input_str);
string Utf8_to_cp1251(string input_string);

string readNumber();
string simpleNumber(string number);
string formatName(string name);
string formatNumber(string number);

struct NOTE {
	string firstname;
	string lastname;
	string phone_number;

	int* birth_date;

	NOTE* next = nullptr;
};

class Note {
	int length = 0;

	NOTE* list = nullptr;

	bool isExist(string phone_number);
	bool compDates(NOTE* ptr1, NOTE* ptr2);
	NOTE* getTail(NOTE* head);
	NOTE* divide(NOTE* head, NOTE* end, NOTE** newhead, 
		         NOTE** newend, int key, int reverse_key);
	NOTE* quickSort(NOTE* head, NOTE* end, int key, int reverse_key);

public:

	void add();
	void push(NOTE* elem);
	void remove();
	void remove(string phone_number);

	void edit(string phone_number, int key);
	void editAll(string phone_number);

	void sort(int key, int reverse_key);
	void editManager();
	void sortManager();

	void get(string value, int key);
	void get(int birth_date[3]);
	void find();

	void show();
	void show(NOTE* person);

	void extract();
	void save();

	~Note();
};