#pragma once

#include "model.h"

class entity
{
public:
	entity();
	~entity();

	int loadModel(const std::string &modelName); //By default goes to deps/models.
};

