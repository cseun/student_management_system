#include "pch.h"
#include <map>
#include <vector>
#include "StudentStorage.h"

std::map<int, Student>& StudentStorage::getAllStudents()
{
	return studentTable;
}


std::vector<std::pair<int, Student*>> StudentStorage::getAllStudentsIndexOrder() 
{
    std::vector<std::pair<int, Student*>> result; // ref는 long-lived 관리가 어려움 -> 포인터 사용
    result.reserve(studentIndexList.size());

    for (auto& it : studentIndexList) {
        Student& student = studentTable.at(it.second);
        result.emplace_back(it.second, &student);
    }

    return result;
}