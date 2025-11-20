#include "pch.h"
#include <map>
#include "StudentStorage.h"

const std::map<int, Student>& StudentStorage::getAllStudents() const
{
	return studentTable;
}