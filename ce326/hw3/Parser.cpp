#include "Parser.hpp"
#include "Number.hpp"
#include "String.hpp"
#include "ObjectArray.hpp"
#include <regex>
#include <iostream>
 
void Parser::skipWhitespace(string& input) {
    size_t i = 0;
    while (i < input.size() && isspace(input[i])) i++;
    input = input.substr(i);
}
 
shared_ptr<Object> Parser::parseString(string& input) {
    regex mismatch1(R"(^'([^']*)\")");
    regex mismatch2(R"(^\"([^\"]*)')");
    regex stringRegex(R"(^\"([^\"]*)\"|^'([^']*)')");
    smatch matches;

    if (regex_search(input, matches, mismatch1) ||
        regex_search(input, matches, mismatch2)) {
        cout << "Error: Ill-formatted string." << endl;
        
        return nullptr;
    }

    if (regex_search(input, matches, stringRegex)) {
        string val = matches[1].matched ? matches[1] : matches[2];
        input = matches.suffix().str();

        return make_shared<String>(val);
    }

    return nullptr;
}
 
shared_ptr<Object> Parser::parseNumber(string& input) {
    regex doubleRegex(R"(^(-?[0-9]+\.[0-9]+))");
    regex intRegex(R"(^(-?[0-9]+))");
    smatch matches;
    
    if (regex_search(input, matches, doubleRegex)) {
        double val = stod(matches[1]);
        input = matches.suffix().str();
        return make_shared<Number>(val);
    }
    
    if (regex_search(input, matches, intRegex)) {
        double val = stod(matches[1]);
        input = matches.suffix().str();
        return make_shared<Number>(val);
    }
    
    return nullptr;
}
 
shared_ptr<Object> Parser::parseObjectArray(string& input) {
    if (input.empty() || input[0] != '{') {
        return nullptr;
    }

    input = input.substr(1);
    shared_ptr<ObjectArray> array = make_shared<ObjectArray>();
    skipWhitespace(input);
 
    if (!input.empty() && input[0] == '}') {
        input = input.substr(1);
        return array;
    }
 
    while (!input.empty()) {
        skipWhitespace(input);
 
        shared_ptr<Object> elem = parseObject(input);
        if (elem) {
            array->addElement(elem);
        }

        skipWhitespace(input);
 
        if (!input.empty() && input[0] == ',') {
            input = input.substr(1);
        } else if (!input.empty() && input[0] == '}') {
            input = input.substr(1);
            break;
        } else {
            cout << "Error: Expected ',' or '}'" << endl;
            break;
        }
    }
 
    return array;
}
 
shared_ptr<Object> Parser::parseObject(string& input) {
    regex varRegex(R"(^([a-zA-Z_][a-zA-Z0-9_]*))");
    smatch matches;
    
    skipWhitespace(input);
    if (input.empty()) {
        return nullptr;
    }

    if (input[0] == '{') {
        return parseObjectArray(input);
    }
    if (input[0] == '"' || input[0] == '\'') {
        return parseString(input);
    }
    if (isdigit(input[0]) || input[0] == '-') {
        return parseNumber(input);
    }
    
    if (regex_search(input, matches, varRegex)) {
        string varName = matches[1];
        input = matches.suffix().str();

        if (variables.count(varName)) {
            return variables[varName]->clone();
        } else {
            cout << "[Invalid assignment] " << varName << "  =" << endl;
            return nullptr;
        }
    }
 
    return nullptr;
}
 
shared_ptr<Object> Parser::parseExpression(string& input) {
    shared_ptr<Object> left = parseObject(input);
    if (!left) {
        return nullptr;
    }

    while (true) {
        skipWhitespace(input);
 
        if (!input.empty() && input[0] == '+') {
            input = input.substr(1);
            skipWhitespace(input);
            shared_ptr<Object> right = parseObject(input);
            
            if (!right) {
                break;
            }
            left = (*left) + (*right);
            
            if (!left) {
                return nullptr;
            }
        }
        else if (!input.empty() && input[0] == '^') {
            input = input.substr(1);
            skipWhitespace(input);
            shared_ptr<Object> right = parseObject(input);
            
            if (!right) {
                break;
            }

            left = (*left) ^ (*right);
        }
        else {
            break;
        }
    }
 
    return left;
}
 
shared_ptr<Object> Parser::applyIndexing(shared_ptr<Object> obj, string& input) {
    while (!input.empty() && input[0] == '[') {
        input = input.substr(1);
        smatch matches;
        regex intRegex(R"(^([0-9]+))");

        if (!regex_search(input, matches, intRegex)) {
            cout << "Error: Expected integer index." << endl;
            return nullptr;
        }

        int idx = stoi(matches[1]);
        input = matches.suffix().str();
 
        skipWhitespace(input);
        if (input.empty() || input[0] != ']') {
            cout << "Error: Expected ']'." << endl;
            return nullptr;
        }
        input = input.substr(1);
 
        obj = (*obj)[idx];
        if (!obj) {
          return nullptr;  
        } 
    }

    return obj;
}
 
void Parser::parseLine(string input) {
    regex assignRegex(R"(^([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*)");
    regex invalidVarRegex(R"(^([0-9][a-zA-Z0-9_]*|[.][a-zA-Z0-9_.]*|[a-zA-Z_][a-zA-Z0-9_]*[^a-zA-Z0-9_\s=][a-zA-Z0-9_]*|[a-zA-Z_][a-zA-Z0-9_]*\s+[a-zA-Z0-9_]+)\s*=)");
    smatch matches, invalidMatches;

    skipWhitespace(input);
    if (input.empty()) {
        return;
    }

    if (regex_search(input, invalidMatches, invalidVarRegex)) {
        cout << "[Invalid assignment] " << invalidMatches[1] << "  =" << endl;
        return;
    }
     
    if (regex_search(input, matches, assignRegex)) {
        string varName = matches[1];
        input = matches.suffix().str();
 
        shared_ptr<Object> value = parseExpression(input);
        if (value) {
            variables[varName] = value;
            cout << "[Assigned] " << varName << " = ";
            value->print();
            cout << endl;
        }

    } else {
        shared_ptr<Object> value = parseExpression(input);
        skipWhitespace(input);
 
        if (value && !input.empty() && input[0] == '[') {
            value = applyIndexing(value, input);
        }
 
        if (value) {
            cout << "[Result] ";
            value->print();
            cout << endl;
        }
    }
}