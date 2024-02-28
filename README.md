# interprocess-communication

## Example

```cpp
#include <string>
#include <sstream>

#include "process.hpp"
#include "file_mapping.hpp"
 
/* 
 * This program illustrates how to create inherited FileMapping object
 * and inherite it to child process using CMD.
 */

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Please, provide correct list of arguments" << std::endl;
		std::cout << "CLI example: arg_count child_proces_app_name" << std::endl;
		return 1;
	}

	try {
		std::string msg("Hello World!");
		UniqueInheritedFileMapping<msg.length()> f_map;

		strcpy(static_cast<char *>(f_map.begin()), msg.c_str());
		
		std::stringstream cmd;
		cmd << argv[1] << (UINT_PTR)(f_map.handle());
		
		Process process(cmd);
		process.join();
	} catch (FileMappingException e) {
		std::cout << "Error: " << e.msg();
	}
	
	return 0;
}
```

```cpp
#include "file_mapping.hpp"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::wcout << "Please, provide FileMapping Handle to child process using CLI\n";
		return 1;
	}

	HANDLE hFileMap = (HANDLE)(std::stoi(argv[1]));
	std::wcout << "hFileMap: " << hFileMap << std::endl;
	
	const size_t size = 12;
	UniqueFileMapping f_map<size>(hFileMap);
	
	std::wcout << "Message from first process: " << (const char*)(f_map.begin());

	return 0;
}
```
