/***************-************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file Address.h
 *	\brief Header file for Address class
 *
 *  Created on: 29-01-2020
 *  Author: Aditi Prakash
 */
/****************************************************************************/

#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>

class Address
{
private:
	//! Name of the street
	std::string street;

	//! Postal code of the city/area
	unsigned short postalCode;

	//! Name of the city
	std::string cityName;

	//! Additional info such as building number or landmark
	std::string additionalInfo;

public:

	Address();
    /**
     * \brief		: Parametrised constructor
     * \param[IN]	: std::string street - Street name
     * \param[IN]	: unsigned short postalCode - Postal code of the address
     * \param[IN]	: std::string cityName - Name of the city
     * \param[IN] 	: std::string additionalInfo - Additional info such as building number or landmark
     * \return		: const std::string& - Name of the city
     */
	Address(std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo);

	/**
	 * \brief		: Method to add additional info to the student address
	 * \param		: NONE
	 * \return		: const std::string& - Additional info related to student
	 */
	const std::string& getAdditionalInfo() const;

    /**
     * \brief		: Getter method for city name
     * \param[]		: NONE
     * \return		: const std::string& - Name of the city
     */
	const std::string& getCityName() const;

    /**
     * \brief		: Getter method for Postal code
     * \param[]		: NONE
     * \return		: unsigned short - postal code of the city
     */
	unsigned short getPostalCode() const;

    /**
     * \brief		: Getter method for street
     * \param[]		: NONE
     * \return		: const std::string& - Name of the street
     */
	const std::string& getStreet() const;

	/*
	 * \brief		: Default destructor
	 */
	~Address();
};

#endif /* ADDRESS_H_ */
