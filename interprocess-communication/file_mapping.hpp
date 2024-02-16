#ifndef __FILE_MAPPING_HPP__
#define __FILE_MAPPING_HPP__

#include <iostream>
#include <string>
#include "Windows.h"
#include "common.hpp"

enum FILE_MODES {
	READ = PAGE_READONLY,
	WRITE = PAGE_READWRITE
};

class FileMapping {
private:
	size_t m_size;
	std::wstring m_name;
	HANDLE m_hFileMap;
	void* m_buffer;

	void free_members() {
		if (m_buffer) {
			UnmapViewOfFile(m_buffer);
		}

		if (m_hFileMap) {
			CloseHandle(m_hFileMap);
		}
	}

	void map_view_of_file(const size_t size, const FILE_MODES& mode) {
		bool mapViewMode;
		if (mode == FILE_MODES::WRITE) {
			mapViewMode = FILE_MAP_ALL_ACCESS;
		}
		else {
			mapViewMode = FILE_MAP_READ;
		}

		m_buffer = MapViewOfFile(m_hFileMap, mapViewMode, 0, 0, size);
		if (m_buffer == NULL) {
			free_members();
			throw(std::runtime_error("Cannot map view of file!"));
		}
	}

public:
	FileMapping(const size_t size, const FILE_MODES& mode, const std::wstring& name = L"", const bool inheritHandle = false)
		: m_size(size), m_name(name), m_hFileMap(NULL), m_buffer(NULL) {
		SECURITY_ATTRIBUTES sa = create_security_attr(inheritHandle);
		m_hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, &sa, mode, 0, m_size, m_name.length() ? m_name.c_str() : NULL);
		if (m_hFileMap == NULL) {
			throw(std::runtime_error("Cannot create file mapping object!"));
		}

		map_view_of_file(m_size, mode);
	}

	FileMapping(const size_t size, HANDLE hFileMap, const FILE_MODES& mode)
		: m_size(size), m_hFileMap(hFileMap), m_buffer(NULL) {
		map_view_of_file(size, mode);
	}

	FileMapping(const FileMapping& other) = delete;

	FileMapping& operator=(const FileMapping& other) = delete;

	size_t size() const {
		return m_size;
	}
	const std::wstring& name() const {
		return m_name;
	}

	void* begin() {
		return m_buffer;
	}
	void* end() {
		return static_cast<uint8_t*>(m_buffer) + m_size;
	}

	HANDLE handle() {
		return m_hFileMap;
	}

	~FileMapping() {
		free_members();
	}
};

#endif // __FILE_MAPPING_HPP__
