/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file Enrollment.cpp
 *	\brief Source file for Enrollment class
 *
 *  Created on	: 29-01-2020
 *  Author		: Aditi Prakash
 */
/****************************************************************************/

//! System Includes
#include <iostream>

//! User Includes
#include "Enrollment.h"


/********************** Method Implementations ******************************/

/**
 * \brief		: Parametrised constructors
 */
Enrollment::Enrollment(float grade, std::string semester, const Course* course)
	: grade{grade}, semester{semester}, course{course}
{}

/**
 * \brief		: Getter method for student grade
 * \param		: NONE
 * \return		: float - student grade for the particular course enrollment
 */
float Enrollment::getGrade() const
{
	return grade;
}

/**
 * \brief		: Setter method for student grade
 * \param		: float grade - grade to be set for a student's course
 * \return		: NONE
 */
void Enrollment::setGrade(float grade)
{
	if(grade > 0 || grade < 6)
	{
		this->grade = grade;
	}
	else
	{
		std::cout << "Enter a valid grade" << std::endl;
	}
}

/**
 * \brief		: Getter method for Semester attribute
 * \param		: NONE
 * \return		: std::string - Semester
 */
const Course& Enrollment::getCourse() const
{
	return (*this->course);
}

/**
 * \brief		: Getter method for Course object attribute
 * \param		: NONE
 * \return		: const Course& - Reference to course object
 */
std::string Enrollment::getSemester () const
{
	return semester;
}

/**
 * \brief		: Destructor
 */
Enrollment::~Enrollment()
{}

