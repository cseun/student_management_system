#pragma once
#include <string>
#include <sstream>

struct StudentListKey
{
	int grade = 0;
	std::string className = "0";
	int studentNumber = 0;

	bool operator<(const StudentListKey& other) const
	{
		if (grade != other.grade)
			return grade < other.grade;
		if (className != other.className)
			return className < other.className;
		return studentNumber < other.studentNumber;
	}

	bool operator==(const StudentListKey& other) const {
		return grade == other.grade &&
			className == other.className &&
			studentNumber == other.studentNumber;
	}

	bool operator!=(const StudentListKey& other) const {
		return !(*this == other);
	}

	std::string toString() const
	{
		return std::to_string(grade) + "-" +
			className + "-" +
			std::to_string(studentNumber);
	}

	static StudentListKey fromString(std::string& listKeyStr)
	{
		StudentListKey key;
		std::stringstream ss(listKeyStr);
		std::string token;

		std::getline(ss, token, '-');
		key.grade = std::stoi(token);

		std::getline(ss, key.className, '-');

		std::getline(ss, token, '-');
		key.studentNumber = std::stoi(token);

		return key;
	}
};