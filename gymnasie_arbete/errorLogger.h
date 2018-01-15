#pragma once

#include <fstream>
#include <iostream>
#include <string>

struct errorLogger {
	void log(const std::string& msg, const std::string& function) {
		std::ofstream log;
		log.open("error.txt", std::fstream::app);
		std::cout << " stuff ";
		if (log.is_open()) {
			std::string to_log;
			to_log = "Latest function visited: ";
			to_log += function;
			to_log += " Error message: ";
			to_log += msg;
			std::cout << to_log;
			log << to_log;
		} else {
			std::cout << "Unable to open errorlog." << std::endl;
			int a;
			std::cin >> a;
		}
		log.close();
	}
};