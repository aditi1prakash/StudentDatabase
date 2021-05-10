/***************-************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file WeeklyCourse.h
 *	\brief Header file for WeeklyCourse class
 *
 *  Created on: 29-01-2020
 *  Author: Aditi Prakash
 */
/****************************************************************************/

#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_

//! System includes
#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>

//! User includes
#include "Course.h"

class WeeklyCourse : public Course
{

private:
	/**
	 * \brief		: Days of the week, Poco library enumerator type
	 *  SUNDAY 		= 0,
		MONDAY 		= 1,
		TUESDAY		= 2,
		WEDNESDAY	= 3,
		THURSDAY 	= 4,
		FRIDAY		= 5,
		SATURDAY 	= 6
	 */
	Poco::DateTime::DaysOfWeek dayOfWeek;

	/**
	 * \brief		: Poco library time object
	 * \details		: Indicates the start time of the particular course
	 */
	Poco::Data::Time startTime;

	/**
	 * \brief		: Poco library time object
	 * \details		: Indicates the end time of the particular course
	 */
	Poco::Data::Time endTime;

public:
	/**
	 * \brief		: Parametrised constructor
	 */
	WeeklyCourse(unsigned int courseKey, std::string title, unsigned char major, float creditPoints,
				Poco::DateTime::DaysOfWeek dayOfWeek, Poco::Data::Time startTime, Poco::Data::Time endTime);

	/**
	 * \brief		: Virtual print method overridden on Course print method
	 * \param		: NONE
	 * \return		: NONE
	 */
	virtual void print () const override;

	/**
	 * \brief		: Virtual write method overridden on Course write method
	 * \param		: std::ostream& out - output stream object
	 * \return		: NONE
	 */
	virtual void write (std::ostream& out) const override;

	/*
	 * \brief		: Destructor
	 */
	virtual ~WeeklyCourse();
};

#endif /* WEEKLYCOURSE_H_ */
