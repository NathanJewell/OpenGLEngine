//InitGLUT.h
#pragma once

#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include <iostream>
#include "InitGLEW.h"
#include "../Listener.h"

namespace Core
{
	class InitGLUT
	{
	public:
		static void init(const Core::WindowInfo& window,
			const Core::ContextInfo& context,
			const Core::FramebufferInfo& framebufferInfo);

		static void run();
		static void close();

		void enterFullscreen();
		void exitFullscreen();

		static void printOpenGLInfo(const Core::WindowInfo& windowInfo,
			const Core::ContextInfo& contextInfo);

		static void setListener(Core::Listener*& listener);

	private:
		static void idleCallback();
		static void displayCallback();
		static void reshapeCallback(int width, int height);
		static void closeCallback();

		static Core::Listener* listener;
		static Core::WindowInfo windowInformation;

	};
}