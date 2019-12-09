///////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#include "../sf_performance.hpp"

void poly_tests_07()
{
#ifdef TEST_CPP_BIN_FLOAT
   time_proc("cpp_bin_float_50", test_polynomial<cpp_bin_float_50>);
#endif
}
