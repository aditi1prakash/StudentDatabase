/***************-************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file SimpleUI.h
 *	\brief Header file for SimpleUI class
 *
 *  Created on: 29-01-2020
 *  Author: Aditi Prakash
 */
/****************************************************************************/

#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_

//! System includes

//! User includes
#include "StudentDb.h"


class SimpleUI {

private:

	/**
	 * \brief		:Attribute to read the user choice and execute respective command
	 */
	unsigned short userInput;

	/**
	 * \brief		:Association link to the StudentDb class
	 */
    StudentDb &studentDb;

public:

    /**
     * \brief		: Parametrised Constructor
     */
	SimpleUI(StudentDb &studentDb);

	/**
	 * \brief		: Helper function to add new student to the database
	 * \param		: NONE
	 * \return		: NONE
	 */
	void addNewStudent ();

	/**
	 * \brief		: Helper function to add new course to the database
	 * \param		: NONE
	 * \return		: NONE
	 */
	void addNewCourse ();

	/**
	 * \brief		: Helper function to list all the courses
	 * \param		: NONE
	 * \return		: NONE
	 */
	void listCourses ();

	/**
	 * \brief		: Helper function to add enrollment
	 * \param		: NONE
	 * \return		: NONE
	 */
	void addEnrollment ();

	/**
	 * \brief		: Helper function to print students in the database
	 * \param		: NONE
	 * \return		: NONE
	 */
	void printStudent ();

	/**
	 * \brief		: Helper function to search a student in the database
	 * \param		: NONE
	 * \return		: NONE
	 */
	void searchStudent ();

	/**
	 * \brief		: Helper function to update student details in the database
	 * \param		: NONE
	 * \return		: NONE
	 */
	void updateStudent ();

	/**
	 * \brief		: Helper function to read database from the server
	 * \param		: NONE
	 * \return		: NONE
	 */
	void addStudentFromServerToDatabase (unsigned int numberOfStudents);


	/**
	 * \brief		: run method - lists the available commands and read the user input
	 * \param		: NONE
	 * \return		: NONE
	 */
    void run();

	/**
	 * \brief		: Method to print the available commands
	 * \param		: NONE
	 * \return		: NONE
	 */
    void printCommands ();
};

#endif /* SIMPLEUI_H_ */
