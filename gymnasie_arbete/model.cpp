#include "model.h"

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <glm-0.9.9-a1\glm\glm.hpp>

using namespace std;

model::model()
{
}


model::~model()
{
}

/*string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}*/

int model::loadModelFromFile(const std::string &modelName) {
	std::string modelPath = "C:\\Users\\lukas.lonnbro\\source\\repos\\gymnasie_arbete\\gymnasie_arbete\\models\\" + modelName;
	std::cout << "model name: " << modelName << " Executing path: " << modelPath << endl;
	FILE *file;
	fopen_s(&file, modelPath.c_str(), "r");
	if (file == NULL) {
		printf("Unable to open file.");
		return 0;
	}

	while (1) {
		std::cout << "parsing." << std::endl;

		char lineHeader[128];
		int res = scanf_s("%s", &lineHeader, 128);
		if (res == EOF) {
			break;
		}
		if (strcmp(lineHeader, "v")){
			glm::vec3 vertex;
			scanf_s("%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			cout << vertex.x << vertex.y << vertex.z << endl;
		}
	}

	std::cout << "done parsing." << endl;
	return 1;
}