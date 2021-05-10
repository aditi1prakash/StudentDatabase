/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************/
/*! \file StudentDb.cpp
 *	\brief Source file for StudentDb class
 *
 *  Created on	: 29-01-2020
 *  Author		: Aditi Prakash
 */
/****************************************************************************/

//! System Includes
#include <iostream>
#include <sstream>
#include <vector>
#include <boost/algorithm/string.hpp>

//!User Includes
#include "StudentDb.h"
#include "Student.h"
#include "Course.h"


/********************** Method Implementations ******************************/

/**
 * \brief		: Constructor
 */
StudentDb::StudentDb()
{}

/**
 * \brief		: Method to add weekly course to the database
 * \param[IN]	: const WeeklyCourse &course - constant weekly course object reference
 * \return		: NONE
 */
void StudentDb::addWeeklyCourseToDb(const WeeklyCourse &course)
{
	std::unique_ptr<const Course> weeklyCoursePtr (new WeeklyCourse(course));
	courses.insert(std::make_pair(course.getCourseKey(), std::move(weeklyCoursePtr)));
}

/**
 * \brief		: Method to add Block course to the database
 * \param[IN]	: const BlockCourse &course - constant block course object reference
 * \return		: NONE
 */
void StudentDb::addBlockCourseToDb (const BlockCourse &course)
{
	std::unique_ptr<const Course> blockCoursePtr (new BlockCourse(course));
	courses.insert(std::make_pair(course.getCourseKey(), std::move(blockCoursePtr)));
}

/**
 * \brief		: Method to list the courses in the database
 * \param[IN]	: NONE
 * \return		: NONE
 */
void StudentDb::listCoursesInDb () const
{
	for(const auto &eachCourse: courses)
	{
		eachCourse.second->print ();
	}
}

/**
 * \brief		: Method to add students to the database
 * \param[IN]	: Student &student - reference to object of student class
 * \return		: NONE
 */
void StudentDb::addStudentToDb(Student &student)
{
	students.insert(std::make_pair(student.getMatrikelNumber(), student));
}

/**
 * \brief		: Method to add enrollment to the student in the database
 * \param[IN]	: unsigned int matrikelNumber - matrikulation number of the student to be enrolled
 * \param[IN]	: unsigned courseKey - Course key of the course to be added to
 * \param[IN] 	: std::string semester - Semester to which the student has to be enrolled to
 * \return		: NONE
 */
void StudentDb::addEnrollmentToStudent(unsigned int matrikelNumber, unsigned courseKey, std::string semester)
{
	//! Get the existing enrollments of the student in a local vector
	std::vector<Enrollment> enrollment = students.at(matrikelNumber).getEnrollments();

	//! Iterate through the enrollments to check if the student is already enrolled to a particular course
	for (auto eachEnrollment = enrollment.begin(); eachEnrollment != enrollment.end(); eachEnrollment++)
	{
		if (courseKey == eachEnrollment->getCourse().getCourseKey())
		{
			std::cerr << "Enrollment already exists" << std::endl;
			return;
		}
		else { /* do nothing */}
	}

	//! Add the enrollments to the respective student in the database
	Enrollment enrolStudent (0, semester, courses.find(courseKey)->second.get());
	students.at(matrikelNumber).updateEnrollments(enrolStudent);
}

/**
 * \brief		: Method to search the student in the database
 * \param[IN]	: unsigned int matrikelNumber - matrikulation number of the student
 * \return		: bool - true if the student already exists in the database, false otherwise
 */
bool StudentDb::isStudentExists (unsigned int matrikelNumber) const
{
	//! Iterate through the database of students for the matrikulation number
	for (auto eachStudent = students.begin(); eachStudent != students.end(); eachStudent++)
	{
		if (matrikelNumber == eachStudent->second.getMatrikelNumber())
		{
			//! Return true if student exists in the database
			return true;
		}
		else
		{

		}
	}
	std::cout << "No student exists by this matrikel number" << std::endl;
	return false;
}

/**
 * \brief		: Method to search the course in the database
 * \param[IN]	: unsigned int courseKey - course key of the course
 * \return		: bool - true if the course already exists in the database, false otherwise
 */
