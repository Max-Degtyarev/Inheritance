#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using std::cout;
using std::cin;
using std::endl;

#define delimiter "\n---------------------------------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, unsigned int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
protected:
	std::string last_name;
	std::string first_name;
	unsigned int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	unsigned int get_age()const
	{
		return age;
	}

	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(unsigned int age)
	{
		this->age = age;
	}

	// Constructors

	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}

	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	// Methods

	virtual std::ostream& print(std::ostream& os /*= std::cout*/)const
	{
		return os << last_name << " " << first_name << " " << age << " years\n";

	}

	virtual std::ofstream& print(std::ofstream& ofs)const
	{
		ofs.width(20);
		ofs << std::left;
		ofs << last_name + " " + first_name;
		ofs.width(8);
		ofs << std::right;
		ofs << age;
		return ofs;
		
	}




};

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.print(os);
}

std::ofstream& operator<<(std::ofstream& ofs, const Human& obj)
{
	return obj.print(ofs);
	//std::ofstream fout;

	/*of << obj.get_last_name() << " " << obj.get_first_name() << " " << obj.get_age() << " years\n";
	return of;*/
}



#define STUDENT_TAKE_PARAMETERS const std::string& specialty, const std::string& group, unsigned int year, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS specialty, group, year, rating, attendance

class Student :public Human
{
	std::string specialty;
	std::string group;
	unsigned int year;
	double rating;
	double attendance;
public:
	const std::string& get_specialty()const
	{
		return specialty;
	}
	const std::string& get_group()const
	{
		return group;
	}
	unsigned int get_year()const
	{
		return year;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}

	void set_specialty(const std::string& specialty)
	{
		this->specialty = specialty;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_year(unsigned int year)
	{
		this->year = year;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	// Constructors
	Student (HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS):Human(HUMAN_GIVE_PARAMETERS)
	{
		set_specialty(specialty);
		set_group(group);
		set_year(year);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}

	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	// Methods

	std::ostream& print(std::ostream& os)const
	{
		Human::print(os);
		return os << "speciality - " << specialty << endl << "group - " << group << endl << "year - " << year << endl <<
			"rating - " << rating << endl << "attendance - " << attendance << endl;
	}
	std::ofstream& print(std::ofstream& ofs)const
	{
		Human::print(ofs) << " ";
		ofs.width(25);
		ofs << std::left;
		ofs << specialty;
		ofs.width(8);
		ofs << group << " " << year;
		ofs.width(8);
		ofs << std::right;
		ofs << std::setprecision(2) << std::fixed;
		ofs << rating << " " << attendance << " ";
		return ofs;
	}

	

};





class Teacher :public Human
{
	std::string specialty;
	unsigned int experience;
public:
	const std::string& get_specialty()const
	{
		return specialty;
	}
	unsigned int get_experience()const
	{
		return experience;
	}

	void set_specialty(const std::string& specialty)
	{
		this->specialty = specialty;
	}
	void set_experience(unsigned int experience)
	{
		this->experience = experience;
	}

	// Constructors

	Teacher
	(
		const std::string& last_name, const std::string& first_name, unsigned int age,
		const std::string& specialty, unsigned int experience
	) : Human(last_name, first_name, age)
	{
		set_specialty(specialty);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}

	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}


	// Methods

	std::ostream& print(std::ostream& os)const
	{
		Human::print(os);
		return os << specialty << " " << experience << endl;
	}
	std::ofstream& print(std::ofstream& ofs)const
	{
		/*Human::print(ofs);
		ofs << specialty << " " << experience;
		return ofs;*/

		Human::print(ofs) << " ";
		ofs.width(30);
		ofs << std::left;
		ofs << specialty;
		ofs.width(5);
		ofs << std::right;
		ofs << experience;
		return ofs;



	}


};


class Graduate:public Student
{
	std::string theme;
	unsigned int mark;
public:
	const std::string& get_theme()const
	{
		return theme;
	}
	unsigned int get_mark()const
	{
		return mark;
	}

	void set_theme(const std::string& theme)
	{
		this->theme = theme;
	}
	void set_mark(unsigned int mark)
	{
		this->mark = mark;
	}

	// Constructors

	Graduate
	(
		const std::string& last_name, const std::string& first_name, unsigned int age,
		const std::string& specialty, const std::string& group, unsigned int year, double rating, double attendance,
		const std::string& theme, unsigned int mark
	) :Student(last_name, first_name, age, specialty, group, year, rating, attendance)
	{
		set_theme(theme);
		set_mark(mark);
		cout << "GConstructor:\t" << this << endl;
	}
	
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}


	// Methods

	std::ostream& print(std::ostream& os)const
	{
		//Student::print(os);
		return Student::print(os) << "theme - " << theme << endl << "mark - " << mark << endl;
	}
	
	std::ofstream& print(std::ofstream& ofs)const
	{
		Student::print(ofs) << " ";
		ofs.width(15);
		ofs << std::left;
		ofs << theme << mark;
		return ofs;

	}



};


//#define INHERITANCE_CHECK
#define GENERALISATION_CHECK



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



#ifdef GENERALISATION_CHECK
	//Generalisation:
	//Upcast - приведение к базовому типу
	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 23, "Chemistry", "WW_220", 1, 91.2, 95),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Schreder", "Hank", 25, "Criminalistics", "WW_220", 5, 87.22, 80, "Alps mountain", 5),
		new Student("Vercetti", "Tomas", 30, "Theft", "Vice", 3, 90, 85),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20),
		new Teacher("Einstein", "Albert", 143, "Astronomy", 100),
		new Teacher("Montana", "Antonio", 25, "Criminalistics", 3)
	};


	std::ofstream fout("Academy.txt");
	cout << "--------------------------------------\n";
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		//RTTI - Runtime Type Information
		cout << typeid(*group[i]).name() << endl;
		//group[i]->print();
		cout << *group[i] << endl;
		cout << "--------------------------------------\n";
		fout << *group[i] << endl;;
		//fout << "--------------------------------------\n";
	}
	//if (typeid(*group[0]) == typeid(Student))fout << *dynamic_cast<Student*>(group[0]) << endl;
	fout.close();
	system("notepad Academy.txt");

	//cout << sizeof(group[0]);

	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];
	}




#endif // GENERALISATION_CHECK



	

	

}