//          Copyright hotwatermorning 2011.
//  Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <string>
#include <boost/test/minimal.hpp>
#include <boost/current_function.hpp>

#include "deep_copy_ptr.hpp"

struct A
{
    int     i;

    A() : i(0)
    {
        std::cout << BOOST_CURRENT_FUNCTION << std::endl;
    }

    A(A const &a) : i(a.i)
    {
        std::cout << BOOST_CURRENT_FUNCTION << std::endl;
    }

    A& operator= (A const &a)
    {
        std::cout << BOOST_CURRENT_FUNCTION << std::endl;
        i = a.i;

        return *this;
    }

    void swap(A &rhs)
    {
        using std::swap;
        swap(i, rhs.i);
    }

    bool    operator==  (A const &rhs) const { return i == rhs.i; }

    virtual void foo() = 0;
};

struct B
    :   public A
{
    std::string s;

    B(char const *c = "") : s(c)
    {
        std::cout << BOOST_CURRENT_FUNCTION << std::endl;
    }

    B(B const &rhs)
    :   A(rhs)
    ,   s(rhs.s)
    {
        std::cout << BOOST_CURRENT_FUNCTION << std::endl;
    }

    B& operator= (B const &rhs)
    {
        std::cout << BOOST_CURRENT_FUNCTION << std::endl;
        B(rhs).swap(*this);
        return *this;
    }

    void    swap(B &rhs)
    {
        A::swap(rhs);
        using std::swap;
        swap(s, rhs.s);
    }

    bool operator==(B const &rhs) const
    {
        return
            static_cast<A const &>(*this) == static_cast<A const &>(rhs) &&
            s == rhs.s;
    }

    void foo() {}
};

struct C
    :   public B
{
    C(char const *c = "", int num = 0)
        :   B(c)
        ,   num_(num)
    {
        std::cout << BOOST_CURRENT_FUNCTION << std::endl;
    }

    C(C const &rhs)
        :   B(rhs)
        ,   num_(rhs.num_)
    {
        std::cout << BOOST_CURRENT_FUNCTION << std::endl;
    }

    C& operator= (C const &rhs)
    {
        std::cout << BOOST_CURRENT_FUNCTION << std::endl;

        C(rhs).swap(*this);
        return *this;
    }

    bool operator==(C const &rhs) const
    {
        return
            static_cast<B const &>(*this) == static_cast<B const &>(rhs) &&
            num_ == rhs.num_;
    }

public:
    int num_;
};

int test_main(int argc, char **argv)
{
    {
        // create
        hwm::deep_copy_ptr<C>   cp1(new C);
        // copy construct
        hwm::deep_copy_ptr<C>   cp2(cp1);
        // assignment
        hwm::deep_copy_ptr<C>   cp3;
        cp3 = cp2;
        // swap
        hwm::deep_copy_ptr<C>   cp4;
        swap(cp4, cp3);
    }

    {
        hwm::deep_copy_ptr<B>   bp1(new B("this is B"));
        hwm::deep_copy_ptr<B>   bp2(new B("this is also B, but having different string"));

        // comparable
        BOOST_CHECK(bp1 == bp1);
        BOOST_CHECK(bp1 != bp2);
    }

    {
        int const   num1 = 1;
        int const   num2 = 2;
        int const   num3 = 3;
        int const   num4 = 4;
        int const   num5 = 5;
    
        hwm::deep_copy_ptr<B>   cp1(new C("this is C contained as B", num1));
        hwm::deep_copy_ptr<B>   cp2(new C("this is also C, but having different string", num2));

        // deep comparable but comparison context is just B.
        BOOST_CHECK(cp1 == cp1);
        BOOST_CHECK(cp1 != cp2);
        
        hwm::deep_copy_ptr<B>   cp3(new C("this is C having same string", num3));
        hwm::deep_copy_ptr<B>   cp4(new C("this is C having same string", num4));
        hwm::deep_copy_ptr<B>   cp5(new C("this is C having same string", num5));
        cp5->i = cp4->i + 1;
    
        BOOST_CHECK(cp3 == cp4);
        BOOST_CHECK(cp4 != cp5);
    }

    {
        int const   num6 = 6;
        hwm::deep_copy_ptr<B>   cp6(new C("this is C contained as B", num6));
        hwm::deep_copy_ptr<B>   cp7;
        cp7 = cp6;

        // deep copyable
        BOOST_CHECK(cp6 == cp7);
        // cp6 was copied as C, because cp6 was constructed as C. so all C's member was copied to cp7.
        BOOST_CHECK(static_cast<C *>(&*cp6)->num_ == static_cast<C *>(&*cp7)->num_);
    }

    return 0;
}
