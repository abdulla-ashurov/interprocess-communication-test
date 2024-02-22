#ifndef __FILE_MAPPING_HPP_
#define __FILE_MAPPING_HPP__

#include <Windows.h>

#include "common.hpp"

template <size_t m_size>
class BaseFileMapping {
private:
	std::wstring m_name;

public:
	BaseFileMapping(SECURITY_ATTRIBUTES& sa, const std::wstring& name) : m_name(name) {
		CreateFileMapping(INVALID_HANDLE_VALUE, &sa, PAGE_READWRITE, 0, m_size, m_name.length() ? m_name.c_str() : NULL);
	}
	virtual ~BaseFileMapping() = 0;

public:
	BaseFileMapping(const BaseFileMapping& other);
	BaseFileMapping& operator=(const BaseFileMapping& other);

public:
	size_t size() const;
	const std::wstring& name() const;
	HANDLE handle();
	void* begin();
	void* end();
};

class FileMapping : public BaseFileMapping<size_t> {
public:
	explicit FileMapping(const std::wstring& name = L"");
	~FileMapping();
};

class InheritedFileMapping : public BaseFileMapping<size_t> {
public:
	explicit InheritedFileMapping(const std::wstring& name = L"");
	~InheritedFileMapping();
};

#endif // __FILE_MAPPING_HPP__
