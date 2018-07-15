#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <map>

std::string& to_upper(std::string& str);

enum LanguageName
{
	UnknownName,
	C,
	CPP,
	Java,
	CSharp,
};

enum LanguageSection
{
	UnknownSection,
	Header,
	Body,
	Footer,
	StorageType,
	CommentStart,
	CommentEnd,
};

static std::map<std::string, LanguageName> to_language
{
	{ "c", C },
	{ "cpp", CPP },
	{ "java", Java },
	{ "cs", CSharp},
};

class Language
{
private:
	std::string header_name = "cpack_binary_files";

	std::string header = "";
	std::string body = "";
	std::string footer = "";
	std::string storagetype = "";
	std::string comment_start, comment_end;
	LanguageName current_language = UnknownName;
public:
	Language();
	~Language();
	std::string operator[](LanguageSection sect);
	bool set_language(LanguageName lang);
	void set_name(const std::string _name);
};

