//          Copyright hotwatermorning 2011.
//  Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef HWM_ARITHMETIC_HPP
#define HWM_ARITHMETIC_HPP

//! hwm.Arithmetic
//! abs, sign, modulus, division
//! @file

#include <cmath>
#include <boost/assert.hpp>
#include <boost/mpl/and.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/utility/enable_if.hpp>

namespace hwm { namespace arithmetic {

    //! @cond DETAIL
    namespace detail
    {
        template<typename T>
        T abs_switch    (
            T const t,
            typename boost::enable_if<
                boost::mpl::and_<
                    boost::is_signed<T>,
                    boost::is_integral<T>
                > >::type* = 0 )
        {
            return ::abs(t);
        }

        template<typename T>
        T abs_switch    (
            T const t,
            typename boost::enable_if<
                boost::mpl::and_<
                    boost::is_unsigned<T>,
                    boost::is_integral<T>
                > >::type* = 0 )
        {
            return t;
        }

        template<typename T>
        T abs_switch    (
            T const t,
            typename boost::enable_if<
                boost::is_floating_point<T>
            >::type* = 0 )
        {
            return ::fabs(t);
        }
    }   //namespace detail
    //! @endcond
    
    //! @brief round simply
    //! @return floor(t + 0.5) casted as type of t.
    template<typename T>
    T   round_simple(T f)
    {
        return static_cast<T>(floor(static_cast<double>(f) + 0.5));
    }

    //! @brief round to nearest even.
    //! also known as banker's round.
    //! @return floor(t + 0.5) but when reminder is just 0.5, the return will be rounded to nearest even.
    //! and the return is casted as type of t.
    template<typename T>
    T       round_to_nearest_even   (T f)
    {
        double int_part;
        double const frac_part = modf(f, &int_part);
        if      ( frac_part < 0.5 )     { return static_cast<T>(int_part); }
        else if ( frac_part == 0.5 )    { return static_cast<T>(int_part + fmod(int_part, 2.0)); }
        else                            { return static_cast<T>(int_part + 1.0); }
    }

    //! @return if `t' is odd.
    //! the behaviour is unspecified if operator % is overloaded.
    template<typename T>
    bool    odd                     (T const &t) { return t % 2 != 0; }

    //! @return if `t' is even.
    //! the behaviour is unspecified if operator % is overloaded.
    template<typename T>
    bool    even                    (T const &t) { return t % 2 == 0; }

    //! @brief return the signature as 1, 0 or -1
    //! @return return 1 if `t' is positive, -1 if `t' is negative, and 0 if `t' is zero.
    template<typename T>
    int     sign                    (T const &t) { return ((t>0)*1)+((t<0)*(-1)); }

    //! @return return abs(t) if `t' is integral, return fabs(t) if `t' is floating point number.
    template<typename T>
    T       abs                     (T const &t) { return detail::abs_switch(t); }

    //============================================================================//
    //! @defgroup modulus Modulus Operations.
    //! <a href ="http://en.wikipedia.org/wiki/Modulo_operation">see also</a>
    //! @{
    //============================================================================//
    
    //fmod(x, y) : x = i * y + f, return f;
    //sign(f) == sign(x), abs(f) < abs(y)

    //! @brief modulus operation for integral value.
    //! @return return modulo by truncated division.
    template<typename T>
    T       mod_truncated           (T const &dividend, T const &divisor)
    {
        BOOST_ASSERT(divisor != 0);
        return
            (detail::abs_switch(dividend) % detail::abs_switch(divisor)) *
            sign(dividend);
    }

    //! @brief modulus operation for floating point value.
    //! @return return modulo by truncated division.
    inline
    double  fmod_truncated          (double dividend, double divisor)
    {
        BOOST_ASSERT(divisor != 0);
        return fmod(dividend, divisor);
    }

    //! @brief modulus operation for integral value.
    //! @return return modulo by floored division.
    template<typename T>
    T       mod_floored             (T const &dividend, T const &divisor)
    {
        BOOST_ASSERT(divisor != 0);

        bool const is_dividend_negative = dividend < 0;
        bool const is_divisor_negative  = divisor < 0;
        bool const exclusive_sign       = is_dividend_negative ^ is_divisor_negative;
        
        T const mod_tr = mod_truncated(dividend, divisor);

        return
            mod_tr +
            (exclusive_sign * (mod_tr != 0) * divisor);
    }

