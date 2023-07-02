// Хеш-таблица.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <cmath>


struct Room
{
	char litera;
	int digit;
};

struct FIO
{
	std::string fullname;
};

struct Time
{
	int hour;
	int minute;
};

struct subject
{
	std::string object;
};

struct HT_item
{
	Room room;
	FIO fios;
	Time times;
	subject obj;
	int hash;
};

class Hash_Table
{
public:

	Hash_Table(int size, int k)
	{
		sizeHT = size;
		items = new HT_item[size];
		k1 = k;
		status.resize(size);
	}

	~Hash_Table() = default;

	int FirstHF(int hour, int minute, std::string fiokey)
	{
		int sum = 0;
		int sum1 = 0;
		sum = sum + hour + minute;
		int j = pow(10, sizeHT);
		for (int i = 0; i < fiokey.length(); i++)
		{
			sum = sum + (int)fiokey[i];
		}
		while (sum > 0)
		{
			int hash = sum % j;
			sum1 = sum1 + hash;
			sum = (sum - hash) / j;
		}
		return sum1 % sizeHT;
	}

	int SecondHF(int FirstHash, int step)
	{
		return (FirstHash + k1 * step) % sizeHT;
	}

	void Add(HT_item& el)
	{
		if (count < sizeHT)
		{
			int key1 = FirstHF(el.times.hour,el.times.minute,el.fios.fullname);
			el.hash = key1;
			if (status[key1] == 0)
			{
				status[key1] = 1;
				items[key1] = el;
				count++;
			}
			else
			{
				if ((status[key1] == 2) || ((status[key1] == 1) && (std::tie(el.fios.fullname,el.hash, el.obj.object,el.room.digit,el.room.litera,el.times.hour,el.times.minute) != 
					                                                std::tie(items[key1].fios.fullname, items[key1].hash, items[key1].obj.object, items[key1].room.digit, items[key1].room.litera, items[key1].times.hour, items[key1].times.minute))))
				{
					int key2 = CollisionAdd(key1, status, el);
					if (key2 != -1)
					{
						status[key2] = 1;
						items[key2] = el;
						count++;
					}
				}
			}
		}
		else
			std::cout << "таблица заполнена..." << std::endl;

	}

	int CollisionAdd(int key, std::vector<int>status, HT_item el)
	{

		int num = 1, tmp = key, step = 1;
		bool zero = false, same = false;
		while ((status[tmp] != 0) && (num <= sizeHT))
		{
			tmp = SecondHF(key,step);
			if ((status[tmp] == 1) && (std::tie(el.fios.fullname, el.hash, el.obj.object, el.room.digit, el.room.litera, el.times.hour, el.times.minute) ==
				                       std::tie(items[tmp].fios.fullname, items[tmp].hash, items[tmp].obj.object, items[tmp].room.digit, items[tmp].room.litera, items[tmp].times.hour, items[tmp].times.minute)))
			{
				same = true;
			}
			num++;
			step++;
		}
		num = 1;
		if (!same)
		{
			if (status[tmp] == 0)
			{
				zero = true;
			}
			if (!zero)
			{
				tmp = key;
				while ((status[tmp] != 2) && (num <= sizeHT))
				{
					tmp = SecondHF(key,step);
					num++;
					step++;
				}
			}
			key = tmp;
			return key;
		}
		else
			return key = -1;

	}

	int Collision(int key, std::vector<int>status, HT_item el, int& step)
	{
		int num = 1, tmp = key;
		while (num <= sizeHT)
		{
			num++;
			step++;
			tmp = SecondHF(key,step);
			if ((status[tmp] == 0) || (status[tmp] == 2))
			{
				tmp = -1;
				break;
			}
			else if ((status[tmp] == 1) && (std::tie(el.fios.fullname, el.hash, el.obj.object, el.room.digit, el.room.litera, el.times.hour, el.times.minute) ==
				                            std::tie(items[tmp].fios.fullname, items[tmp].hash, items[tmp].obj.object, items[tmp].room.digit, items[tmp].room.litera, items[tmp].times.hour, items[tmp].times.minute)))
			{
				break;
			}
		}
		return tmp;
	}

	bool Search(HT_item el)
	{
		int step = 0;
		if (count != 0)
		{
			int key1 = FirstHF(el.times.hour, el.times.minute, el.fios.fullname);

			if (status[key1] == 1 && (std::tie(el.fios.fullname, el.hash, el.obj.object, el.room.digit, el.room.litera, el.times.hour, el.times.minute) ==
				                      std::tie(items[key1].fios.fullname, items[key1].hash, items[key1].obj.object, items[key1].room.digit, items[key1].room.litera, items[key1].times.hour, items[key1].times.minute)))
			{
				std::cout << items[key1].hash << ". " << items[key1].fios.fullname << " " << items[key1].times.hour << ":" << items[key1].times.minute << std::endl;
				return true;
			}
			else
			{
				int key2 = Collision(key1, status, el, step);
				if ((key2 != -1) && (std::tie(el.fios.fullname, el.hash, el.obj.object, el.room.digit, el.room.litera, el.times.hour, el.times.minute) ==
					                 std::tie(items[key2].fios.fullname, items[key2].hash, items[key2].obj.object, items[key2].room.digit, items[key2].room.litera, items[key2].times.hour, items[key2].times.minute)))
				{
					std::cout << items[key2].hash << ". " << items[key2].fios.fullname << " " << items[key2].times.hour << ":" << items[key2].times.minute << std::endl;
					return true;
				}
				else
				{
					std::cout << "False\n"; 
					return false;
				}
			}

		}
		else
		{
			std::cout << "таблица пуста..." << std::endl;
			return false;
		}
	}