bool StudentDb::isCourseExists (unsigned int courseKey) const
{
	//! Iterate through the database of courses for the course key
	for (const auto &eachCourse: courses)
	{
		if (courseKey == eachCourse.second->getCourseKey())
		{
			//! Return true if the course exists
			return true;
		}
	}
	return false;
}

/**
 * \brief		: Method to print the student in the database
 * \param[IN]	: unsigned int matrikelNumber - matrikulation number of the student
 * \return		: NONE
 */
void StudentDb::printStudent(unsigned int matrikelNumber) const
{
	students.at(matrikelNumber).printStudent();
}

/**
 * \brief		: Method to search the student in the database with a substring of their name
 * \param[IN]	: std::string subString - string that has to be searched for in the database of students
 * \return		: NONE
 */
void StudentDb::searchStudentInDb (std::string subString)
{
	/** Input string from the user could be the first name or last name of the student
	 *  Therefore both first and last names have to be searched in the student database
	 */
	std::string firstNameInDb = " ";
	std::string lastNameInDb = " ";

	//! Converts the string from the user to lower case
	boost::algorithm::to_lower(subString);

	//! Iterate through the student database and search for the student
	for(auto eachStudent = students.begin(); eachStudent != students.end(); eachStudent++)
	{
		//! Get first and last name of each student
		firstNameInDb = eachStudent->second.getFirstName();
		lastNameInDb = eachStudent->second.getLastName();

		//! Convert the names to lower case for a more efficient search
		boost::algorithm::to_lower(firstNameInDb);
		boost::algorithm::to_lower(lastNameInDb);

		//! Find the substring in the student database
		size_t findInFirstName = firstNameInDb.find(subString);
		size_t findInLastName = lastNameInDb.find(subString);

		//! Print the student details if the substring is found in first name or last name
		if(findInFirstName != std::string::npos || findInLastName != std::string::npos)
		{
			std::cout << "Matrikel Number: " << eachStudent->second.getMatrikelNumber()
					  << ", Last Name: " << eachStudent->second.getLastName()
					  << ", First Name: " << eachStudent->second.getFirstName() << std::endl;
		}
	}
}

/**
 * \brief		: Method to update student attributes such as enrollment, first name, last name, address etc..
 * \param[IN]	: unsigned int matrikelNumber - matrikulation number of the student
 * \param[IN]	: unsigned int changeAttribute - Indicates which attribute has to be changed
 * 				 0 - Terminate
 *			  	 1 - First Name
 *				 2 - Last Name
 *			  	 3 - Date Of Birth
 *			  	 4 - Enrollment
 *			  	 5 - Address
 * \return		: NONE
 */
