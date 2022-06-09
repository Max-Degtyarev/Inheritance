
#include"Academy.h"
#include"AcademyStudent.h"
#include"AcademyTeacher.h"
#include"AcademyGraduate.h"


//#define INHERITANCE_CHECK
#define POLIMORPHISM_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef INHERITANCE_CHECK
	Human human("Montana", "Antonio", 25);
	human.print();
	cout << delimiter;
	Student pinkman("Pinkman", "Jessie", 23, "Chemistry", "WW_220", 1, 90, 85);
	pinkman.print();
	cout << delimiter;
	Teacher teacher("Smith", "John", 40, "Professor", 20);
	teacher.print();
	cout << delimiter;
	Graduate graduate("Knight", "Thomas", 22, "Geography", "PV_111", 5, 98.53, 95.85, "Alps mountain", 5);
	graduate.print();
#endif // INHERITANCE_CHECK



#ifdef POLIMORPHISM_CHECK
	//Generalisation:
	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 23, "Chemistry", "WW_220", 1, 90, 95),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Schreder", "Hank", 25, "Criminalistics", "WW_220", 5, 95, 80, "Alps mountain", 5),
		new Student("Vercetti", "Tomas", 30, "Theft", "Vice", 3, 90, 85),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20),
		new Teacher("Einstein", "Albert", 143, "Astronomy", 100)
	};


	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		group[i]->print();
		cout << "--------------------------------------\n";
	}

#endif // POLIMORPHISM_CHECK

	

}