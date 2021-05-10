/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file BlockCourse.cpp
 *	\brief Source file for BlockCourse class
 *
 *  Created on	: 29-01-2020
 *  Author		: Aditi Prakash
 */
/****************************************************************************/

//! System Includes
#include <iostream>

//! User Includes
#include "BlockCourse.h"


/********************** Method Implementations ******************************/

/**
 * \brief		: Parametrised constructor
 */
BlockCourse::BlockCourse(unsigned int courseKey, std::string title, unsigned char major, float creditPoints,
						Poco::Data::Date startDate, Poco::Data::Date endDate,
						Poco::Data::Time startTime, Poco::Data::Time endTime)
			:Course{courseKey, title, major, creditPoints},
			 startDate{startDate}, endDate {endDate}, startTime {startTime}, endTime {endTime}
{}

/**
 * \brief		: Virtual print method overridden on Course print method
 * \param		: NONE
 * \return		: NONE
 */
void BlockCourse::print () const
{
	std::cout << "Course Key: " << courseKey << std::endl << "Title: " << title << std::endl << "Major: " << majorById[major]
								<< std::endl << "Credit Points: " << creditPoints << std::endl
								<< "Duration - " << startDate.day() << "/" << startDate.month() << "/" << startDate.year()
								<< " to " << endDate.day() << "/" << endDate.month() <<"/" << endDate.year() << std::endl
								<< "Timings - " << startTime.hour() << ":" << startTime.minute()
								<< " to " << endTime.hour() << ":" << endTime.minute() << std::endl;
}

/**
 * \brief		: Virtual write method overridden on Course write method
 * \param		: std::ostream& out - output stream object
 * \return		: NONE
 */
void BlockCourse::write(std::ostream &out) const
{
	out << "B;";
	Course::write (out);
	out << startDate.day() << "." << startDate.month() << "." << startDate.year() << ";"
		<< endDate.day() << "." << endDate.month() << "." << endDate.year() << std::endl;
}

/*
 * \brief		: Destructor
 */
BlockCourse::~BlockCourse()
{}

