//			Copyright hotwatermorning 2011.
//	Distributed under the Boost Software License, Version 1.0.
//		(See accompanying file LICENSE_1_0.txt or copy at
//			http://www.boost.org/LICENSE_1_0.txt)

#ifndef HWM_ARITHMETIC_HPP
#define HWM_ARITHMETIC_HPP

#include <cmath>
#include <boost/assert.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>

namespace hwm {
namespace arithmetic {

	namespace detail
	{
		template<typename T>
		T abs_switch	(
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
		T abs_switch	(
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
		T abs_switch	(
			T const t,
			typename boost::enable_if<
				boost::is_floating_point<T>
			>::type* = 0 )
		{
			return ::fabs(t);
		}
	}	//namespace detail

	template<typename T>
	double simple_round(T const &t) { return floor((double)t + 0.5); }

	template<typename T>
	bool	odd(T const &t) { return t % 2 != 0; }

	template<typename T>
	bool	even(T const &t) { return t % 2 == 0; }

	template<typename T>
	int	sign	(T const &t) { return ((t>0)*1)+((t<0)*(-1)); }

	template<typename T>
	T abs(T const &t) { return detail::abs_switch(t); }

	template<typename T>
	T	mod_truncated(T const &dividend, T const &divisor)
	{
		BOOST_ASSERT(divisor != 0);
		return (detail::abs_switch(dividend) % detail::abs_switch(divisor)) * sign(dividend);
	}

	template<typename T>
	T	mod_floored(T const &dividend, T const &divisor)
	{
		BOOST_ASSERT(divisor != 0);
		int const	dividend_sign		= sign(dividend);
		bool const 	positive_dividend	= dividend >= 0;
		bool const	positive_divisor	= divisor >= 0;

		T const unsigned_modulo = (detail::abs_switch(dividend)) % (detail::abs_switch(divisor));
		return
			unsigned_modulo * dividend_sign +
			((int)((unsigned_modulo != 0) && (positive_dividend==false)) * detail::abs_switch(divisor)) -
			((int)((unsigned_modulo != 0) && (positive_divisor==false)) * detail::abs_switch(divisor));
	}

	template<typename T>
	T	mod_euclidean(T const &dividend, T const &divisor)
	{
		BOOST_ASSERT(divisor != 0);
		const int	dividend_sign		= sign(dividend);
		const bool 	positive_dividend	= dividend >= 0;

		T const unsigned_modulo = (detail::abs_switch(dividend)) % (detail::abs_switch(divisor));
		return
			unsigned_modulo * dividend_sign +
			((int)((unsigned_modulo != 0) && (positive_dividend==false)) * detail::abs_switch(divisor));
	}

	template<typename T>
	T	div_truncated(T const &dividend, T const &divisor)
	{
		BOOST_ASSERT(divisor != 0);
		return (detail::abs_switch(dividend) / detail::abs_switch(divisor)) * sign(dividend) * sign(divisor);
	}

	template<typename T>
	T	div_floored(T const &dividend, T const &divisor)
	{
		BOOST_ASSERT(divisor != 0);
		return
			(detail::abs_switch(dividend) / detail::abs_switch(divisor)) * sign(dividend) * sign(divisor) -
			(int)(dividend % divisor != 0) * ((dividend >= 0) ^ (divisor >= 0));
	}

	template<typename T>
	T	div_euclidean(T const &dividend, T const &divisor)
	{
		BOOST_ASSERT(divisor != 0);
		return
			(detail::abs_switch(dividend) / detail::abs_switch(divisor)) * sign(dividend) * sign(divisor) -
			(int)(dividend % divisor != 0) * (((dividend >= 0) ^ (divisor >= 0)) - (int)(divisor < 0));
	}

}	//namespace arithmetic
}	//namespace hwm

#endif	//HWM_ARITHMETIC_HPP
