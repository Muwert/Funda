#include<iostream>
#include<fstream>
#include<string>
#include<chrono>
#include<vector>

struct Room
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
	Room room;
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


void DirectSearch(std::string str, std::string pattern, int& res, int& k)
{
	int strl = str.length();
	int patl = pattern.length();
	res = -1;
	k = 0;
	for (int i = 0; i < strl - patl + 1; i++)
	{
		for (int j = 0; j < patl; j++)
		{
			if (pattern[j] != str[i + j])
				break;
			else if (j == patl - 1)
			{
				k = k + 1;
				res = i;
				break;
			}
		}
	}
}


void DirectTimer(List* record, double& time, std::string pattern, int size, int res1, int res2, int k1, int k2)
{
	std::chrono::time_point<std::chrono::high_resolution_clock>start, end;
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < size; i++)
	{
		DirectSearch(record[i].fullname.fios, pattern, res1, k1);
		DirectSearch(record[i].object.subj, pattern, res2, k2);
	}
	end = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> elapsedTime(end - start);
	const double seconds(elapsedTime.count());
	time = seconds;
}

void Direct(List* record, std::string pattern, int size, int k)
{
	int res1 = -1, k1 = 0, res2 = -1, k2 = 0, j = 0;
	double time = 0;
	List* rezult = new List[size];
	DirectTimer(record, time, pattern, size, res1, res2, k1, k2);
	for (int i = 0; i < size; i++)
	{
		DirectSearch(record[i].fullname.fios, pattern, res1, k1);
		DirectSearch(record[i].object.subj, pattern, res2, k2);
		if ((res1 != -1 && k1 == k) && (res2 != -1 && k2 == k))
		{
			rezult[j] = record[i];
			j++;
		}
	}
	PutArray(rezult, time, j, "OutputDirect.txt");
}

int* Prefix_Function(std::string pattern)
{
	int m = pattern.length();
	int* pi = new int[m];
	pi[0] = 0;
	int k = 0;
	for (auto q = 1; q < m; ++q)
	{
		while (k > 0 and pattern[q] != pattern[k])
			k = pi[k];
		if (pattern[k] == pattern[q])
			k = k + 1;
		pi[q] = k;
	}
	return pi;
}


int KMP_algorithm(int* pi, std::string text, std::string pattern)
{
	int counter = 0;
	int n = (int)text.length();
	int m = (int)pattern.length();
	int q = 0;

	for (auto i = 0; i < n; ++i)
	{
		while (q > 0 and pattern[q] != text[i])
			q = pi[q];

		if (pattern[q] == text[i])
			q = q + 1;

		if (q == m)
		{
			counter++;
			q = pi[q - 1];
		}


	}

	return counter;
}


void KMPtimer(List* record, double& time, std::vector<int*> prefixes, std::vector<std::string> pattern, int l, int size)
{
	std::chrono::time_point<std::chrono::high_resolution_clock>start, end;
	start = std::chrono::high_resolution_clock::now();
	for (int j = 0; j < size; j++) {
		for (auto i : pattern) {
			KMP_algorithm(prefixes[l], record[j].fullname.fios, i);
			KMP_algorithm(prefixes[l], record[j].object.subj, i);
		}
	}
	end = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> elapsedTime(end - start);
	const double seconds(elapsedTime.count());
	time = seconds;
}

void KMP(List* record, std::vector<std::string> pattern, int size, int k)
{
	std::vector<int*> prefixes;
	for (auto i : pattern) prefixes.push_back(Prefix_Function(i));
	int c = 0, l = 0, n = 0;
	double  time = 0;
	auto count = 0, count1 = 0;
	List* rezult = new List[size];

	KMPtimer(record, time, prefixes, pattern, l, size);
	for (int j = 0; j < size; j++)
	{
		for (auto i : pattern) {
			count = KMP_algorithm(prefixes[l], record[j].fullname.fios, i);
			count1 = KMP_algorithm(prefixes[l], record[j].object.subj, i);
		}
		if ((count1 == k) && (count == k))
		{
			rezult[c] = record[j];
			c++;
			n++;
		}
		count = 0;
		count1 = 0;
	}


	PutArray(rezult, time, n, "OutputKMP.txt");
}



int main()
{
	int size;
	std::ifstream file;
	GetSize(size, "2input.txt");
	List* record1 = new List[size];
	GetArray(record1, size, "2input.txt");
	file.close();

	int k = 2;
	std::string pattern1 = "Vayay";
	std::vector<std::string> pattern = {"Vayay"};
	Direct(record1, pattern1, size, k);
	KMP(record1, pattern, size, k);
}
