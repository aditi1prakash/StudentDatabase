/***************-************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file Enrollment.h
 *	\brief Header file for Enrollment class
 *
 *  Created on: 29-01-2020
 *  Author: Aditi Prakash
 */
/****************************************************************************/

#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_

//! System Includes
#include <string>

//! User Includes
#include "Course.h"

class Enrollment
{
private:

	/**
	 * \brief		: Grade of the enrolled student
	 */
	float grade;

	/**
	 * \brief		: Semester of the enrolled student
	 */
	std::string semester;

	/**
	 * \brief		: Constant pointer object to course class
	 */
	const Course* course;

public:

	/**
	 * \brief		: Parametrised constructors
	 */
	Enrollment(float grade, std::string semester, const Course* course);

	/**
	 * \brief		: Getter method for student grade
	 * \param		: NONE
	 * \return		: float - student grade for the particular course enrollment
	 */
	float getGrade() const;

	/**
	 * \brief		: Setter method for student grade
	 * \param		: float grade - grade to be set for a student's course
	 * \return		: NONE
	 */
	void setGrade(float grade);

	/**
	 * \brief		: Getter method for Semester attribute
	 * \param		: NONE
	 * \return		: std::string - Semester
	 */
	std::string getSemester () const;

	/**
	 * \brief		: Getter method for Course object attribute
	 * \param		: NONE
	 * \return		: const Course& - Reference to course object
	 */
	const Course& getCourse() const;

	/**
	 * \brief		: Destructor
	 */
	~Enrollment();

};

#endif /* ENROLLMENT_H_ */
