/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file Address.cpp
 *	\brief Source file for Address class
 *
 *  Created on	: 29-01-2020
 *  Author		: Aditi Prakash
 */
/****************************************************************************/

#include "Address.h"

Address::Address ()
{}

/**
 * \brief		: Parametrised constructor
 * \param[IN]	: std::string street - Street name
 * \param[IN]	: unsigned short postalCode - Postal code of the address
 * \param[IN]	: std::string cityName - Name of the city
 * \param[IN] 	: std::string additionalInfo - Additional info such as building number or landmark
 * \return		: const std::string& - Name of the city
 */
Address::Address(std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo)
	:street{street}, postalCode{postalCode}, cityName{cityName}, additionalInfo{additionalInfo}
	{}

/**
 * \brief		: Method to add additional info to the student address
 * \param		: NONE
 * \return		: const std::string& - Additional info related to student
 */
const std::string& Address::getAdditionalInfo() const
{
	return additionalInfo;
}

/**
 * \brief		: Getter method for city name
 * \param[]		: NONE
 * \return		: const std::string& - Name of the city
 */
const std::string& Address::getCityName() const
{
	return cityName;
}

/**
 * \brief		: Getter method for Postal code
 * \param[]		: NONE
 * \return		: unsigned short - postal code of the city
 */
unsigned short Address::getPostalCode() const
{
	return postalCode;
}

/**
 * \brief		: Getter method for street
 * \param[]		: NONE
 * \return		: const std::string& - Name of the street
 */
const std::string& Address::getStreet() const
{
	return street;
}

/*
 * \brief		: Default destructor
 */
Address::~Address()
{}
