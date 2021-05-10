/***************-************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file Student.h
 *	\brief Header file for Student class
 *
 *  Created on: 29-01-2020
 *  Author: Aditi Prakash
 */
/****************************************************************************/

#ifndef STUDENT_H_
#define STUDENT_H_

//! System Includes
#include <string>
#include <vector>
#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>

//! User Includes
#include "Enrollment.h"
#include "Address.h"

class Student
{
private:

	//! Matrikel number of the student
	unsigned int matrikelNumber;

	//! First name of the student
	std::string firstName;

	//! Last name of the student
	std::string lastName;

	//! Date of birth of the student
	Poco::Data::Date dateOfBirth;

	//! The list of courses enrolled by the student
	std::vector<Enrollment> enrollments;

	//! Object of the address class
    Address address;

public:
    //! Default constructor
    Student ();

    /**
     * \brief		: Parametrised constructor of the Student class
     */
	Student(std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth, Address addressOfStudent);

    /**
     * \brief		: Parametrised constructor of the Student class
     */
	Student(unsigned int matrikelNumber, std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth, Address addressOfStudent);

	/**
	 * \brief		: Getter method for enrollments
	 * \param		: NONE
	 * \return		: const std::vector<Enrollment>& - Enrollments
	 */
	const std::vector<Enrollment>& getEnrollments() const;

	/**
	 * \brief		: Getter method for first name
	 * \param		: NONE
	 * \return		: const std::string& - first name
	 */
	const std::string& getFirstName() const;

	/**
	 * \brief		: Getter method for last name
	 * \param		: NONE
	 * \return		: const std::string& - last name
	 */
	const std::string& getLastName() const;

	/**
	 * \brief		: Getter method for matrikulation number of the student
	 * \param		: NONE
	 * \return		: unsigned int - matrikulation number
	 */
	unsigned int getMatrikelNumber() const;

	/**
	 * \brief		: Method to add enrollment to the enrollment vector
	 * \param		: Enrollment& enrollment - Reference object of the enrollment class
	 * \return		: NONE
	 */
	void updateEnrollments(Enrollment& enrollment);

	/**
	 * \brief		: Method to print the student details
	 * \param		: NONE
	 * \return		: NONE
	 */
	void printStudent () const;

	/**
	 * \brief		: Setter method for address
	 * \param[IN]	: const Address &address - Reference object of the Address class
	 * \return		: NONE
	 */
	void setAddress(const Address &address);

	/**
	 * \brief		: Setter method for date of birth
	 * \param[IN]	: const Poco::Data::Date &dateOfBirth - date of birth
	 * \return		: NONE
	 */
	void setDateOfBirth(const Poco::Data::Date &dateOfBirth);

	/**
	 * \brief		: Setter method for first name
	 * \param[IN]	: const std::string &firstName - first name
	 * \return		: NONE
	 */
	void setFirstName(const std::string &firstName);

	/**
	 * \brief		: Setter method for last name
	 * \param		: const std::string &lastName - last name
	 * \return		: NONE
	 */
	void setLastName(const std::string &lastName);

	/**
	 * \brief		: Method to update the grade
	 * \param[IN]	: unsigned int courseKey
	 * \param[IN]	: float newGrade
	 * \return		: NONE
	 */
	void updateGrade (unsigned int courseKey, float newGrade);

	/**
	 * \brief		: Method to write the student information on to the stream
	 * \param[IN]	: std::ostream& out - reference of stream object
	 * \return		: NONE
	 */
	void write(std::ostream& out);

	/**
	 * \brief		: Method to delete the enrollment for a particular course
	 * \param[IN]	: unsigned int courseKey
	 * \return		: NONE
	 */
	void deleteEnrollment (unsigned int courseKey);

	/**
	 * \brief		: Destructor
	 */
	~Student();
};

#endif /* STUDENT_H_ */
