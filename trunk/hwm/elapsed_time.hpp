#ifndef HWM_ELAPSED_TIME_HPP
#define HWM_ELAPSED_TIME_HPP

#include <algorithm>
#include <boost/config.hpp>
#include <boost/current_function.hpp>
#include <boost/format.hpp>
#include <boost/function.hpp>
#include <boost/preprocessor.hpp>
#include <boost/timer.hpp>
#include <pstade/napkin.hpp>

//default
//output a report to std::cout

//definition
//HWM_ELAPSED_TIME_OUTPUT_TO_DEBUGGER	//<= output a report to debugging window
//HWM_ELAPSED_TIME_DISABPLED			//<= disable tracing elapsed_time

#if defined HWM_ELAPSED_TIME_OUTPUT_TO_DEBUGGER
	#if BOOST_WINDOWS
		#include "./elapsed_time/reporter_windows.hpp"
		typedef hwm::elapsed_time_detail::reporter_windows default_reporter_t;
	#else
		#error repoter_is_not_implemented
	#endif
#else
	#include "./elapsed_time/reporter_std.hpp"
	typedef hwm::elapsed_time_detail::reporter_std default_reporter_t;
#endif

namespace hwm {
namespace elapsed_time_detail {

	struct elapsed_time
	{
		typedef
			elapsed_time
		this_type;

		typedef 
			boost::function<void(this_type const&)>
		reporter_t;

		elapsed_time	(char const *file, size_t const line, char const *func, reporter_t r = default_reporter_t()) 
			:	sum_	(0)
			,	min_	(0)
			,	max_	(0)
			,	count_	(0)
			,	file_	(file)
			,	line_	(line)
			,	func_	(func)
			,	r_		(r)
		{}

		~elapsed_time	() { try { r_(*this); } catch(...){} }

		void add(double elapse) {
			max_ = (std::max)(elapse, max_);
			min_ = (count_) ? (std::min)(elapse, min_) : elapse;
			sum_ += elapse;
			++count_;
		}

		char const *
				get_func	() const { return func_; }
		char const *
				get_file	() const { return file_; }
		size_t	get_line	() const { return line_; }
		double	get_min		() const { return min_; }
		double	get_max		() const { return max_; }
		double	get_total	() const { return sum_; }
		double	get_average	() const { return (count_) ? sum_ / count_ : 0; }
		size_t	get_count	() const { return count_; }
		void	set_reporter(reporter_t &r) { r_ = r; }

		void	clear		()
		{
			sum_ = min_ = max_ = count_ = 0;
		}

		double				sum_;
		double				min_;
		double				max_;
		size_t				count_;
		char const *		file_;
		int const			line_;
		char const *		func_;
		reporter_t			r_;
	};

	template<typename T>
	struct ScopedAdd
	{
		T				&t_;
		boost::timer	timer_;
		ScopedAdd		(T &t) : t_(t) {}
		~ScopedAdd		() { t_.add(timer_.elapsed()); }
	};

}	//namespace elapsed_time_detail
}	//namespace hwm

#if defined HWM_ELAPSED_TIME_DISABLED

	#define HWM_ELAPSED_TIME() (void*)0

#else	//HWM_ELAPSED_TIME_DISABLED

	#define HWM_ELAPSED_TIME()									\
		static hwm::elapsed_time_detail::elapsed_time			\
			BOOST_PP_CAT(hwm_elapsed_time_, __LINE__) (			\
				__FILE__, __LINE__, BOOST_CURRENT_FUNCTION );	\
			hwm::elapsed_time_detail::ScopedAdd<				\
				 hwm::elapsed_time_detail::elapsed_time			\
			>													\
			BOOST_PP_CAT(hwm_elapsed_time_scoped_add, __LINE__)	\
				(BOOST_PP_CAT(hwm_elapsed_time_, __LINE__));

#endif	//HWM_ELAPSED_TIME_DISABLED

#endif	//HWM_ELAPSED_TIME_HPP
