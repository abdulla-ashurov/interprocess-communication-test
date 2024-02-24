#ifndef __FILE_MAPPING_HPP_
#define __FILE_MAPPING_HPP__

#include <Windows.h>

#include "common.hpp"
#include "exceptions.hpp"

template<size_t m_size>
class FileMapping {
private:
	HANDLE m_hFileMap;	// UniqueHandle m_hFileMap;
	void* m_buffer;		// MapViewBuffer m_buffer;

public:
	FileMapping() : m_hFileMap(NULL), m_buffer(NULL) {
		m_hFileMap = create_file_mapping(m_size);
		if (m_hFileMap == NULL) {
			throw FileMappingExceptions(GetLastError());
		}

		m_buffer = map_view_of_file(m_hFileMap, m_size);
		if (m_buffer == NULL) {
			CloseHandle(m_hFileMap);
			throw FileMappingExceptions(GetLastError());
		}
	}

	/*
	* FileMapping() {
	*     m_hFileMap = create_file_mapping(m_size);
	*     m_buffer = map_view_of_file(m_hFileMap, m_size);
	* }
	*/

	~FileMapping() {
		if (m_buffer) {
			UnmapViewOfFile(m_buffer);
		}
		if (m_hFileMap) {
			CloseHandle(m_hFileMap);
		}
	}

public:
	FileMapping(const FileMapping& other);
	FileMapping& operator=(const FileMapping& other);

public:
	size_t size() const;
	HANDLE handle();
	void* begin();
	void* end();
};
class InheritedFileMapping : public BaseFileMapping<size_t>;

#endif // __FILE_MAPPING_HPP__
