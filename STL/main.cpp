#include <iostream>
#include <array>
#include <vector>
#include <list>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n--------------------------------------------------------------\n"

template<typename T> void print(T& Struct);

template<typename T> void vector_info(const std::vector<T>& vec);
template<typename T> void list_info(const std::list<T>& list);

template<typename T> void vector_insert(std::vector<T>& vec, const int pos, const T val);
template<typename T> void vector_erase(std::vector<T>& vec, const int pos);

template<typename T> void list_insert(std::list<T>& list, const int pos, const T val);
template<typename T> void list_erase(std::list<T>& list, const int pos);

//#define STL_ARRAY
//#define STL_VECTOR
//#define VECTOR_ADDING_REMOVING_ELEMENTS
#define LIST_ADDING_REMOVING_ELEMENTS

void main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello STL" << endl;

#ifdef STL_ARRAY

	const int N = 5;
	std::array<int, N> arr = { 3, 5, 8, 13, 21 };

	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << tab;
	cout << endl;

#endif // STL_ARRAY

#ifdef STL_VECTOR

	std::vector<int> vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };

	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << tab;
	cout << endl;
	vector_info(vec);

	vec.push_back(55);
	for (int i = 0; i < vec.size(); i++)
		cout << vec.at(i) << tab;
	cout << endl;
	vector_info(vec);
	vec.reserve(24);
	vector_info(vec);

	vec.shrink_to_fit();
	vector_info(vec);

	vec.resize(8);
	for (std::vector<int>::iterator it = vec.begin(); it < vec.end(); ++it)
		cout << *it << tab;
	cout << endl;
	vector_info(vec);

	vec.resize(14);
	for (int i : vec)
		cout << i << tab;
	cout << endl;
	vector_info(vec);
#endif // STL_VECTOR

#ifdef VECTOR_ADDING_REMOVING_ELEMENTS
	std::vector<int> vec = { 3, 5, 8, 13, 21 };

	print(vec);
	vector_info(vec);

	int pos, val;
	cout << "Введите индекс добавляемого элемента: "; cin >> pos;
	cout << "Введите добавляемый элемент: "; cin >> val;
	vector_insert(vec, pos, val);

	print(vec);
	vector_info(vec);

	cout << "Введите индекс удаляемого элемента: "; cin >> pos;
	vector_erase(vec, pos);

	print(vec);
	vector_info(vec);
#endif // VECTOR_ADDING_REMOVING_ELEMENTS

#ifdef LIST_ADDING_REMOVING_ELEMENTS
	std::list<int> list = { 3, 5, 8, 13, 21 };

	print(list);
	list_info(list);

	int pos, val;
	cout << "Введите индекс добавляемого элемента: "; cin >> pos;
	cout << "Введите добавляемый элемент: "; cin >> val;
	list_insert(list, pos, val);

	print(list);
	list_info(list);

	cout << "Введите индекс удаляемого элемента: "; cin >> pos;
	list_erase(list, pos);

	print(list);
	list_info(list);
#endif // LIST_ADDING_REMOVING_ELEMENTS

}

template<typename T> void print(T& Struct)
{
	for (int i : Struct)
		cout << i << tab;
	cout << endl;
}

template<typename T> void vector_info(const std::vector<T>& vec)
{
	cout << "Size: " << vec.size() << endl;
	cout << "Capacity: " << vec.capacity() << endl;
	cout << "MaxSize: " << vec.max_size() << endl;
}
template<typename T> void list_info(const std::list<T>& list)
{
	cout << "Size: " << list.size() << endl;
	cout << "MaxSize: " << list.max_size() << endl;
}

template<typename T> void vector_insert(std::vector<T>& vec, const int pos, const T val)
{
	if (pos > vec.size()) cerr << "Error: Введен не допустимый индекс!!!" << endl;
	else
	{
		std::vector<int>::iterator it = vec.begin()/* + pos*/;
		advance(it, pos);
		vec.insert(it, val);
	}
}
template<typename T> void vector_erase(std::vector<T>& vec, const int pos)
{
	if (pos > vec.size()) cerr << "Error: Введен не допустимый индекс!!!" << endl;
	else
	{
		std::vector<int>::iterator it = vec.begin()/* + pos*/;
		advance(it, pos);
		vec.erase(it, it + 1);
		vec.shrink_to_fit();
	}
}

template<typename T> void list_insert(std::list<T>& list, const int pos, const T val)
{
	if (pos > list.size()) cerr << "Error: Введен не допустимый индекс!!!" << endl;
	else
	{
		std::list<int>::iterator it = list.begin()/* + pos*/;
		advance(it, pos);
		list.insert(it, val);
	}
}
template<typename T> void list_erase(std::list<T>& list, const int pos)
{
	if (pos > list.size()) cerr << "Error: Введен не допустимый индекс!!!" << endl;
	else
	{
		std::list<int>::iterator it = list.begin();
		std::list<int>::iterator it2 = list.begin();
		advance(it, pos);
		advance(it2, pos + 1);
		list.erase(it, it2);
	}
}