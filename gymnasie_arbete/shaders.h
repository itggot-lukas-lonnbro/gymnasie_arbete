#pragma once
#include <string>

#include <GL\glew.h>

class shaders
{
public:
	shaders();
	~shaders();

	void init(const std::string& vertexName, const std::string& fragmentName);
	void useShader();
	void unUseShader();

	void setFloat(const std::string&, float);
	void setFloat3f(const std::string &name, float value[]);
	void setMat4(const std::string&, GLfloat*);
	void setBool(const std::string&, GLboolean);

	unsigned int shaderProgram;
private:
};

