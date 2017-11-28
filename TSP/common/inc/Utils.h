#ifndef UTILS_H_
#define UTILS_H_

#include <vector>

namespace Utils {
	typedef std::vector< std::vector<int> > matrix_t;

	matrix_t* matrix_builder(std::string const& filename);
	void matrix_dump(matrix_t const& v);


	struct Path
	{
		std::vector<int> path;
		long length = 0;
	};

	void path_dump(Path const&);
	void path_calc(Path&, matrix_t const& matrix);
	bool path_isValid(Path const&, matrix_t const& matrix);
	bool path_isValid_verbose(Path const&, matrix_t const& matrix);

	namespace TSP {
		Path* greedy(matrix_t*);
		Path* two_opt(Path*, matrix_t*);
	}
}

#endif // !UTILS_H_
