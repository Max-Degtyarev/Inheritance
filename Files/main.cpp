#include<iostream>
#include<fstream>
using std::cin;
using std::cout;
using std::endl;


void main()
{

	setlocale(LC_ALL, "");
	std::ofstream fout; // Создаем поток 
	fout.open("File.txt"), std::ios_base::app; // Открываем поток
	//system("REN File.txt");
	fout << "Hello world\n"; // Выводим поток
	fout.close(); //Закрываем поток
	// Потоки обязательно нужно закрывать, это также важно как удалять память
	// Сколько раз был вызван метод open, столько же раз нужно вызвать метод close

	system("notepad File.txt");






}
