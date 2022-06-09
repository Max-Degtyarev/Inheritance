

#include"AcademyGraduate.h"


const std::string& Graduate::get_theme()const
{
	return theme;
}
unsigned int Graduate::get_mark()const
{
	return mark;
}

void Graduate::set_theme(const std::string& theme)
{
	this->theme = theme;
}
void Graduate::set_mark(unsigned int mark)
{
	this->mark = mark;
}

// Constructors

Graduate::Graduate
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

Graduate::~Graduate()
{
	cout << "GDestructor:\t" << this << endl;
}


// Methods

void Graduate::print()const
{
	Student::print();
	cout << "theme - " << theme << endl << "mark - " << mark << endl;
}



