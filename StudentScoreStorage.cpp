#include "pch.h"
#include <map>
#include <vector>
#include "StudentScoreStorage.h"

std::map<int, std::vector<StudentScore>>& StudentScoreStorage::getAllScores()
{
	return studentScoreTable;
}