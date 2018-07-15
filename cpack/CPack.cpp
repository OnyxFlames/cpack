#include "CPack.hpp"

#include <filesystem>
#include <sstream>
#include <iomanip>

CPack::CPack()
{
	lang.set_language(C);
}


CPack::~CPack()
{
}

void CPack::set_header_name(const std::string _header_name)
{
	header_name = _header_name;
	//header_name = to_upper(header_name);
}

File_Struct& CPack::load_file(const char* filename)
{
	//printf("get_bytes()\n");
	std::ifstream input(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = input.tellg();
	std::vector<char> ret((unsigned)pos);
	//printf("File_Struct\n");
	File_Struct fs;
	fs.filename = filename;

	input.seekg(0, std::ios::beg);
	input.read(&ret[0], pos);
	fs.contents = ret;

	files.push_back(fs);

	return files.at(files.size()-1);
}

namespace fs = std::experimental::filesystem;

std::string filename_to_sourcename(std::string str)
{
	str = (fs::path(str)).filename().string();
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '.')
			str[i] = '_';
		if (str[i] == '/' || str[i] == '\\')
			str.erase(i);
	}
	return str;
}

std::string CPack::bytes_to_source(File_Struct& file)
{
	namespace fs = std::experimental::filesystem;

	std::stringstream ret;

	ret << lang[StorageType] << filename_to_sourcename(file.filename) << "_name[] = \"" << fs::path(file.filename).filename().string() << "\";\n";
	ret << lang[StorageType] << filename_to_sourcename(file.filename) << "_contents[" << file.contents.size() << "] = \n{";

	for (size_t i = 0; i < file.contents.size(); i++)
	{
		if (i % 256 == 0)
			if (number_lines)
				ret << "\n" << lang[CommentStart] << std::setw(8) << std::setfill('0') << std::hex << i << lang[CommentEnd];
			else
				ret << "\n";
		ret << "\t(" + lang[StorageType] + ")0x" << std::hex << std::setw(2) << std::setfill('0') << ((unsigned)file.contents[i] & 0x000000FF);
		
		if (i + 1 != file.contents.size())
			 ret << ", ";
	}
	ret << "\n};\n";
	ret << std::dec << "const unsigned long " << filename_to_sourcename(file.filename) << "_size = " << file.contents.size() << ";\n";

	return ret.str();
}

void CPack::generate_file(const char * filename)
{
	std::ofstream output(filename);
	if (!output.is_open())
	{
		std::cerr << "Failed to write to file '" << filename << "'\n";
		std::exit(1);
	}

	output << get_header_data();

	for (auto& it : files)
	{
		output << "// File: " << it.filename << "\n";
		output << bytes_to_source(it);
		output << "// Eof File: " << it.filename << "\n";
	}

	output << get_footer_data();

	output.close();
}