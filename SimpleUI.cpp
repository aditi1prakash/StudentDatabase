/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file SimpleUI.cpp
 *	\brief Source file for SimpleUI class
 *
 *  Created on	: 29-01-2020
 *  Author		: Aditi Prakash
 */
/****************************************************************************/

//! System includes
#include <iostream>
#include <fstream>
#include <exception>

//! User includes
#include "SimpleUI.h"
#include "StudentDb.h"

#include "Poco/Data/Date.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Parser.h"
#include "Poco/StreamCopier.h"

using namespace Poco::JSON;
using namespace Poco::Dynamic;

/**
 * \brief		: Parametrised Constructor
 */
SimpleUI::SimpleUI(StudentDb &studentDb)
	:studentDb{studentDb}
{
	this->userInput = 0;
}

/**
 * \brief		: run method - lists the available commands and read the user input
 * \param		: NONE
 * \return		: NONE
 */
void SimpleUI::run()
{
	do
	{
		printCommands ();
		std::cout << std::endl << "Please choose the command to be executed" << std::endl;
		std::cin >> this->userInput;

		switch (userInput)
		{
			case 1://ADD_NEW_COURSE:
				std::cout << "Adding new course" << std::endl;
				addNewCourse();
				break;

			case 2://LIST_COURSE:
				std::cout << "Listing courses" << std::endl;
				listCourses();
				break;

			case 3://ADD_NEW_STUDENT:
				std::cout << "Enter Student Details" << std::endl;
				addNewStudent();
				break;

			case 4: //ADD_ENROLLMENT:
				std::cout << "Adding enrollment" << std::endl;
				addEnrollment ();
				break;

			case 5: //PRINT_STUDENT:
				std::cout << "Printing" << std::endl;
				printStudent ();
				break;

			case 6://SEARCH_STUDENT:
				std::cout << "Searching student" << std::endl;
				searchStudent();

				break;

			case 7://UPDATE_STUDENT:
				std::cout << "Update student" << std::endl;
				updateStudent ();
				break;

			case 8: // Write data onto a file
			{
				std::string fileName = " ";
				std::cin.ignore();
				std::cout << "Enter the file name you wish to create: ";
				getline (std::cin, fileName);

				//! Create .csv file to store the database
				std::ofstream outFile;
				outFile.open(fileName + ".csv", std::ios::app);

				if(outFile)
				{
					studentDb.write(outFile);
					outFile.close();
				}
				else
				{
					std::cout << "Could not create file" << std::endl;
				}

				break;
			}

			case 9: // Read data from the file
			{
				std::string fileName = " ";
				std::cin.ignore();
				std::cout << "Enter the file name you wish to read from: ";
				getline (std::cin, fileName);

				//! Get the .csv file from which data has to be read
				std::ifstream inFile;
				inFile.open (fileName + ".csv");

				if(inFile.good())
				{
					studentDb.read(inFile);
					std::cout << "Read from file successfully. Exiting switch case" << std::endl;
					inFile.close ();
				}
				else
				{
					std::cout << "Unable to read from file" << std::endl;
				}

				break;
			}

			case 10: //Read student database from the server
			{
				unsigned int numberOfStudents{};
				std::cout << "Enter the number of students to add: " << std::endl;
				std::cin >> numberOfStudents;

				addStudentFromServerToDatabase (numberOfStudents);
				break;
			}

			case 11://QUIT:
				std::cout << "Quit" << std::endl;
				break;

			default:
				std::cout << "Invalid input - Please choose correct option." << std::endl;
				break;
		}
	}
	//! Repeat the operation until the user propmts a Quit input
	while (userInput != 11);

}

/**
 * \brief		: Helper function to add new course to the database
 * \param		: NONE
 * \return		: NONE
 */
