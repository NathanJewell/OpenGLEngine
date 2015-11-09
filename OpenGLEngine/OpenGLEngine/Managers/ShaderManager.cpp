//ShaderManager.cpp
#include "ShaderManager.h"


using namespace Managers;

std::map<std::string, GLuint> ShaderManager::programs; //initialize that static map

ShaderManager::ShaderManager(){} //empty constructor
ShaderManager::~ShaderManager()
{
	std::map<std::string, GLuint>::iterator it;
	for (it = programs.begin(); it != programs.end(); it++)
	{
		GLuint pr = it->second;
		glDeleteProgram(pr);
	}
	programs.clear();
}

std::string ShaderManager::ReadShader(const std::string& fileName)
{
	std::string shaderCode;
	std::ifstream file(fileName, std::ios::in);

	if (!file.good())
	{
		std::cout << "Cannot read file " << fileName << "\n";
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();

	return shaderCode;
}

GLuint ShaderManager::CreateShader(GLenum shaderType, const std::string source, const std::string& shaderName)
{
	int compileResult = 0;
	GLuint shader = glCreateShader(shaderType); //create empty shader object of type shaderType
	const char *shaderCodePtr = source.c_str();
	const int shaderCodeSize = source.size();

	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize); //sets shader code (shadeObject, #charArrays, referenceToArray, #filledArraylocations)
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	//checking for compile errors
		if (compileResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);

		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		std::cout << "ERROR compiling shader: " << shaderName << "\n" << &shaderLog[0] << "\n";
		return 0;
	}

	return shader;

}

void ShaderManager::CreateProgram(const std::string& programName, const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename)
{
	//read shader files and save the code

	std::string vertexShaderCode = ReadShader(vertexShaderFilename);
	std::string fragmentShaderCode = ReadShader(fragmentShaderFilename);

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader");
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader");

	int linkResult = 0;
	//create the program handle, attach the shaders and link it

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

	//check for link errors
	if (linkResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
		std::cout << "Shader Loader: LINK ERROR\n" << &programLog[0] << "\n";
	}

	if (programs.count(programName) == 0)
	{
		programs[programName] = program;
	}
	else //error if there is already a shader with that key value
	{
		std::cout << "Shader Loader: Program Store Error\nFailed to create program " << programName << " from " << vertexShaderFilename << " and " << fragmentShaderFilename << "\n";
	}
	


}

const GLuint ShaderManager::GetShader(const std::string& shaderName)
{
	if (programs.count(shaderName) == 1)
	{
		return programs.at(shaderName);
	}
	//return error
	std::cout << "SHADER MANAGER: Shader Retrieval Error\nShader " << shaderName << " does not exist within stored shader array and could not be accessed.\n";
	return GL_FALSE;
}

const void ShaderManager::DeleteShader(const std::string& shaderName)
{
	if (programs.count(shaderName) == 1)
	{
		//std::map<std::string, GLuint>::iterator it;
		//it = programs.find(shaderName);
		//programs.erase(it);
	}
	//return error
	std::cout << "SHADER MANAGER: Shader Deletion Error\nShader " << shaderName << " does not exist withing stored shader array and could not be deleted.\n";
}