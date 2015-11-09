//LogManager.h
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

enum LogLevel{LOG_NONE, LOG_ERROR, LOG_WARNING, LOG_INFO, LOG_DEBUG};

namespace Managers
{
	class LogManager
	{
	public:

		LogManager();
		LogManager(LogLevel outputLevel); //minimal constructor
		LogManager(LogLevel consoleOutputLevel, LogLevel fileOutputLevel, bool fileOutput, const std::string& outputFileName); //verbose constructor
		~LogManager();

		static void SetConsoleOutputVerbosity(LogLevel level);
		static void SetFileOutputVerbosity(LogLevel level);
		static void FileOutput(bool output);	//true if file should be created
		static void SetOutputFile(const std::string& fileName);	//name (and location) of file

		static void Log(const LogLevel& level, const std::string& text);

	private:
		static void writeLogsToFile();

		static LogLevel consoleOutputVerbosity, fileOutputVerbosity;
		static bool writeToFileOnExit;
		static bool setPerformance; //disable all logging functionality
		static std::string logFileName;

		static std::vector<std::string> logs;
		static std::vector<LogLevel> logLevels;
	};
}