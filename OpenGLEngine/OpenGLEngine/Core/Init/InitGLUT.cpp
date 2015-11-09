//InitGLUT.cpp
#include "InitGLUT.h"
#include <iostream>

//initizialize static vars
Core::Listener* Core::InitGLUT::listener = NULL;
Core::WindowInfo Core::InitGLUT::windowInformation;

void Core::InitGLUT::init(const Core::WindowInfo& windowInfo,
	const Core::ContextInfo& contextInfo,
	const Core::FramebufferInfo& framebufferInfo)
{
	windowInformation = windowInfo;
	int fakeargc = 1;
	char *fakeargv[] = { "fake", NULL }; //create fake arguments
	glutInit(&fakeargc, fakeargv);

	if (contextInfo.core)
	{
		glutInitContextVersion(contextInfo.majorVersion, contextInfo.minorVersion);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
	{
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	//basic setup functions
	//using info from data structures
	glutInitDisplayMode(framebufferInfo.flags);
	glutInitWindowPosition(windowInfo.positionX, windowInfo.positionY);
	glutInitWindowSize(windowInfo.width, windowInfo.height);
	
	glutCreateWindow(windowInfo.name.c_str());

	std::cout << "GLUT: Initialized\n";

	//callback functions for rendering
	glutIdleFunc(idleCallback);
	glutCloseFunc(closeCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);

	//initialize GLEW
	InitGLEW::Init();

	//cleanup
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//display some info about the OpenGL
	printOpenGLInfo(windowInfo, contextInfo);

}

void Core::InitGLUT::run()
{
	std::cout << "GLUT:\tStarting main loop\n";
	glutMainLoop();
}

void Core::InitGLUT::close()
{
	std::cout << "GLUT:\t Finished\n";
	glutLeaveMainLoop();
}

void Core::InitGLUT::idleCallback()
{
	//just idle, so continue displaying the most recent frame
	glutPostRedisplay();
}

void Core::InitGLUT::displayCallback()
{
	//make sure listener exists
	if (listener)
	{
		listener->notifyBeginFrame();
		listener->notifyDisplayFrame();

		glutSwapBuffers();

		listener->notifyEndFrame();
	}
	else //error
	{
		std::cout << "InitGLUT ERROR: \n\tin displayCallback():\tListener does not exist.\n";
	}
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0, 0.0, 0.0, 1.0); //clear to black
	//glutSwapBuffers(); //double buffered so we have to switch
}

void Core::InitGLUT::reshapeCallback(int width, int height)
{
	if (windowInformation.isReshapable == true)
	{
		if (listener)
		{
			listener->notifyReshape(width,
				height,
				windowInformation.width,
				windowInformation.height);
		}
		else
		{
			std::cout << "InitGLUT ERROR: \n\tin reshapeCallback():\tListener does not exist\n";
		}
		windowInformation.width = width;
		windowInformation.height = height;
			
	}
}

void Core::InitGLUT::closeCallback()
{
	close();
}

void Core::InitGLUT::enterFullscreen()
{
	glutFullScreen();
}

void Core::InitGLUT::exitFullscreen()
{
	glutLeaveFullScreen();
}

void Core::InitGLUT::printOpenGLInfo(const Core::WindowInfo& windowInfo,
	const Core::ContextInfo& contextInfo)
{
	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "***********************OpenGL Information***************************\n";
	std::cout << "GLUT:\tVendor : " << vendor << "\n";
	std::cout << "GLUT:\tRenderer : " << renderer << "\n";
	std::cout << "GLUT:\tVersion : " << version << "\n";
}

//set the listener
void Core::InitGLUT::setListener(Core::Listener*& newListener)
{
	listener = newListener;
}