void StudentDb::updateStudentInDb(unsigned int matrikelNumber, unsigned int changeAttribute)
{
	//! To terminate the program
	if (changeAttribute == 0)
	{
		std::cout << "Terminating..." << std::endl;
		return;
	}
	else
	{
		switch(changeAttribute)
		{
		//! Change first name
		case 1:
		{
			std::string newFirstName = " ";
			std::cin.ignore();
			std::cout << "Enter the new first name: " << std::endl;
			std::cin >> newFirstName;

			//! Iterate over the student database and change the first name based on the matrikulation number input
			for (auto eachStudent = students.begin(); eachStudent != students.end(); eachStudent++)
			{
				if(matrikelNumber == eachStudent->second.getMatrikelNumber())
				{
					eachStudent->second.setFirstName (newFirstName);
				}
			}
			break;
		}
		//! Change last name
		case 2:
		{
			std::string newLastName = " ";
			std::cin.ignore ();
			std::cout << "Enter the new last name: " << std::endl;
			getline (std::cin, newLastName);

			//! Iterate over the student database and change the last name based on the matrikulation number input
			for (auto eachStudent = students.begin(); eachStudent != students.end(); eachStudent++)
			{
				if(matrikelNumber == eachStudent->second.getMatrikelNumber())
				{
					eachStudent->second.setLastName(newLastName);
				}
			}
			break;
		}
		//! Change date of birth
		case 3:
		{
			int newDate {}, newMonth {}, newYear {};
			std::cout << "Enter the new date of birth (dd mm yyyy): " << std::endl;
			std::cin >> newDate >> newMonth >> newYear;

			//! Iterate over the student database and change the date of birth based on the matrikulation number input
			for (auto eachStudent = students.begin(); eachStudent != students.end(); eachStudent++)
			{
				if(matrikelNumber == eachStudent->second.getMatrikelNumber())
				{
					eachStudent->second.setDateOfBirth(Poco::Data::Date (newYear, newMonth, newDate));
				}
			}
			break;
		}
		//! Change enrollment
		case 4:
		{
			unsigned int courseKey {}, enrollmentAction {};
			float newGrade {};

			std::cout << "1 - Change Grade" 	 << std::endl
					  << "2 - Delete Enrollment" << std::endl;
			std::cin >> enrollmentAction;

			std::cout << "Enter the course key" << std::endl;
			std::cin >> courseKey;

			//! Change grade of the student
			if (1 == enrollmentAction)
			{
				std::cout << "Enter the new grade: " << std::endl;
				std::cin >> newGrade;

				//! Iterate over the student database and change the grade based on the matrikulation number input
				for (auto eachStudent = students.begin(); eachStudent != students.end(); eachStudent++)
				{
					if(matrikelNumber == eachStudent->second.getMatrikelNumber())
					{
						eachStudent->second.updateGrade(courseKey, newGrade);
					}
				}
			}
			//! Delete enrollment
			else if (2 == enrollmentAction)
			{
				//! Iterate over the student database and delete the enrollment based on the matrikulation number input
				for (auto eachStudent = students.begin(); eachStudent != students.end(); eachStudent++)
				{
					if (matrikelNumber == eachStudent->second.getMatrikelNumber())
					{
						eachStudent->second.deleteEnrollment (courseKey);
					}
				}
			}
			else
			{
				std::cout << "Incorrect option!" << std::endl;
			}
			break;
		}
		//! Change address
		case 5:
		{
			std::string newStreetName = " ", newCityName = " ", newAdditionalInfo = " ";
			unsigned short newPostalCode {};

			std::cout << "Enter the new address" << std::endl;
			std::cout << "---------------------" << std::endl;

			std::cin.ignore();
			std::cout << "Street Name: " << std::endl;
			getline (std::cin, newStreetName);

			std::cin.ignore();
			std::cout << "City Name: " << std::endl;
			getline (std::cin, newCityName);

			std::cout << "Postal Code: " << std::endl;
			std::cin >> newPostalCode;

			std::cin.ignore();
			std::cout << "Additional Info: ";
			getline (std::cin, newAdditionalInfo);

			//! Iterate over the student database and set the address based on the matrikulation number input
			for (auto eachStudent = students.begin(); eachStudent != students.end(); eachStudent++)
			{
				if (matrikelNumber == eachStudent->second.getMatrikelNumber())
				{
					eachStudent->second.setAddress(Address(newStreetName, newPostalCode, newCityName, newAdditionalInfo));
				}
			}
			break;
		}
		}
	}
}

/**
 * \brief		: Method to update student grade in the database
 * \param[IN]	: unsigned int matrikelNumber - matrikulation number of the student
 * \param[IN]	: unsigned courseKey - Course key of the course to be graded
 * \param[IN] 	: float grade - New grade for the course
 * \return		: NONE
 */
void StudentDb::updateStudentGradeInDb(unsigned int matrikelNumber, unsigned int courseKey, float grade)
{
	//! Iterate over the student database and update the grade based on the matrikulation number and course key
	for (auto eachStudent = students.begin(); eachStudent != students.end(); eachStudent++)
	{
		if (eachStudent->second.getMatrikelNumber() == matrikelNumber)
		{
			eachStudent->second.updateGrade(courseKey, grade);
		}
	}

}

/**
 * \brief		: Method to write the student attributes onto the stream
 * \param[IN]	: std::ostream& out - reference to ostream object
 * \return		: NONE
 */
