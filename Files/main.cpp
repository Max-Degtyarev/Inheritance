#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
using std::cin;
using std::cout;
using std::endl;


//#define WRITE_TO_FILE

void main()
{

	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
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
#endif // WRITE_TO_FILE

	std::ifstream fin;
	fin.open("File.txt");
	if (fin.is_open())
	{
		const int n = 102400;
		char buffer[n] = {};
		while (!fin.eof()) // end of file
		{
			//fin >> buffer;
			fin.getline(buffer, n);
			cout << buffer << endl;
		}
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
	fin.close();
	system("notepad File.txt");





}
