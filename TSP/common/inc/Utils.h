#ifndef UTILS_H_
#define UTILS_H_

#include <vector>

namespace Utils {
	std::vector< std::vector<int> >* matrix_builder(std::string const& filename);
	void matrix_dump(std::vector< std::vector< int > > const& v);
}

#endif // !UTILS_H_
