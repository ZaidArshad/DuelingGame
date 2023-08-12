#include "Logger.hpp"
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
	std::stringstream repeatCountMsg;

	// To prevent spamming of the same log message
	if (instance.lastLog != msg)
	{
		if (instance.lastLogCount > 0)
		{
			repeatCountMsg << "Repeated last line "
						   << instance.lastLogCount << "times\n";
			std::cout << repeatCountMsg.str();
			instance.outFile << repeatCountMsg.str();
		}

		instance.lastLogCount = 0;
		std::cout << msg << std::endl;
		instance.outFile << msg << std::endl;
	}
	else if (instance.lastLogCount < 100)
	{
		instance.lastLogCount++;
	}
	else if (instance.lastLogCount == 100)
	{
		repeatCountMsg << "Repeated last line 100+ times\n";
		std::cout << repeatCountMsg.str();
		instance.outFile << repeatCountMsg.str();
		instance.lastLogCount++;
	}
	instance.lastLog = msg;
}
