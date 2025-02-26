#pragma once
#include "Singleton.h"
#include <iostream>
#include <string>

class DebugManager
{
private:
	DebugManager() = default;
	
public:
	static void Log(std::string message)
	{
		std::cout << message << std::endl;
	}

	static void LogError(std::string message)
	{
		std::cerr << "Error:" << message << std::endl;
	}
	static void LogWarning(std::string message)
	{
		std::cout << "Warning: " << message << std::endl;
	}

	static void LogInfo(std::string message)
	{
		std::cout << "Info: " << message << std::endl;
	}
};

