// Prog lab 1(3.b).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <chrono>
using namespace std;

struct monstersStr
{
	string name{}, typeOfSpecial{};
	int health{}, attack{};
	double chanceAtSpecial{};
	tm time{};
	int id{};
};

void interactiveMode(vector<monstersStr>monstersVec);
void demonstrationMode(vector<monstersStr>monstersVec);
void benchmarkMode(vector<monstersStr>monstersVec);

void writeToBinaryFile(vector<monstersStr>monstersVec, size_t act);
void writeToTextFile(vector<monstersStr>monstersVec, size_t act);
void writeToFile(vector<monstersStr>monstersVec, char* fname, size_t mode, size_t act);
vector<monstersStr> saveElementsInStructure(vector<monstersStr>monstersVec, size_t act);

void addToBinaryFile(vector<monstersStr>monstersVec, size_t act);
void addToTextFile(vector<monstersStr>monstersVec, size_t act);

vector<monstersStr> readFromBinaryFile(vector<monstersStr>monstersVec);
vector<monstersStr> readFromTextFile(vector<monstersStr>monstersVec);
vector<monstersStr> readFromFile(vector<monstersStr>monstersVec, char* fname, size_t mode);

void searchBySpecifiedCriteria1(vector<monstersStr>monstersVec, size_t act);
void searchBySpecifiedCriteria2(vector<monstersStr>monstersVec, size_t act);
void searchBySpecifiedCriteria3(vector<monstersStr>monstersVec, size_t act);

void printElements(size_t i, vector<monstersStr>monstersVec);

int main()
{
	vector<monstersStr>monstersVec(200);
	monstersStr m1;

	cout << " Select the operating mode:\n1 - interactive\n2 - demonstration\n3 - benchmark " << endl;
	size_t oper;
	cin >> oper;

	switch (oper)
	{
	case 1:
	{
		interactiveMode(monstersVec);
		break;
	}
	case 2:
	{
		demonstrationMode(monstersVec);
		break;
	}
	case 3:
	{
		benchmarkMode(monstersVec);
		break;
	}
	default: break;
	}

	return 0;
}


void interactiveMode(vector<monstersStr>monstersVec)
{
	string check = "Yes";
	while (check == "Yes")
	{
		cout << " Select an operation:\n1 - add items\n2 - write items\n3 - read items\n4 - output of saved data\n5 - search by specified criteria " << endl;
		size_t op;
		cin >> op;
		cout << " \n ";

		size_t tp;
		if (op == 1 || op == 3)
		{
			cout << " Select an type of file:\n1 - binary\n2 - text " << endl;
			cin >> tp;
		}
		else if (op == 2)
		{
			cout << " Select an type of file:\n1 - binary\n2 - text\n(3 - save in memory) " << endl;
			cin >> tp;
		}
		cout << " \n ";

		switch (op)
		{
		case 1:
		{
			switch (tp)
			{
			case 1:
			{
				auto start = chrono::high_resolution_clock::now();
				addToBinaryFile(monstersVec, 1);
				auto finish = chrono::high_resolution_clock::now();
				chrono::duration<float> dur = finish - start;
				cout << " Duration: " << dur.count() << "s" << endl;
				break;
			}

			case 2:
			{
				auto start = chrono::high_resolution_clock::now();
				addToTextFile(monstersVec, 1);
				auto finish = chrono::high_resolution_clock::now();
				chrono::duration<float> dur = finish - start;
				cout << " Duration: " << dur.count() << "s" << endl;
				break;
			}

			default: break;
			}
			break;
		}

		case 2:
		{
			switch (tp)
			{
			case 1:
			{
				auto start = chrono::high_resolution_clock::now();
				writeToBinaryFile(monstersVec, 1);
				auto finish = chrono::high_resolution_clock::now();
				chrono::duration<float> dur = finish - start;
				cout << " Duration: " << dur.count() << "s" << endl;
				break;
			}

			case 2:
			{
				auto start = chrono::high_resolution_clock::now();
				writeToTextFile(monstersVec, 1);
				auto finish = chrono::high_resolution_clock::now();
				chrono::duration<float> dur = finish - start;
				cout << " Duration: " << dur.count() << "s" << endl;
				break;
			}

			case 3:
			{
				auto start = chrono::high_resolution_clock::now();
				monstersVec = saveElementsInStructure(monstersVec, 1);
				auto finish = chrono::high_resolution_clock::now();
				chrono::duration<float> dur = finish - start;
				cout << " Duration: " << dur.count() << "s" << endl;
				break;
			}

			default: break;
			}
			break;
		}
		case 3:
		{
			switch (tp)
			{
			case 1:
			{
				auto start = chrono::high_resolution_clock::now();
				monstersVec = readFromBinaryFile(monstersVec);
				auto finish = chrono::high_resolution_clock::now();
				chrono::duration<float> dur = finish - start;
				cout << " Duration: " << dur.count() << "s" << endl;
				break;
			}

			case 2:
			{
				auto start = chrono::high_resolution_clock::now();
				monstersVec = readFromTextFile(monstersVec);
				auto finish = chrono::high_resolution_clock::now();
				chrono::duration<float> dur = finish - start;
				cout << " Duration: " << dur.count() << "s" << endl;
				break;
			}
			default: break;
			}
			break;
		}

		case 4:
		{
			cout << " ! Make sure you read the items before (or have saved in memory) ! " << endl;
			auto start = chrono::high_resolution_clock::now();
			monstersVec.shrink_to_fit();
			for (size_t i = 0; i < monstersVec.size(); i++)
			{
				printElements(i, monstersVec);
			}
			auto finish = chrono::high_resolution_clock::now();
			chrono::duration<float> dur = finish - start;
			cout << " Duration: " << dur.count() << "s" << endl;
			break;
		}

		case 5:
		{
			cout << " ! Make sure you read the items before (or have saved in memory) ! " << endl;
			cout << " Specify search criteria:\n1 - name\n2 - type of special attack and number of attack units\n3 - time " << endl;
			int crit;
			cin >> crit;

			switch (crit)
			{
			case 1:
			{
				auto start = chrono::high_resolution_clock::now();
				searchBySpecifiedCriteria1(monstersVec, 1);
				auto finish = chrono::high_resolution_clock::now();
				chrono::duration<float> dur = finish - start;
				cout << " Duration: " << dur.count() << "s" << endl;
				break;
			}

			case 2:
			{
				auto start = chrono::high_resolution_clock::now();
				searchBySpecifiedCriteria2(monstersVec, 1);
				auto finish = chrono::high_resolution_clock::now();
				chrono::duration<float> dur = finish - start;
				cout << " Duration: " << dur.count() << "s" << endl;
				break;
			}

			case 3:
			{
				auto start = chrono::high_resolution_clock::now();
				searchBySpecifiedCriteria3(monstersVec, 1);
				auto finish = chrono::high_resolution_clock::now();
				chrono::duration<float> dur = finish - start;
				cout << " Duration: " << dur.count() << "s" << endl;
				break;
			}

			default: break;
			}
			break;
		}
		default: break;
		}

		cout << " Do you want to perform one more operation? Write Yes or No: " << endl;
		cin >> check;
		cin.ignore();
	}

}

