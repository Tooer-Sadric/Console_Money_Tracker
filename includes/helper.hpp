#ifndef HELPER
#define HELPER

#include <string>
#include "user.hpp"
#include <vector>

//helps with indexing outputs
short findNextIdx(std::string const& fileName);

//Check if the file exists
void FileCheck(std::string const& fileName);

//the main writing function
void FileWrite(std::size_t, std::string const&, std::string const&, std::string const&, std::string const&, std::vector<Data> const&);

#endif