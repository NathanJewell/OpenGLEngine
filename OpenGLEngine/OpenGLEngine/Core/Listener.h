//Listener.h
#pragma once

namespace Core
{
	class Listener
	{
	public:
		virtual ~Listener() = 0;

		//drawing functions
		virtual void notifyBeginFrame() = 0;
		virtual void notifyDisplayFrame() = 0;
		virtual void notifyEndFrame() = 0;
		virtual void notifyReshape(int width,
			int height,
			int prevWidth,
			int prevHeight) = 0;

	};

	inline Listener::~Listener(){
		//nada right now
	}
}