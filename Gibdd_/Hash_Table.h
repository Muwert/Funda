#pragma once

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


struct Rezult
{
	DataSdachi data;
	int pasport;
	int udostoverenie;
	Time time;
	int hash;
	int index;
};



class Hash_Table
{
public:

	Hash_Table(int size)
	{
		sizeHT = size;
		items = new Rezult[size];
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
			sovokypnost = (sovokypnost - sovokypnost % j) / j;
		}
		return sum1 % sizeHT;
	}

	int SecondHF(int FirstHash, int k1, int step)
	{
		return (FirstHash + k1 * step) % sizeHT;
	}

	void Add(Rezult& el, int k)
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

	int CollisionAdd(int key, std::vector<int>status, Rezult el, int k)
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
			if ((status[tmp] == 0) || (status[tmp] == 2))
			{
				key = tmp;
			}
			else if ((status[tmp] == 1) && (del == true))
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


	bool Search(Rezult el, int k)
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

	bool Delete(Rezult el, int k)
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

	int CollisionDelete(int key, std::vector<int>status, Rezult el, int& step, int k)
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

	std::string  Print()
	{
		std::string str;
		for (int i = 0; i < sizeHT; i++)
		{
			str = str + "[" + std::to_string(i) + "]" + " ";
			if (status[i] == 1)
				str = str + "First Hash - " + std::to_string(items[i].hash) + ". " + std::to_string (items[i].data.date) + "." + std:: to_string (items[i].data.month) + "." + std:: to_string (items[i].data.year) + " " + std::to_string (items[i].pasport) + " " + std::to_string(items[i].udostoverenie) + " " + std::to_string (items[i].time.minute) + ":" + std::to_string(items[i].time.seconds) + " " + "Status [" + std::to_string(status[i]) + "]" + "\n";
			else
				str = str + " " + " Status [" + std::to_string(status[i]) + "]" + "\n";
		}
		std::cout << "\n";
	}






private:
	int sizeHT, k1;
	Rezult* items;
	std::vector <int> status;


};