    //! @brief modulus operation for floating point value.
    //! @return return modulo by floored division.
    inline
    double  fmod_floored            (double dividend, double divisor)
    {   
        BOOST_ASSERT(divisor != 0);

        bool const is_dividend_negative = dividend < 0;
        bool const is_divisor_negative  = divisor < 0;
        bool const exclusive_sign       = is_dividend_negative ^ is_divisor_negative;

        double const mod_tr = fmod_truncated(dividend, divisor);

        return
            mod_tr +
            (exclusive_sign * (mod_tr != 0) * divisor);
    }

    //! @brief modulus operation for integral value.
    //! @return return modulo by Euclidean division.
    template<typename T>
    T       mod_euclidean           (T const &dividend, T const &divisor)
    {
        BOOST_ASSERT(divisor != 0);

        bool const  is_dividend_negative    = dividend < 0;
        T const mod_tr = mod_truncated(dividend, divisor);

        return
            mod_tr +
            (is_dividend_negative * (mod_tr != 0) * detail::abs_switch(divisor));
    }

    //! @brief modulus operation for floating point value.
    //! @return return modulo by Euclidean division.
    inline
    double  fmod_euclidean          (double dividend, double divisor)
    {
        BOOST_ASSERT(divisor != 0);
        bool const  is_dividend_negative    = dividend < 0;

        double const mod_tr = fmod_truncated(dividend, divisor);

        return
            mod_tr +
            (is_dividend_negative * (mod_tr != 0) * detail::abs_switch(divisor));
    }

    //============================================================================//
    //! @}
    //  enddef of modulus
    //============================================================================//

    //============================================================================//
    //! @defgroup division Division Operations.
    //! <a href="http://en.wikipedia.org/wiki/Modulo_operation">see also</a>
    //! @{
    //============================================================================//

    //! @brief division operation for integral value.
    //! @return return quatient by truncated division.
    template<typename T>
    T       div_truncated           (T const &dividend, T const &divisor)
    {
        BOOST_ASSERT(divisor != 0);
        return
            (detail::abs_switch(dividend) / detail::abs_switch(divisor)) *
            sign(dividend) *
            sign(divisor);
    }

    //! @brief division operation for floating point value.
    //! @return return quatient by truncated division.
    inline
    double  fdiv_truncated          (double dividend, double divisor)
    {
        BOOST_ASSERT(divisor != 0);
        double const division = (detail::abs_switch(dividend) / detail::abs_switch(divisor));
        return
            floor(division) *
            sign(dividend) *
            sign(divisor);
    }

    //! @brief division operation for integral value.
    //! @return return quatient by floored division.
    template<typename T>
    T       div_floored             (T const &dividend, T const &divisor)
    {
        BOOST_ASSERT(divisor != 0);
        bool const is_dividend_negative = dividend < 0;
        bool const is_divisor_negative  = divisor < 0;
        bool const exclusive_sign       = is_dividend_negative ^ is_divisor_negative;

        double const mod_tr = fmod_truncated(dividend, divisor);
        return
            div_truncated(dividend, divisor) +
            ((int)exclusive_sign * (int)(mod_tr != 0) * (-1));
    }

    //! @brief division operation for floating point value.
    //! @return return quatient by floored division.
    inline
    double  fdiv_floored            (double dividend, double divisor)
    {
        BOOST_ASSERT(divisor != 0);
        bool const is_dividend_negative = dividend < 0;
        bool const is_divisor_negative  = divisor < 0;
        bool const exclusive_sign       = is_dividend_negative ^ is_divisor_negative;

        double const mod_tr = fmod_truncated(dividend, divisor);
        return
            fdiv_truncated(dividend, divisor) +
            ((int)exclusive_sign * (int)(mod_tr != 0) * (-1));
    }

    //! @brief division operation for integral value.
    //! @return return quatient by Euclidean division.
    template<typename T>
    T       div_euclidean           (T const &dividend, T const &divisor)
    {
        BOOST_ASSERT(divisor != 0);
        bool const is_divisor_negative  = divisor < 0;

        double const mod_tr = fmod_truncated(dividend, divisor);
        return 
            div_floored(dividend, divisor) +
            ((int)is_divisor_negative * (int)(mod_tr != 0) * 1);
    }

    //! @brief division operation for floating point value.
    //! @return return quatient by Euclidean division.
    inline
    double  fdiv_euclidean          (double dividend, double divisor)
    {
        BOOST_ASSERT(divisor != 0);
        bool const is_divisor_negative  = divisor < 0;

        double const mod_tr = fmod_truncated(dividend, divisor);
        return 
            fdiv_floored(dividend, divisor) +
            ((int)is_divisor_negative * (int)(mod_tr != 0) * 1);
    }
    //============================================================================//
    //! @}
    // enddef of division
    //============================================================================//

}}  //namespace hwm::arithmetic

#endif  //HWM_ARITHMETIC_HPP
