#include "FileSearcher.hpp"

void FileSearcher::generateLPS(const std::string &keyword, std::vector<int> &lps, const int &n) {
    int pre = 0, suf = 1;

    while (suf < n) {
        if (keyword[pre] == keyword[suf]) {
            lps[suf] = pre + 1;
            pre++, suf++;
        } else {
            if (pre == 0)
                suf++;
            else
                pre = lps[pre - 1];
        }
    }
}

bool FileSearcher::contains(const std::string &line, const std::string &keyword) {
    int n = line.length(), m = keyword.length();
    if (m > n) return false;

    std::vector<int> lps(m, 0);
    generateLPS(keyword, lps, m);

    int first = 0, second = 0;
    while (first < n) {
        if (line[first] == keyword[second]) {
            first++, second++;
            if (second == m) return true;
        } else {
            if (second == 0) first++;
            else second = lps[second - 1];
        }
    }

    return false;
}

bool FileSearcher::containsKeyword(const std::string &path, const std::string &keyword) {
    std::ifstream read(path);
    if (!read) {
        std::cerr << "Could not open file " << path << "\n";
        return false;
    }

    std::string line;
    while (getline(read, line)) {
        if (contains(line, keyword)) {
            read.close();
            return true;
        }
    }

    read.close();
    return false;
}
