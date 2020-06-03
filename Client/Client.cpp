
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include "conio.h"
#include "functional"
#include "vector"
#include <iomanip>
#include <windows.h>
#pragma comment(lib, "winmm")
#pragma warning(disable: 4996)

SOCKET Connection;
using namespace std;

int menu();
int menuAdmin();
int menuAdminMange();
int menuAdminPolicy();
int menuUser();
int menuAdminTaks();
int menuTask();
int chooseTak(vector<string> List);

int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Error" << endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		cout << "Ошибка подключения\n";
		return 1;
	}

	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);
	PlaySound(TEXT("turn_on.wav"), NULL, SND_FILENAME | SND_ASYNC);
	std::cout << "Loading.";
	for (int counter = 0; counter < 34; counter++) {
		std::cout << ".";
		Sleep(110);
	}
	system("cls");
	std::cout << "|              Инструкция            |" << std::endl;
	std::cout << "|------------------------------------|" << std::endl;
	std::cout << "|     'Arrow UP'     - курсор вверх  |" << std::endl;
	std::cout << "|     'Arrow Down'   - курсор вниз   |" << std::endl;
	std::cout << "|     'Enter'        - выбрать пункт |" << std::endl;
	std::cout << "|____________________________________|" << std::endl;
	std::cout << "Нажмите любую клавишу для продолжения..." << std::endl;
	_getch();
	string msg1;
	int gl_check = 1;
	while (gl_check == 1) {
		/*getline(cin, msg1);
		int msg_size = msg1.size();
		send(Connection, (char*)&msg_size, sizeof(int), NULL);
		send(Connection, msg1.c_str(), msg_size, NULL);
		Sleep(10);*/
		switch (menu())
		{
		case 1:
		{
			int point = 1;
			send(Connection, (char*)&point, sizeof(int), NULL);
			system("cls");
			int answer;

			int msg_size;
			string login_access;
			string pass_access;
			do {
				cin.clear();

				cout << "Введите логин: ";
				getline(cin, login_access);
				msg_size = login_access.size();
				send(Connection, (char*)&msg_size, sizeof(int), NULL);
				send(Connection, login_access.c_str(), msg_size, NULL);
				cout << "Введите пароль: ";


				int ch;
				while (true)
				{
					ch = _getch();
					if (ch == 13)
					{
						break;
					}
					if (ch == 8)
					{
						if (!pass_access.empty())
						{
							cout << (char)8 << ' ' << char(8);
							pass_access.erase(pass_access.length() - 1);
						}
					}
					else
					{
						cout << '*';
						pass_access += (char)ch;
					}
				}
				cout << endl;

				msg_size = pass_access.size();
				send(Connection, (char*)&msg_size, sizeof(int), NULL);
				send(Connection, pass_access.c_str(), msg_size, NULL);

				recv(Connection, (char*)&answer, sizeof(int), NULL);

				Sleep(100);
				if (answer == 0) break;
				if (answer == 1) break;
				if (answer == 2) break;
				if (answer == 3) break;
				if (answer == -1) break;
				if (answer == 4)
				{
					cout << "\nЕще раз\n" << endl;
				}
				if (answer == 5)
				{
					cout << "\nЕще раз\n" << endl;
				}
			} while (true);
			if (answer == -1) break;
			int statusAccess = answer;
			Sleep(1000);
			system("cls");
			switch (statusAccess)
			{
			case 1:
			{
				Sleep(1000);
				int help;
				int exit = 0;
				while (exit != 1)
				{
					switch (menuUser())
					{
					case 1:
					{
						help = 1;
						send(Connection, (char*)&help, sizeof(int), NULL);
						system("cls");

						int count_car;
						recv(Connection, (char*)&count_car, sizeof(int), NULL);
						cout << endl;
						cout << "|          Наименование страховки             |    Тип    |  Длительность (дней)  |     Цена ($)     |" << endl;
						for (int i = 0; i < count_car; i++)
						{

							int size;
							recv(Connection, (char*)&size, sizeof(int), NULL);
							char* login_read = new char[size + 1];
							login_read[size] = '\0';
							recv(Connection, login_read, size, NULL);
							string name = login_read;
							recv(Connection, (char*)&size, sizeof(int), NULL);
							char* pass_read = new char[size + 1];
							pass_read[size] = '\0';
							recv(Connection, pass_read, size, NULL);
							string type = pass_read;
							recv(Connection, (char*)&size, sizeof(int), NULL);
							cout << "|" << setw(45) << name << "|" << setw(11) << type << "|" << setw(23) << size << "|";
							recv(Connection, (char*)&size, sizeof(int), NULL);
							cout << setw(18) << size << "|" << endl;
							delete[] login_read, pass_read;
						}
						for (int counter = 0; counter < 102; counter++) {
							cout << "—";
						}
						cout << endl;
						_getch();

						break;
					}
					case 2:
					{
						help = 2;
						send(Connection, (char*)&help, sizeof(int), NULL);
						system("cls");

						int size = login_access.size();
						send(Connection, (char*)&size, sizeof(int), NULL);
						send(Connection, login_access.c_str(), size, NULL);
						int count;
						recv(Connection, (char*)&count, sizeof(int), NULL);
						cout << endl;
						if (count == 0) {


						}
						else {
							for (int i = 0; i < count; i++)
							{
								recv(Connection, (char*)&size, sizeof(int), NULL);
								char* login_read = new char[size + 1];
								login_read[size] = '\0';
								recv(Connection, login_read, size, NULL);
								string name_car = login_read;
								cout << "Полис: " << name_car << endl;
								cout << endl;
							}
						}
						_getch();
						break;
					}
					case 3:
					{
						help = 3;
						send(Connection, (char*)&help, sizeof(int), NULL);
						system("cls");

						int size = login_access.size();
						send(Connection, (char*)&size, sizeof(int), NULL);
						send(Connection, login_access.c_str(), size, NULL);


						string name;
						cout << "Введите наименование полиса: ";
						getline(cin, name);
						size = name.size();
						send(Connection, (char*)&size, sizeof(int), NULL);
						send(Connection, name.c_str(), size, NULL);

						recv(Connection, (char*)&size, sizeof(int), NULL);
						if (size == 0)
						{
							cout << "Полиса нет" << endl;
						}
						else if (size == 1)
						{
							
							cout << "Полис добавлен" << endl;
						}
						else {
	
							cout << "Такой полис уже добавлен" << endl;
						}
						Sleep(1000);


						break;
					}
					case 4:
					{
						help = 4;
						send(Connection, (char*)&help, sizeof(int), NULL);
						system("cls");

						int size = login_access.size();
						send(Connection, (char*)&size, sizeof(int), NULL);
						send(Connection, login_access.c_str(), size, NULL);


						string name;
						cout << "Введите наименование полиса: ";
						getline(cin, name);
						size = name.size();
						send(Connection, (char*)&size, sizeof(int), NULL);
						send(Connection, name.c_str(), size, NULL);

						recv(Connection, (char*)&size, sizeof(int), NULL);
						if (size == 0)
						{
							cout << "Полис нет" << endl;
						}
						else
						{
							cout << "Полис удален" << endl;
						}

						Sleep(1000);
						break;
					}
					case 5:
					{
						help = 5;
						send(Connection, (char*)&help, sizeof(int), NULL);
						system("cls");

						int size = login_access.size();
						send(Connection, (char*)&size, sizeof(int), NULL);
						send(Connection, login_access.c_str(), size, NULL);


						string name;
						cout << "Введите наименование полиса и марку вашего авто: ";
						getline(cin, name);
						size = name.size();
						send(Connection, (char*)&size, sizeof(int), NULL);
						send(Connection, name.c_str(), size, NULL);
						recv(Connection, (char*)&size, sizeof(int), NULL);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

						Sleep(1000);
						break;
					}
					case 6:
					{
						exit = 6;
						send(Connection, (char*)&exit, sizeof(int), NULL);
						exit = 1;
						break;
					}
					}
				}
				break;
			}
			case 2:
			{
				int help;
				int exit = 0;
				while (exit != 1)
				{
					switch (menuTask())
					{
					case 1:
					{
						help = 1;
						send(Connection, (char*)&help, sizeof(int), NULL);
						system("cls");
						int status = 1;
						cout << endl;
						int count_task = 1;
						int amount;
						do
						{
							recv(Connection, (char*)&status, sizeof(int), NULL);
							if (status == 1)
							{
								int size;
								recv(Connection, (char*)&size, sizeof(int), NULL);
								char* login_read = new char[size + 1];
								login_read[size] = '\0';
								recv(Connection, login_read, size, NULL);
								string task = login_read;
								cout << "Задача " << count_task << ": " << task << endl;
								cout << "Варианты решений:" << endl;
								recv(Connection, (char*)&amount, sizeof(int), NULL);
								for (int i = 0; i < amount; i++)
								{
									recv(Connection, (char*)&size, sizeof(int), NULL);
									char* login_re = new char[size + 1];
									login_re[size] = '\0';
									recv(Connection, login_re, size, NULL);
									string decide = login_re;
									cout << " — " << decide << endl;
								}
								cout << endl;

								count_task++;
							}
							else break;
						} while (status == 1);
						_getch();
						break;
					}
					case 2:
					{
						help = 2;
						send(Connection, (char*)&help, sizeof(int), NULL);
						system("cls");

						int status = 1;
						cout << endl;
						int count_task = 1;
						int mark;
						int amount;
						int summ = 0;
						int top_mark = 0;
						string top;
						do
						{
							recv(Connection, (char*)&status, sizeof(int), NULL);
							if (status == 1)
							{
								summ = 0;
								int size;
								recv(Connection, (char*)&size, sizeof(int), NULL);
								char* login_read = new char[size + 1];
								login_read[size] = '\0';
								recv(Connection, login_read, size, NULL);
								string task = login_read;
								cout << "Задача " << count_task << ": " << task << endl;
								cout << "Варианты решений:" << endl;
								recv(Connection, (char*)&amount, sizeof(int), NULL);
								top_mark = 0;
								for (int i = 0; i < amount; i++)
								{

									recv(Connection, (char*)&size, sizeof(int), NULL);
									char* login_re = new char[size + 1];
									login_re[size] = '\0';
									recv(Connection, login_re, size, NULL);
									string decide = login_re;
									cout << " — " << decide << endl;
									recv(Connection, (char*)&mark, sizeof(int), NULL);
									cout << "	Ожидаемая денежная оценка: " << mark << endl;
									summ += mark;
									if (mark > top_mark)
									{
										top_mark = mark;
										top = decide;
									}
								}
								float res = top_mark;
								cout << "Самых выгодный вариант из заданных: " << top << ", ожидаемая денежная оценка: " << res << endl;
								cout << endl;

								count_task++;
							}
							else break;
						} while (status == 1);
						_getch();
						break;
					}
					case 3:
					{
						help = 3;
						send(Connection, (char*)&help, sizeof(int), NULL);
						system("cls");

						int status_list = 1;
						cout << endl;
						int count_task_list = 0;
						vector<string> LISt;
						int amount_list;
						do
						{
							recv(Connection, (char*)&status_list, sizeof(int), NULL);
							if (status_list == 1)
							{
								int size;
								recv(Connection, (char*)&size, sizeof(int), NULL);
								char* login_read = new char[size + 1];
								login_read[size] = '\0';
								recv(Connection, login_read, size, NULL);
								string task = login_read;
								cout << task << endl;
								LISt.push_back(task);


								count_task_list++;
							}
							else break;
						} while (status_list == 1);
						int choise_list = chooseTak(LISt);
						vector<string>::iterator it = LISt.begin();
						for (int k = 0; k < choise_list - 1; k++)
						{
							++it;
						}
						string name = *it;
						int size = name.size();
						send(Connection, (char*)&size, sizeof(int), NULL);
						send(Connection, name.c_str(), size, NULL);
						int status;
						int amount;
						do
						{
							recv(Connection, (char*)&status, sizeof(int), NULL);
							if (status == 5)
							{
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
								int size;
								recv(Connection, (char*)&size, sizeof(int), NULL);
								char* login_read = new char[size + 1];
								login_read[size] = '\0';
								recv(Connection, login_read, size, NULL);
								string task = login_read;
								cout << *it << ")" << endl;
								cout << "\nПосле каждого варианта введите предполагаемую прибыль и убыток: \n" << endl;
								cout << "Варианты решений:" << endl;
								recv(Connection, (char*)&amount, sizeof(int), NULL);
								for (int i = 0; i < amount; i++)
								{
									recv(Connection, (char*)&size, sizeof(int), NULL);
									char* login_re = new char[size + 1];
									login_re[size] = '\0';
									recv(Connection, login_re, size, NULL);
									string decide = login_re;
									cout << " — " << decide << endl;
									int mark;
									int income, lesion;
									cout << "	Введите прибыль:";
									do
									{
										try
										{
											if (!(cin >> income) || (cin.peek() != '\n'))
											{
												cin.clear();

												throw "err";
											}
											if (income >= 0) break;

											throw "err";
										}
										catch (...)
										{
											cout << "Еще раз" << endl;
											cin.clear();
											while (cin.get() != '\n');
										}
									} while (true);
									cout << "	Введите убыток:";
									do
									{
										try
										{
											if (!(cin >> lesion) || (cin.peek() != '\n'))
											{
												cin.clear();

												throw "err";
											}
											if (lesion <= 0) break;

											throw "err";
										}
										catch (...)
										{
											cout << "Еще раз" << endl;
											cin.clear();
											while (cin.get() != '\n');
										}
									} while (true);
									mark = (income * 0.5) + (lesion * 0.5);
									cin.clear();
									cin.ignore(cin.rdbuf()->in_avail());
									send(Connection, (char*)&mark, sizeof(int), NULL);
								}
								cout << endl;


							}
							else {};
						} while (status == 1);
						if (status == 2)
						{
							cout << "Задача не найдена" << endl;
						}
						if (status == 5)
						{
							cout << "Готово" << endl;
						}
						Sleep(1000);
						break;
					}
					case 4:
					{
						exit = 4;
						send(Connection, (char*)&exit, sizeof(int), NULL);
						exit = 1;
						break;
					}
					}
				}

				break;
			}
			case 3:
			{
				Sleep(1000);

				int exit = 0;
				while (exit != 1)
				{
					switch (menuAdmin())
					{
					case 1:
					{
						int help = 1;
						send(Connection, (char*)&help, sizeof(int), NULL);
						int exit_user = 0;
						while (exit_user != 1)
						{
							switch (menuAdminMange())
							{
							case 1:
							{
								help = 1;
								send(Connection, (char*)&help, sizeof(int), NULL);
								system("cls");
								int count_user;
								recv(Connection, (char*)&count_user, sizeof(int), NULL);
								cout << endl;
								for (int i = 0; i < count_user; i++)
								{

									int size;
									recv(Connection, (char*)&size, sizeof(int), NULL);
									char* login_read = new char[size + 1];
									login_read[size] = '\0';
									recv(Connection, login_read, size, NULL);
									string login = login_read;
									cout << "Логин: " << login << endl;
									recv(Connection, (char*)&size, sizeof(int), NULL);
									char* pass_read = new char[size + 1];
									pass_read[size] = '\0';
									recv(Connection, pass_read, size, NULL);
									string pass = pass_read;
									cout << "Пароль: " << pass << endl;
									recv(Connection, (char*)&size, sizeof(int), NULL);
									cout << "Уровень доступа: " << size << endl;
									cout << endl;
									delete[] login_read, pass_read;
								}
								_getch();

								break;
							}
							case 2:
							{
								help = 2;
								cin.clear();

								send(Connection, (char*)&help, sizeof(int), NULL);
								system("cls");
								string login;
								string pass;
								int size;
								cout << "Введите логин: ";
								getline(cin, login);
								size = login.size();
								send(Connection, (char*)&size, sizeof(int), NULL);
								send(Connection, login.c_str(), size, NULL);
								cout << "Введите пароль: ";
								getline(cin, pass);
								size = pass.size();
								send(Connection, (char*)&size, sizeof(int), NULL);
								send(Connection, pass.c_str(), size, NULL);
								cout << "Уровень доступа: ";
								do
								{
									try
									{
										if (!(cin >> size) || (cin.peek() != '\n'))
										{
											cin.clear();

											throw "err";
										}
										if (size == 1) {
										 break;
										}
										if (size == 2) {
				
											break;
										}
										if (size == 3) {
	
											break;
										}
										throw "err";
									}
									catch (...)
									{
										cout << " Еще раз" << endl;
										cin.clear();
										while (cin.get() != '\n');
									}
								} while (true);
								cin.clear();
								cin.ignore(cin.rdbuf()->in_avail());
								send(Connection, (char*)&size, sizeof(int), NULL);
								recv(Connection, (char*)&size, sizeof(int), NULL);
								if (size == 0)
								{
									cout << "Пользователь добавлен" << endl;
								}
								else {
									cout << "Логин занят" << endl;
								}
								Sleep(1000);
								break;
							}
							case 3:
							{
								help = 3;
								send(Connection, (char*)&help, sizeof(int), NULL);

								system("cls");
								string login;
								string pass;
								int size;
								cout << "Введите логин: ";
								getline(cin, login);
								size = login.size();
								send(Connection, (char*)&size, sizeof(int), NULL);
								send(Connection, login.c_str(), size, NULL);
								recv(Connection, (char*)&size, sizeof(int), NULL);
								if (size == 1)
								{
									cout << "Пользователь удален" << endl;
								}
								else {
									cout << "Логин не найден" << endl;
								}
								Sleep(1000);
								break;
							}
							case 4:
							{
								help = 4;
								send(Connection, (char*)&help, sizeof(int), NULL);
								exit_user = 1;
								break;
							}
							}
						}
						break;
					}
					case 2:
					{
						int help = 2;
						send(Connection, (char*)&help, sizeof(int), NULL);
						int exit_user = 0;
						while (exit_user != 1)
						{
							switch (menuAdminPolicy())
							{
							case 1:
							{
								help = 1;
								send(Connection, (char*)&help, sizeof(int), NULL);
								system("cls");

								int count_car;
								recv(Connection, (char*)&count_car, sizeof(int), NULL);
								cout << endl;
								cout << "|          Наименование страховки             |    Тип    |  Длительность (дней)  |     Цена ($)     |" << endl;
								for (int i = 0; i < count_car; i++)
								{

									int size;
									recv(Connection, (char*)&size, sizeof(int), NULL);
									char* login_read = new char[size + 1];
									login_read[size] = '\0';
									recv(Connection, login_read, size, NULL);
									string name = login_read;
									recv(Connection, (char*)&size, sizeof(int), NULL);
									char* pass_read = new char[size + 1];
									pass_read[size] = '\0';
									recv(Connection, pass_read, size, NULL);
									string type = pass_read;
									recv(Connection, (char*)&size, sizeof(int), NULL);
									cout << "|" << setw(45) << name << "|" << setw(11) << type << "|" << setw(23) << size << "|";
									recv(Connection, (char*)&size, sizeof(int), NULL);
									cout << setw(18) << size << "|" << endl;
									delete[] login_read, pass_read;
								}
								for (int counter = 0; counter < 102; counter++) {
									cout << "—";
								}
								cout << endl;
								_getch();


								break;
							}
							case 2:
							{
								help = 2;
								cin.clear();
								send(Connection, (char*)&help, sizeof(int), NULL);
								system("cls");

								string name;
								string type;
								int size;
								cout << "Введите наименование полиса: ";
								getline(cin, name);
								size = name.size();
								send(Connection, (char*)&size, sizeof(int), NULL);
								send(Connection, name.c_str(), size, NULL);
								cout << "Введите тип полиса: ";
								getline(cin, type);
								size = type.size();
								send(Connection, (char*)&size, sizeof(int), NULL);
								send(Connection, type.c_str(), size, NULL);
								cout << "Введите длительность действия: ";
								do
								{
									try
									{
										if (!(cin >> size) || (cin.peek() != '\n'))
										{
											cin.clear();

											throw "err";
										}
										break;
									}
									catch (...)
									{
										cout << "Еще раз" << endl;
										cin.clear();
										while (cin.get() != '\n');
									}
								} while (true);
								cin.clear();
								cin.ignore(cin.rdbuf()->in_avail());
								send(Connection, (char*)&size, sizeof(int), NULL);
								cout << "Введите цену: ";
								do
								{
									try
									{
										if (!(cin >> size) || (cin.peek() != '\n'))
										{
											cin.clear();

											throw "err";
										}
										break;
									}
									catch (...)
									{
										cout << " Еще раз" << endl;
										cin.clear();
										while (cin.get() != '\n');
									}
								} while (true);
								cin.clear();
								cin.ignore(cin.rdbuf()->in_avail());
								send(Connection, (char*)&size, sizeof(int), NULL);

								recv(Connection, (char*)&size, sizeof(int), NULL);
								if (size == 0)
								{

									cout << "Добавлено" << endl;
								}
								else {

									cout << "Уже существует" << endl;
								}
								Sleep(1000);

								break;
							}
							case 3:
							{
								help = 3;
								send(Connection, (char*)&help, sizeof(int), NULL);
								system("cls");

								string name;

								int size;
								cout << "Введите логин для удаления: ";
								getline(cin, name);
								size = name.size();
								send(Connection, (char*)&size, sizeof(int), NULL);
								send(Connection, name.c_str(), size, NULL);
								recv(Connection, (char*)&size, sizeof(int), NULL);
								if (size == 1)
								{

									cout << "Полис удален" << endl;
								}
								else {

									cout << "Полис не найден" << endl;
								}
								Sleep(1000);
								break;
							}
							case 4:
							{
								help = 4;
								send(Connection, (char*)&help, sizeof(int), NULL);
								system("cls");

								int count_car;
								recv(Connection, (char*)&count_car, sizeof(int), NULL);
								cout << "|          Наименование страховки             |    Тип    |  Длительность (дней)  |     Цена ($)     |" << endl;
								for (int i = 0; i < count_car; i++)
								{

									int size;
									recv(Connection, (char*)&size, sizeof(int), NULL);
									char* login_read = new char[size + 1];
									login_read[size] = '\0';
									recv(Connection, login_read, size, NULL);
									string name = login_read;
									recv(Connection, (char*)&size, sizeof(int), NULL);
									char* pass_read = new char[size + 1];
									pass_read[size] = '\0';
									recv(Connection, pass_read, size, NULL);
									string type = pass_read;
									recv(Connection, (char*)&size, sizeof(int), NULL);
									
									cout << "|" << setw(45) << name << "|" << setw(11) << type << "|" << setw(23) << size << "|";
									recv(Connection, (char*)&size, sizeof(int), NULL);
									cout << setw(18) << size << "|" << endl;
									delete[] login_read, pass_read;
								}
								for (int counter = 0; counter < 102; counter++) {
									cout << "—";
								}
								cout << endl;
								_getch();
								break;
							}
							case 5:
							{
								help = 5;
								send(Connection, (char*)&help, sizeof(int), NULL);
								system("cls");

								int count_car;
								recv(Connection, (char*)&count_car, sizeof(int), NULL);

								cout << "|          Наименование страховки             |    Тип    |  Длительность (дней)  |     Цена ($)     |" << endl;
								for (int i = 0; i < count_car; i++)
								{

									int size;
									recv(Connection, (char*)&size, sizeof(int), NULL);
									char* login_read = new char[size + 1];
									login_read[size] = '\0';
									recv(Connection, login_read, size, NULL);
									string name = login_read;
									recv(Connection, (char*)&size, sizeof(int), NULL);
									char* pass_read = new char[size + 1];
									pass_read[size] = '\0';
									recv(Connection, pass_read, size, NULL);
									string type = pass_read;
									recv(Connection, (char*)&size, sizeof(int), NULL);
									cout << "|" << setw(45) << name << "|" << setw(11) << type << "|" << setw(23) << size << "|";
									recv(Connection, (char*)&size, sizeof(int), NULL);
									cout << setw(18) << size << "|" << endl;
									delete[] login_read, pass_read;
								}
								for (int counter = 0; counter < 102; counter++) {
									cout << "—";
								}
								cout << endl;
								_getch();

								break;
							}
							case 6:
							{
								help = 6;
								send(Connection, (char*)&help, sizeof(int), NULL);
								exit_user = 1;
								break;
							}
							}
						}
						break;
					}
					case 3:
					{
						int help = 3;
						send(Connection, (char*)&help, sizeof(int), NULL);
						int exit_user = 0;
						while (exit_user != 1)
						{
							switch (menuAdminTaks())
							{
							case 1:
							{
								int help = 1;
								send(Connection, (char*)&help, sizeof(int), NULL);
								system("cls");
								int count = 0;
								recv(Connection, (char*)&count, sizeof(int), NULL);
								cout << endl;
								for (int i = 0; i < count; i++)
								{
									int size;
									recv(Connection, (char*)&size, sizeof(int), NULL);
									char* login_read = new char[size + 1];
									login_read[size] = '\0';
									recv(Connection, login_read, size, NULL);
									string name = login_read;

									cout << "Автор: " << name << endl;
									recv(Connection, (char*)&size, sizeof(int), NULL);
									char* login_re = new char[size + 1];
									login_re[size] = '\0';
									recv(Connection, login_re, size, NULL);
									name = login_re;

									cout << "Заявка: " << name << endl;
									cout << endl;
									delete[] login_read, login_re;
								}
								_getch();
								break;
							}
							case 2:
							{
								int help = 2;
								send(Connection, (char*)&help, sizeof(int), NULL);
								system("cls");
								int status = 1;
								cout << endl;
								int count_task = 1;
								int amount;
								do
								{
									recv(Connection, (char*)&status, sizeof(int), NULL);
									if (status == 1)
									{
										int size;
										recv(Connection, (char*)&size, sizeof(int), NULL);
										char* login_read = new char[size + 1];
										login_read[size] = '\0';
										recv(Connection, login_read, size, NULL);
										string task = login_read;

										cout << "Задача " << count_task << ": " << task << endl;

										cout << "Варианты реализации:" << endl;
										recv(Connection, (char*)&amount, sizeof(int), NULL);
										for (int i = 0; i < amount; i++)
										{
											recv(Connection, (char*)&size, sizeof(int), NULL);
											char* login_re = new char[size + 1];
											login_re[size] = '\0';
											recv(Connection, login_re, size, NULL);
											string decide = login_re;
											cout << " — " << decide << endl;
										}
										cout << endl;

										count_task++;
									}
									else break;
								} while (status == 1);
								_getch();
								break;
							}
							case 3:
							{
								int help = 3;
								send(Connection, (char*)&help, sizeof(int), NULL);
								system("cls");

								int status = 1;
								cout << endl;
								int count_task = 1;
								int mark;
								int amount;
								int summ = 0;
								int top_mark = 0;
								string top;
								do
								{
									recv(Connection, (char*)&status, sizeof(int), NULL);
									if (status == 1)
									{
										summ = 0;
										int size;
										recv(Connection, (char*)&size, sizeof(int), NULL);
										char* login_read = new char[size + 1];
										login_read[size] = '\0';
										recv(Connection, login_read, size, NULL);
										string task = login_read;

										cout << "Задача " << count_task << ": " << task << endl;
										cout << "Варианты решений:" << endl;
										recv(Connection, (char*)&amount, sizeof(int), NULL);
										top_mark = 0;
										for (int i = 0; i < amount; i++)
										{

											recv(Connection, (char*)&size, sizeof(int), NULL);
											char* login_re = new char[size + 1];
											login_re[size] = '\0';
											recv(Connection, login_re, size, NULL);
											string decide = login_re;
											cout << " — " << decide << ".";
											recv(Connection, (char*)&mark, sizeof(int), NULL);
											cout << "  Ожидаемая денежная оценка: " << mark << endl;
											summ += mark;
											if (mark > top_mark)
											{
												top_mark = mark;
												top = decide;
											}
										}
										float res = top_mark;
										cout << "Самый выгодный вариант из заданных: " << top << ", его ожидаемая денежная оценка: " << res << endl;
										cout << endl;

										count_task++;
									}
									else break;
								} while (status == 1);
								_getch();
								break;
							}
							case 4:
							{
								int help = 4;
								send(Connection, (char*)&help, sizeof(int), NULL);
								system("cls");

								string task;
								string decide;
								int count;
								int size;
								cout << "Введите задачу: ";
								getline(cin, task);
								size = task.size();
								send(Connection, (char*)&size, sizeof(int), NULL);
								send(Connection, task.c_str(), size, NULL);
								cout << "Введите количество вариантов решения: ";
								do
								{
									try
									{
										if (!(cin >> count) || (cin.peek() != '\n'))
										{
											cin.clear();

											throw "err";
										}
										break;
									}
									catch (...)
									{
										cout << " Еще раз" << endl;
										cin.clear();
										while (cin.get() != '\n');
									}
								} while (true);
								cin.clear();
								cin.ignore(cin.rdbuf()->in_avail());
								send(Connection, (char*)&count, sizeof(int), NULL);
								for (int i = 0; i < count; i++)
								{
									cout << "Введите вариант решения: ";
									getline(cin, decide);
									size = decide.size();
									send(Connection, (char*)&size, sizeof(int), NULL);
									send(Connection, decide.c_str(), size, NULL);
								}


								cout << ":)" << endl;

								Sleep(1000);
								break;
							}
							case 5:
							{
								exit_user = 5;
								send(Connection, (char*)&exit_user, sizeof(int), NULL);
								exit_user = 1;
								break;
							}
							}
						}
						break;
					}
					case 4:
					{
						exit = 4;
						send(Connection, (char*)&exit, sizeof(int), NULL);
						exit = 1;
						break;
					}
					}
				}
				break;
			}
			}

			break;
		}
		case 2:
		{
			int help = 2;
			cin.clear();

			send(Connection, (char*)&help, sizeof(int), NULL);
			system("cls");
			string login;
			string pass;
			int size;
			cout << "Введите логин: ";
			getline(cin, login);
			size = login.size();
			send(Connection, (char*)&size, sizeof(int), NULL);
			send(Connection, login.c_str(), size, NULL);
			cout << "Введите пароль: ";
			getline(cin, pass);
			size = pass.size();
			send(Connection, (char*)&size, sizeof(int), NULL);
			send(Connection, pass.c_str(), size, NULL);
			size = 1;
			send(Connection, (char*)&size, sizeof(int), NULL);
			recv(Connection, (char*)&size, sizeof(int), NULL);
			if (size == 0)
			{

				cout << "Пользователь добавлен" << endl;
			}
			else {
				cout << "Логин занят" << endl;
			}
			Sleep(1000);
			break;
		}
		case 3:
		{
			int help = 3;
			cin.clear();
			send(Connection, (char*)&help, sizeof(int), NULL);
			cout << "Отключено" << endl;
			gl_check = 0;
			break;
		}
		}

	}
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	PlaySound(TEXT("turn_off.wav"), NULL, SND_FILENAME | SND_ASYNC);
	std::cout << "Loading.";
	for (int counter = 0; counter < 30; counter++) {
		std::cout << ".";
		Sleep(100);
	}
	return 0;
}

