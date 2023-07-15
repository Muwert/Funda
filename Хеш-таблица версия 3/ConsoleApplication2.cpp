// Хеш-таблица.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <cmath>
#include <sstream>

struct DataSdachi
{
	int date;
	int month;
	int year;
};


struct Time
{
	int minute;
	int seconds;
};


struct HT_item
{
	DataSdachi data;
	int pasport;
	int udostoverenie;
	Time time;
	int hash;
};

class Hash_Table
{
public:

	Hash_Table(int size)
	{
		sizeHT = size;
		items = new HT_item[size];
		status.resize(size);
	}

	~Hash_Table() = default;

	 int FirstHF(int _date, int _mounth, int _year, int _pasport)
	{
		int hash;
		std::stringstream ss;
		long long sovokypnost;
		ss << _date << _mounth << _year << _pasport;
		ss >> sovokypnost;
		int sum1 = 0;
		long long j = pow(10, sizeHT);
		while (sovokypnost > 0)
		{
			hash = sovokypnost % j;
			sum1 = sum1 + hash;
			sovokypnost = (sovokypnost - sovokypnost%j)/j;
		}
		return sum1 % sizeHT;
	}

	int SecondHF(int FirstHash, int k1, int step)
	{
		return (FirstHash + k1 * step) % sizeHT;
	}

	void Add(HT_item& el, int k)
	{
		
		int key1 = FirstHF(el.data.date, el.data.month, el.data.year, el.pasport);
			el.hash = key1;
			if (status[key1] == 0)
			{
				status[key1] = 1;
				items[key1] = el;
			}
			else
			{
				if ((status[key1] == 2) || ((status[key1] == 1) && ((el.data.date != items[key1].data.date) || (el.data.month != items[key1].data.month) || (el.data.year != items[key1].data.year) || (el.pasport != items[key1].pasport))))
				{
					int key2 = CollisionAdd(key1, status, el, k);
					if (key2 != -1)
					{
						status[key2] = 1;
						items[key2] = el;
					}
				}
			}
		}

	int CollisionAdd(int key, std::vector<int>status, HT_item el, int k)
	{

		int num = 1, tmp = key, step = 1, tmp1 = -2;
		bool same = false, del = false; 
		int i = 0;
			while ((status[tmp] != 0) && (num <= sizeHT))
			{
				if ((status[tmp] == 1) && (el.data.date == items[tmp].data.date) && (el.data.month == items[tmp].data.month) && (el.data.year == items[tmp].data.year) && (el.pasport == items[tmp].pasport))
				{
					same = true;
				}
				if ((status[tmp] == 2) && (del != true))
				{
					tmp1 = tmp;
					del = true;
				}
				tmp = SecondHF(key, k, step);
				num++;
				step++;
			}
			if (!same)
			{
				if (((status[tmp] == 0) && (del == false)) || ((status[tmp] == 2) && (del == false)))
				{
					key = tmp;
				}
				else if (((status[tmp] == 2) && (del == true)) || ((status[tmp] == 1) && (del == true)) || ((status[tmp] == 0) && (del == true)))
				{
					key = tmp1;
				}
				else if ((status[tmp] == 1) && (del == false))
				{
					std::cout << "Нет места" << std::endl;
					key = -1;
				}
				return key;
			}
			else
				return key = -1;
	}


	bool Search(HT_item el, int k)
	{
			int step = 0;

			int key1 = FirstHF(el.data.date, el.data.month, el.data.year, el.pasport);

			if ((status[key1] == 1) && (el.data.date == items[key1].data.date) && (el.data.month == items[key1].data.month) && (el.data.year == items[key1].data.year) && (el.pasport == items[key1].pasport))
			{
				std::cout << items[key1].hash << ". " << items[key1].data.date << "." << items[key1].data.month << "." << items[key1].data.year << " " 
				  << items[key1].pasport << " " << items[key1].udostoverenie << " " << items[key1].time.minute << ":" << items[key1].time.seconds << std::endl;
				return true;
			}
			else
			{
				int key2 = CollisionDelete(key1, status, el, step, k);
				if ((key2 != -1) && (el.data.date == items[key2].data.date) && (el.data.month == items[key2].data.month) && (el.data.year == items[key2].data.year) && (el.pasport == items[key2].pasport))
				{
					std::cout << items[key2].hash << ". " << items[key2].data.date << "." << items[key2].data.month << "." << items[key2].data.year << " "
						<< items[key2].pasport << " " << items[key2].udostoverenie << " " << items[key2].time.minute << ":" << items[key2].time.seconds << std::endl;
					return true;
				}
				else
				{
					std::cout << "False\n";
					return false;
				}
			}
	}

	bool Delete(HT_item el, int k)
	{
		int step = 0;
		int n = 0;
		el.hash = FirstHF(el.data.date, el.data.month, el.data.year, el.pasport);
		int key1 = FirstHF(el.data.date, el.data.month, el.data.year, el.pasport);
		if ((status[key1] == 1) && (el.data.date == items[key1].data.date) && (el.data.month == items[key1].data.month) && (el.data.year == items[key1].data.year) && (el.pasport == items[key1].pasport))
		{
			status[key1] = 2;
			return true;
		}
		else
		{
			int key2 = CollisionDelete(key1, status, el, step, k);
			if ((key2 != -1) && (el.data.date == items[key2].data.date) && (el.data.month == items[key2].data.month) && (el.data.year == items[key2].data.year) && (el.pasport == items[key2].pasport))
			{
				status[key2] = 2;
				return true;
			}
			else if (key2 == -1)
			{
				int key3 = CollisionDelete(key1, status, el, step, k);
				while ((key3 == -1) && (n < sizeHT))
				{
					key3 = CollisionDelete(key1, status, el, step, k);
					n++;
				}
				if ((el.data.date == items[key3].data.date) && (el.data.month == items[key3].data.month) && (el.data.year == items[key3].data.year) && (el.pasport == items[key3].pasport))
				{
					status[key3] = 2;
					return true;
				}
				else return false;
			}
			else
				return false;
		}
	}

