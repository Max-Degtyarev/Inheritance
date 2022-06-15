#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
using std::cin;
using std::cout;
using std::endl;


void main()
{

	setlocale(LC_ALL, "");
	const int SIZE = 256;
	char sz_filename[SIZE] = {}; //sz - String Zero
	cout << "Введите имя файла: ";
	cin.getline(sz_filename, SIZE);
	if (strcmp(sz_filename + strlen(sz_filename) - 4, ".txt"))
		strcat(sz_filename, ".txt");
	std::ofstream fout; // Создаем поток 
	fout.open(sz_filename, std::ios_base::app); // Открываем поток
	char sz_contents[SIZE] = {};
	cout << "Введите содержимое файла: ";
	cin.getline(sz_contents, SIZE);
	fout << sz_contents; // Выводим поток
	fout.close(); //Закрываем поток
	char sz_command[SIZE] = "notepad ";
	strcat(sz_command, sz_filename);
	system(sz_command);
	// Потоки обязательно нужно закрывать, это также важно как удалять память
	// Сколько раз был вызван метод open, столько же раз нужно вызвать метод close






}
