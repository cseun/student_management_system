#pragma once
#include <string>

enum class ExamType
{
    Unknown = -1,
    Midterm,   
    Final,     
    Quiz,      
    MockTest,  
    Assignment 
};

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