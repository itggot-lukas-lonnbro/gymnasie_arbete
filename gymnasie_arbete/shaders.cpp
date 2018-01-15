#include "shaders.h"

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>

using namespace std;

shaders::shaders()
{
}

shaders::~shaders()
{
}

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

string readFromFile(string filePath) {
	string contents;
	ifstream source(filePath, ios::in);

	if (!source.is_open()) {
		std::cout << "Could not read file " << filePath << ". File does not exist." << std::endl;
		int a;
		cin >> a;
		return "";
	}

	string line;
	while (!source.eof()) {
		getline(source, line);
		contents.append(line + "\n");
	}
	source.close();

	return contents;
}

void shaders::init(const string& vertexName, const string& fragmentName) {

	//Read our shaders into the appropriate buffer
	//cout << "vertex Input name: " << vertexName << "Full path: " << ExePath() + "\\shaders\\" + vertexName << endl;
	std::string vertexSource = readFromFile(ExePath() + "\\shaders\\" + vertexName);
	std::string fragmentSource = readFromFile(ExePath() + "\\shaders\\" + fragmentName);

	//Create an empty vertex shader handle
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Send the vertex shader source code to GL
	//Note that std::string's .c_str is NULL character terminated.
	const GLchar *source = (const GLchar *)vertexSource.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	//Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		std::cout << "Vertexshader " << vertexName << " compilation not successful." << std::endl;
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		//We don't need the shader anymore.
		glDeleteShader(vertexShader);

		//Use the infoLog as you see fit.
		for (std::vector<char>::const_iterator i = infoLog.begin(); i != infoLog.end(); ++i)
			std::cout << *i;

		int a;
		std::cin >> a;
		//In this simple program, we'll just leave
		return;
	}

	//Send the fragment shader source code to GL
	//Note that std::string's .c_str is NULL character terminated.
	source = (const GLchar *)fragmentSource.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	//Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		cout << "Fragmentshader '" << fragmentName << "' compilation not sucessfull" << endl;
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		//We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		//Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		//Use the infoLog as you see fit.
		for (std::vector<char>::const_iterator i = infoLog.begin(); i != infoLog.end(); ++i)
			std::cout << *i;


		int a;
		std::cin >> a;
		//In this simple program, we'll just leave
		return;
	}

	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	shaderProgram = glCreateProgram();

	//Attach our shaders to our program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//Link our shaderProgram
	glLinkProgram(shaderProgram);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		std::cout << "Linking unsuccessfull." << std::endl;
		GLint maxLength = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);

		//We don't need the shaderProgram anymore.
		glDeleteProgram(shaderProgram);
		//Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		//Use the infoLog as you see fit.

		//In this simple shaderProgram, we'll just leave
		return;
	}

	//Always detach shaders after a successful link.
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
}

void shaders::setFloat(const std::string &name, float value) {
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}
void shaders::setFloat3f(const std::string &name, float value[]) {
	glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), value[0], value[1], value[2]);
}
void shaders::setMat4(const std::string &name, GLfloat* mat4) {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, mat4);
}
void shaders::setBool(const std::string &name, GLboolean boolean) {
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), boolean);
}

void shaders::useShader() {
	glUseProgram(shaderProgram);
}

void shaders::unUseShader() {
	glUseProgram(0);
}
