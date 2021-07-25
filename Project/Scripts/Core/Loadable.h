#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "IdHolder.h"

class Loadable : public IdHolder
{
private:
	Loadable(const Loadable&) = delete;
	Loadable operator=(const Loadable&) = delete;

protected:
	std::string filePath;

	Loadable(std::string filePath)
	{
		this->filePath = std::move(filePath);
	}
public:
	const std::string& GetFilePath()
	{
		return filePath;
	}

	virtual bool Load() = 0;
	virtual void Unload() = 0;

	static std::string ReadResourceFileAsString(std::string filePath)
	{
		std::ifstream fileStream("Resources/" + filePath, std::ios::in);
		if (!fileStream.is_open())
		{
			throw "Unable to open file.";
		}

		std::string content;
		std::string line = "";

		while (!fileStream.eof())
		{
			std::getline(fileStream, line);
			content.append(line + "\n");
		}

		return content;
	}
};
