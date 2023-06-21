#include<iostream>
#include<fstream>
#include<string>
#include<chrono>
#include<vector>
# define NO_OF_CHARS 256

struct Auditorium
{
	char litera;
	int num;
};

struct sub
{
	std::string subj;
};

struct fio
{
	std::string fios;
};

struct Times
{
	int hour;
	int minute;
};

struct List
{
	Auditorium room;
	fio fullname;
	Times time;
	sub object;
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


void GetArray(List*& record, int size, std::string filename)
{
	std::ifstream(file);
	file.open(filename);
	std::string line;
	getline(file, line);
	int i = 0;
	while (i != size)
	{
		getline(file, line, ' ');
		record[i].room.litera = line[0];
		std::string number = line.erase(0, 1);
		record[i].room.num = stoi(number);
		getline(file, line, ' ');
		std::string name = line;
		getline(file, line, ' ');
		name = name + " " + line;
		getline(file, line, ' ');
		record[i].fullname.fios = name + " " + line;
		getline(file, line, ':');
		record[i].time.hour = stoi(line);
		getline(file, line, ' ');
		record[i].time.minute = stoi(line);
		getline(file, line);
		record[i].object.subj = line;
		i++;
	}
	file.close();
}


void PutArray(List*& record, double time, int size, std::string filename)
{
	std::ofstream(file);
	file.open(filename);
	file << time << "s\n";
	for (int i = 0; i < size; i++)
	{
		file << record[i].room.litera << record[i].room.num << " ";
		file << record[i].fullname.fios << " ";
		file << record[i].time.hour << ":" << record[i].time.minute << " ";
		file << record[i].object.subj << std::endl;
	}
	file.close();
};


void DirectSearch(std::string str, std::string pattern, int& res, int& m)
{
	int strl = str.length();
	int patl = pattern.length();
	res = -1;
	m = 0;
	for (int i = 0; i < strl - patl + 1; i++)
	{
		for (int j = 0; j < patl; j++)
		{
			if (pattern[j] != str[i + j])
				break;
			else if (j == patl - 1)
			{
				m = m + 1;
				res = i;
				break;
			}
		}
	}
}


void DirectTimer(List* record, double& time, std::string pattern, int size, int res1, int res2, int m1, int m2, std::string filename)
{
	std::chrono::time_point<std::chrono::high_resolution_clock>start, end;
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < size; i++)
	{
		DirectSearch(record[i].fullname.fios, pattern, res1, m1);
		DirectSearch(record[i].object.subj, pattern, res2, m2);
	}
	end = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> elapsedTime(end - start);
	const double seconds(elapsedTime.count());
	time = seconds;
}

void Direct(List* record, std::string pattern, int size, int k)
{
	int res1 = -1, m1 = 0, res2 = -1, m2 = 0, j = 0;
	double time = 0;
	List* listing1 = new List[size];
	DirectTimer(record, time, pattern, size, res1, res2, m1, m2, "OutputDirect.txt");
	for (int i = 0; i < size; i++)
	{
		DirectSearch(record[i].fullname.fios, pattern, res1, m1);
		DirectSearch(record[i].object.subj, pattern, res2, m2);
		if ((res1 != -1 && m1 == k) && (res2 != -1 && m2 == k))
		{
			listing1[j] = record[i];
			j++;
		}
	}
	PutArray(listing1, time, j, "Output.txt");
}



int main()
{
	int size;
	std::ifstream file;
	GetSize(size, "2input.txt");
	List* record1 = new List[size];
	GetArray(record1, size, "2input.txt");
	file.close();

	int k = 1;
	std::string pattern = "Vayay";
	Direct(record1, pattern, size, k);
}