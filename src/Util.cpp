#include "Util.hpp"

namespace Util {
    bool validInteger(const std::string integer) {
        for (int i = 0; i < integer.length(); i++) {
            int curVal = integer[i] - '0';
            if (curVal < 0 || curVal > 9)
                return false;
        }
        return true;
    }

    bool validByte(const std::string charSeq) {
        if (charSeq.length() < 3) return false;
        char firstChar = tolower(charSeq[0]);
        if (firstChar != 'c' && firstChar != 'f') return false;
        if (charSeq[1] != '\'' || charSeq[charSeq.length() - 1] != '\'') return false;
        if (firstChar == 'f') {
            for (int i = 2; i < charSeq.length() - 1; i++) {
                int value = charSeq[i] - '0';
                int alphaVal = charSeq[i] - 'a';
                if ((value >= 0 & value <= 9) || (alphaVal >= 0 && alphaVal <= 5))
                    continue;
                return false;
            }
        }
    }

    bool equalsIgnoreCase(const std::string &str1, const char *str2) {
        if (str1.length() != std::strlen(str2)) {
            return false;
        }
        for (int i = 0; i < str1.length(); i++) {
            if (tolower(str1[i]) != tolower(str2[i])) {
                return false;
            }
        }
        return true;
    }

    std::string to_hexadecimal(int number) {
        std::stringstream stream;
        stream << std::hex << number;
        return stream.str();
    }

    std::string to_hexadecimal(const std::string number) {
        return to_hexadecimal(stoi(number));
    }

    std::string formalize(std::string code, const int len) {
        while (code.length() < len) {
            code = "0" + code;
        }
        return code;
    }

    std::vector<std::string> split(std::string input, char breaker) {
        std::vector<std::string> result;
        std::string curStr;
        for(int i = 0; i < input.length(); i++){
            curStr += input[i];
            if(i + 1 < input.length() && input[i + 1] == breaker){
                result.push_back(curStr);
                while(i + 1 < input.length() && input[i + 1] == breaker) i++;
                curStr = std::string();
            }
        }
        result.push_back(curStr);
        return result;
    }

    int getConstSize(std::string data) {
        char firstChar = tolower(data[0]);
        if (firstChar == 'c')
            return data.length() - 3;
        return (data.length() - 3 + 1) / 2;
    }

};