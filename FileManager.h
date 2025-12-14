#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

class FileManager
{
private:
	static std::vector<std::string> parseLine(const std::string& line)
	{
		std::vector<std::string> cells;
		std::string cell;
		bool insideQuote = false;

		for (size_t i = 0; i < line.size(); i++)
		{
			char c = line[i];

			if (c == '"')
			{
				if (insideQuote && i + 1 < line.size() && line[i + 1] == '"')
				{
					cell += '"';   // 이스케이프 ""
					i++;
				}
				else
				{
					insideQuote = !insideQuote;
				}
			}
			else if (c == ',' && !insideQuote)
			{
				cells.push_back(cell);
				cell.clear();
			}
			else
			{
				cell += c;
			}
		}

		cells.push_back(cell);
		return cells;
	}
public:
		// 파일 불러오기
		static std::vector<std::vector<std::string>> loadFromCSV(const std::string& filePath)
		{
			std::vector<std::vector<std::string>> rows;
			std::ifstream in(filePath, std::ios::binary);

			if (!in.is_open())
				return rows;

			std::string line;
			bool firstLine = true;

			while (std::getline(in, line))
			{
				// CR 제거 (CRLF 대응)
				if (!line.empty() && line.back() == '\r')
					line.pop_back();

				// UTF-8 BOM 제거 (첫 줄만)
				if (firstLine)
				{
					firstLine = false;
					if (line.rfind("\xEF\xBB\xBF", 0) == 0)
						line.erase(0, 3);
				}

				rows.push_back(parseLine(line));
			}

			return rows;
		}

		// 파일 저장하기
		static bool saveToCSV(std::string& filePath, std::vector<std::vector<std::string>> rows)
		{
			// 바이너리 모드로 열기
			std::ofstream out(filePath, std::ios::binary);
			if (!out.is_open())
				return false;

			// UTF-8 BOM
			const char bom[] = { '\xEF', '\xBB', '\xBF' };
			out.write(bom, 3);

			for (const auto& row : rows)
			{
				for (size_t i = 0; i < row.size(); ++i)
				{
					std::string cell = row[i];

					// CSV 특수문자 처리
					bool needQuotes =
						cell.find(',') != std::string::npos ||
						cell.find('"') != std::string::npos ||
						cell.find('\n') != std::string::npos;

					if (needQuotes)
					{
						std::string escaped;
						for (char c : cell)
						{
							if (c == '"')
								escaped += "\"\"";
							else
								escaped += c;
						}
						cell = "\"" + escaped + "\"";
					}

					// UTF-8 바이트 그대로 기록
					out.write(cell.c_str(), cell.size());

					if (i < row.size() - 1)
						out.write(",", 1);
				}
				out.write("\n", 1);
			}

			out.close();
			return true;
		}

	static std::string getFileType(std::string& filePath)
	{
		int dotPos = filePath.find_last_of('.');
		if (dotPos == std::string::npos)
			return "";

		std::string extends = filePath.substr(dotPos + 1); // csv

		std::transform(
			extends.begin(),
			extends.end(),
			extends.begin(),
			[](unsigned char c) { return std::tolower(c); }
		);

		return extends;
	}
};

