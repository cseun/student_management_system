#pragma once
#include <string>
#include <vector>

enum class ExamType
{
    Unknown = -1,
    Midterm,   
    Final,     
    Quiz,      
    MockTest,  
    Assignment 
};

inline std::vector<ExamType> getExamTypes()
{
    return {
        ExamType::Midterm,
        ExamType::Final,
        ExamType::Quiz,
        ExamType::MockTest,
        ExamType::Assignment
    };
}

// 과목 문자열 변환
inline std::string getExamName(ExamType examType)
{
    switch (examType)
    {
    case ExamType::Midterm:
        return "중간고사";
    case ExamType::Final:
        return "기말고사";
    case ExamType::Quiz:
        return "수행평가";
    case ExamType::MockTest:
        return "모의고사";
    case ExamType::Assignment:
        return "과제";
    case ExamType::Unknown:
        return "미정";
    default:
        return "미정";
    }
}

inline ExamType getExamTypeFromName(const std::string& name)
{
    if (name == "중간고사")
        return ExamType::Midterm;
    if (name == "기말고사") 
        return ExamType::Final;
    if (name == "수행평가") 
        return ExamType::Quiz;
    if (name == "모의고사") 
        return ExamType::MockTest;
    if (name == "과제")     
        return ExamType::Assignment;
    return ExamType::Unknown;
}
