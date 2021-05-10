/***************-************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file Course.h
 *	\brief Header file for Course class
 *
 *  Created on: 29-01-2020
 *  Author: Aditi Prakash
 */
/****************************************************************************/

#ifndef COURSE_H_
#define COURSE_H_

//! System Includes
#include <string>
#include <map>

class Course
{
protected:
	/**
	 * \brief		: Map of first char of the major and the major string
	 */
	static std::map<unsigned char, std::string> majorById;

	/**
	 * \brief		: Course key for every course
	 */
	unsigned int courseKey;

	/**
	 * \brief		: Title of the course
	 */
	std::string title;

	/**
	 * \brief		: Indicates the first character of the major
	 */
	unsigned char major;

	/**
	 * \brief		: Credit points for each course
	 */
	float creditPoints;

public:

	/**
	 * \brief		: Parametrised constructor
	 */
	Course(unsigned int courseKey, std::string title, unsigned char major, float creditPoints);

	/**
	 * \brief		: Getter method for course key
	 * \param		: NONE
	 * \return		: unsigned int - courseKey
	 */
	unsigned int getCourseKey() const;

	/**
	 * \brief		: Getter method for title of the course
	 * \param		: NONE
	 * \return		: unsigned int - title
	 */
	std::string getTitle() const;

	/**
	 * \brief		: Pure virtual print method (to be implemented in the inherited classes)
	 * \param		: NONE
	 * \return		: NONE
	 */
	virtual void print () const = 0;

	/**
	 * \brief		: Virtual write method overridden on Course write method
	 * \param		: std::ostream& out - output stream object
	 * \return		: NONE
	 */
	virtual void write(std::ostream& out) const;

	/**
	 * \brief		: Virtual destructor
	 */
	virtual ~Course() = 0;
};

#endif /* COURSE_H_ */
