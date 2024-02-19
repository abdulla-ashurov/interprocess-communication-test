# interprocess-communication

## Example

```cpp
#include <string>
#include <sstream>

#include "process.hpp"
#include "file_mapping.hpp"
 
int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Please, provide correct list of arguments" << std::endl;
		std::cout << "CLI example: arg_count child_app_name" << std::endl;
		return 1;
	}

	try {
		std::string msg("Hello World!");
		InheritedFileMapping<msg.length()> f_map;

		strcpy(static_cast<char *>(f_map.begin()), msg.c_str());
		
		std::stringstream cmd;
		cmd << argv[1] << (UINT_PTR)(f_map.handle());
		
		Process process(cmd);
		process.join();
	}
	catch (...) { // Wait specific error
		std::cout << "Error in FileMapping class\n";
	}
	
	return 0;
}
```
