#pragma once
#include <string>

class Student
{
private:
    int studentKey = -1; // 기본값
    std::string name;
    std::string grade;
    std::string className;
    std::string studentNumber;

public:
    static int studentIndex; // 학생 키 인덱스

    Student() = default;
    Student(
        std::string& name,
        std::string& grade,
        std::string& className,
        std::string& studentNumber
    );

    int getKey() const;

    // Getter
    const std::string& getName() const;
    const std::string& getGrade() const;
    const std::string& getClassName() const;
    const std::string& getStudentNumber() const;
	
    // Setter
    void setName(const std::string& name);
    void setGrade(const std::string& grade);
    void setClassName(const std::string& className);
    void setStudentNumber(const std::string& studentNumber);

    void setStudent(const Student& updateStudent);
	std::string getListKey() const;
    bool isSameStudentInfo(const Student& compareStudent) const;
};