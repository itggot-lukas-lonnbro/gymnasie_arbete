#include "entity.h"

#include "model.h"


entity::entity()
{
}


entity::~entity()
{
}

int entity::loadModel(const std::string &modelName) {
	model test;
	return test.loadModelFromFile(modelName);
}