void demonstrationMode(vector<monstersStr>monstersVec)
{
	cout << " Write data " << endl;
	cout << " Binary file(name - my_binFile.bin): " << endl;
	system("pause");
	writeToBinaryFile(monstersVec, 2);
	cout << " \n\n ";

	cout << " Text file(name - my_txtFile.txt): " << endl;
	system("pause");
	writeToTextFile(monstersVec, 2);
	cout << " \n\n ";

	cout << " Storage in memory: " << endl;
	system("pause");
	monstersVec = saveElementsInStructure(monstersVec, 2);
	cout << " \n\n ";

	cout << " Add data to file " << endl;
	cout << " Binary file(name - my_binFile.bin): " << endl;
	system("pause");
	addToBinaryFile(monstersVec, 2);
	cout << " \n\n ";
	cout << " Text file(name - my_txtFile.txt): " << endl;
	system("pause");
	addToTextFile(monstersVec, 2);
	cout << " \n\n ";

	cout << " Read data from file " << endl;
	cout << " Binary file(name - my_binFile.bin): " << endl;
	system("pause");
	monstersVec = readFromBinaryFile(monstersVec);
	cout << " \n\n ";
	cout << " Text file(name - my_txtFile.txt): " << endl;
	system("pause");
	monstersVec = readFromTextFile(monstersVec);
	cout << " \n\n ";

	cout << " Output of saved data " << endl;
	cout << " For example, from text file(name - my_txtFile.txt): " << endl;
	system("pause");
	for (size_t i = 0; i < monstersVec.size(); i++)
	{
		printElements(i, monstersVec);
	}
	cout << " \n\n ";

	cout << " Search by specified criteria " << endl;
	cout << " For example, data from text file(name - my_txtFile.txt): " << endl;
	cout << " Monsters with a name that starts with a given piece of text: " << endl;
	cout << " For example, with a name that starts with 'Km' " << endl;
	system("pause");
	searchBySpecifiedCriteria1(monstersVec, 2);
	cout << " \n\n ";
	cout << " Monsters with a given type of special attack and the number of attack units in a given range: " << endl;
	cout << " For example, with a 'Increase damage' type of special attack and 200 - 800 attack units " << endl;
	system("pause");
	searchBySpecifiedCriteria2(monstersVec, 2);
	cout << " \n\n ";
	cout << " Monsters that appeared in the game after a certain time: " << endl;
	cout << " For example, after 9/19/2007 at 16:23 " << endl;
	system("pause");
	searchBySpecifiedCriteria3(monstersVec, 2);
	cout << " \n\n ";
}

