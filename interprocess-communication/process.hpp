#ifndef __PROCESS_HPP__
#define __PROCESS_HPP__

#include <iostream>
#include <string>
#include "Windows.h"
#include "common.hpp"

// DRAFT

class Process {
private:
	PROCESS_INFORMATION m_pi;

public:
	Process(const std::wstring& cmd, const bool inherit_handles = false) : m_pi{ 0 } {
		SECURITY_ATTRIBUTES sa = create_security_attr(inherit_handles);
		

		if (CreateProcess(NULL, const_cast<LPWSTR>(cmd.c_str()), &sa, &sa, inherit_handles, NULL, NULL, NULL, &si, &m_pi) == NULL) {
			std::wcout << "It cannot create a new process" << std::endl;
			return;
		}

		WaitForSingleObject(m_pi.hProcess, INFINITE);
	}

	Process(const Process& other) = delete;
	Process& operator=(const Process& other) = delete;

	~Process() {
		if (m_pi.hProcess) {
			CloseHandle(m_pi.hProcess);
		}

		if (m_pi.hThread) {
			CloseHandle(m_pi.hThread);
		}
	}
};

#endif // __PROCESS_HPP__
