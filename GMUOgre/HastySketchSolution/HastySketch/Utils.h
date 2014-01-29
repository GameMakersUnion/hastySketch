#ifndef UTILS_H
#define UTILS_H

#define DBOUT( s )					 \
{									  \
	std::ostringstream os_;			   \
	os_ << s;							\
	OutputDebugString(os_.str().c_str()); \
}
#define DBOUTL( s )				      \
{								       \
	std::ostringstream os_;		        \
	os_ << s << std::endl;		     	 \
	OutputDebugString(os_.str().c_str()); \
}

#endif