void StudentDb::write(std::ostream &out)
{
	//! Get the size of the database
	size_t studentSize = students.size();
	size_t courseSize = courses.size();

	//! Output the course size onto the stream
	out << courseSize << std::endl;

	//! Iterate over the course database and write the course information onto the stream
	for(const auto &eachCourse: courses)
	{
		eachCourse.second->write(out);
	}

	//! Output the number of students onto the stream
	out << studentSize << std::endl;

	//! Iterate over the student database and write the course information onto the stream
	for (auto eachStudent: students)
	{
		eachStudent.second.write(out);
	}
}

/**
 * \brief		: Method to read the student attributes from the stream
 * \param[IN]	: std::istream& in - reference to istream object
 * \details		:
 * Example reference of the database file
 * 2
 * W;5387;APT;Automation;5;3;17:45;19:15
 * B;2371;C Programming;Automation;5;16.9.2019;20.9.2019;14:15;19;15
 * 2
 * 100000;Olsen;Peter;23.11.1998;7158 Spurvevej;21361;Juelsminde;
 * 100001;Stein;Josephine;5.3.1997;2575 Tannenweg;49733;Delitzsch;Apartement 6b
 * 1
 * 100000;5387;WS2018;2.3
 *
 * \return		: NONE
 */
void StudentDb::read(std::istream &in)
{
	//! Clear the database before reading from the file
	students.clear();
	courses.clear();

	/**
	 *  Local variable declarations
	 */
	std::string line;
	std::string courseNameStr, majorStr, startTimeStr, endTimeStr, startDateStr, endDateStr, firstNameStr, lastNameStr, dateOfBirthStr,
				streetNameStr, cityNameStr, additionalInfoStr, semesterStr;

	int numberOfCourses{}, courseKey{}, creditPoints{}, dayOfWeek{}, numberOfStudents{}, i {1}, j{}, k{}, matrikelNumber{}, postalCode{}, numberOfEnrollments{};

	unsigned char major{}, dateDelimiter {'.'}, timeDelimiter{':'};

	float grade {};

	std::vector<std::string> lines;

	//! Get all the lines from the stream object into a vector
	while(getline(in, line))
	{
		lines.push_back(line);
	}

	//! Get the number of courses from first line
	numberOfCourses = std::stoi(lines.at(0));
	for (i = 1; i <= numberOfCourses; i++)
	{
		std::vector<std::string> courseVec;
		//! Parse the data of the courses and get it into a local vector
		boost::split(courseVec, lines.at(i), boost::is_any_of(";"));

		if ("W" == courseVec.at(0))
		{
			//! Extract all the data from the weekly course
			courseKey 		= stoi(courseVec.at(1));
			courseNameStr 	= courseVec.at(2);
			majorStr 		= courseVec.at(3);
			major 			= majorStr.at(0);
			creditPoints 	= stoi(courseVec.at(4));
			dayOfWeek		= stoi(courseVec.at(5));
			startTimeStr 	= courseVec.at(6);
			endTimeStr 		= courseVec.at(7);

			courseVec.clear();

			//! Add course information to database
			WeeklyCourse weeklyCourse(courseKey, courseNameStr, major, creditPoints,
							Poco::DateTime::DaysOfWeek (dayOfWeek),
							splitTime(startTimeStr, timeDelimiter), splitTime(endTimeStr, timeDelimiter));

			addWeeklyCourseToDb(weeklyCourse);
		}
		else if ("B" == courseVec.at(0))
		{
			//! Extract all the data from block course
			courseKey 		= stoi(courseVec.at(1));
			courseNameStr 	= courseVec.at(2);
			majorStr 		= courseVec.at(3);
			major 			= majorStr.at(0);
			creditPoints 	= stoi(courseVec.at(4));
			startDateStr	= courseVec.at(5);
			endDateStr		= courseVec.at(6);
			startTimeStr 	= courseVec.at(7);
			endTimeStr 		= courseVec.at(8);

			courseVec.clear();

			//! Add course information to the database
			BlockCourse blockCourse (courseKey, courseNameStr, major, creditPoints,
									splitDate(startDateStr, dateDelimiter), splitDate(endDateStr, dateDelimiter),
									splitTime(startTimeStr, timeDelimiter), splitTime(endTimeStr, timeDelimiter));

			addBlockCourseToDb(blockCourse);
		}

	}

	//! Get the number of students
	numberOfStudents = stoi(lines.at(i));
	/**
	 *  Loop variable starts from one higher to where the previous loop ends due to the format in which the
	 *  data is obtained from the stream object
	 */
	for (j = i + 1; j <= i + numberOfStudents; j++)
	{
		std::vector<std::string> studentVec;

		//! Parse the student information from the stream into a local vector
		boost::split(studentVec, lines.at(j), boost::is_any_of(";"));

		//! Extract data from the local vector
		matrikelNumber 		= stoi(studentVec.at(0));
		lastNameStr			= studentVec.at(1);
		firstNameStr 		= studentVec.at(2);
		dateOfBirthStr 		= studentVec.at(3);
		streetNameStr 		= studentVec.at(4);
		postalCode 			= stoi(studentVec.at(5));
		cityNameStr 		= studentVec.at(6);
		additionalInfoStr 	= studentVec.at(7);

		studentVec.clear();

		//! Add student to the database
		Student student(matrikelNumber, firstNameStr, lastNameStr, splitDate(dateOfBirthStr, dateDelimiter),
										Address(streetNameStr, postalCode, cityNameStr, additionalInfoStr));
		addStudentToDb(student);
	}

	//! Get the number of enrollments
	numberOfEnrollments = stoi(lines.at(j));

	/**
	 *  Loop variable starts from one higher to where the previous loop ends due to the format in which the
	 *  data is obtained from the stream object
	 */
	for(k = j + 1; k <= j + numberOfEnrollments; k++)
	{
		std::vector<std::string> enrollmentVec;

		//! Parse the enrollment information from the stream into a local vector
		boost::split(enrollmentVec, lines.at(k), boost::is_any_of(";"));

		//! Extract data from the local vector
		matrikelNumber 	= stoi(enrollmentVec.at(0));
		courseKey 		= stoi(enrollmentVec.at(1));
		semesterStr 	= enrollmentVec.at(2);
		grade 			= stof(enrollmentVec.at(3));

		enrollmentVec.clear();

		//! Add enrollment to the database
		addEnrollmentToStudent(matrikelNumber, courseKey, semesterStr);
		updateStudentGradeInDb(matrikelNumber, courseKey, grade);
	}

}

