#include "RegexSearch.hpp"

vector<std::string> regexSearch(const std::string& input, const std::string& pattern) {
    vector<std::string> result;
    std::regex r{pattern};
    std::smatch s;
    std::regex_match(input, s, r);
    for (int i = 1; i < s.length(); i++) {
        result.push_back(s[i].str());
    }
    return result;
}
