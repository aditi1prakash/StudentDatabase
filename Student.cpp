/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file Student.cpp
 *	\brief Source file for Student class
 *
 *  Created on	: 29-01-2020
 *  Author		: Aditi Prakash
 */
/****************************************************************************/

//! System Includes
#include <iostream>

//! User includes
#include "Student.h"
#include "Address.h"

//! Attribute that stores the next matrikel number
unsigned int nextMatrikelNumber = 100000;

Student::Student()
{
	matrikelNumber = nextMatrikelNumber;
}

/**
  * \brief		: Parametrised constructor of the Student class
  */
Student::Student(std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth, Address addressOfStudent)
	: matrikelNumber {nextMatrikelNumber}, firstName{firstName}, lastName{lastName}, dateOfBirth{dateOfBirth}, address {addressOfStudent}
{
	nextMatrikelNumber = nextMatrikelNumber + 1;
}

/**
  * \brief		: Parametrised constructor of the Student class
  */
Student::Student(unsigned int matrikelNumber, std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth, Address addressOfStudent) :
		matrikelNumber {matrikelNumber}, firstName {firstName}, lastName {lastName}, dateOfBirth {dateOfBirth}, address {addressOfStudent}
{}

/**
 * \brief		: Getter method for enrollments
 * \param		: NONE
 * \return		: const std::vector<Enrollment>& - Enrollments
 */
const std::vector<Enrollment>& Student::getEnrollments() const
{
	return enrollments;
}

/**
 * \brief		: Getter method for first name
 * \param		: NONE
 * \return		: const std::string& - first name
 */
const std::string& Student::getFirstName() const
{
	return firstName;
}

/**
 * \brief		: Getter method for last name
 * \param		: NONE
 * \return		: const std::string& - last name
 */
const std::string& Student::getLastName() const
{
	return lastName;
}

/**
 * \brief		: Getter method for matrikulation number of the student
 * \param		: NONE
 * \return		: unsigned int - matrikulation number
 */
unsigned int Student::getMatrikelNumber() const
{
	return matrikelNumber;
}

/**
 * \brief		: Method to add enrollment to the enrollment vector
 * \param		: Enrollment& enrollment - Reference object of the enrollment class
 * \return		: NONE
 */
void Student::updateEnrollments(Enrollment& enrollment)
{
	enrollments.push_back(enrollment);
}

/**
 * \brief		: Method to print the student details
 * \param		: NONE
 * \return		: NONE
 */
void Student::printStudent () const
{
	std::cout << "Student Name: " << this->firstName << " " << this->lastName << std::endl
			  << "Matrikel Number: " << this->matrikelNumber << std::endl
			  << "Date Of Birth(dd/mm/yyyy): " << this->dateOfBirth.day() << "/" << this->dateOfBirth.month() << "/" << this->dateOfBirth.year() << std::endl
			  << "Address Of Student" << std::endl
			  << this->address.getStreet() << " - "
			  << this->address.getCityName() << ", "
			  << this->address.getPostalCode() << std::endl
			  << this->address.getAdditionalInfo() << std::endl;

	std::cout << "Enrollments" << std::endl;

	for (auto enrollment = enrollments.begin(); enrollment < enrollments.end(); enrollment++)
	{
		std::cout << "Course: " << (*enrollment).getCourse().getTitle() << std::endl
				  << "Semester: " << (*enrollment).getSemester() << std::endl
				  << "Grade: " << (*enrollment).getGrade() << std::endl;
	}
}

/**
 * \brief		: Setter method for address
 * \param[IN]	: const Address &address - Reference object of the Address class
 * \return		: NONE
 */
void Student::setAddress(const Address &address)
{
	this->address = address;
}

/**
 * \brief		: Setter method for date of birth
 * \param[IN]	: const Poco::Data::Date &dateOfBirth - date of birth
 * \return		: NONE
 */
void Student::setDateOfBirth(const Poco::Data::Date &dateOfBirth)
{
	this->dateOfBirth = dateOfBirth;
}

/**
 * \brief		: Setter method for first name
 * \param[IN]	: const std::string &firstName - first name
 * \return		: NONE
 */
void Student::setFirstName(const std::string &firstName)
{
	this->firstName = firstName;
}

/**
 * \brief		: Setter method for last name
 * \param		: const std::string &lastName - last name
 * \return		: NONE
 */
void Student::setLastName(const std::string &lastName)
{
	this->lastName = lastName;
}

/**
 * \brief		: Method to update the grade
 * \param[IN]	: unsigned int courseKey
 * \param[IN]	: float newGrade
 * \return		: NONE
 */
void Student::updateGrade (unsigned int courseKey, float newGrade)
{
	for (auto eachEnrollment = enrollments.begin(); eachEnrollment != enrollments.end(); eachEnrollment++)
	{
		if (courseKey == eachEnrollment->getCourse().getCourseKey())
		{
			eachEnrollment->setGrade(newGrade);
		}
		else
		{
			std::cout << "Course not found. Enter the correct course key" << std::endl;
		}
	}
}

/**
 * \brief		: Method to delete the enrollment for a particular course
 * \param[IN]	: unsigned int courseKey
 * \return		: NONE
 */
void Student::deleteEnrollment (unsigned int courseKey)
{
	/** Range based auto for loop could not be used since erase() operation on a vector invalidates all iterators
	 *  beginning with the element being erased upto the end(). We have to make sure that the iterators remain valid
	 *  by assigning the iterator with a valid value. Does not serve much of a purpose in our use case, as it is only
	 *  one enrollment that is to be deleted. If there were multiple enrollments that were to be deleted this would
	 *  be an optimal solution without causing any undefined behavior in the software.
	 *  NOTE: erase() returns an iterator pointing to the new location of the element that followed the last element
	 *  erased by the function call. This is the container end if the operation erased the last element in the sequence.
	 */

	for (std::vector<Enrollment>::iterator enrollment = enrollments.begin(); enrollment != enrollments.end(); )
	{
		if(courseKey == enrollment->getCourse().getCourseKey())
		{
			enrollment = enrollments.erase(enrollment);
			return;
		}
		else
		{
			++enrollment;
		}
	}
}

/**
 * \brief		: Method to write the student information on to the stream
 * \param[IN]	: std::ostream& out - reference of stream object
 * \return		: NONE
 */
void Student::write(std::ostream &out)
{
	out << matrikelNumber << ";" << lastName << ";" << firstName << ";"
		<< dateOfBirth.day() << "." << dateOfBirth.month() << "." << dateOfBirth.year() << ";"
		<< address.getStreet() << ";" << address.getPostalCode() << ";" << address.getCityName() << ";" << address.getAdditionalInfo() << ";" << std::endl;
}

/**
 * \brief		: Destructor
 */
Student::~Student()
{}