	int CollisionDelete(int key, std::vector<int>status, HT_item el, int& step, int k)
	{
		int num = 1, tmp = key;
		while (num <= sizeHT)
		{
			num++;
			step++;
			tmp = SecondHF(key, k, step);
			if ((status[tmp] == 0) || (status[tmp] == 2))
			{
				tmp = -1;
				break;
			}
			else if ((status[tmp] == 1) && (el.data.date == items[tmp].data.date) && (el.data.month == items[tmp].data.month) && (el.data.year == items[tmp].data.year) && (el.pasport == items[tmp].pasport))
			{
				break;
			}
		}
		return tmp;
	}

	void Print()
	{
		for (int i = 0; i < sizeHT; i++)
		{
			std::cout << "[" << i << "]" << " ";
			if (status[i] == 1)
				std::cout << "First Hash - " << items[i].hash << ". " << items[i].data.date  << "." << items[i].data.month << "." << items[i].data.year << " "
				<< items[i].pasport << " " << items[i].udostoverenie << " " << items[i].time.minute << ":" << items[i].time.seconds << " " << "Status [" << status[i] << "]" << std::endl;
			else
				std::cout << " " << " Status [" << status[i] << "]" << std::endl;
		}
		std::cout << std::endl;
	}






private:
	int sizeHT, k1;
	HT_item* items;
	std::vector <int> status;


};

int main()
{
	setlocale(LC_ALL, "rus");
	int size, k;
	k = 2;
	std::cin >> size;
	Hash_Table Table(size);
	HT_item el;

	//el.data.date = 13;
	//el.data.month = 4;
	//el.data.year = 2013;
	//el.pasport = 333326;
	//el.udostoverenie = 999999999;
	//el.time.minute = 23;
	//el.time.seconds = 30;
	//Table.Add(el, k);
	//Table.Print();

	//el.data.date = 13;
	//el.data.month = 4;
	//el.data.year = 2013;
	//el.pasport = 333326;
	//el.udostoverenie = 999999999;
	//el.time.minute = 23;
	//el.time.seconds = 30;
	//Table.Add(el, k);
	//Table.Print();

	//el.data.date = 13;
	//el.data.month = 4;
	//el.data.year = 2013;
	//el.pasport = 333327;
	//el.udostoverenie = 999933999;
	//el.time.minute = 23;
	//el.time.seconds = 30;
	//Table.Add(el, k);
	//Table.Print();

	//el.data.date = 13;
	//el.data.month = 4;
	//el.data.year = 2013;
	//el.pasport = 333328;
	//el.udostoverenie = 999933999;
	//el.time.minute = 23;
	//el.time.seconds = 30;
	//Table.Add(el, k);
	//Table.Print();

	/*el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333326;
	el.udostoverenie = 999999999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Delete(el, k);
	Table.Print();

	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333327;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Delete(el, k);
	Table.Print();

	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333328;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Delete(el, k);
	Table.Print();*/

	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333327;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();


	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333328;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();

	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333329;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();


	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333330;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();

	Table.Search(el, k);

	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333331;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Search(el, k);

	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333332;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();


	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333333;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();

	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333334;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();


	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333335;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();
	Table.Search(el, k);

	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333336;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();
	Table.Search(el, k);

	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333337;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();
	Table.Search(el, k);
	/*el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2014;
	el.pasport = 333333;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Delete(el, k);
	Table.Print();

	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333331;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Delete(el, k);
	Table.Print();

	Table.Add(el, k);
	Table.Print();

	;
	Table.Delete(el, k);
	Table.Print();*/

	/*el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333366;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();

	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333376;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();

	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333386;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();*/

	/*el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333353;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();

	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333363;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();*/

	/*el.data.date = 10;
	el.data.month = 1;
	el.data.year = 2013;
	el.pasport = 333333;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();
	
	el.data.date = 10;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333330;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();

	Table.Search(el, k);

	el.data.date = 10;
	el.data.month = 4;
	el.data.year = 2023;
	el.pasport = 333330;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();
	Table.Search(el, k);

	el.data.date = 10;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333330;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Delete(el,k);
	Table.Print();

	el.data.date = 10;
	el.data.month = 4;
	el.data.year = 2023;
	el.pasport = 333330;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();

	el.data.date = 12;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333333;
	el.udostoverenie = 999999999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Delete(el, k);
	Table.Print();
	Table.Delete(el, k);
	Table.Print();

	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333333;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Delete(el, k);
	Table.Print();

	el.data.date = 10;
	el.data.month = 1;
	el.data.year = 2013;
	el.pasport = 333333;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Delete(el, k);
	Table.Print();

	el.data.date = 10;
	el.data.month = 4;
	el.data.year = 2023;
	el.pasport = 333330;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Delete(el, k);
	Table.Print();

	el.data.date = 10;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333333;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Delete(el, k);
	Table.Print();


	Table.Delete(el, k);
	Table.Print();

	el.data.date = 12;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333333;
	el.udostoverenie = 999999999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();

	el.data.date = 12;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333333;
	el.udostoverenie = 999999999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();

	el.data.date = 13;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333333;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();

	el.data.date = 10;
	el.data.month = 4;
	el.data.year = 2013;
	el.pasport = 333333;
	el.udostoverenie = 999933999;
	el.time.minute = 23;
	el.time.seconds = 30;
	Table.Add(el, k);
	Table.Print();*/


	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
