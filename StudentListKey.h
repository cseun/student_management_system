#pragma once
struct StudentListKey
{
	int grade;
	int classNumber;
	int studentNumber;

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