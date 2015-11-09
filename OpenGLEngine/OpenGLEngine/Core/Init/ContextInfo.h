//ContextInfo.h
#pragma once

namespace Core
{
	//openGL versions
	struct ContextInfo
	{
		int majorVersion, minorVersion;
		bool core;

		//default constructor
		ContextInfo()
		{
			majorVersion = 3;
			minorVersion = 3;
			core = true;
		}

		//verbose constructor
		ContextInfo(int majorVersion, int minorVersion, bool core)
		{
			this->majorVersion = majorVersion;
			this->minorVersion = minorVersion;
			this->core = core;
		}

		//copy constructor
		ContextInfo(const ContextInfo& contextInfo)
		{
			ContextInfo(contextInfo.majorVersion, contextInfo.minorVersion, contextInfo.core);
		}

		void operator=(const ContextInfo& contextInfo)
		{
			majorVersion = contextInfo.majorVersion;
			minorVersion = contextInfo.minorVersion;
			core = contextInfo.core;;
		}


	};
}