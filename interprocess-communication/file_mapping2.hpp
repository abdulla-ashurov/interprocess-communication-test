#ifndef __FILE_MAPPING_HPP_
#define __FILE_MAPPING_HPP__

#include <Windows.h>

#include "handle.hpp"
#include "buffer.hpp"
#include "common.hpp"
#include "exceptions.hpp"

template<size_t m_size>
class FileMapping {
private:
	UniqueHandle m_hFileMap;
	UniqueMapViewBuffer m_buffer;

public:
	FileMapping() {
		m_hFileMap = create_file_mapping(m_size);
		m_buffer = map_view_of_file(m_hFileMap.get(), m_size);
	}

public:
	FileMapping(const FileMapping& other) = delete;
	FileMapping& operator=(const FileMapping& other) = delete;

public:
	size_t size() const { return m_size; }
	HANDLE handle() { return m_hFileMap.get(); }
	void* begin() { return m_buffer.begin(); }
	void* end() { return static_cast<uint8_t*>(m_buffer.begin()) + m_size; }
};

#endif // __FILE_MAPPING_HPP__
