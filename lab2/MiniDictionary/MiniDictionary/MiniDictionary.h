#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

void DialogueWithUser(std::istream& cIn, std::ostream& cOut, std::string& dictionaryFileName);

void SaveFile(std::ostream& cOut, const std::string& dictionaryFileName, const std::map<std::string, std::string>& dictionary, const std::vector<std::string>& newWords);

std::map<std::string, std::string> ReadDictionaryFromFile(std::istream& cIn, std::ostream& cOut, std::string& dictionaryFileName, bool& isReadFile);