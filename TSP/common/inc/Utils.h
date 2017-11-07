#ifndef UTILS_H_
#define UTILS_H_

#include <vector>

namespace Utils {
	typedef std::vector< std::vector<int> > matrix_t;

	matrix_t* matrix_builder(std::string const& filename);
	void matrix_dump(matrix_t const& v);
}

#endif // !UTILS_H_
