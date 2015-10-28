#ifndef _L5R_LIBRARY_
#define _L5R_LIBRARY_

#include <iostream>
#include <string>
#include <vector>


namespace L5R_Library {
    void tokenizer(std::string str, std::vector<int>& nums);
    bool find(const int& val, const std::vector<int>& values);
    bool question(std::string question);
};

#endif // _L5R_LIBRARY_