void benchmarkMode(vector<monstersStr>monstersVec)
{
	cout << " Write data " << endl;
	cout << " Binary file(name - my_binFile.bin): " << endl;
	cout << " Operation time: \nN = 10 -> 0.432375s, \nN = 20 -> 1.40585s, \nN = 40 -> 1.48466s, \nN = 60 -> 2.65442s, \nN = 80 -> 3.10747s, \nN = 100 -> 4.36105s, \nN = 120 -> 5.66998s, \nN = 140 -> 7.45104s, \nN = 160 -> 7.79732s, \nN = 180 -> 8.66392s, \nN = 200 -> 9.54951s. " << endl;
	cout << " \n ";
	cout << " Size: \nN = 10 -> 3 028b, \nN = 20 -> 6 051b, \nN = 60 -> 18 131b, \nN = 80 -> 24 196b, \nN = 100 -> 30 212b, \nN = 120 -> 36 310b, \nN = 140 -> 42 340b, \nN = 160 -> 48 346b, \nN = 200 -> 60 441b, \nN = 240 -> 72 574b. " << endl;
	cout << " \n";

	cout << " Text file(name - my_txtFile.txt): " << endl;
	cout << " Operation time: \nN = 10 -> 0.715381s, \nN = 20 -> 1.10667s, \nN = 40 -> 2.14649s, \nN = 60 -> 3.63764s, \nN = 80 -> 4.1387s, \nN = 100 -> 5.1498s, \nN = 120 -> 6.09938s, \nN = 140 -> 8.07188s, \nN = 160 -> 8.59868s, \nN = 180 -> 8.9851s, \nN = 200 -> 11.8273s. " << endl;
	cout << " \n";
	cout << " Size: \nN = 10 -> 3 186b, \nN = 20 -> 6 376b, \nN = 60 -> 19 094b, \nN = 80 -> 25 485b, \nN = 100 -> 31 835b, \nN = 120 -> 38 177b, \nN = 140 -> 44 547b, \nN = 160 -> 50 885b, \nN = 200 -> 63 664b, \nN = 240 -> 76 469b. " << endl;
	cout << " \n";

	cout << " Storage in memory: " << endl;
	cout << " Operation time: \nN = 10 -> 0.429653s, \nN = 20 -> 1.16945s, \nN = 40 -> 1.81986s, \nN = 60 -> 3.0292s, \nN = 80 -> 4.36972s, \nN = 100 -> 5.35739s, \nN = 120 -> 6.71028s, \nN = 140 -> 6.93264s, \nN = 160 -> 7.66517s, \nN = 180 -> 10.1539s. " << endl;
	cout << " \n ";

	cout << " Add data to file " << endl;
	cout << " Binary file(name - my_binFile.bin): " << endl;
	cout << " Operation time: \nN = 10 -> 0.837501s, \nN = 20 -> 0.676062s, \nN = 40 -> 1.97301s, \nN = 80 -> 4.53648s, \nN = 120 -> 6.82646s, \nN = 160 -> 8.75215s, \nN = 200 -> 8.28018s, \nN = 240 -> 12.6563s. " << endl;
	cout << " \n ";
	cout << " Text file(name - my_txtFile.txt): " << endl;
	cout << " Operation time: \nN = 10 -> 0.418849s, \nN = 20 -> 1.20434s, \nN = 40 -> 2.31454s, \nN = 60 -> 3.1967s, \nN = 80 -> 5.00988s, \nN = 100 -> 5.78491s, \nN = 120 -> 6.56913s, \nN = 140 -> 6.72939s, \nN = 160 -> 7.94113s, \nN = 180 -> 9.98951s. " << endl;
	cout << " \n";

	cout << " Read data from file " << endl;
	cout << " Binary file(name - my_binFile.bin): " << endl;
	cout << " Operation time: \nN = 10 -> 0.516989s, \nN = 20 -> 1.17253s, \nN = 40 -> 2.23446s, \nN = 60 -> 3.73837s, \nN = 80 -> 4.60701s, \nN = 100 -> 6.69746s, \nN = 120 -> 7.41287s, \nN = 140 -> 9.46401s. " << endl;
	cout << " \n ";
	cout << " Text file(name - my_txtFile.txt): " << endl;
	cout << " Operation time: \nN = 10 -> 0.386138s, \nN = 20 -> 1.28842s, \nN = 40 -> 2.29316s, \nN = 60 -> 4.35082s, \nN = 80 -> 5.36692s, \nN = 100 -> 6.73302s, \nN = 120 -> 8.67287s, \nN = 140 -> 9.56244s. " << endl;
	cout << " \n";

	cout << " Output of saved data " << endl;
	cout << " Operation time: \nN = 10 -> 0.703737s, \nN = 20 -> 1.26329s, \nN = 40 -> 1.81699s, \nN = 60 -> 2.72501s, \nN = 80 -> 3.8419s, \nN = 100 -> 5.0806s, \nN = 120 -> 6.30945s, \nN = 140 -> 7.46784s, \nN = 160 -> 8.56022s, \nN = 180 -> 9.20088s, \nN = 200 -> 10.5234s. " << endl;
	cout << " \n ";

	cout << " Search by specified criteria " << endl;
	cout << " Monsters with a name that starts with a given piece of text: " << endl;
	cout << " Operation time: \nN = 10 -> 0.072823s, \nN = 20 -> 0.31263s, \nN = 40 -> 0.67938s, \nN = 80 -> 1.67822s, \nN = 160 -> 3.2377s, \nN = 240 -> 4.6806s, \nN = 360 -> 6.2675s, \nN = 400 -> 7.37822s, \nN = 480 -> 9.00267s, \nN = 560 -> 9.78266s. " << endl;
	cout << " \n ";
	cout << " Monsters with a given type of special attack and the number of attack units in a given range: " << endl;
	cout << " Operation time: \nN = 10 -> 0.08399s, \nN = 20 -> 0.24233s, \nN = 40 -> 0.48729s, \nN = 80 -> 1.00225s, \nN = 160 -> 2.1244s, \nN = 240 -> 4.53039s, \nN = 360 -> 5.18739s, \nN = 400 -> 6.96731s, \nN = 480 -> 8.39818s, \nN = 560 -> 9.6223s. " << endl;
	cout << " \n ";
	cout << " Monsters that appeared in the game after a certain time: " << endl;
	cout << " Operation time: \nN = 10 -> 0.137748s, \nN = 20 -> 0.38575s, \nN = 40 -> 0.510594s, \nN = 80 -> 1.28842s, \nN = 160 -> 2.8211s, \nN = 240 -> 4.7216s, \nN = 320 -> 5.89122s, \nN = 400 -> 7.12953s, \nN = 480 -> 9.51782s, \nN = 560 -> 9.93237s. " << endl;
	cout << " \n ";
}