int chooseTak(vector<string> List)
{
	Sleep(500);
	int pointer = 0;
	vector<string>::iterator it = List.begin();
	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		for (vector<string>::iterator itter = List.begin(); itter != List.end(); ++itter)
		{
			if (*itter == *it)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
				cout << *itter << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << *itter << endl;
			}
		}
		while (true)
		{
			char vvod;
			vvod = _getch();
			if (vvod == 72)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = List.size() - 1;
					--it;
				}
				Sleep(100);
				break;
			}
			else if (vvod == 80)
			{
				pointer += 1;
				++it;
				if (pointer == List.size())
				{
					pointer = 0;
					it = List.begin();
				}
				Sleep(100);
				break;
			}
			else if (vvod == 13)
			{
				return (pointer + 1);
			}

		}
	}
}
int menu()
{
	Sleep(500);
	int pointer = 0;
	string menu[3] = { "Вход", "Зарегистрировать пользователя", "Выход" };

	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		for (int i = 0; i < 3; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
				cout << menu[i] << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << menu[i] << endl;
			}
		}

		while (true)
		{
			char vvod;
			vvod = _getch();
			if (vvod == 72)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 2;
				}
				Sleep(100);
				break;
			}
			else if (vvod == 80)
			{
				pointer += 1;
				if (pointer == 3)
				{
					pointer = 0;
				}
				Sleep(100);
				break;
			}
			else if (vvod == 13)
			{
				return (pointer + 1);
			}
		}
	}
}
int menuAdmin()
{
	Sleep(500);
	int pointer = 0;
	string menu[4] = { "Администрирование", "Управление", "Поддержка", "Выход" };

	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
				cout << menu[i] << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << menu[i] << endl;
			}
		}
		while (true)
		{
			char vvod;
			vvod = _getch();
			if (vvod == 72)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 3;
				}
				Sleep(100);
				break;
			}
			else if (vvod == 80)
			{
				pointer += 1;
				if (pointer == 4)
				{
					pointer = 0;
				}
				Sleep(100);
				break;
			}
			else if (vvod == 13)
			{
				return (pointer + 1);
			}

		}
	}

}
int menuAdminMange()
{
	Sleep(500);
	int pointer = 0;
	string menu[4] = { "Просмотр всех пользователей", "Добавление пользователя", "Удаление пользователя", "Выход" };

	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
				cout << menu[i] << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << menu[i] << endl;
			}
		}
		while (true)
		{
			char vvod;
			vvod = _getch();
			if (vvod == 72)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 3;
				}
				Sleep(100);
				break;
			}
			else if (vvod == 80)
			{
				pointer += 1;
				if (pointer == 4)
				{
					pointer = 0;
				}
				Sleep(100);
				break;
			}
			else if (vvod == 13)
			{
				return (pointer + 1);
			}

		}
	}
}
int menuAdminPolicy()
{
	Sleep(500);
	int pointer = 0;
	string menu[6] = { "Просмотр всех полисов", "Добавить полис", "Удалить полис", "Сортировать по цене", "Фильтрация по сроку (на 1 год и более)","Выход" };

	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		for (int i = 0; i < 6; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
				cout << menu[i] << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << menu[i] << endl;
			}
		}
		while (true)
		{
			char vvod;
			vvod = _getch();
			if (vvod == 72)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 5;
				}
				Sleep(100);
				break;
			}
			else if (vvod == 80)
			{
				pointer += 1;
				if (pointer == 6)
				{
					pointer = 0;
				}
				Sleep(100);
				break;
			}
			else if (vvod == 13)
			{
				return (pointer + 1);
			}

		}
	}
}
int menuAdminTaks()
{
	Sleep(500);
	int pointer = 0;
	string menu[6] = { "Просмотр заявок", "Нерешенные задачи","Решенные задачи", "Добавить задачу","Выход" };

	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		for (int i = 0; i < 5; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
				cout << menu[i] << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << menu[i] << endl;
			}
		}
		while (true)
		{
			char vvod;
			vvod = _getch();
			if (vvod == 72)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 4;
				}
				Sleep(100);
				break;
			}
			else if (vvod == 80)
			{
				pointer += 1;
				if (pointer == 5)
				{
					pointer = 0;
				}
				Sleep(100);
				break;
			}
			else if (vvod == 13)
			{
				return (pointer + 1);
			}

		}
	}
}
int menuUser()
{
	Sleep(500);
	int pointer = 0;
	string menu[6] = { "Просмотр полисов", "Избранное","Добавить в избранное", "Удаление полиса из избранного", "Создать заявку", "Выход" };

	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		for (int i = 0; i < 6; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
				cout << menu[i] << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << menu[i] << endl;
			}
		}
		while (true)
		{
			char vvod;
			vvod = _getch();
			if (vvod == 72)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 5;
				}
				Sleep(100);
				break;
			}
			else if (vvod == 80)
			{
				pointer += 1;
				if (pointer == 6)
				{
					pointer = 0;
				}
				Sleep(100);
				break;
			}
			else if (vvod == 13)
			{
				return (pointer + 1);
			}

		}
	}
}
int menuTask()
{
	Sleep(500);
	int pointer = 0;
	string menu[4] = { "Нерешенные задачи", "Решенные задачи","Решение задачи","Выход" };

	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
				cout << menu[i] << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << menu[i] << endl;
			}
		}
		while (true)
		{
			char vvod;
			vvod = _getch();
			if (vvod == 72)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 3;
				}
				Sleep(100);
				break;
			}
			else if (vvod == 80)
			{
				pointer += 1;
				if (pointer == 4)
				{
					pointer = 0;
				}
				Sleep(100);
				break;
			}
			else if (vvod == 13)
			{
				return (pointer + 1);
			}

		}
	}
}