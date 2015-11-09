//LogManager.cpp
#include "LogManager.h"

using namespace Managers;

//initialize static variables
LogLevel LogManager::consoleOutputVerbosity = LOG_ERROR;
LogLevel LogManager::fileOutputVerbosity = LOG_NONE;
bool LogManager::writeToFileOnExit = false;
bool LogManager::setPerformance = false; //disable all logging functionality
std::string LogManager::logFileName = "";

std::vector<std::string> LogManager::logs;
std::vector<LogLevel> LogManager::logLevels;

LogManager::LogManager(){} //default constructor

LogManager::LogManager(LogLevel level)
{
	SetConsoleOutputVerbosity(level);
	FileOutput(false); //default is to not write to file
}

LogManager::LogManager(LogLevel consoleOutputLevel, LogLevel fileOutputLevel, bool fileOutput, const std::string& fileName)
{
	SetConsoleOutputVerbosity(consoleOutputLevel);
	SetFileOutputVerbosity(fileOutputLevel);
	FileOutput(fileOutput);
	SetOutputFile(fileName);
}

LogManager::~LogManager()
{
	if (writeToFileOnExit)
	{
		writeLogsToFile();
	}
}

void LogManager::SetConsoleOutputVerbosity(LogLevel level)
{
	consoleOutputVerbosity = level;
}


void LogManager::SetFileOutputVerbosity(LogLevel level)
{
	fileOutputVerbosity = level;
}

void LogManager::FileOutput(bool output)
{
	writeToFileOnExit = output;
	if (writeToFileOnExit){ Log(LOG_INFO, "File output set to true."); }
	else{ Log(LOG_INFO, "File output set to false."); }
	
}

void LogManager::SetOutputFile(const std::string& fileName)
{
	logFileName = fileName;
	Log(LOG_INFO, "Output file set to \"" + logFileName + "\".");
}

void LogManager::Log(const LogLevel& level, const std::string& text) //automatically prefix with level and push to vectors, output if needed
{
	//option for totally ignoring things
	if (setPerformance)
	{
		return;
	}
	else if ((consoleOutputVerbosity >= level || fileOutputVerbosity >= level))
	{
		logLevels.push_back(level);
		std::string tmp = text;
		switch (level) //append prefixes
		{
		case LOG_ERROR:		tmp = "ERROR: " + text; break;
		case LOG_WARNING:	tmp = "WARNING: " + text; break;
		case LOG_INFO:		tmp = "INFO: " + text; break;
		case LOG_DEBUG:		tmp = "DEBUG: " + text; break;

		}
		tmp += "\n"; //add new line to any log
		logs.push_back(tmp); //FEATURE ADDITION: add ifSaveLogs option
		if (consoleOutputVerbosity >= level)
		{
			std::cout << logs[logs.size() - 1]; //print the most recent log
		}
	}
}

void LogManager::writeLogsToFile()
{
	std::string finalFileName;
	int i = 0;
	while (true) //check if file exists and change the place we try to make the file if it allready exists
	{

		std::ifstream f(logFileName.c_str());
		if (f.good())
		{
			f.close();
			finalFileName = logFileName + std::to_string(i);
		}
		else
		{
			break;
		}
		
	}
	std::ofstream outputFile(finalFileName.c_str());
	//FEATURE ADDITION: add some sort of standardized header to file

	for (int i = 0; i < logs.size(); i++)
	{
		if (logLevels[i] >= fileOutputVerbosity)
		{
			outputFile << logs[i];
		}
	}
	
	outputFile.close();

	return;

}