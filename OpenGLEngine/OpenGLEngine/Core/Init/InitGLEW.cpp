//InitGLEW.cpp
#include "InitGLEW.h"

using namespace Core;

void InitGLEW::Init()
{
	glewExperimental = true;
	if (glewInit() == GLEW_OK)
	{
		std::cout << "GLEW: Initialized\n";
	}
	if (glewIsSupported("GL_VERSION_4_5"))
	{
		std::cout << "GLEW GL_VERSION_4_5 is 4.5\n";
	}
	else 
	{
		std::cout << "GLEW GL_VERSION_4_5 is not supported\n";
	}
}