void SimpleUI::addNewCourse()
{
	//! Local variable declaration
	unsigned int courseKey {};
	unsigned char courseType {};
	std::string title = " ";
	std::string majorAsString = " ";
	unsigned char majorAsChar {};
	float creditPoints {};

	//! Obtain course data from the user
	std::cout << "Weekly Course (W) or Block Course (B)?" << std::endl;
	std::cin >> courseType;
	courseType = toupper(courseType);

	std::cout << "Enter the course key: " << std::endl;
	std::cin >> courseKey;

	std::cin.ignore();
	std::cout << "Enter the title of the course: " << std::endl;
	getline(std::cin, title);

	std::cout << "Enter the major: " << std::endl;
	getline(std::cin, majorAsString);

	majorAsChar = majorAsString.at(0);
	majorAsChar = toupper(majorAsChar);

	std::cout << "Enter the credit points: " << std::endl;
	std::cin >> creditPoints;

	if ('W' == courseType)
	{
		int dayOfWeek {};
		int startTimeHour {}, startTimeMinute {}, startTimeSecond {};
		int endTimeHour {}, endTimeMinute {}, endTimeSecond {};

		std::cout << "Enter the day of the week: " << std::endl
				<< "SUNDAY = 0" 	<< std::endl
				<< "MONDAY = 1" 	<< std::endl
				<< "TUESDAY = 2" 	<< std::endl
				<< "WEDNESDAY = 3" 	<< std::endl
				<< "THURSDAY = 4"	<< std::endl
				<< "FRIDAY = 5"		<< std::endl
				<< "SATURDAY = 6"	<< std::endl;
		std::cin >> dayOfWeek;

		std::cout << "Enter the start time in 'hh mm ss' format" << std::endl;
		std::cin >> startTimeHour >> startTimeMinute >> startTimeSecond;

		std::cout << "Enter the end time in 'hh mm ss' format" << std::endl;
		std::cin >> endTimeHour >> endTimeMinute >> endTimeSecond;

		//! Add weekly course to the database
		WeeklyCourse weeklyCourse(courseKey, title, majorAsChar, creditPoints,
						Poco::DateTime::DaysOfWeek (dayOfWeek),
						Poco::Data::Time (startTimeHour, startTimeMinute, startTimeSecond),
						Poco::Data::Time (endTimeHour, endTimeMinute, endTimeSecond));

		studentDb.addWeeklyCourseToDb(weeklyCourse);

	}
	else if ('B' == courseType)
	{
		int startDate {}, startMonth {}, startYear {};
		int endDate {}, endMonth {}, endYear {};
		int startTimeHour {}, startTimeMinute {}, startTimeSecond {};
		int endTimeHour {}, endTimeMinute {}, endTimeSecond {};

		std::cout << "Enter the start date of the course (dd mm yyyy): " << std::endl;
		std::cin >> startDate >> startMonth >> startYear;

		std::cout << "Enter the end date of the course (dd mm yyyy): " << std::endl;
		std::cin >> endDate >> endMonth >> endYear;

		std::cout << "Enter the starting time of the course (hh mm ss): " << std::endl;
		std::cin >> startTimeHour >> startTimeMinute >> startTimeSecond;

		std::cout << "Enter the ending time of the course (hh mm ss): " << std::endl;
		std::cin >> endTimeHour >> endTimeMinute >> endTimeSecond;

		//! Add block course to the database
		BlockCourse blockCourse (courseKey, title, majorAsChar, creditPoints,
								Poco::Data::Date (startYear, startMonth, startDate),
								Poco::Data::Date (endYear, endMonth, endDate),
								Poco::Data::Time (startTimeHour, startTimeMinute, startTimeSecond),
								Poco::Data::Time (endTimeHour, endTimeMinute, endTimeSecond));

		studentDb.addBlockCourseToDb(blockCourse);

	}
	else
	{
		std::cout << " Invalid course type" << std::endl;
	}

}

/**
 * \brief		: Helper function to list all the courses
 * \param		: NONE
 * \return		: NONE
 */
void SimpleUI::listCourses()
{
	studentDb.listCoursesInDb();
}

/**
 * \brief		: Helper function to add new student to the database
 * \param		: NONE
 * \return		: NONE
 */
