//ShaderManager.h
#pragma once


#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include "../Dependencies/glew/glew.h"
#include "../Dependencies/freeglut/freeglut.h"

namespace Managers
{
	class ShaderManager
	{
	public:
		ShaderManager();
		~ShaderManager();

		void CreateProgram(const std::string& programName, const std::string& VertexShaderFilename, const std::string& FragmentShaderFilename);
		static const GLuint GetShader(const std::string& shaderName);
		static const void DeleteShader(const std::string& shaderName);
	private:
		std::string ReadShader(const std::string& filename);
		GLuint CreateShader(GLenum shadertype, const std::string source, const std::string& shaderName);

		static std::map<std::string, GLuint> programs;

	};
}