#pragma once
#include <fstream>
#include <locale>
#include <codecvt>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "ExcelManager.h"

// csv 파일 불러오기

// studentInfos.reset(); // clear (불러오기를 위해)
std::vector<std::vector<std::wstring>> ExcelManager::loadFromCSV(const std::string& filePath)
{
	std::vector<std::vector<std::wstring>> rows;

	std::wifstream in(filePath, std::ios::binary);
	// UTF-8로 읽기 설정
	in.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
	
	if (!in.is_open()) return rows;

	std::wstring line;
	bool isHeader = true;

	while (std::getline(in, line))
	{
		// 첫 번째 줄의 BOM(Byte Order Mark) 제거
		if (isHeader) {
			if (!line.empty() && line[0] == 0xFEFF)
			{
				line.erase(0, 1);
			}
			isHeader = false;
			continue; 
		}

		std::wstringstream ss(line);
		std::wstring cell;
		std::vector<std::wstring> cells;

		while (std::getline(ss, cell, L',')) {
			cells.push_back(cell);
		}
		rows.push_back(cells);
	}

	in.close();
	return rows;
}

// csv 파일 저장
bool ExcelManager::saveToCSV(std::string& filePath, std::vector<std::vector<std::wstring>> rows)
{
	std::wofstream out(filePath, std::ios::binary);
	out.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

	if (!out.is_open())
		return false;

	// UTF-8 BOM 추가 (Excel 호환)
	const wchar_t bom = 0xFEFF;
	out << bom;

	for (auto& rowIt : rows)
	{
		for (int i = 0; i < rowIt.size(); ++i)
		{
			std::wstring cell = rowIt[i];

			bool needQuotes = (cell.find(L',') != std::wstring::npos ||
				cell.find(L'"') != std::wstring::npos ||
				cell.find(L'\n') != std::wstring::npos);
			
			if (needQuotes)
			{
				std::wstring escaped;
				for (wchar_t c : cell)
				{
					if (c == L'"')
						escaped += L"\"\""; // 따옴표 2개로 escape
					else
						escaped += c;
				}
				cell = L"\"" + escaped + L"\"";
			}

			out << cell;
			if (i < rowIt.size() - 1)
			{
				out << L",";
			}
		}
		out << L"\n";
	}

	out.close();
	return true;
}