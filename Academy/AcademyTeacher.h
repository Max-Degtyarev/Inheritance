#pragma once

#include"Academy.h"

class Teacher :public Human
{
	std::string specialty;
	unsigned int experience;
public:
	const std::string& get_specialty()const;
	unsigned int get_experience()const;

	void set_specialty(const std::string& specialty);
	void set_experience(unsigned int experience);

	// Constructors

	Teacher
	(
		const std::string& last_name, const std::string& first_name, unsigned int age,
		const std::string& specialty, unsigned int experience
	);// : Human(last_name, first_name, age);

	~Teacher();


	// Methods

	void print()const;

};