void SimpleUI::addNewStudent()
{
	//! Student information
	std::string firstName = " ", lastName = " ";
	int date {}, month {}, year{};

	//! Address information
	std::string street = " ", cityName = " ", additionalInfo = " ";
	unsigned short postalCode {};

	//! Get Student information
	std::cout << "First Name: " << std::endl;
	std::cin >> firstName;
	std::cout << "Last Name: " << std::endl;
	std::cin >> lastName;
	std::cout << "Date of Birth - Enter (dd mm yyyy): " << std::endl;
	std::cin >> date >> month >> year;

	//! Get Address information
	std::cin.ignore();
	std::cout << "Enter Address of the student" << std::endl << "Street Name: " << std::endl;
	getline (std::cin, street);

	std::cout << "City Name: " << std::endl;
	getline (std::cin, cityName);
	std::cout << "Postal Code: " << std::endl;
	std::cin >> postalCode;

	std::cin.ignore();
	std::cout << "Enter additional info (if any, else press enter): "<< std::endl;
	getline (std::cin, additionalInfo);

	//! Add student to the database
	Student student(firstName, lastName, Poco::Data::Date(year, month, date),
									Address(street, postalCode, cityName, additionalInfo));
	studentDb.addStudentToDb(student);

}

/**
 * \brief		: Helper function to add enrollment
 * \param		: NONE
 * \return		: NONE
 */
void SimpleUI::addEnrollment ()
{
	//! Get enrollment details from the user
	unsigned int matrikelNumber {}, courseKey {};
	std::string semester = " ";

	std::cout << "Enter the matrikel number: " << std::endl;
	std::cin >> matrikelNumber;

	std::cout << "Enter the course key: " << std::endl;
	std::cin >> courseKey;

	//! Check if student exists with the provided matrikulation number
	if(studentDb.isStudentExists(matrikelNumber) == false)
	{
		std::cout << "Student does not exist in the database" << std::endl;
		return;
	}

	//! Check if the course key exists in the database
	if(studentDb.isCourseExists(courseKey) == false)
	{
		std::cout << "Course does not exist" << std::endl;
		return;
	}

	std::cin.ignore();
	std::cout << "Enter the semester: " << std::endl;
	getline(std::cin, semester);

	//! Add enrollment
	studentDb.addEnrollmentToStudent(matrikelNumber, courseKey, semester);
}

/**
 * \brief		: Helper function to print students in the database
 * \param		: NONE
 * \return		: NONE
 */
void SimpleUI::printStudent ()
{
	unsigned int matrikelNumber {};

	std::cout << "Enter the matrikel number of the student: " << std::endl;
	std::cin >> matrikelNumber;

	//! Check for valid matrikulation number and print the student
	if(studentDb.isStudentExists(matrikelNumber))
	{
		studentDb.printStudent(matrikelNumber);
	}
}

/**
 * \brief		: Helper function to search a student in the database
 * \param		: NONE
 * \return		: NONE
 */
void SimpleUI::searchStudent ()
{
	std::string subString = " ";

	std::cin.ignore();
	std::cout << "Enter the student name to be searched" << std::endl;
	getline(std::cin, subString);

	studentDb.searchStudentInDb (subString);
}

/**
 * \brief		: Helper function to update student details in the database
 * \param		: NONE
 * \return		: NONE
 */
void SimpleUI::updateStudent()
{
	unsigned int matrikelNumber {}, changeAttribute {};
	std::cout << "Enter the Matrikel Number of the student to be updated: " << std::endl;
	std::cin >> matrikelNumber;

	//! If student exists in the database then update the student information in the database
	if(studentDb.isStudentExists(matrikelNumber) == true)
	{
		std::cout << "Enter the attribute number that you wish to change" << std::endl
				  << "0 - Terminate" 	<< std::endl
				  << "1 - First Name" 	<< std::endl
				  << "2 - Last Name" 	<< std::endl
				  << "3 - Date Of Birth"<< std::endl
				  << "4 - Enrollment" 	<< std::endl
				  << "5 - Address"		<< std::endl;

		std::cin >> changeAttribute;

		studentDb.updateStudentInDb(matrikelNumber, changeAttribute);
		studentDb.printStudent(matrikelNumber);
	}
	else
	{
		std::cout << "No student exists with this matrikulation number" << std::endl;
	}
}

/**
 * \brief		: Helper function to read database from the server
 * \param		: NONE
 * \return		: NONE
 */
