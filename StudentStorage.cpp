#include "pch.h"
#include <map>
#include <vector>
#include "StudentStorage.h"

const std::map<int, Student>& StudentStorage::getAllStudents() const
{
	return studentTable;
}


const std::vector<std::pair<int, const Student*>> StudentStorage::getAllStudentsIndexOrder() const 
{
    std::vector<std::pair<int, const Student*>> result; // ref는 long-lived 관리가 어려움 -> 포인터 사용
    result.reserve(studentIndexList.size());

    for (const auto& it : studentIndexList) {
        const Student& student = studentTable.at(it.second);
        result.emplace_back(it.second, &student);
    }

    return result;
}