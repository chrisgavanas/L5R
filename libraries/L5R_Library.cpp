#include <sstream>
#include <cstdlib>
#include "L5R_Library.hpp"

/*
 * Takes a string and a reference to an empty vector and
 * adds to the vector every integer found in the string.
 * All integers in the vector must be different.
 */
void L5R_Library::tokenizer(std::string str, std::vector<int>& nums)
{
    std::istringstream str_stream(str);
    std::string token;

    while(std::getline(str_stream, token, ' ')) {   // tokenize the string
        int num = atoi(token.c_str());              // convert ascii to integer
        std::vector<int>::iterator it;
        nums.push_back(num);                        // add integer to the vector
        for (int i = 0 ; i < nums.size()-1 ; ++i) {
            if (nums[i] == num) {                   // if it already exist
                nums.pop_back();                    // remove
                break;
            }
        }
    }
}

/*
 * Return true if val is found in values.
 * Return false if not.
 */
bool L5R_Library::find(const int& val, const std::vector<int>& values)
{
    for (int i = 0 ; i < values.size() ; ++i) {
        if (val == values[i])
            return true;
    }
    return false;
}

/*
 * Print the "question" and wait for a "yes" or "no"
 * answer. If "yes" return true, If "no" return false.
 */
bool L5R_Library::question(std::string question)
{
    std::string answer;

    while (true) {
        std::cout << question << " (y) or (n)\n";
        std::cout << "Answer: ";
        std::getline(std::cin, answer);
        std::cout << std::endl;
        if (answer == "y" || answer == "yes") {
            return true;
        } else if (answer == "n" || answer == "no") {
            return false;
        } else {
            continue;
        }

    }
}