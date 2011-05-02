//          Copyright hotwatermorning 2011.
//  Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef HWM_SAFEBOOL_HPP
#define HWM_SAFEBOOL_HPP

//! @file

namespace hwm {

//! @brief A Helper class that provided a easy-way to become a derived class evaluable in the Boolean context.

//! @note please implement a function `bool boolean_test() const' as a public member in derived class.
//! @class safe_bool
template<typename Derived>
struct safe_bool
{
protected:
    safe_bool () {}

private:
    typedef safe_bool<Derived> this_safe_bool_type;
    
public:
    //! this is used to evaluate in boolean context.
    typedef void    (this_safe_bool_type::*unspecified_bool_type)   () const;
    void            safe_bool_true          () const {}

    operator        unspecified_bool_type   () const
    {
        return 
            static_cast<Derived const &>(*this).boolean_test()
            ?   &this_safe_bool_type::safe_bool_true
            :   0;
    }

    //! operator! is redundant, but some compilers need it.
    bool operator!  () const
    {
        return !static_cast<unspecified_bool_type const>(*this);
    }
};

}   //namespace hwm

#endif  //HWM_SAFEBOOL_HPP
