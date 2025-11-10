#pragma once
#include <fstream>

class ExcelManager
{
public:
	std::vector<std::vector<std::wstring>> loadFromCSV(const std::string& filePath);
	bool saveToCSV(std::string& filePath, std::vector<std::vector<std::wstring>> rows);
};