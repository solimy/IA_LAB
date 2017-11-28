#include "Utils.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <set>

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

void Utils::path_calc(Utils::Path& path, Utils::matrix_t const& matrix) {
	path.length = 0;
	for (long i = 0, j = path.path.size() - 1; i < j; ++i) {
		path.length += matrix[path.path[i]][path.path[i+1]];
	}
}

bool Utils::path_isValid(Utils::Path const& p, Utils::matrix_t const& matrix) {
	std::set<int> cities;
	std::vector<int> tmp;

	std::cout << "verifying path size" << std::endl;
	if (p.path.size() != matrix.size() + 1) {
		std::cout << "path size: KO" << std::endl;
		return false;
		}
	std::cout << "path size: OK" << std::endl;
	std::cout << "verifying if path loops" << std::endl;
	if (p.path.front() != p.path.back()) {
		std::cout << "path loop: KO" << std::endl;
		return false;
	}
	std::cout << "path loop: OK" << std::endl;
	tmp.assign(p.path.begin(), p.path.end() - 1);
	std::cout << "verifying city duplication" << std::endl;
	for (int i = 0, j = matrix.size(); i < j; ++i) cities.insert(i);
	for (int i = 0, j = tmp.size(); i < j; ++i) {
		int city = tmp[i];
		if (cities.find(city) == cities.end()) {
			std::cout << "duplicated city: index[" << i << "] = " << city << std::endl;
			//return false;
		}
		else cities.erase(city);
	}
	std::cout << "looking for missing cities in path" << std::endl;
	if (cities.size() > 0) {
		for (int city : cities) std::cout << "missing city: " << city << std::endl;
		return false;
	}
	return true;
}
