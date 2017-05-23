#include "Util.hpp"
#include "OperationTable.h"

namespace Util {
    bool validInteger(const std::string integer) {
        int shift = 0;
        if(integer.length() > 1 && integer[0] == '-')
            shift = 1;
        for (int i = 0 + shift; i < integer.length(); i++) {
            int curVal = integer[i] - '0';
            if (curVal < 0 || curVal > 9)
                return false;
        }
        if(integer.length() - shift > 4 || integer.length() - shift == 0)
            return false;
        return true;
    }


    bool validByte(const std::string charSeq) {
        if (charSeq.length() < 3) return false;
        char firstChar = tolower(charSeq[0]);
        if (firstChar != 'c' && firstChar != 'x') return false;
        if (charSeq[1] != '\'' || charSeq[charSeq.length() - 1] != '\'') return false;
        if (firstChar == 'x') {
            for (int i = 2; i < charSeq.length() - 1; i++) {
                if (isHexaCharacter(charSeq[i]))
                    continue;
                return false;
            }
        }
        if((firstChar == 'c' && charSeq.length() > 18) || (firstChar == 'x' && charSeq.length() > 17))
            return false;
        return true;
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

    std::vector<std::string> split(std::string input, char separator) {
        std::vector<std::string> result;
        std::string curStr;
        for (int i = 0; i < input.length(); i++) {
            curStr += input[i];
            if (i + 1 < input.length() && input[i + 1] == separator) {
                result.push_back(curStr);
                while (i + 1 < input.length() && input[i + 1] == separator) i++;
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

    std::string formalize(std::string code, const int len) {
        while (code.length() < len) {
            code = '0' + code;
        }
        return code;
    }

    int to_int(std::string hexadecimal_string) {
        unsigned int number;
        std::stringstream ss;
        ss << std::hex << hexadecimal_string;
        ss >> number;
        return number;
    }

    bool hasCharacter(std::string str, char reqChar) {
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == reqChar)
                return true;
        }
        return false;
    }


    bool isDirective(std::string arg1) {
        for (int i = 0; i < DIR_SIZE; i++) {
            if (equalsIgnoreCase(arg1, DIRECTIVES[i]))
                return true;
        }
        return false;
    }

    bool validLabel(std::string arg1) {
        bool firstLetter = false;
        for (int i = 0; i < arg1.length(); i++) {
            if (isalpha(arg1[i]))
                firstLetter = true;
            if ((!firstLetter) && (isspace(arg1[i]) ||
                                   ((isalnum(arg1[i])) && (!isalpha(arg1[i])))))
                return false;
        }
        return true;
    }

    bool validOperation(std::string arg1) {
        if ((!OperationTable::getInstance()->hasOperation(arg1))) {
            return false;
        }
        return true;
    }

    bool validOperand(std::string arg1) {
        if (validLabel(arg1) || validHexa(arg1))
            return true;
        return false;
    }

    bool validIndexed(std::string arg1) {
        if (!hasCharacter(arg1, ','))
            return false;
        std::vector<std::string> vec = split(arg1, ',');
        if (vec.size() != 2)
            return false;
        return validOperand(vec[0]) && validOperand(vec[1]);
    }

    bool validHexa(std::string arg1) {
        if(arg1.length() > 2 && arg1[0] == '0' && tolower(arg1[1]) == 'x' &&
                isHexaCharacter(arg1[2]) && isalpha(arg1[2])){
            for(int i = 3; i < arg1.length(); i++){
                if(!isHexaCharacter(arg1[i]))
                    return false;
            }
            return true;
        }else{
            if(isalpha(arg1[0]))
                return false;
            for(int i = 0; i < arg1.length(); i++){
                if(!isHexaCharacter(arg1[i]))
                    return false;
            }
        }
        return true;
    }

    bool isHexaCharacter(char arg1){
        if(!isalnum(arg1))
            return false;
        if(isalpha(arg1) && tolower(arg1) <= 'f')
            return true;
        if(isalnum(arg1) && !isalpha(arg1))
            return true;
        return false;
    }

    bool validHexaArray(std::string _operand){
        std::vector<std::string> vec = split(_operand, ',');
        bool goodArray = true;
        for(int i = 0; i < vec.size(); i++)
            goodArray = goodArray && validHexa(vec[i]);
        return goodArray;
    }

    bool validMathExpression(std::string data, SymbolTable* symbolTable){
        std::string val = "";
        bool opFound = true;
        for(int i = 0; i < data.length(); i++){
            if(data[i] == '+' || data[i] == '-'){
                if(opFound)
                    return  false;
                opFound = true;
                if((val != "*") && (!symbolTable->hasLabel(val)) && (!validInteger(val)))
                    return false;
                continue;
            }
            val += data[i];
            opFound = false;
        }
        if((val != "*") && (!symbolTable->hasLabel(val)) && (!validInteger(val)))
            return false;
    }

    int evalMathExpression(std::string data, SymbolTable* symbolTable, int locCtr){
        std::string val = "";
        bool positive = true;
        int result = 0;
        for(int i = 0; i < data.length(); i++){
            if(data[i] == '+' || data[i] == '-'){
                if(val == "*")
                    result += (positive ? 1 : -1) * locCtr;
                else if(validInteger(val))
                    result += (positive ? 1 : -1) * std::stoi(val);
                else
                    result += (positive ? 1 : -1) * symbolTable->getAddress(val);
                val = "";
                if(data[i] == '+')
                    positive = true;
                else
                    positive = false;
                continue;
            }
            val += data[i];
        }
        if(val == "*")
            return locCtr;
        else if(validInteger(val))
            result += (positive ? 1 : -1) * std::stoi(val);
        else
            result += (positive ? 1 : -1) * symbolTable->getAddress(val);
        return result;
    }

    bool validLiteral(std::string literal){
        if(literal.length() <= 4 || literal[0] != '=')
            return false;
        literal = literal.substr(1,literal.length() - 1);
        if(validByte(literal) || validLiteralWord(literal))
            return true;
        return false;
    }

    bool validLiteralWord(std::string literalWord){
        if(tolower(literalWord[0]) == 'w' && literalWord[1] == '\'' && literalWord[literalWord.length() - 1] == '\''){
            literalWord = literalWord.substr(2, literalWord.length() - 3);
            return validInteger(literalWord);
        }
        return false;
    }
};