void SimpleUI::addStudentFromServerToDatabase(unsigned int numberOfStudents)
{

	//! Vector container of strings to store the json data from the server
	std::vector<std::string> data;

	for (unsigned int i = 0; i < numberOfStudents; i++)
	{
		//! Create host address object and initialise the host and its port
		Poco::Net::SocketAddress host ("mnl.de", 4242);

		//! Create a socket for the host
		Poco::Net::StreamSocket socket (host);

		//! Create a stream for the socket to read the data from the host
		Poco::Net::SocketStream serverStream (socket);

		/**
		 * The server understands two commands 'generate' and 'quit'.
		 * Commands to initiate and close communication with the server
		 */
		std::string generate {"generate\n"};
		std::string quit {"quit"};

		//! Establish connection with the server
		serverStream << generate;

		/*
		 * Data written to a network stream is buffered internally before being sent. If
		 * writing a single character to a network stream led to immediate transmission
		 * of the character, the network would be congested with packets containing only
		 * a small amount of useful information.
		 * The buffered data will therefore only be written to the network when the
		 * buffer becomes full or you trigger writing by calling the flush method.
		 */
		serverStream.flush();

		//! String to receive the json data from the server stream
		std::string receivedJsonData{};

		//! Get the data and store it in a vector container of strings
		while (getline(serverStream, receivedJsonData))
		{
			data.push_back(receivedJsonData);
		}

		//! Quit the connection and flush the data onto the stream
		serverStream << quit;
		serverStream.flush();
	}
	for (auto serverData: data)//.begin(); serverData != data.end(); serverData++)
	{
		std::cout << serverData << " " << std::endl;
	}

	//! Iterate over the data from the server stream, parse and extract it to local variables
	for (auto vec: data)
	{
		std::cout << "in for loop" << std::endl;
//		std::string json = *it;
		Poco::JSON::Parser jsonDataFromServer;
		Poco::Dynamic::Var result = jsonDataFromServer.parse(vec);
		//TODO: Check the pointer
		Object::Ptr object = result.extract<Object::Ptr>();

		std::cout << "Getting the name" << std::endl;
		//Get name
		Var value = object->get("name");
		object = value.extract<Object::Ptr>();

		value = object->get("firstName");
		std::string firstName = value.convert<std::string>();
		std::cout << firstName << std::endl;

		value = object->get("lastName");
		std::string lastName = value.convert<std::string>();
		std::cout << lastName << std::endl;

		//Get date of birth
		object = result.extract<Object::Ptr>();
		value = object->get("dateOfBirth");
		object = value.extract<Object::Ptr>();

		value = object->get("date");
		int date = value.convert<int>();
		std::cout << date << std::endl;

		value = object->get("month");
		int month = value.convert<int>();
		std::cout << month << std::endl;

		value = object->get("year");
		int year = value.convert<int>();
		std::cout << year << std::endl;

		//Get Address
		object = result.extract<Object::Ptr>();
		value = object->get("location");
		object = result.extract<Object::Ptr>();

		value = object->get("city");
		std::string cityName = value.convert<std::string>();
		std::cout << cityName << std::endl;

		value = object->get("postCode");
		unsigned short postalCode = 0;
		postalCode = value.convert<unsigned short>();
		std::cout << postalCode << std::endl;
		try
		{
			postalCode = value.convert<unsigned short>();
		} catch (std::exception &e)
		{
			std::cout << "\nException occurred: " << e.what()
					<< ", Invalid postal code received: "
					<< value.convert<std::string>();
			continue;
		}


		value = object->get("street");
		std::string street = value.convert<std::string>();
		std::cout << street << std::endl;

		value = object->get("state");
		std::string additionalInfo = value.convert<std::string>();
		std::cout << additionalInfo << std::endl;

		Student student(firstName, lastName, Poco::Data::Date(date, month, year),
								Address(street, postalCode, cityName, additionalInfo));

		studentDb.addStudentToDb (student);

		std::cout << "Added students to database" << std::endl;

	}
}

/**
 * \brief		: Method to print the available commands
 * \param		: NONE
 * \return		: NONE
 */
void SimpleUI::printCommands ()
{
	std::cout << "1. Add new course " << std::endl
			  << "2. List courses"	  << std::endl
			  << "3. Add New Student" << std::endl
			  << "4. Add Enrollment"  << std::endl
			  << "5. Print Student"	  << std::endl
			  << "6. Search Student"  << std::endl
			  << "7. Update Student"  << std::endl
			  << "8. Write to File"	  << std::endl
			  << "9. Read from File"  << std::endl
			  << "10. Add student from server database" << std::endl
			  << "11. QUIT"			  << std::endl;
}

