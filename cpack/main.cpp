#include <iostream>

#include "CPack.hpp"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << argv[0] << " - Binary-to-source packager\n\tUse '--help' for usage.\n";
	}
	else
	{
		std::string output_file = "cpack_file.h";
		CPack cpack;
		Language language;
		for (int i = 1; i < argc; i++)
		{
			if (std::string(argv[i]) == "--help")
			{
				std::cout << argv[0] << " usage: \n"
					"-o <value> | set output file to <value>\n"
					"-h <value> | set the files namespace equivalent to <value>\n"
					"-c | count byte numbers in emitted code\n"
					"--language:<lang> | configure cpack to emit code compatible with <lang> (default: C)\n";
				i++;
				return 0;
			}
			if (std::string(argv[i]) == "-o" && i < argc)
			{
				output_file = argv[i + 1];
				i++;
			}
			else if (std::string(argv[i]) == "-h" && i < argc)
			{
				//std::cout << "[" << i << "] setting header value: " << argv[i + 1] << "\n";
				//cpack.set_header_name(argv[i + 1]);
				language.set_name(argv[i + 1]);
				cpack.set_language(language);
				i++;
			}
			else if (std::string(argv[i]) == "-c" && i < argc)
			{
				cpack.count_lines(true);
			}
			else if (std::string(argv[i]).substr(0, 11) == "--language:")
			{
				language.set_language(to_language[std::string(argv[i]).substr(11)]);
				cpack.set_language(language);
			}
			else
				cpack.load_file(argv[i]);
		}

		cpack.generate_file(output_file.c_str());
	}
	return 0;
}