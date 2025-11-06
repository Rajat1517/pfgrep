#ifndef FILESEARCHER_HPP
#define FILESEARCHER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class FileSearcher {
    static void generateLPS(const std::string &keyword, std::vector<int> &lps, const int &n);
    static bool contains(const std::string &line, const std::string &keyword);

public:
    static bool containsKeyword(const std::string &path, const std::string &keyword);
};

#endif
