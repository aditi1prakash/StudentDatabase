/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file Course.cpp
 *	\brief Source file for Course class
 *
 *  Created on	: 29-01-2020
 *  Author		: Aditi Prakash
 */
/****************************************************************************/

//! System Includes
#include <iostream>

//! User Includes
#include "Course.h"

//! Static map container to store the key value of major character and value of course string
std::map<unsigned char, std::string> Course::majorById = {{ 'A', "Automation" },
														  { 'C', "Communication" },
														  { 'E', "Embedded" },
														  { 'P', "Power" }};

/**
 * \brief		: Parametrised constructor
 */
Course::Course(unsigned int courseKey, std::string title, unsigned char major, float creditPoints)
	:courseKey{courseKey}, title{title}, major{major}, creditPoints{creditPoints}
	{}

/**
 * \brief		: Getter method for course key
 * \param		: NONE
 * \return		: unsigned int - courseKey
 */
unsigned int Course::getCourseKey() const
{
	return courseKey;
}

/**
 * \brief		: Getter method for title of the course
 * \param		: NONE
 * \return		: unsigned int - title
 */
std::string Course::getTitle() const
{
	return title;
}

/**
 * \brief		: Virtual write method overridden on Course write method
 * \param		: std::ostream& out - output stream object
 * \return		: NONE
 */
void Course::write(std::ostream &out) const
{
	out << courseKey << ";" << title << ";" << majorById[major] <<";" << creditPoints << ";";
}

/**
 * \brief		: Virtual destructor
 */
Course::~Course()
{}
