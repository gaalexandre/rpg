#include "lib.h"
#include <boost/ut.hpp>

int main () {
	using namespace boost::ut;
	expect(8_i == add(3, 5));
	return 0;
}
