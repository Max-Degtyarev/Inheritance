

#include"AcademyTeacher.h"

const std::string& Teacher::get_specialty()const
{
	return specialty;
}
unsigned int Teacher::get_experience()const
{
	return experience;
}

void Teacher::set_specialty(const std::string& specialty)
{
	this->specialty = specialty;
}
void Teacher::set_experience(unsigned int experience)
{
	this->experience = experience;
}

// Constructors

Teacher::Teacher
(
	const std::string& last_name, const std::string& first_name, unsigned int age,
	const std::string& specialty, unsigned int experience
) : Human(last_name, first_name, age)
{
	set_specialty(specialty);
	set_experience(experience);
	cout << "TConstructor:\t" << this << endl;
}

Teacher::~Teacher()
{
	cout << "TDestructor:\t" << this << endl;
}


// Methods

void Teacher::print()const
{
	Human::print();
	cout << specialty << " " << experience << endl;
}
