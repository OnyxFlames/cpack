#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

typedef unsigned char byte;

#include "Language.hpp"


struct File_Struct
{
	std::string filename = "";
	std::vector<char> contents;
};

class CPack
{
private:
	Language lang;
	// When this is emitted, it's all capitalized regardless of the actual values 
	// capitalization to follow with the C standard of capitalizing header guards.
	std::string header_name = "cpack_binary_files";
	std::vector<File_Struct> files;
	bool number_lines = false;
public:
	const std::string get_header_data()
	{
		return lang[Header];
		/*return std::string("#ifndef ") +
			to_upper(header_name) +
			"\n\n";*/
		//return "#ifndef CPACK_BINARY_FILES\n#define CPACK_BINARY_FILES\n\n";
	}
	const std::string get_footer_data()
	{
		return lang[Footer];
		//return "// end of cpack header\n\n#endif\n";
	}
	std::string bytes_to_source(File_Struct& file);
public:
	CPack();
	~CPack();
	void set_header_name(const std::string _header_name);
	File_Struct& load_file(const char* filename);
	void generate_file(const char* filename);
	void count_lines(bool b) { number_lines = b; }
	void set_language(Language _lang) { lang = _lang;  }
	Language& get_language() { return lang; }
};

