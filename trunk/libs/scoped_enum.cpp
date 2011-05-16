//          Copyright hotwatermorning 2011.
//  Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/minimal.hpp>
#include "../hwm/scoped_enum.hpp"

namespace color_detail {

struct color_enum_base1
{
    enum enum_type {
        red, green, blue
    };
};

struct color_enum_base2
{
    enum enum_type {
        cyan, magenta, yellow
    };
};

typedef hwm::scoped_enum<color_enum_base1>  color1;
typedef hwm::scoped_enum<color_enum_base2>  color2;

}   //namespace color_detail

int test_main(int, char**)
{
    typedef color_detail::color1 color1;
    typedef color_detail::color2 color2;

    {
        color1 const c1 = color1::red;      //construct
        color1 const c1_copy = c1;          //copy-construct
        color1 c1_assign;
        c1_assign = c1;                     //assignment

        //swap
        color1 c1_swap1 = color1::green;
        color1 c1_swap2 = color1::blue;
        swap(c1_swap1, c1_swap2);
        BOOST_CHECK(c1_swap1 == color1::blue);
        BOOST_CHECK(c1_swap2 == color1::green);

        //color2 const c2 = color1::red;    //expected compilation error
        //color2 const c2_copy = c1;        //expected compilation error
        //color2 const c2_assign = c1;      //expected compilation error
        color2 c2_swap1 = color2::cyan;
        //swap(c1_swap1, c2_swap1);         //expected compilation error
    }
    
    {
        color1 const c1 = color1::red;

        //int conversion
        int const n1 = c1;

        //not int -> color1
        //color1 const c1_ = n1;            //expected compilation error
    }

    
    {
        color1 const c1_red     = color1::red;
        color1 const c1_green   = color1::green;

        //comparison with same type
        BOOST_CHECK(c1_red == c1_green);
        BOOST_CHECK(!(c1_red == c1_green));
        BOOST_CHECK(!(c1_red != c1_green));
        BOOST_CHECK(c1_red != c1_green);

        //comparison with base enum
        BOOST_CHECK(  c1_red == color1::red   );
        BOOST_CHECK(!(c1_red == color1::green));
        BOOST_CHECK(!(c1_red != color1::red  ));
        BOOST_CHECK(  c1_red != color1::green );
        BOOST_CHECK(  color1::red   == c1_red );
        BOOST_CHECK(!(color1::green == c1_red));
        BOOST_CHECK(!(color1::red   != c1_red));
        BOOST_CHECK(  color1::green != c1_red );

        //comparison with another type
        //BOOST_CHECK(c1_red == 1);             //expected compilation error
        //BOOST_CHECK(!(c1_red == 2));          //expected compilation error
        //BOOST_CHECK(!(c1_red != 1));          //expected compilation error
        //BOOST_CHECK(c1_red != 2);             //expected compilation error
        //BOOST_CHECK(1 == c1_red);             //expected compilation error
        //BOOST_CHECK(!(2 == c1_red));          //expected compilation error
        //BOOST_CHECK(!(1 != c1_red));          //expected compilation error
        //BOOST_CHECK(2 != c1_red);             //expected compilation error

        color2 const c2_cyan    = color2::cyan;
        //BOOST_CHECK(c1_red == c2_cyan);           //expected compilation error
        //BOOST_CHECK(c1_red != c2_cyan);           //expected compilation error
    }

    {
        //just enum value comparison
        BOOST_CHECK(color1::red != color1::green);
        BOOST_CHECK(color1::red != color2::cyan);   //unfortunately compilation passed...(gcc will issue a warning).
    }

    return 0;
}
