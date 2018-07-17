#include "Language.hpp"

#include <sstream>

std::string& to_upper(std::string& str)
{
	for (auto& i : str)
		i = toupper(i);
	return str;
}


Language::Language()
{
	header_name = to_upper(header_name);
}


Language::~Language()
{
}

std::string Language::operator[](LanguageSection sect)
{
	switch (sect)
	{
	case Header:
		return header;
	case Body:
		return body;
	case Footer:
		return footer;
	case StorageType:
		return storagetype;
	case CastType:
		return casttype;
	case StringType:
		return stringtype;
	case CommentStart:
		return comment_start;
	case CommentEnd:
		return comment_end;
	case SizeType:
		return sizetype;
	default:
		return "Unknown";
	}
}

bool Language::set_language(LanguageName lang)
{
	current_language = lang;
	switch (lang)
	{
	case UnknownName:
		header = "UnknownLanguageHeader";
		body = "UnknownLanguageBody";
		footer = "UnknownLangageFooter";
		break;
	case C:
	case CPP:
		header = "#ifndef " + header_name + "\n#define " + header_name + " \n";
		body = "";
		footer = "\n\n#endif";
		storagetype = "char ";
		casttype = "(char)";
		comment_start = "/*";
		comment_end = "*/";
		stringtype = "char[] ";
		sizetype = "const unsigned long ";
		break;
	case CSharp:
		header = "namespace " + header_name + "\n{\nclass Storage\n{\n";
		body = "";
		footer = "}\n}\n";
		storagetype = "public static char[";
		casttype = "(char) ";
		comment_start = "/*";
		comment_end = "*/";
		stringtype = "string ";
		sizetype = "public const long ";
		break;
	default:
		std::cout << "Language not supported.\n";
		std::exit(1);
		//
		header = "UnknownLanguageHeader";
		body = "UnknownLanguageBody";
		footer = "UnknownLangageFooter";
		comment_start = "/*";
		comment_end = "*/";
		break;
	}
	return false;
}

void Language::set_name(const std::string _name)
{
	header_name = _name;
	header_name = to_upper(header_name);
	// Update language values
	set_language(current_language);
}

std::string Language::generate_entry(const std::string name, const size_t size)
{
	// formats how a variable entry is emitted.
	std::stringstream ss;

	switch (current_language)
	{
	case C:
	case CPP:
		ss << this->operator[](StorageType) << " " << name << "_contents[" << size << "] = \n{";
		break;
	case CSharp:
		ss << this->operator[](StorageType) << "] file_" << name
			<< "_contents = new char[" << size << "] {";
		break;
	}



	return ss.str();
}
