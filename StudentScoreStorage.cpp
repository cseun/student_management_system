#include "pch.h"
#include <map>
#include <vector>
#include "StudentScoreStorage.h"

const std::map<int, std::vector<StudentScore>>& StudentScoreStorage::getAllScores() const
{
	return studentScoreTable;
}