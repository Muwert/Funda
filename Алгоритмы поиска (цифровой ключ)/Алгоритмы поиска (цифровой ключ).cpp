// Алгоритмы поиска (цифровой ключ).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


struct Room
{
	int digit;
};

struct FIO
{
	std::string fullname;
};

struct Time
{
	int hour;
	int time;
};

struct subject
{
	std::string object;
};

struct list
{
	Room room;
	FIO fios;
	Time times;
	subject obj;
	int str;
};

void GetSize(int& size, std::string filename)
{
	std::ifstream(file);
	file.open(filename);
	std::string line;
	std::getline(file, line);
	size = std::stoi(line);
	file.close();
};

void GetArray(list*& record, int size, std::string filename)
{
	std::ifstream(file);
	file.open(filename);
	std::string line;
	getline(file, line);
	int i = 0;
	while (i != size)
	{
		getline(file, line, ' ');
		record[i].room.digit = stoi(line);
		getline(file, line, ' ');
		std::string name = line;
		getline(file, line, ' ');
		name = name + " " + line;
		getline(file, line, ' ');
		record[i].fios.fullname = name + " " + line;
		getline(file, line, ':');
		record[i].times.hour = stoi(line);
		getline(file, line, ' ');
		record[i].times.time = stoi(line);
		getline(file, line);
		record[i].obj.object = line;
		record[i].str = i;
		i++;
	}
	file.close();
}

void PutArray(int line, int step, std::string filename)
{
	std::ofstream(file);
	file.open(filename);
	file << "Номер строки: " << line << std::endl
		<< "Количество шагов: " << step << std::endl;

	file.close();
};

void LinearSearch(std::vector<int>& array, int size, int& line, int& step, int pattern)
{
	line = -1;
	step = 0;
	int vh = 0;
	for (int i = 0; i < size; i++)
	{
		if ((array[i] == pattern) && (vh==0))
		{
			line = i+1;
			vh = 1;
			i = size;
		}
		step++;
	}
}
	
void Linear(list* record, int size, int pattern)
{
	int step, line;
	std::vector <int> array(size);
	for (int i = 0; i < size; i++)
	{
		array[i] = record[i].room.digit;
	}
	LinearSearch(array, size, step, line, pattern);
	PutArray(step, line, "LinearOutput.txt");
	
}

void Sort(list* record, int size)
{
	list temp;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (record[j].room.digit > record[j + 1].room.digit)
			{
				temp = record[j];
				record[j] = record[j + 1];
				record[j + 1] = temp;
			}
		}
	}

}
void UniformBinarySearch(list* record, int size, int pattern,int& step, int& line)
{
	int count = 1;
	int i = size / 2;
	int m = size / 2;
	int vh = 0;
	while ((pattern != record[i].room.digit && m != 0) && (vh == 0))
	{
		if (pattern < record[i].room.digit)
		{
			i = i - m / 2;
			m = m / 2;
			count++;
		}
		else
		{
			i = i + m / 2;
			m = m / 2;
			count++;
		}

	}
	if ((pattern == record[i].room.digit) && (vh == 0))
	{
		line = record[i].str+2;
		step = count;
		vh += 1;
		count++;
	}
	m = i + 1;
	i = i - 1;
	int a = count;

	count = a;
	while (i >= 0)
	{
		if ((i >= 0 && pattern == record[i].room.digit) && (vh==0))
		{
			line = record[i].str+2;
			step = count;
			count++;
		}
		i--;
	}

	count = a;
	while (m <= size)
	{
		if ((m <= size && pattern == record[m].room.digit) && (vh==0))
		{
			line = record[m].str+2;
			step = count;
			count++;
		}
		m++;
	}


}

int main()
{
	int size, size1, step = 0, line = 0;
	int pattern = 300;
	std::ifstream file;
	file.open("data1.txt");
	GetSize(size, "data1.txt");

	//GetSize(size1, "data2.txt");
	list* record = new list[size];
	list* record1 = new list[size];
	GetArray(record, size, "data1.txt");
	GetArray(record1, size, "data1.txt");

	Linear(record, size, pattern);

	Sort(record1, size);
	UniformBinarySearch(record1, size, pattern, step, line);
	PutArray(line, step, "BinarySearch.txt");

	file.close();

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
