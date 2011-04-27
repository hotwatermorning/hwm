//          Copyright hotwatermorning 2011.
//  Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/minimal.hpp>
#include "../hwm/arithmetic.hpp"

int test_main(int, char**)
{
    namespace har = hwm::arithmetic;
    BOOST_CHECK(har::round_simple(0.00) == 0.0);
    BOOST_CHECK(har::round_simple(0.49) == 0.0);
    BOOST_CHECK(har::round_simple(0.50) == 1.0);
    BOOST_CHECK(har::round_simple(0.51) == 1.0);
    BOOST_CHECK(har::round_simple(1.00) == 1.0);
    BOOST_CHECK(har::round_simple(1.50) == 2.0);

    BOOST_CHECK(har::round_to_nearest_even(0.00) == 0.0);
    BOOST_CHECK(har::round_to_nearest_even(0.49) == 0.0);
    BOOST_CHECK(har::round_to_nearest_even(0.50) == 0.0);
    BOOST_CHECK(har::round_to_nearest_even(0.51) == 1.0);
    BOOST_CHECK(har::round_to_nearest_even(1.00) == 1.0);
    BOOST_CHECK(har::round_to_nearest_even(1.50) == 2.0);
    BOOST_CHECK(har::round_to_nearest_even(2.50) == 2.0);
    BOOST_CHECK(har::round_to_nearest_even(3.50) == 4.0);
    BOOST_CHECK(har::round_to_nearest_even(4.50) == 4.0);

    BOOST_CHECK(har::odd(3) == true);
    BOOST_CHECK(har::even(3) == false);
    BOOST_CHECK(har::odd(4) == false);
    BOOST_CHECK(har::even(4) == true);

    int             const in[] = { -5, 0, 5 };
    unsigned int    const un[] = { -5, 0, 5 };
    double          const fn[] = { -5, 0, 5 };

    //============================================================================//
    //  integral
    //============================================================================//
    BOOST_CHECK(har::sign(in[0]) == -1);
    BOOST_CHECK(har::sign(in[1]) == 0);
    BOOST_CHECK(har::sign(in[2]) == 1);
    BOOST_CHECK(har::sign(un[0]) == 1);
    BOOST_CHECK(har::sign(un[1]) == 0);
    BOOST_CHECK(har::sign(un[2]) == 1);
    BOOST_CHECK(har::sign(fn[0]) == -1);
    BOOST_CHECK(har::sign(fn[1]) == 0);
    BOOST_CHECK(har::sign(fn[2]) == 1);

    BOOST_CHECK(har::abs(in[0]) == 5);
    BOOST_CHECK(har::abs(in[1]) == 0);
    BOOST_CHECK(har::abs(in[2]) == 5);
    BOOST_CHECK(har::abs(un[0]) == (unsigned int)-5);
    BOOST_CHECK(har::abs(un[1]) == 0);
    BOOST_CHECK(har::abs(un[2]) == 5);
    BOOST_CHECK(har::abs(fn[0]) == 5);
    BOOST_CHECK(har::abs(fn[1]) == 0);
    BOOST_CHECK(har::abs(fn[2]) == 5);

    BOOST_CHECK(har::div_truncated(13, 4)   == 3);
    BOOST_CHECK(har::div_truncated(-13, 4)  == -3);
    BOOST_CHECK(har::div_truncated(13, -4)  == -3);
    BOOST_CHECK(har::div_truncated(-13, -4) == 3);
    BOOST_CHECK(har::mod_truncated(13, 4)   == 1);
    BOOST_CHECK(har::mod_truncated(-13, 4)  == -1);
    BOOST_CHECK(har::mod_truncated(13, -4)  == 1);
    BOOST_CHECK(har::mod_truncated(-13, -4) == -1);
    BOOST_CHECK(har::div_floored(13, 4)     == 3);
    BOOST_CHECK(har::div_floored(-13, 4)    == -4);
    BOOST_CHECK(har::div_floored(13, -4)    == -4);
    BOOST_CHECK(har::div_floored(-13, -4)   == 3);
    BOOST_CHECK(har::mod_floored(13, 4)     == 1);
    BOOST_CHECK(har::mod_floored(-13, 4)    == 3);
    BOOST_CHECK(har::mod_floored(13, -4)    == -3);
    BOOST_CHECK(har::mod_floored(-13, -4)   == -1);
    BOOST_CHECK(har::div_euclidean(13, 4)   == 3);
    BOOST_CHECK(har::div_euclidean(-13, 4)  == -4);
    BOOST_CHECK(har::div_euclidean(13, -4)  == -3);
    BOOST_CHECK(har::div_euclidean(-13, -4) == 4);
    BOOST_CHECK(har::mod_euclidean(13, 4)   == 1);
    BOOST_CHECK(har::mod_euclidean(-13, 4)  == 3);
    BOOST_CHECK(har::mod_euclidean(13, -4)  == 1);
    BOOST_CHECK(har::mod_euclidean(-13, -4) == 3);

    //============================================================================//
    //  floating point
    //============================================================================//
    BOOST_CHECK(har::fdiv_truncated(13, 4)  == 3);
    BOOST_CHECK(har::fdiv_truncated(-13, 4) == -3);
    BOOST_CHECK(har::fdiv_truncated(13, -4) == -3);
    BOOST_CHECK(har::fdiv_truncated(-13, -4) == 3);
    BOOST_CHECK(har::fmod_truncated(13, 4)  == 1);
    BOOST_CHECK(har::fmod_truncated(-13, 4) == -1);
    BOOST_CHECK(har::fmod_truncated(13, -4) == 1);
    BOOST_CHECK(har::fmod_truncated(-13, -4)== -1);
    BOOST_CHECK(har::fdiv_floored(13, 4)    == 3);
    BOOST_CHECK(har::fdiv_floored(-13, 4)   == -4);
    BOOST_CHECK(har::fdiv_floored(13, -4)   == -4);
    BOOST_CHECK(har::fdiv_floored(-13, -4)  == 3);
    BOOST_CHECK(har::fmod_floored(13, 4)    == 1);
    BOOST_CHECK(har::fmod_floored(-13, 4)   == 3);
    BOOST_CHECK(har::fmod_floored(13, -4)   == -3);
    BOOST_CHECK(har::fmod_floored(-13, -4)  == -1);
    BOOST_CHECK(har::fdiv_euclidean(13, 4)  == 3);
    BOOST_CHECK(har::fdiv_euclidean(-13, 4) == -4);
    BOOST_CHECK(har::fdiv_euclidean(13, -4) == -3);
    BOOST_CHECK(har::fdiv_euclidean(-13, -4)== 4);
    BOOST_CHECK(har::fmod_euclidean(13, 4)  == 1);
    BOOST_CHECK(har::fmod_euclidean(-13, 4) == 3);
    BOOST_CHECK(har::fmod_euclidean(13, -4) == 1);
    BOOST_CHECK(har::fmod_euclidean(-13, -4)== 3);

    BOOST_CHECK(har::fdiv_truncated(12, 4)  == 3);
    BOOST_CHECK(har::fdiv_truncated(-12, 4) == -3);
    BOOST_CHECK(har::fdiv_truncated(12, -4) == -3);
    BOOST_CHECK(har::fdiv_truncated(-12, -4) == 3);
    BOOST_CHECK(har::fmod_truncated(12, 4)  == 0);
    BOOST_CHECK(har::fmod_truncated(-12, 4) == 0);
    BOOST_CHECK(har::fmod_truncated(12, -4) == 0);
    BOOST_CHECK(har::fmod_truncated(-12, -4)== 0);
    BOOST_CHECK(har::fdiv_floored(12, 4)    == 3);
    BOOST_CHECK(har::fdiv_floored(-12, 4)   == -3);
    BOOST_CHECK(har::fdiv_floored(12, -4)   == -3);
    BOOST_CHECK(har::fdiv_floored(-12, -4)  == 3);
    BOOST_CHECK(har::fmod_floored(12, 4)    == 0);
    BOOST_CHECK(har::fmod_floored(-12, 4)   == 0);
    BOOST_CHECK(har::fmod_floored(12, -4)   == 0);
    BOOST_CHECK(har::fmod_floored(-12, -4)  == 0);
    BOOST_CHECK(har::fdiv_euclidean(12, 4)  == 3);
    BOOST_CHECK(har::fdiv_euclidean(-12, 4) == -3);
    BOOST_CHECK(har::fdiv_euclidean(12, -4) == -3);
    BOOST_CHECK(har::fdiv_euclidean(-12, -4)== 3);
    BOOST_CHECK(har::fmod_euclidean(12, 4)  == 0);
    BOOST_CHECK(har::fmod_euclidean(-12, 4) == 0);
    BOOST_CHECK(har::fmod_euclidean(12, -4) == 0);
    BOOST_CHECK(har::fmod_euclidean(-12, -4)== 0);

    BOOST_CHECK(har::fdiv_truncated(14, 4)  == 3);
    BOOST_CHECK(har::fdiv_truncated(-14, 4) == -3);
    BOOST_CHECK(har::fdiv_truncated(14, -4) == -3);
    BOOST_CHECK(har::fdiv_truncated(-14, -4) == 3);
    BOOST_CHECK(har::fmod_truncated(14, 4)  == 2);
    BOOST_CHECK(har::fmod_truncated(-14, 4) == -2);
    BOOST_CHECK(har::fmod_truncated(14, -4) == 2);
    BOOST_CHECK(har::fmod_truncated(-14, -4)== -2);
    BOOST_CHECK(har::fdiv_floored(14, 4)    == 3);
    BOOST_CHECK(har::fdiv_floored(-14, 4)   == -4);
    BOOST_CHECK(har::fdiv_floored(14, -4)   == -4);
    BOOST_CHECK(har::fdiv_floored(-14, -4)  == 3);
    BOOST_CHECK(har::fmod_floored(14, 4)    == 2);
    BOOST_CHECK(har::fmod_floored(-14, 4)   == 2);
    BOOST_CHECK(har::fmod_floored(14, -4)   == -2);
    BOOST_CHECK(har::fmod_floored(-14, -4)  == -2);
    BOOST_CHECK(har::fdiv_euclidean(14, 4)  == 3);
    BOOST_CHECK(har::fdiv_euclidean(-14, 4) == -4);
    BOOST_CHECK(har::fdiv_euclidean(14, -4) == -3);
    BOOST_CHECK(har::fdiv_euclidean(-14, -4)== 4);
    BOOST_CHECK(har::fmod_euclidean(14, 4)  == 2);
    BOOST_CHECK(har::fmod_euclidean(-14, 4) == 2);
    BOOST_CHECK(har::fmod_euclidean(14, -4) == 2);
    BOOST_CHECK(har::fmod_euclidean(-14, -4)== 2);


    //work as http://en.wikipedia.org/wiki/Modulo_operation
    BOOST_CHECK(13  == har::div_truncated   (13, 4)     *   4   + har::mod_truncated(13, 4)     );
    BOOST_CHECK(-13 == har::div_truncated   (-13, 4)    *   4   + har::mod_truncated(-13, 4)    );
    BOOST_CHECK(13  == har::div_truncated   (13, -4)    *   -4  + har::mod_truncated(13, -4)    );
    BOOST_CHECK(-13 == har::div_truncated   (-13, -4)   *   -4  + har::mod_truncated(-13, -4)   );
    BOOST_CHECK(13  == har::div_floored     (13, 4)     *   4   + har::mod_floored  (13, 4)     );
    BOOST_CHECK(-13 == har::div_floored     (-13, 4)    *   4   + har::mod_floored  (-13, 4)    );
    BOOST_CHECK(13  == har::div_floored     (13, -4)    *   -4  + har::mod_floored  (13, -4)    );
    BOOST_CHECK(-13 == har::div_floored     (-13, -4)   *   -4  + har::mod_floored  (-13, -4)   );
    BOOST_CHECK(13  == har::div_euclidean   (13, 4)     *   4   + har::mod_euclidean(13, 4)     );
    BOOST_CHECK(-13 == har::div_euclidean   (-13, 4)    *   4   + har::mod_euclidean(-13, 4)    );
    BOOST_CHECK(13  == har::div_euclidean   (13, -4)    *   -4  + har::mod_euclidean(13, -4)    );
    BOOST_CHECK(-13 == har::div_euclidean   (-13, -4)   *   -4  + har::mod_euclidean(-13, -4)   );

    return 0;
}
