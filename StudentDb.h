/***************-************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file StudentDb.h
 *	\brief Header file for StudentDb class
 *
 *  Created on: 29-01-2020
 *  Author: Aditi Prakash
 */
/****************************************************************************/

#ifndef STUDENTDB_H
#define STUDENTDB_H

//! System Includes
#include <map>
#include <memory>

//! User Includes
#include "Student.h"
#include "Course.h"
#include "BlockCourse.h"
#include "WeeklyCourse.h"

class StudentDb {

private:

	/**
	 * \brief		: Map of Student values with matrikel number as their key
	 */
    std::map<int, Student> students;

    /**
     * \brief		: Object of student class
     */
    Student student;

    /**
     * \brief		: Pointer object to course class
     */
    Course *course;

    /**
     * \brief		: Map of unique pointer of course type to courses with course key as their key
     */
    std::map<int, std::unique_ptr<const Course>> courses;

public:
    /**
     * \brief		: Constructor
     */
    StudentDb();

	/**
	 * \brief		: Method to add weekly course to the database
	 * \param[IN]	: const WeeklyCourse &course - constant weekly course object reference
	 * \return		: NONE
	 */
    void addWeeklyCourseToDb (const WeeklyCourse &course);

	/**
	 * \brief		: Method to add Block course to the database
	 * \param[IN]	: const BlockCourse &course - constant block course object reference
	 * \return		: NONE
	 */
    void addBlockCourseToDb (const BlockCourse &course);

	/**
	 * \brief		: Method to list the courses in the database
	 * \param[IN]	: NONE
	 * \return		: NONE
	 */
    void listCoursesInDb () const;

	/**
	 * \brief		: Method to add students to the database
	 * \param[IN]	: Student &student - reference to object of student class
	 * \return		: NONE
	 */
    void addStudentToDb (Student &student);

	/**
	 * \brief		: Method to add enrollment to the student in the database
	 * \param[IN]	: unsigned int matrikelNumber - matrikulation number of the student to be enrolled
	 * \param[IN]	: unsigned courseKey - Course key of the course to be added to
	 * \param[IN] 	: std::string semester - Semester to which the student has to be enrolled to
	 * \return		: NONE
	 */
    void addEnrollmentToStudent(unsigned int matrikelNumber, unsigned courseKey, std::string semester);

	/**
	 * \brief		: Method to search the student in the database
	 * \param[IN]	: unsigned int matrikelNumber - matrikulation number of the student
	 * \return		: bool - true if the student already exists in the database, false otherwise
	 */
    bool isStudentExists (unsigned int matrikelNumber) const;

	/**
	 * \brief		: Method to search the course in the database
	 * \param[IN]	: unsigned int courseKey - course key of the course
	 * \return		: bool - true if the course already exists in the database, false otherwise
	 */
    bool isCourseExists (unsigned int courseKey) const;

	/**
	 * \brief		: Method to print the student in the database
	 * \param[IN]	: unsigned int matrikelNumber - matrikulation number of the student
	 * \return		: NONE
	 */
    void printStudent (unsigned int matrikelNumber) const;

	/**
	 * \brief		: Method to search the student in the database with a substring of their name
	 * \param[IN]	: std::string subString - string that has to be searched for in the database of students
	 * \return		: NONE
	 */
    void searchStudentInDb (std::string subString);

	/**
	 * \brief		: Method to update student attributes such as enrollment, first name, last name, address etc..
	 * \param[IN]	: unsigned int matrikelNumber - matrikulation number of the student
	 * \param[IN]	: unsigned int changeAttribute - Indicates which attribute has to be changed
	 * 				 0 - Terminate
	 *			  	 1 - First Name
     *				 2 - Last Name
	 *			  	 3 - Date Of Birth
	 *			  	 4 - Enrollment
	 *			  	 5 - Address
	 * \return		: NONE
	 */
    void updateStudentInDb (unsigned int matrikelNumber, unsigned int changeAttribute);

	/**
	 * \brief		: Method to update student grade in the database
	 * \param[IN]	: unsigned int matrikelNumber - matrikulation number of the student
	 * \param[IN]	: unsigned courseKey - Course key of the course to be graded
	 * \param[IN] 	: float grade - New grade for the course
	 * \return		: NONE
	 */
    void updateStudentGradeInDb(unsigned int matrikelNumber, unsigned int courseKey, float grade);

	/**
	 * \brief		: Method to write the student attributes onto the stream
	 * \param[IN]	: std::ostream& out - reference to ostream object
	 * \return		: NONE
	 */
    void write(std::ostream& out);

	/**
	 * \brief		: Method to read the student attributes from the stream
	 * \param[IN]	: std::istream& in - reference to istream object
	 * \return		: NONE
	 */
    void read(std::istream& in);

	/**
	 * \brief		: Helper method to split the date into dd mm yyyy(int) values from string
	 * \param[IN]	: const std::string& dateString - reference to string object having date
	 * \param[IN] 	: char delimiter - delimiter to parse the data
	 * \return		: Poco::Data::Date - Poco date object in 'dd mm yyyy'(int) format
	 */
    Poco::Data::Date splitDate(const std::string& dateString, char delimiter);

	/**
	 * \brief		: Helper method to split the time into hh mm ss(int) values from string
	 * \param[IN]	: const std::string& timeString - reference to string object having time
	 * \param[IN] 	: char delimiter - delimiter to parse the data
	 * \return		: Poco::Data::Time - Poco time object in 'hh mm ss'(int) format
	 */
    Poco::Data::Time splitTime(const std::string& timeString, char delimiter);

    /**
     * \brief		: Destructor
     */
    ~StudentDb();

};
/********************
**  CLASS END
*********************/
#endif /* STUDENTDB_H */
