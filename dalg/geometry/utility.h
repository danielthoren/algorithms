
#ifndef DALG_UTILITY
#define DALG_UTILITY

#include <string>
#include <sstream>

namespace dalg
{
#define p_type double
    
    constexpr static double PI = 3.141592653589793;
    constexpr static double DEFAULT_PREC = 0.0001;

    inline p_type get_pref_prec(p_type p1, p_type p2)
    {
	return std::max(p1, p2);
    }
    
    struct BadArgumentException : public std::exception
    {
	BadArgumentException(std::string msg)
	    {
		std::stringstream stream("Bad arguments given: ");
		stream << msg << std::endl;
		this->msg = stream.str();
	    }
	    
	const char * what () const throw ()
	    {
		return msg.c_str();
	    }

	std::string msg;
    };

}

#endif
