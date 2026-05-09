#include "Parser.hpp"
#include "Number.hpp"
#include "String.hpp"
#include "ObjectArray.hpp"
#include <regex>
#include <iostream>
 
map<string, shared_ptr<Object>> variables;
 
void skipWhitespace(string& input) {
    size_t i = 0;
    while (i < input.size() && isspace(input[i])) i++;
    input = input.substr(i);
}
 
shared_ptr<Object> parseString(string& input) {
    regex stringRegex(R"(^\"([^\"]*)\"|^'([^']*)')");
    smatch matches;
    if (regex_search(input, matches, stringRegex)) {
        string val = matches[1].matched ? matches[1] : matches[2];
        input = matches.suffix().str();
        return make_shared<String>(val);
    }
    return nullptr;
}
 
shared_ptr<Object> parseNumber(string& input) {
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
 
shared_ptr<Object> parseObjectArray(string& input) {
    if (input.empty() || input[0] != '{') return nullptr;
    input = input.substr(1);
 
    auto array = make_shared<ObjectArray>();
    skipWhitespace(input);
 
    if (!input.empty() && input[0] == '}') {
        input = input.substr(1);
        return array;
    }
 
    while (!input.empty()) {
        skipWhitespace(input);
 
        shared_ptr<Object> elem = parseObject(input);
        if (elem) array->addElement(elem);
 
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
 
shared_ptr<Object> parseObject(string& input) {
    skipWhitespace(input);
    if (input.empty()) return nullptr;
 
    if (input[0] == '{') return parseObjectArray(input);
    if (input[0] == '"' || input[0] == '\'') return parseString(input);
    if (isdigit(input[0]) || input[0] == '-') return parseNumber(input);
 
    regex varRegex(R"(^([a-zA-Z_][a-zA-Z0-9_]*))");
    smatch matches;
    if (regex_search(input, matches, varRegex)) {
        string varName = matches[1];
        input = matches.suffix().str();
        if (variables.count(varName)) {
            return variables[varName]->clone();
        } else {
            cout << "Error: Undefined variable '" << varName << "'" << endl;
            return nullptr;
        }
    }
 
    return nullptr;
}
 
shared_ptr<Object> parseExpression(string& input) {
    shared_ptr<Object> left = parseObject(input);
    if (!left) return nullptr;
 
    while (true) {
        skipWhitespace(input);
 
        if (!input.empty() && input[0] == '+') {
            input = input.substr(1);
            skipWhitespace(input);
            shared_ptr<Object> right = parseObject(input);
            if (!right) break;
            left = (*left) + (*right);
            if (!left) return nullptr;
        }
        else if (!input.empty() && input[0] == '^') {
            input = input.substr(1);
            skipWhitespace(input);
            shared_ptr<Object> right = parseObject(input);
            if (!right) break;
            left = (*left) ^ (*right);
        }
        else {
            break;
        }
    }
 
    return left;
}
 
shared_ptr<Object> applyIndexing(shared_ptr<Object> obj, string& input) {
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
        if (!obj) return nullptr;
    }
    return obj;
}
 
void parseLine(string input) {
    skipWhitespace(input);
    if (input.empty()) return;
 
    regex assignRegex(R"(^([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*)");
    smatch matches;
 
    if (regex_search(input, matches, assignRegex)) {
        string varName = matches[1];
        input = matches.suffix().str();
 
        shared_ptr<Object> value = parseExpression(input);
        if (value) {
            variables[varName] = value;
            cout << varName << " = ";
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
            value->print();
            cout << endl;
        }
    }
}