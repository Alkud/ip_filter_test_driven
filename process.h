#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <tuple>
#include <set>

using stringVector = std::vector<std::string>;
using ipTuple = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>;
//using ipList = std::list<ipTuple>;
//using ipVector = std::vector<ipTuple>;
using ipMultiset = std::multiset<ipTuple, std::greater<>>;
using containerType = ipMultiset;

stringVector split(const std::string& inputString, const char& delimiter) ;

ipTuple stringToTuple(const std::string& inputString);

containerType userInput(std::istream& inputStream);

void outputSorted(std::ostream& outputStream, containerType& container, bool ascending = true);

void outputFiltered(std::ostream& outputStream, const containerType& container, int byte3, int byte2 = -1, int byte1 = -1, int byte0 = -1);

void outputFilteredAny(std::ostream& outputStream, const containerType& container, const uint8_t byte);

void process(std::istream& inputStream, std::ostream& outputStream);

