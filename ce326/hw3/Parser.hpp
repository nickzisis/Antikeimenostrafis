#ifndef PARSER_HPP
#define PARSER_HPP
 
#include <string>
#include <map>
#include <memory>
#include "Object.hpp"
using namespace std;
 
extern map<string, shared_ptr<Object>> variables;
 
void skipWhitespace(string& input);
 
shared_ptr<Object> parseString(string& input);
shared_ptr<Object> parseNumber(string& input);
shared_ptr<Object> parseObjectArray(string& input);
shared_ptr<Object> parseObject(string& input);
shared_ptr<Object> parseExpression(string& input);
shared_ptr<Object> applyIndexing(shared_ptr<Object> obj, string& input);
 
void parseLine(string input);
 
#endif