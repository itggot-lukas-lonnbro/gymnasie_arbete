#pragma once

#include <string>

class model
{
public:
	model();
	~model();

	int loadModelFromFile(const std::string &modelName);
};