	bool Delete(HT_item el)
	{
		int step = 0;
		int n=0;
		if (count != 0)
		{
			el.hash = FirstHF(el.times.hour, el.times.minute, el.fios.fullname);
			int key1 = FirstHF (el.times.hour, el.times.minute, el.fios.fullname);
			if ((status[key1] == 1) && (std::tie(el.fios.fullname, el.hash, el.obj.object, el.room.digit, el.room.litera, el.times.hour, el.times.minute) == 
										std::tie(items[key1].fios.fullname, items[key1].hash, items[key1].obj.object, items[key1].room.digit, items[key1].room.litera, items[key1].times.hour, items[key1].times.minute)))
			{
				status[key1] = 2;
				count = count - 1;
				return true;
			}
			else
			{
				int key2 = Collision(key1, status, el,step);
				if ((key2 != -1) && (std::tie(el.fios.fullname, el.hash, el.obj.object, el.room.digit, el.room.litera, el.times.hour, el.times.minute) ==
					                 std::tie(items[key2].fios.fullname, items[key2].hash, items[key2].obj.object, items[key2].room.digit, items[key2].room.litera, items[key2].times.hour, items[key2].times.minute)))
				{
					status[key2] = 2;
					count = count - 1;
					return true;
				}
				else if (key2 == -1)
				{
					int key3 = Collision(key1, status, el, step);
					while ((key3 == -1) && (n<sizeHT))
					{
						key3 = Collision(key1, status, el, step);
						n++;
					}
					if (std::tie(el.fios.fullname, el.hash, el.obj.object, el.room.digit, el.room.litera, el.times.hour, el.times.minute) ==
						std::tie(items[key3].fios.fullname, items[key3].hash, items[key3].obj.object, items[key3].room.digit, items[key3].room.litera, items[key3].times.hour, items[key3].times.minute))
					{
						status[key3] = 2;
						count = count - 1;
						return true;
					}
					else return false;
				}
				else
					return false;
			}
		}
		else
		{
			std::cout << "таблица пуста..." << std::endl;
			return false;
		}
	}

	void Print()
	{
		for (int i = 0; i < sizeHT; i++)
		{
			std::cout << "[" << i << "]" << " ";
			if (status[i] == 1)
				std::cout <<"First Hash - " << items[i].hash << "  " << items[i].fios.fullname << " " << items[i].times.hour << ":" << items[i].times.minute << " Status [" << status[i] << "] " << std::endl;
			else
				std::cout << " " << " Status [" << status[i] << "]" << std::endl;
		}
		std::cout << std::endl;
	}




	

private:
	int sizeHT, k1;
	HT_item* items;
	std::vector <int> status;
	int count = 0;

	
};

int main()
{
	setlocale(LC_ALL, "rus");
	int size, k;
	k = 2;
	std::cin >> size;
	Hash_Table Table(size,k);
	HT_item el;

	//4
	el.fios.fullname= "Ivanov Ivan Ivanovich";
	el.times.hour = 10;
	el.times.minute = 30;
	Table.Add(el);
	Table.Print();

	el.fios.fullname = "Ivanov Ivan Ivanovich";
	el.times.hour = 10;
	el.times.minute = 30;
	Table.Add(el);


	el.fios.fullname = "Ivanov Ivan Ivanovich";
	el.times.hour = 10;
	el.times.minute = 30;
	Table.Add(el);

	Table.Print();

	//2
	el.fios.fullname = "Ivanov Ivan Ivanovich";
	el.times.hour = 23;
	el.times.minute = 20;
	Table.Add(el);
	Table.Print();


	//4
	el.fios.fullname = "Ivano Ivan Ivanovich";
	el.times.hour = 23;
	el.times.minute = 20;
	Table.Add(el);
	Table.Print();

	//4
	el.fios.fullname = "Iva Ivan Ivanovich";
	el.times.hour = 23;
	el.times.minute = 11;
	Table.Add(el);
	Table.Print();

	//3
	el.fios.fullname = "Iva Iva Ivanovich";
	el.times.hour = 23;
	el.times.minute = 15;
	Table.Add(el);
	Table.Print();

	el.fios.fullname = "Iva Iva Ivanovich";
	el.times.hour = 23;
	el.times.minute = 15;
	Table.Delete(el);
	Table.Print();

	el.fios.fullname = "Ivanov Ivan Ivanovich";
	el.times.hour = 10;
	el.times.minute = 30;
	Table.Delete(el);
	Table.Print();


	el.fios.fullname = "Iva Ivan Ivanovich";
	el.times.hour = 23;
	el.times.minute = 11;
	Table.Delete(el);
	Table.Print();


	el.fios.fullname = "Ivano Ivan Ivanovich";
	el.times.hour = 23;
	el.times.minute = 20;
	Table.Delete(el);
	Table.Print();

	el.fios.fullname = "Iva Iva Ivanovich";
	el.times.hour = 23;
	el.times.minute = 15;
	Table.Add(el);
	Table.Print();

	el.fios.fullname = "Ivanov Ivan Ivanovich";
	el.times.hour = 10;
	el.times.minute = 30;
	Table.Add(el);
	Table.Print();

	el.fios.fullname = "Iva Ivan Ivanovich";
	el.times.hour = 23;
	el.times.minute = 11;
	Table.Add(el);
	Table.Print();


	el.fios.fullname = "Ivano Ivan Ivanovich";
	el.times.hour = 23;
	el.times.minute = 20;
	Table.Add(el);
	Table.Print();
	

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
