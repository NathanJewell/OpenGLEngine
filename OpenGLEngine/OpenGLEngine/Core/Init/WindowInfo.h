//WindowInfo.h
#pragma once
#include <string>

namespace Core
{
	struct WindowInfo
	{
		std::string name;
		int width, height;
		int positionX, positionY;
		bool isReshapable;

		WindowInfo()
		{
			//default values for default constructor
			name = "OpenGL Engine v 0.001";
			width = 800; height = 600;
			positionX = 300;
			positionY = 300;
			isReshapable = true;
		}

		//verbose constructor
		WindowInfo(std::string startName, int startPosX, int startPosY, int startWidth, int startHeight, bool startIsReshapable)
		{
			//set member variables
			name = startName;
			width = startWidth;
			height = startHeight;
			positionX = startPosX;
			positionY = startPosY;
			isReshapable = startIsReshapable;
			
		}

		//copy constructor
		WindowInfo(const WindowInfo& windowInfo)
		{
			WindowInfo(windowInfo.name,
				windowInfo.positionX,
				windowInfo.positionY,
				windowInfo.width,
				windowInfo.height,
				windowInfo.isReshapable);
		}

		void operator=(const WindowInfo& windowInfo)
		{
			name = windowInfo.name;
			width = windowInfo.width;
			height = windowInfo.height;
			positionX = windowInfo.positionX;
			positionY = windowInfo.positionY;
			isReshapable = windowInfo.isReshapable;
		}
	};
}