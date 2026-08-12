/**
 * @author  Sadric Koh
 * @date    27 July 2026
 * @brief   The helper functions for the program
 */

#include "helper.hpp"
#include "user.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <algorithm>
#include <cctype>

#define new_line "\n";


std::string centerText(std::string const& text, std::size_t width) {
    std::size_t padding = (width > text.size()) ? (width - text.size()) / 2 : 0;
    return std::string(padding, ' ') + text;
}

short findNextIdx(std::string const& fileName) {
    std::ifstream ifs{fileName};
    std::string line;
    short maxIdx = -1;

    while (std::getline(ifs, line)) {
        std::istringstream lineStream{line};
        short possibleIdx;
        if (lineStream >> possibleIdx) {   // first token on the line parses as a number
            maxIdx = std::max(maxIdx, possibleIdx);
        }
    }
    return static_cast<short>(maxIdx + 1);
}

void FileCheck(std::string const& fileName){
    //check for file path(folder)
    std::filesystem::path filePath{fileName};
    if (filePath.has_parent_path()) {
        std::cout << "no folder found, generating new folder" << new_line;
        std::filesystem::create_directories(filePath.parent_path());
    }


    std::ifstream ifs{fileName};
    if(!ifs){
        std::cout << "no data found, generating new data" << new_line;
        std::ofstream ofs{fileName};
        if(!ofs){
            std::cout << "Cannot create new file" << new_line;
            return;
        }
    }else{
        std::cout << "Data found, loading data" << new_line;
    }
}

//helper function to center my texts
std::string centerText(const std::string& s, int width) {
    int padding = width - static_cast<int>(s.size());
    if (padding <= 0) return s;               // string too long to center, just return as-is
    int left = padding / 2;
    int right = padding - left;                // gives the extra space to the right if odd
    return std::string(left, ' ') + s + std::string(right, ' ');
}

//converts data into a formattable text to be printed
std::string toString(const Data& d) {
    std::ostringstream oss;
    std::ostringstream tmp;
    tmp << std::fixed << std::setprecision(2) << d.price;
    std::ostringstream inttmp;
    inttmp << d.quantity;

    oss << std::left  << std::setw(7)  << d.d_idx
        << centerText(d.item,10)
        << centerText(tmp.str(),10)
        << centerText(inttmp.str(),10) << std::defaultfloat;
    return oss.str();
}

void FileWrite(std::size_t sz, std::string const& fileName, std::string const& month, std::string const& year, std::string const& sep, std::vector<Data> const& data){
    std::vector<std::string> str_vec{};
    std::string monthYear{month + " " + year};
    std::string centeredMonthYear = centerText(monthYear,sz);
    
    // 1. Read existing file into memory
    std::vector<std::string> lines;
    {
        std::ifstream ifs{fileName};
        std::string line;
        while (std::getline(ifs, line)) {
            lines.push_back(line);
        }
    }
    // 2. Look for an existing header matching this month/year
    std::size_t headerIdx = lines.size(); // sentinel: "not found"
    for (std::size_t i = 0; i < lines.size(); ++i) {
        std::string lowerLine = lines[i];
        std::transform(lowerLine.begin(), lowerLine.end(), lowerLine.begin(),
            [](unsigned char c) { return std::tolower(c); });

        std::string lowerCenteredMonthYear = centeredMonthYear;
        std::transform(lowerCenteredMonthYear.begin(), lowerCenteredMonthYear.end(), lowerCenteredMonthYear.begin(),
            [](unsigned char c) { return std::tolower(c); });

        if (lowerLine == lowerCenteredMonthYear) {
            headerIdx = i;
            break;
        }
    }
    if (headerIdx != lines.size()) {
        // 3a. Found it — figure out where this month's section ends.
        // Section = sep, header, sep, <entries...>, until the next sep (next month) or EOF.
        std::size_t insertPos = lines.size(); // default: end of file
        for (std::size_t i = headerIdx + 2; i < lines.size(); ++i) { // skip the sep right after header
            if (lines[i] == sep) {
                insertPos = i;
                break;
            }
        }

        std::vector<std::string> formatted;
        formatted.reserve(data.size());
        std::transform(data.begin(), data.end(), std::back_inserter(formatted),
            [](Data const& d) {
                return toString(d);
            });

        lines.insert(lines.begin() + insertPos, formatted.begin(), formatted.end());
    }else{
        // 3b. Not found — append a brand-new month block at the end
        lines.push_back(sep);
        lines.push_back(centeredMonthYear);
        lines.push_back(sep);
        //add header here
        std::string header{" Index |  item  |  price  | Quantity"};
        lines.push_back(header);

        for (Data const& entry : data) {
            std::ostringstream priceStream;
            priceStream << std::fixed << std::setprecision(2) << entry.price;
            std::string priceStr = priceStream.str();
            std::string newLine{toString(entry)};
            lines.push_back(newLine);
        }
    }
    // 4. Rewrite the whole file
    std::ofstream ofs{fileName};
    for (auto const& l : lines) {
        ofs << l << new_line;
    }

    //todo
    //print out total value and such
}