void writeToFile(vector<monstersStr>monstersVec, const char* fname, size_t mode, size_t act)
{
	monstersStr m1;
	ofstream fptr;

	switch (mode)
	{
	case 1:
	{
		fptr.open(fname, ios_base::out | ios_base::binary);
		break;
	}
	case 2:
	{
		fptr.open(fname, ios_base::out);
		break;
	}
	case 3:
	{
		fptr.open(fname, ios_base::app | ios_base::binary);
		break;
	}
	case 4:
	{
		fptr.open(fname, ios_base::app);
		break;
	}
	default: break;
	}

	cout << " File opened successfully! " << endl;

	size_t filling;
	switch (act)
	{
	case 1:
	{
		cout << " Choose a data entry method:\n1 - self-filling\n2 - random filling " << endl;
		cin >> filling;
		break;
	}
	case 2:
	{
		filling = 2;
		break;
	}
	default: break;
	}


	string check = "Yes";
	switch (filling)
	{
	case 1:
	{
		cout << " Enter information about monsters in the computer game! " << endl;
		while (check == "Yes")
		{
			for (size_t i = 0; i < 200; i++)
			{
				char ignore;
				cout << " Monster: " << endl;
				fptr << " Monster: " << endl;

				cin.ignore();
				cout << " Enter the name of the monster: ";
				getline(cin, monstersVec[i].name);
				fptr << " The name of the monster: " << endl;
				fptr << monstersVec[i].name << endl;

				cout << " Enter the number of health units (integer, not more than 50 000): ";
				cin >> monstersVec[i].health;
				fptr << " The number of health units: " << endl;
				fptr << monstersVec[i].health << endl;

				cout << " Enter the number of attack units (integer, not more than 2 000): ";
				cin >> monstersVec[i].attack;
				fptr << " The number of attack units: " << endl;
				fptr << monstersVec[i].attack << endl;

				cout << " Enter the chance to perform a special attack (number from 0 to 1): ";
				cin >> monstersVec[i].chanceAtSpecial;
				fptr << " The chance to perform a special attack: " << endl;
				fptr << monstersVec[i].chanceAtSpecial << endl;

				cin.ignore();
				cout << " Enter the type of special attack: Increase damage, Repeat the attack, Heal yourself, Paralyze the enemy: ";
				getline(cin, monstersVec[i].typeOfSpecial);
				if ((monstersVec[i].typeOfSpecial != "Increase damage") && (monstersVec[i].typeOfSpecial != "Repeat the attack") && (monstersVec[i].typeOfSpecial != "Heal yourself") && (monstersVec[i].typeOfSpecial != "Paralyze the enemy"))
				{
					monstersVec[i].typeOfSpecial = "";
				}
				fptr << " The type of special attack: " << endl;
				fptr << monstersVec[i].typeOfSpecial << endl;

				cout << " Enter the date and time the monster appeared in the game:";
				cout << " date (mm/dd/yyyy): ";
				cin >> monstersVec[i].time.tm_mon >> ignore >> monstersVec[i].time.tm_mday >> ignore >> monstersVec[i].time.tm_year;
				cout << " time (hh:mm): ";
				cin >> monstersVec[i].time.tm_hour >> ignore >> monstersVec[i].time.tm_min;
				fptr << " The date and time the monster appeared in the game: " << endl;
				fptr << monstersVec[i].time.tm_mon << "/" << monstersVec[i].time.tm_mday << "/" << monstersVec[i].time.tm_year << " at " << monstersVec[i].time.tm_hour << ":" << monstersVec[i].time.tm_min << " " << endl;

				cout << " Enter the monster ID: " << endl;
				cin >> monstersVec[i].id;

				fptr << " Monster ID: " << endl;
				fptr << monstersVec[i].id << endl;

				cout << " \n ";
				fptr << " \n ";

				cout << " Want to add more monsters? Write Yes or No: ";
				cin >> check;
				if (check != "Yes")
				{
					break;
				}
			}
		}
		break;
	}

	case 2:
	{
		srand(time(NULL));
		int numberOfMonsters = 1 + rand() % 29;
		char letterNameFirst[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
		char letterName[] = "qwertyuiopasdfghjklzxcvbnm";
		int k;
		int setLenFirst = strlen(letterNameFirst);
		int setLen = strlen(letterName);

		cout << " Your random set of monsters: " << endl;
		for (size_t i = 0; i < numberOfMonsters; i++)
		{
			int N = 2 + rand() % 6;
			char randomName[10];

			cout << " Monster: " << endl;
			fptr << " Monster: " << endl;

			randomName[0] = letterNameFirst[rand() % setLenFirst];
			for (size_t j = 1; j < N - 1; j++)
			{
				randomName[j] = letterName[rand() % setLen];
			}
			monstersVec[i].name = randomName;
			monstersVec[i].name.erase(N);
			cout << " The name of the monster: " << monstersVec[i].name << endl;
			fptr << " The name of the monster: " << endl;
			fptr << monstersVec[i].name << endl;

			monstersVec[i].health = 1 + rand() % 49999;
			cout << " The number of health units: " << monstersVec[i].health << endl;
			fptr << " The number of health units: " << endl;
			fptr << monstersVec[i].health << endl;

			monstersVec[i].attack = 1 + rand() % 1999;
			cout << " The number of attack units: " << monstersVec[i].attack << endl;
			fptr << " The number of attack units: " << endl;
			fptr << monstersVec[i].attack << endl;

			monstersVec[i].chanceAtSpecial = (1 + rand() % 8) / 10.0;
			cout << " The chance to perform a special attack: " << monstersVec[i].chanceAtSpecial << endl;
			fptr << " The chance to perform a special attack: " << endl;
			fptr << monstersVec[i].chanceAtSpecial << endl;

			const char* linebank[] = { "Increase damage", "Repeat the attack", "Heal yourself", "Paralyze the enemy" };
			monstersVec[i].typeOfSpecial = linebank[rand() % 4];
			cout << " The type of special attack: " << monstersVec[i].typeOfSpecial << endl;
			fptr << " The type of special attack: " << endl;
			fptr << monstersVec[i].typeOfSpecial << endl;

			monstersVec[i].time.tm_mon = 1 + rand() % 12;
			monstersVec[i].time.tm_mday = 1 + rand() % 30;
			monstersVec[i].time.tm_year = 2000 + rand() % 22;
			monstersVec[i].time.tm_hour = 0 + rand() % 23;
			monstersVec[i].time.tm_min = 0 + rand() % 59;
			cout << " The date and time the monster appeared in the game: ";
			fptr << " The date and time the monster appeared in the game: " << endl;
			cout << monstersVec[i].time.tm_mon << "/" << monstersVec[i].time.tm_mday << "/" << monstersVec[i].time.tm_year << " at " << monstersVec[i].time.tm_hour << ":" << monstersVec[i].time.tm_min << endl;
			fptr << monstersVec[i].time.tm_mon << "/" << monstersVec[i].time.tm_mday << "/" << monstersVec[i].time.tm_year << " at " << monstersVec[i].time.tm_hour << ":" << monstersVec[i].time.tm_min << " " << endl;

			monstersVec[i].id = 1 + rand() % 10000000;
			cout << " Monster ID: " << monstersVec[i].id << endl;
			fptr << " Monster ID: " << endl;
			fptr << monstersVec[i].id << endl;

			cout << " \n ";
			fptr << " \n ";
		}
		break;
	}
	default: break;
	}
	fptr.close();
}

vector<monstersStr> readFromFile(vector<monstersStr>monstersVec, const char* fname, size_t mode)
{
	monstersStr m1;
	ifstream fptr;

	switch (mode)
	{
	case 1:
	{
		fptr.open(fname, ios_base::in | ios_base::binary);
		break;
	}
	case 2:
	{
		fptr.open(fname, ios_base::in);
		break;
	}
	default: break;
	}

	cout << " File opened successfully! " << endl;
	string line;
	int pos;
	while (!fptr.eof())
	{
		for (size_t i = 0; i < 200; i++)
		{
			getline(fptr, line);
			getline(fptr, line);
			getline(fptr, monstersVec[i].name);
			getline(fptr, line);
			getline(fptr, line);
			monstersVec[i].health = atoi(line.c_str());
			getline(fptr, line);
			getline(fptr, line);
			monstersVec[i].attack = atoi(line.c_str());
			getline(fptr, line);
			getline(fptr, line);

			monstersVec[i].chanceAtSpecial = atof(line.c_str());
			getline(fptr, line);
			getline(fptr, monstersVec[i].typeOfSpecial);
			getline(fptr, line);
			getline(fptr, line);

			pos = line.find('/');
			monstersVec[i].time.tm_mon = atoi(line.substr(0, pos).c_str());
			line.erase(0, pos + 1);

			pos = line.find('/');
			monstersVec[i].time.tm_mday = atoi(line.substr(0, pos).c_str());
			line.erase(0, pos + 1);

			pos = line.find(' ');
			monstersVec[i].time.tm_year = atoi(line.substr(0, pos).c_str());
			line.erase(0, pos + 4);

			pos = line.find(':');
			monstersVec[i].time.tm_hour = atoi(line.substr(0, pos).c_str());
			line.erase(0, pos + 1);

			pos = line.find(' ');
			monstersVec[i].time.tm_min = atoi(line.substr(0, pos).c_str());
			line.erase(0, pos + 1);

			getline(fptr, line);
			getline(fptr, line);
			monstersVec[i].id = atoi(line.c_str());
			getline(fptr, line);

			printElements(i, monstersVec);
		}
	}

	fptr.close();
	return monstersVec;
}

void writeToBinaryFile(vector<monstersStr>monstersVec, size_t act)
{
	ofstream fptr;
	fptr.open("my_binFile.bin", ios_base::out | ios_base::binary);
	writeToFile(monstersVec, "my_binFile.bin", 1, act);
	fptr.close();
}

void writeToTextFile(vector<monstersStr>monstersVec, size_t act)
{
	ofstream fptr;
	fptr.open("my_txtFile.txt", ios_base::out);
	writeToFile(monstersVec, "my_txtFile.txt", 2, act);
	fptr.close();
}

void addToBinaryFile(vector<monstersStr>monstersVec, size_t act)
{
	ofstream fptr;
	fptr.open("my_binFile.bin", ios_base::app | ios_base::binary);
	writeToFile(monstersVec, "my_binFile.bin", 3, act);
	fptr.close();
}

void addToTextFile(vector<monstersStr>monstersVec, size_t act)
{
	ofstream fptr;
	fptr.open("my_txtFile.txt", ios_base::app);
	writeToFile(monstersVec, "my_txtFile.txt", 4, act);
	fptr.close();
}

vector<monstersStr> readFromBinaryFile(vector<monstersStr>monstersVec)
{
	ifstream fptr;
	fptr.open("my_binFile.bin", ios_base::in | ios_base::binary);
	if (!fptr.is_open())
	{
		cout << " Error! " << endl;
		exit(1);
	}
	else
	{
		monstersVec = readFromFile(monstersVec, "my_binFile.bin", 1);
	}
	fptr.close();
	return monstersVec;
}

vector<monstersStr> readFromTextFile(vector<monstersStr>monstersVec)
{
	ifstream fptr;
	fptr.open("my_txtFile.txt", ios_base::in);
	if (!fptr.is_open())
	{
		cout << " Error! " << endl;
		exit(1);
	}
	else
	{
		monstersVec = readFromFile(monstersVec, "my_txtFile.txt", 2);
	}
	fptr.close();
	return monstersVec;
}

vector<monstersStr> saveElementsInStructure(vector<monstersStr>monstersVec, size_t act)
{
	monstersStr m1;
	string check;
	size_t filling;
	char ignore;
	switch (act)
	{
	case 1:
	{
		cout << " Choose a data entry method:\n1 - self-filling\n2 - random filling " << endl;
		cin >> filling;
		break;
	}
	case 2:
	{
		filling = 2;
		break;
	}
	default: break;
	}

	switch (filling)
	{
	case 1:
	{
		cout << " Enter information about monsters in the computer game! " << endl;
		for (size_t i = 0; i < 200; i++)
		{
			cout << " Monster: " << endl;

			cin.ignore();
			cout << " Enter the name of the monster: ";
			getline(cin, monstersVec[i].name);

			cout << " Enter the number of health units (integer, not more than 50 000): ";
			cin >> monstersVec[i].health;

			cout << " Enter the number of attack units (integer, not more than 2 000): ";
			cin >> monstersVec[i].attack;

			cout << " Enter the chance to perform a special attack (number from 0 to 1): ";
			cin >> monstersVec[i].chanceAtSpecial;

			cin.ignore();
			cout << " Enter the type of special attack: Increase damage, Repeat the attack, Heal yourself, Paralyze the enemy: ";
			getline(cin, monstersVec[i].typeOfSpecial);
			if ((monstersVec[i].typeOfSpecial != "Increase damage") && (monstersVec[i].typeOfSpecial != "Repeat the attack") && (monstersVec[i].typeOfSpecial != "Heal yourself") && (monstersVec[i].typeOfSpecial != "Paralyze the enemy"))
			{
				monstersVec[i].typeOfSpecial = "";
			}

			cout << " Enter the date and time the monster appeared in the game:";
			cout << " date (mm/dd/yyyy): ";
			cin >> monstersVec[i].time.tm_mon >> ignore >> monstersVec[i].time.tm_mday >> ignore >> monstersVec[i].time.tm_year;
			cout << " time (hh:mm): ";
			cin >> monstersVec[i].time.tm_hour >> ignore >> monstersVec[i].time.tm_min;

			cout << " Enter the monster ID: " << endl;
			cin >> monstersVec[i].id;

			std::cout << " Want to add more monsters? Write Yes or No: ";
			std::cin >> check;
			if (check != "Yes")
			{
				break;
			}
		}
		break;
	}
	case 2:
	{
		srand(static_cast<unsigned int>(time(0)));
		int numberOfMonsters = 1 + rand() % 29;
		char letterNameFirst[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
		char letterName[] = "qwertyuiopasdfghjklzxcvbnm";
		int setLenFirst = strlen(letterNameFirst);
		int setLen = strlen(letterName);

		cout << " Your random set of monsters: " << endl;
		for (size_t i = 0; i < numberOfMonsters; i++)
		{
			int N = 2 + rand() % 6;
			char randomName[10];

			cout << " Monster: " << endl;

			randomName[0] = letterNameFirst[rand() % setLenFirst];
			for (size_t j = 1; j < N - 1; j++)
			{
				randomName[j] = letterName[rand() % setLen];
			}
			monstersVec[i].name = randomName;
			monstersVec[i].name.erase(N);

			cout << " The name of the monster: " << monstersVec[i].name << endl;

			monstersVec[i].health = 1 + rand() % 49999;
			cout << " The number of health units: " << monstersVec[i].health << endl;

			monstersVec[i].attack = 1 + rand() % 1999;
			cout << " The number of attack units: " << monstersVec[i].attack << endl;

			monstersVec[i].chanceAtSpecial = (1 + rand() % 10) / 10.0;
			cout << " The chance to perform a special attack: " << monstersVec[i].chanceAtSpecial << endl;

			const char* linebank[] = { "Increase damage", "Repeat the attack", "Heal yourself", "Paralyze the enemy" };
			monstersVec[i].typeOfSpecial = linebank[rand() % 4];
			cout << " The type of special attack: " << monstersVec[i].typeOfSpecial << endl;

			monstersVec[i].time.tm_mon = 1 + rand() % 12;
			monstersVec[i].time.tm_mday = 1 + rand() % 30;
			monstersVec[i].time.tm_year = 2000 + rand() % 22;
			monstersVec[i].time.tm_hour = 0 + rand() % 23;
			monstersVec[i].time.tm_min = 0 + rand() % 59;
			cout << " The date and time the monster appeared in the game: ";
			cout << monstersVec[i].time.tm_mon << "/" << monstersVec[i].time.tm_mday << "/" << monstersVec[i].time.tm_year << " at " << monstersVec[i].time.tm_hour << ":" << monstersVec[i].time.tm_min << endl;

			monstersVec[i].id = 1 + rand() % 10000000;
			cout << " Monster ID: " << monstersVec[i].id << endl;

			cout << " \n ";
		}
		break;
	}
	default: break;
	}
	return monstersVec;
}

void searchBySpecifiedCriteria1(vector<monstersStr>monstersVec, size_t act)
{
	char nameFind[100];
	char namePresent[100];
	size_t existence = 0;
	size_t check = 0;

	switch (act)
	{
	case 1:
	{
		cout << " Enter the text on which the monster's name should begin " << endl;
		cin >> nameFind;
		break;
	}
	case 2:
	{
		strcpy_s(nameFind, "Km");
		break;
	}
	default: break;
	}

	cout << " All monsters with such characteristics: " << "\n" << endl;

	for (size_t i = 0; i < monstersVec.size(); i++)
	{
		strcpy_s(namePresent, monstersVec[i].name.c_str()); 
		if (strlen(nameFind) <= strlen(namePresent))
		{
			for (size_t j = 0; j < strlen(nameFind); j++)
			{
				if (nameFind[j] == namePresent[j])
				{
					check++;
				}
			}
			if (check == strlen(nameFind))
			{
				printElements(i, monstersVec);
				existence++;
			}
			check = 0;
		}
	}

	if (!existence)
	{
		cout << " There are no such monsters :( " << endl;
	}

}

void searchBySpecifiedCriteria2(vector<monstersStr>monstersVec, size_t act)
{
	string type;
	char ignore;
	int minim, maxum;
	size_t existence = 0;

	switch (act)
	{
	case 1:
	{
		cin.ignore();
		cout << " Enter monsters with which type of special attack you want to find:" << endl;
		getline(cin, type);

		cout << " Enter the range of attack units (min-max):" << endl;
		cin >> minim >> ignore >> maxum;

		break;
	}
	case 2:
	{
		type = "Increase damage";
		minim = 300;
		maxum = 900;

		break;
	}
	default: break;
	}

	cout << " All monsters with such characteristics: " << "\n" << endl;

	for (size_t i = 0; i < monstersVec.size(); i++)
	{

		if ((type == monstersVec[i].typeOfSpecial) && (monstersVec[i].attack >= minim) && (monstersVec[i].attack <= maxum))
		{
			printElements(i, monstersVec);
			existence++;
		}
	}

	if (!existence)
	{
		cout << " There are no such monsters :( " << endl;
	}
}

void searchBySpecifiedCriteria3(vector<monstersStr>monstersVec, size_t act)
{
	int mon, day, year, hour, min;
	char ignore;

	switch (act)
	{
	case 1:
	{
		cout << " Enter the date and time the monster appeared in the game:" << endl;
		cout << " date (mm/dd/yyyy): ";
		cin >> mon >> ignore >> day >> ignore >> year;
		cout << " time (hh:mm): ";
		cin >> hour >> ignore >> min;

		break;
	}
	case 2:
	{
		mon = 9;
		day = 19;
		year = 2007;
		hour = 16;
		min = 23;

		break;
	}
	default: break;
	}

	cout << " All monsters that appeared after the specified time: " << "\n" << endl;
	for (size_t i = 0; i < monstersVec.size(); i++)
	{
		if (monstersVec[i].time.tm_year > year)
		{
			printElements(i, monstersVec);
		}
		else if (monstersVec[i].time.tm_year == year)
		{
			if (monstersVec[i].time.tm_mon > mon)
			{
				printElements(i, monstersVec);
			}
			else if (monstersVec[i].time.tm_mon == mon)
			{
				if (monstersVec[i].time.tm_mday > day)
				{
					printElements(i, monstersVec);
				}
				else if (monstersVec[i].time.tm_mday == day)
				{
					if (monstersVec[i].time.tm_hour > hour)
					{
						printElements(i, monstersVec);
					}
					else if (monstersVec[i].time.tm_hour == hour)
					{
						if (monstersVec[i].time.tm_min > min)
						{
							printElements(i, monstersVec);
						}
						else
						{
							break;
						}
					}
				}
			}
		}
	}

}

void printElements(size_t i, vector<monstersStr>monstersVec)
{
	if (monstersVec[i].name != "" && monstersVec[i].id != 0)
	{
		cout << " Monster: " << endl;
		cout << " The name of the monster: " << monstersVec[i].name << endl;
		cout << " The number of health units: " << monstersVec[i].health << endl;
		cout << " The number of attack units: " << monstersVec[i].attack << endl;
		cout << " The chance to perform a special attack: " << monstersVec[i].chanceAtSpecial << endl;
		cout << " The type of special attack: " << monstersVec[i].typeOfSpecial << endl;
		cout << " The date and time the monster appeared in the game: ";
		cout << monstersVec[i].time.tm_mon << "/" << monstersVec[i].time.tm_mday << "/" << monstersVec[i].time.tm_year;
		cout << " at " << monstersVec[i].time.tm_hour << ":" << monstersVec[i].time.tm_min << endl;
		cout << " Monster ID: " << monstersVec[i].id << endl;
		cout << " \n ";
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
