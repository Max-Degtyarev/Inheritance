#include<iostream>
#include<string>
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

	~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	// Methods

	virtual void print()const
	{
		cout << last_name << " " << first_name << " " << age << " years\n";

	}

};

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

	void print()const
	{
		Human::print();
		cout << "speciality - " << specialty << endl << "group - " << group << endl << "year - " << year << endl <<
			"rating - " << rating << endl << "attendance - " << attendance << endl;
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

	void print()const
	{
		Human::print();
		cout << specialty << " " << experience << endl;
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

	void print()const
	{
		Student::print();
		cout << "theme - " << theme << endl << "mark - " << mark << endl;
	}
	
};


//#define INHERITANCE_CHECK


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



}