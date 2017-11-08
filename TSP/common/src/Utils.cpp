#include "Utils.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

Utils::matrix_t* Utils::matrix_builder(std::string const& filename) {
	auto matrix = new Utils::matrix_t();
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

void Utils::matrix_dump(matrix_t const& v) {
	for (auto &line : v) {
		for (auto &i : line) {
			std::cout << i;
		}
		std::cout << std::endl;
	}
}

void Utils::path_dump(Path const& p) {
	std::ofstream file;
	unsigned long long time = std::chrono::system_clock::now().time_since_epoch().count();

	std::stringstream filename;
	filename << "path_output_";
	filename << time;
	filename << ".txt";
	try
	{
		file.open(filename.str());
	}
	catch (const std::exception&e)
	{
		throw std::runtime_error("Error: Utils::path_dump: could not create output file");
	}
	if (file.is_open() == false) {
		throw std::runtime_error("Error: Utils::path_dump: could not create output file");
	}
	for (auto& i : p.path) file << i+1 << std::endl;
	file.close();

	std::stringstream filename2;
	filename2 << "path_output_length_";
	filename2 << time;
	filename2 << ".txt";
	try
	{
		file.open(filename2.str());
	}
	catch (const std::exception&e)
	{
		throw std::runtime_error("Error: Utils::path_dump: could not create output file");
	}
	if (file.is_open() == false) {
		throw std::runtime_error("Error: Utils::path_dump: could not create output file");
	}
	file << p.length<< std::endl;
	file.close();
}