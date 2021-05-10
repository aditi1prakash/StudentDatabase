/***************-************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file BlockCourse.h
 *	\brief Header file for BlockCourse class
 *
 *  Created on: 29-01-2020
 *  Author: Aditi Prakash
 */
/****************************************************************************/

#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_

//! System Includes
#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>

//! User Includes
#include "Course.h"

class BlockCourse : public Course
{
private:

	/**
	 * \brief		: Poco library date object
	 * \details		: Indicates the start date of the particular course
	 */
	Poco::Data::Date startDate;

	/**
	 * \brief		: Poco library date object
	 * \details		: Indicates the end date of the particular course
	 */
	Poco::Data::Date endDate;

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
	BlockCourse(unsigned int courseKey, std::string title, unsigned char major, float creditPoints,
				Poco::Data::Date startDate, Poco::Data::Date endDate, Poco::Data::Time startTime, Poco::Data::Time endTime);

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
	virtual ~BlockCourse();
};

#endif /* BLOCKCOURSE_H_ */
