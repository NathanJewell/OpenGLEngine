#pragma once

#include "Core\Init\InitGLUT.h"
#include "Managers\SceneManager.h"
#include "Managers\LogManager.h"

int main(int argc, char**argv)
{
	Core::WindowInfo window(std::string("This is hype!"),//window name
		400, 200, //position
		1200, 900, //size
		true);//reshape
	Core::ContextInfo context(3, 3, true);
	Core::FramebufferInfo frameBufferInfo(true, true, true, true);

	//initialize GLUT
	Core::InitGLUT::init(window, context, frameBufferInfo);

	Core::Listener* scene = new Managers::SceneManager();
	Core::InitGLUT::setListener(scene);

	//initialize LogManager
	Managers::LogManager::SetConsoleOutputVerbosity(LOG_DEBUG);	//set console log level to debug (everything)
	Managers::LogManager::FileOutput(false);	//don't output to a file
	Managers::LogManager::Log(LOG_INFO, "Log Manager Initialized...");
	//start GLUT main loop
	Core::InitGLUT::run();

	delete scene;
	return 0;
}