/**
 * \brief		: Helper method to split the date into dd mm yyyy(int) values from string
 * \param[IN]	: const std::string& dateString - reference to string object having date
 * \param[IN] 	: char delimiter - delimiter to parse the data
 * \return		: Poco::Data::Date - Poco date object in 'dd mm yyyy'(int) format
 */
Poco::Data::Date StudentDb::splitDate(const std::string& dateString, char delimiter)
{
   std::vector<std::string> parsedDate;
   std::string token;
   std::istringstream dateStream(dateString);

   //! Parse the string based on the delimiter input
   while (getline(dateStream, token, delimiter))
   {
	   parsedDate.push_back(token);
   }

   return Poco::Data::Date(stoi(parsedDate.at(2)), stoi(parsedDate.at(1)), stoi(parsedDate.at(0)));
}

/**
 * \brief		: Helper method to split the time into hh mm ss(int) values from string
 * \param[IN]	: const std::string& timeString - reference to string object having time
 * \param[IN] 	: char delimiter - delimiter to parse the data
 * \return		: Poco::Data::Time - Poco time object in 'hh mm ss'(int) format
 */
Poco::Data::Time StudentDb::splitTime(const std::string& timeString, char delimiter)
{
   std::vector<std::string> parsedTime;
   std::string token;
   std::istringstream timeStream(timeString);

   //! Parse the string based on the delimiter input
   while (getline(timeStream, token, delimiter))
   {
      parsedTime.push_back(token);
   }
   //! Update seconds(ss)
   if(parsedTime.size() <= 2)
	   parsedTime.push_back("0");

   return Poco::Data::Time(stoi(parsedTime.at(0)), stoi(parsedTime.at(1)), stoi(parsedTime.at(2)));
}

/**
 * \brief		: Destructor
 */
StudentDb::~StudentDb()
{}

