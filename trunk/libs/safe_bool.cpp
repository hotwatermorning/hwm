//          Copyright hotwatermorning 2011.
//  Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/minimal.hpp>

#include "safe_bool.hpp"

class safe_bool_test
    :   public hwm::safe_bool<safe_bool_test>
{
public:
    safe_bool_test(bool b)
        :   b_(b)
    {}

    bool boolean_test() const { return b_; }

private:
    bool    b_;
};

int test_main(int, char **)
{
    safe_bool_test test_t(true);
    safe_bool_test test_f(false);

    BOOST_CHECK(test_t);
    BOOST_CHECK(test_t != false);
    BOOST_CHECK(!!test_t);

    BOOST_CHECK(!test_f);
    BOOST_CHECK(test_f == false);
    BOOST_CHECK(!!!test_f);

    if(test_t) {
        if(test_f) {
            BOOST_CHECK(false);
        } else {
            //pass
        }
    } else {
        BOOST_CHECK(false);
    }

    return 0;
}
