#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 4326)
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <map>
#include <list>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------------------------------------------------------\n"

const std::map<int, std::string> VIOLATIONS =
{
	{1, "Ремень безопасности"},
	{2, "Парковка в неположенном месте"},
	{3, "Пересечение сплошной"},
	{4, "Превышение скорости"},
	{5, "Отсутствие ваодительского удостоверения"},
	{6, "Отсутсвие права управления автомобилем"},
	{7, "Отсутствие страховки"},
	{8, "Проезд на красный"},
	{9, "Выезд на встречную полосу"},
	{10, "Дрифт на перекрестке"},
	{11, "Езда в нетрезвом состоянии"},
	{12, "Оскорбление офицера"},
	{13, "Внесение изменений в конструецию автомобиля"},
	{14, "Перевозка негабаритного груза"},
	{15, "Превышение максимальной нагрузки на ось"},
	{16, "Перевозка ребенка без кресла"},
};

class Crime
{
	//std::string licence_plate;
	int id;
	std::string place;
	tm time;
public:
	/*const std::string& get_licence_plate()const
	{
		return licence_plate;
	}*/
	int get_violation_id()const
	{
		return id;
	}
	const std::string& get_violation()const
	{
		return VIOLATIONS.at(id);
	}
	const std::string& get_place()const
	{
		return place;
	}
	const std::string get_time()const
	{
		/*std::string result = asctime(&time);
		result.pop_back();
		return result;*/
		const int SIZE = 256;
		char formatted[SIZE]{};
		strftime(formatted, SIZE, "%R %e.%m.%Y", &time);
		return formatted;
	}
	/*void set_licence_plate(const std::string& licence_plate)
	{
		this->licence_plate = licence_plate;
	}*/
	void set_violation_id(int id)
	{
		this->id = id;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(const std::string& time)
	{
		//this->time = time;
		char* time_buffer = new char[time.size() + 1] {};
		strcpy(time_buffer, time.c_str());

		int time_elements[5]{};
		int i = 0;
		char delimiters[] = ":./ ";
		for (char* pch = strtok(time_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			time_elements[i++] = std::atoi(pch);

		delete[] time_buffer;

		this->time.tm_hour = time_elements[0];
		this->time.tm_min = time_elements[1];
		this->time.tm_mday = time_elements[2];
		this->time.tm_mon = time_elements[3];
		this->time.tm_year = time_elements[4] - 1900;
	}

	//	Constructors:
	Crime(int violance_id, const std::string& place, const std::string& time)
	{
		this->time = {};
		set_violation_id(violance_id);
		set_place(place);
		set_time(time);
#ifdef DEBUG/
		cout << "Constructor:\t" << this << endl;
#endif // DEBUG
	}
	~Crime()
	{
#ifdef DEBUG
		cout << "Destructor:\t" << this << endl;
#endif // DEBUG
	}

};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << obj.get_time() << tab << obj.get_place() << " - " << obj.get_violation();
}

void print(const std::map<std::string, std::list<Crime>>& base);
void write_to_file(const std::map<std::string, std::list<Crime>>& base, const std::string& filename);
void read_form_file(const std::string& filename);

void main()
{
	setlocale(LC_ALL, "");
	/*Crime crime(1, "ул. Ленина", "18:10 01.09.2024");
	cout << crime << endl;*/

	std::map<std::string, std::list<Crime>> base =
	{
		{"a777bb",{Crime(1, "ул. Ленина", "18:10 01.09.2024"), Crime(2, "пл. Свободы", "12:25 20.08.2024")}},
		{"a000bb", {Crime(6, "ул. Космонавтов", "17:50 01.08.2024"), Crime(8,"ул. Космонавтов", "17:45 01.08.2024")}},
		{"a001aa", {Crime(10, "ул. Пролетарская", "21:50 01.08.2024"), Crime(9,"ул. Пролетарская", "21:50 01.08.2024"), Crime(11,"ул. Пролетарская", "21:50 01.08.2024"), Crime(12,"ул. Пролетарская", "22:05 01.08.2024")}}
	};

	print(base);

	write_to_file(base, "Database.txt");

	//read_form_file();
}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	cout << delimiter << endl;
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin(); map_it != base.end(); ++map_it)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
			cout << tab << *it << endl;
		cout << delimiter << endl;
	}
}

void write_to_file(const std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ofstream fout;
	fout.open(filename);
	fout << "Номер машины" << tab << "Дата и время" << tab << "Место и нарушение" << endl;
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin(); map_it != base.end(); ++map_it)
	{
		fout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			fout << tab << *it << endl;
		}
	}
}
void read_form_file(const std::string& filename)
{
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		std::string line;
		while (getline(fin, line))
		{
			cout << line << endl;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
}