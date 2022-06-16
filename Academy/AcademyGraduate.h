#pragma once

#include"Academy.h"
#include"AcademyStudent.h"


class Graduate :public Student
{
	std::string theme;
	unsigned int mark;
public:
	const std::string& get_theme()const;
	unsigned int get_mark()const;

	void set_theme(const std::string& theme);
	void set_mark(unsigned int mark);

	// Constructors

	Graduate
	(
		const std::string& last_name, const std::string& first_name, unsigned int age,
		const std::string& specialty, const std::string& group, unsigned int year, double rating, double attendance,
		const std::string& theme, unsigned int mark
	);// :Student(last_name, first_name, age, specialty, group, year, rating, attendance);

	~Graduate();


	// Methods

	void print()const;

};


std::ostream& operator<<(std::ostream& os, const Graduate& obj);

