//          Copyright hotwatermorning 2011.
//  Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef HWM_SCOPED_ENUM_HPP
#define HWM_SCOPED_ENUM_HPP

//! @file

#include <boost/static_assert.hpp>
#include <boost/operators.hpp>
#include <boost/type_traits/is_enum.hpp>

namespace hwm {

//! @tparam enum_base has an enum type which named enum_type.
template<typename enum_base>
struct scoped_enum
    :   enum_base
    ,   boost::equality_comparable<scoped_enum<enum_base>
    ,   boost::equality_comparable<scoped_enum<enum_base>, typename enum_base::enum_type> >
{
    typedef scoped_enum<enum_base>  this_type;

    typedef typename enum_base::enum_type enum_type;
    BOOST_STATIC_ASSERT(boost::is_enum<enum_type>::value);

    scoped_enum() : value_() {}
    scoped_enum(enum_type value) : value_(value) {}

    template<typename T>
    operator T() const { return value_; }

    bool operator== (this_type const &rhs) const { return value_ == rhs.value_; }
    bool operator== (enum_type const rhs) const { return value_ == rhs; }

    void    swap(this_type &rhs) throw()
    {
        enum_type tmp = value_;
        value_ = rhs.value_;
        rhs.value_ = tmp;
    }
    
private:
    enum_type   value_;
};

template<typename T>
void swap(scoped_enum<T> &lhs, scoped_enum<T> &rhs) { lhs.swap(rhs); }

}   //namespace hwm

#endif  //HWM_SCOPED_ENUM_HPP
