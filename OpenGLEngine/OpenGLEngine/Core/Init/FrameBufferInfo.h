//FrameBufferInfo.h
#pragma once

#include "..\..\Dependencies\glew\glew.h"
#include "..\..\Dependencies\freeglut\freeglut.h"

namespace Core
{
	struct FramebufferInfo
	{
		unsigned int flags;
		bool msaa;

		FramebufferInfo()
		{
			flags = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
			msaa = false;
		}

		FramebufferInfo(bool color, bool depth, bool stencil, bool useMSAA)
		{
			flags = GLUT_DOUBLE;
			if (color)
				flags |= GLUT_RGBA | GLUT_ALPHA;
			if (depth)
				flags |= GLUT_DEPTH;
			if (stencil)
				flags |= GLUT_STENCIL;
			if (useMSAA)
				flags |= GLUT_MULTISAMPLE;

			msaa = useMSAA;
		}

		FramebufferInfo(const FramebufferInfo& framebufferInfo)
		{
			flags = framebufferInfo.flags;
			msaa = framebufferInfo.msaa;
		}

		void operator=(const FramebufferInfo& framebufferInfo)
		{
			flags = framebufferInfo.flags;
			msaa = framebufferInfo.msaa;
		}
	};
}