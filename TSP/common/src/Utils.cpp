#include "Utils.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

std::vector< std::vector< int > >* Utils::matrix_builder(std::string const& filename) {
	auto matrix = new std::vector< std::vector< int > >();
	std::vector< int > tmp;
	std::ifstream file;

	try	{
		file.open(filename);
	}
	catch (const std::exception& e) {
		throw std::runtime_error("Error: Utils::matrix_builder: could not open file");
	}

	if (file.is_open() == false) {
		throw std::runtime_error("Error: Utils::matrix_builder: could not open file");
	}

	std::string line;
	char* token;
	while (std::getline(file, line))
	{
		matrix->push_back(tmp);
		std::istringstream line_stream(line);
		std::string token;
		while (std::getline(line_stream, token, ',')) {
			matrix->back().push_back(std::stoi(token));
		}
	}
	file.close();
	return matrix;
}

void Utils::matrix_dump(std::vector< std::vector< int > > const& v) {
	for (auto &line : v) {
		for (auto &i : line) {
			std::cout << i;
		}
		std::cout << std::endl;
	}
}