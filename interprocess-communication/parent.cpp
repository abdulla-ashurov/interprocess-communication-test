#include "file_mapping.hpp"
#include "process.hpp"
#include <sstream>
#include <tchar.h>

int main() {
	try {
		wchar_t msg[] = L"Hello World!";
		FileMapping f_map(255, FILE_MODES::WRITE, L"hFileMap", true);

		CopyMemory(f_map.begin(), msg, (_tcslen(msg) * sizeof(TCHAR)));

		std::wcout << "Message: " << (const wchar_t*)(f_map.begin()) << std::endl;

		const std::wstring app_name(L"C:\\Users\\ashur\\source\\repos\\interprocess-communication\\x64\\Release\\interprocess-communication.exe ");
		std::wstringstream cmd;
		cmd << app_name << (UINT_PTR)(f_map.handle());

		Process process(cmd.str(), true);

	}
	catch (...) {
		std::cout << "Error in FileMapping class\n";
	}
}
