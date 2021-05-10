/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file WeeklyCourse.cpp
 *	\brief Source file for WeeklyCourse class
 *
 *  Created on	: 29-01-2020
 *  Author		: Aditi Prakash
 */
/****************************************************************************/

//! System Includes
#include <iostream>

//! User Includes
#include "WeeklyCourse.h"


/********************** Method Implementations ******************************/
/**
 * \brief		: Parametrised constructor
 */
WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title, unsigned char major, float creditPoints,
				Poco::DateTime::DaysOfWeek dayOfWeek, Poco::Data::Time startTime, Poco::Data::Time endTime)
				:Course(courseKey, title, major, creditPoints), dayOfWeek{dayOfWeek}, startTime{startTime}, endTime{endTime}
				{}

/**
 * \brief		: Virtual print method overridden on Course print method
 * \param		: NONE
 * \return		: NONE
 */
void WeeklyCourse::print () const
{
	std::cout << "Course Key: " << courseKey << std::endl << "Title: " << title << std::endl << "Major: " << majorById[major]
								<< std::endl << "Credit Points: " << creditPoints << std::endl
								<< "Day of week - " << dayOfWeek << std::endl << "Timings - " << startTime.hour() << ":" << startTime.minute()
								<< " to " << endTime.hour() << ":" << endTime.minute() << std::endl;
}

/**
 * \brief		: Virtual write method overridden on Course write method
 * \param		: std::ostream& out - output stream object
 * \return		: NONE
 */
void WeeklyCourse::write(std::ostream &out) const
{
	out << "W;";
	Course::write (out);
	out << dayOfWeek << ";" << startTime.hour() << ":" << startTime.minute() << ";"
							<< endTime.hour() << ":" << endTime.minute() << ";" << std::endl;
}

/*
 * \brief		: Destructor
 */
WeeklyCourse::~WeeklyCourse()
{

}

