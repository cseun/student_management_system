#pragma once
struct StudentListKey
{
	int grade = 0;
	int classNumber = 0;
	int studentNumber = 0;

	bool operator<(const StudentListKey& other) const
	{
		if (grade != other.grade)
			return grade < other.grade;
		if (classNumber != other.classNumber)
			return classNumber < other.classNumber;
		return studentNumber < other.studentNumber;
	}

	bool operator==(const StudentListKey& other) const {
		return grade == other.grade &&
			classNumber == other.classNumber &&
			studentNumber == other.studentNumber;
	}

	bool operator!=(const StudentListKey& other) const {
		return !(*this == other);
	}
};