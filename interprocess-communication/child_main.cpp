#include "file_mapping.hpp"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::wcout << "Please, provide FileMapping Handle to child process using CLI\n";
		return 1;
	}

	HANDLE hFileMap = (HANDLE)(std::stoi(argv[1]));
	std::wcout << "hFileMap: " << hFileMap << std::endl;

	FileMapping f_map(255, hFileMap, FILE_MODES::WRITE);
	std::wcout << "Message from first process: " << (const wchar_t*)(f_map.begin());

	return 0;
}
