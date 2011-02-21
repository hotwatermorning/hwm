#ifndef	HWM_ELAPSED_TIME_REPORTER_WINDOWS_HPP
#define	HWM_ELAPSED_TIME_REPORTER_WINDOWS_HPP

#include <string>
#include <boost/format.hpp>
#include <windows.h>

namespace hwm {
namespace elapsed_time_detail {

	struct reporter_windows
	{
		template<typename T>
		void operator()(T const &t) const
		{
			std::string const re = 
				(	boost::format(
						"%s(%d)\n"
						"\tfunc    : %s\n"
						"\taverage : %10.8f•b\n"
						"\tmin     : %10.8f•b\n"
						"\tmax     : %10.8f•b\n"
						"\ttotal   : %10.8f•b(called %d times)\n")
						%	t.get_file()
						%	t.get_line()
						%	t.get_func()
						%	t.get_average()
						%	t.get_min()
						%	t.get_max()
						%	t.get_total()
						%	t.get_count() ).str();
			OutputDebugString(re.c_str());
		}
	};

}	//namespace elapsed_time_detail
}	//namespace hwm

#endif	//HWM_ELAPSED_TIME_REPORTER_WINDOWS_HPP
