#include "Logger.h"

#include "Error/GLErrorMaps.h"

#include <iostream>
#include <sstream>

Logger Logger::instance;

Logger::Logger()
{
	instance.outFile = std::ofstream("log.txt");
}

void Logger::log(std::string msg)
{
	std::cout << msg << std::endl;
	instance.outFile << msg << std::endl;
}

void Logger::log(GLError err)
{
	// Avoids spam from same object error
	if (err.id != instance.lastErr.id)
	{
		std::stringstream log;
		log << "[OpenGL Error] ("
			<< "Severity: " << GLErrorSeverity[err.severity]
			<< " Source: " << GLErrorSources[err.source]
			<< " Type: " << GLErrorTypes[err.type]
			<< " ID: " << err.id
			<< " Message: " << err.message
			<< ")" << std::endl;
		Logger::log(log.str());
	}
	instance.lastErr = err;
}