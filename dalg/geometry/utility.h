
#ifndef DALG_UTILITY
#define DALG_UTILITY

#include <string>
#include <sstream>

namespace dalg
{
    constexpr static double PI = 3.141592653589793;
    
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
