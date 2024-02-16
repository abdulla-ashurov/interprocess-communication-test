#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include "Windows.h"

SECURITY_ATTRIBUTES create_security_attr(const bool inherit_handle = false) {
	return SECURITY_ATTRIBUTES{
		sizeof(SECURITY_ATTRIBUTES), // nLength
		NULL,                        // lpSecurityDescriptor
		inherit_handle               // bInheritHandle
	};
}

#endif // __COMMON_HPP__
