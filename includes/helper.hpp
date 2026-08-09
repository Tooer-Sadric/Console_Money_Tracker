#ifndef HELPER
#define HELPER

#include <string>
#include "user.hpp"
#include <vector>

void FileCheck(std::string const& fileName);

void FileWrite(std::size_t, std::string const&, std::string const&, std::string const&, std::string const&, std::vector<Data> const&);

short findNextIdx(std::string const& fileName);
#endif