#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include "details.hpp"

SECURITY_ATTRIBUTES create_security_attr(const bool inherit_handle = false) {
	return details::security_attr(inherit_handle);
}

HANDLE create_file_mapping(const size_t size) {
	HANDLE hFileMap = details::create_file_mapping(size);
	if (hFileMap == NULL) {
		throw FileMappingExceptions(GetLastError());
	}

	return hFileMap;
}



HANDLE create_inherited_file_mapping(const size_t size) {
	HANDLE hFileMap = details::create_inherited_file_mapping(size);
	if (hFileMap == NULL) {
		throw FileMappingExceptions(GetLastError());
	}

	return hFileMap;
}

void* map_view_of_file(HANDLE f_map, const size_t size) {
	void* buffer = details::map_view_of_file(f_map, size);
	if (buffer == NULL) {
		throw FileMappingExceptions(GetLastError());
	}

	return buffer;
}

std::string error_message(const size_t err_code) {
	std::string err_msg;
	char* out_err_msg(NULL);
	if (details::format_message(err_code, out_err_msg)) {
		err_msg = out_err_msg;
	}
	details::local_free(out_err_msg);

	return err_msg;
}

#endif // __COMMON_HPP__
