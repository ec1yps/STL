#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n---------------------------------------------------------------\n"
#define tab "\t"\

void print_by_car_plate(std::multimap<std::string, std::string>& database, std::string& key);
void print_all_database(std::multimap<std::string, std::string>& database);

//#define STL_MAP

void main()
{
	setlocale(LC_ALL, "");

#ifdef STL_MAP
	std::map<int, std::string> week =
	{
		std::pair<int, std::string>(0, "Sanday"),
		std::pair<int, std::string>(1, "Monday"),
		std::pair<int, std::string>(2, "Tuesday"),
		std::pair<int, std::string>(3, "Wednesday"),
		{4, "Thursday"},
		{5, "Friday"},
		{6, "Saturday"}
	};

	for (std::map<int, std::string>::iterator it = week.begin(); it != week.end(); ++it)
		cout << it->first << tab << it->second << endl;

#endif // STL_MAP


	std::multimap<std::string, std::string> database;

	database.emplace("A324OP|01", "Превышение скорости.");
	database.emplace("T846EA|21", "Превышение скорости.");
	database.emplace("O632KB|23", "Превышение скорости.");
	database.emplace("C235CE|12", "Пересечение сплошной.");
	database.emplace("A324OP|01", "Пересечение сплошной.");
	
	int n;
	do
	{
		cout << "1. Вывести всю базу" << endl;
		cout << "2. Вывести штрафы по номеру" << endl;
		cout << "3. Вывести штрафы по нескольким номерам" << endl;
		cout << "4. Выход" << endl;
		cout << "Выберете пункт: "; cin >> n;

		std::string key;
		switch (n)
		{
		case 1: 
			system("cls");
			print_all_database(database);
			system("pause");
			break;
		case 2: 
			system("cls");
			cout << "Введите номер машины: "; cin >> key;
			print_by_car_plate(database, key);
			system("pause");
			break;
		case 3:
			system("cls");
			int m;
			cout << "Введите количество проверяемых номеров: "; cin >> m;
			for (int i = 0; i < m; i++)
			{
				std::string key;
				cout << "Введите номер машины: "; cin >> key;
				print_by_car_plate(database, key);
				cout << delimiter << endl;
			}
			system("pause");
			break;
		}
		system("cls");

	} while (n!=4);

	std::ofstream fout;
	fout.open("Database.txt");
	fout.clear();
	for (std::map<std::string, std::string>::iterator it = database.begin(); it != database.end(); ++it)
		fout << it->first << tab << it->second << endl;
	fout.close();

	std::ifstream fin("Database.txt");
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			const int SIZE = 102400;
			char buffer[SIZE]{};
			//fin >> buffer;
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
}

void print_by_car_plate(std::multimap<std::string, std::string>& database, std::string& key)
{
	std::pair<std::multimap<std::string, std::string>::iterator, std::multimap<std::string, std::string>::iterator> res = database.equal_range(key);

	for (std::map<std::string, std::string>::iterator it = res.first; it != res.second; ++it)
		cout << it->second << endl;
}
void print_all_database(std::multimap<std::string, std::string>& database)
{
	for (std::map<std::string, std::string>::iterator it = database.begin(); it != database.end(); ++it)
		cout << it->first << tab << it->second << endl;
}