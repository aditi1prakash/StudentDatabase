/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file main.cpp
 *	\brief main file
 *
 *  Created on	: 29-01-2020
 *  Author		: Aditi Prakash
 */
/****************************************************************************/

//! User includes
#include "SimpleUI.h"
#include "StudentDb.h"

int main ()
{

	StudentDb studentDb;
	SimpleUI simpleUI (studentDb);

	//! Run the student database UI
	simpleUI.run();

	return 0;
}



