#include "process.h"

#include <sstream>
#include <algorithm>

stringVector split(const std::string& inputString, const char& delimiter)
{
  stringVector result;
  size_t first {0U};
  size_t last{inputString.find_first_of(delimiter, 0)};
  while(last != std::string::npos)
  {
    result.push_back(inputString.substr(first, last - first));
    first = last + 1;
    last = inputString.find_first_of(delimiter, first);
  }
  if (result.size() == 0) // no legal delimiters found
  {
    last = inputString.find_first_not_of(".0123456789\n", 0); // find any delimiter
    if (std::string::npos == last) // delimiter is '.' or no delimiters
    {
      size_t start{};
      size_t pointPosition{inputString.find_first_of('.', start)}; // find 1st '.' position
      for (size_t i{}; i < 3; i++) // looking for 3 more '.'
      {
        if (std::string::npos == pointPosition) // '.' not found
          break;
        start = pointPosition + 1;
        pointPosition = inputString.find_first_of('.', start);
      }
      if (std::string::npos != pointPosition)
        last = pointPosition;
    }
  }
  result.push_back(inputString.substr(first, last - first));
  return result;
}

ipTuple stringToTuple(const std::string& inputString)
{
  std::stringstream tmpStream{inputString};
  char tmpChar;
  int b0{}, b1{}, b2{}, b3{};
  tmpStream >> b3 >> tmpChar >> b2 >> tmpChar >> b1 >> tmpChar >> b0;
  if ( b0 < 0   || b1 < 0   || b2 < 0   || b3 < 0 ||   // any octet is negative
       b0 > 255 || b1 > 255 || b2 > 255 || b3 > 255)   // any octet is greater than 255
  {
    b0 = b1 = b2 = b3 = 0;
  }
  return std::tie(b3, b2, b1, b0);
}

containerType userInput(std::istream& inputStream)
{
  containerType result{};
  std::string nextString;
  while(std::getline(inputStream, nextString))
  {
    std::string addressString{split(nextString, '\t').at(0)};
    //std::string addressString{"1.2.3.4"};
    ipTuple addressTuple{stringToTuple(addressString)};
    //ipTuple addressTuple{1, 2, 3, 4};
    //result.push_back(addressTuple);
    result.insert(addressTuple);
  }
  return result;
}

void outputSorted(std::ostream& outputStream, containerType& container, bool ascending)
{
  //if (ascending)
  //  std::sort(container.begin(), container.end(), std::less<>());
    //container.sort(std::less<>());
  //else
  //  std::sort(container.begin(), container.end(), std::greater<>());
    //container.sort(std::greater<>());
  for (auto addressTuple : container)
  {
    int b0 {std::get<3>(addressTuple)};
    int b1 {std::get<2>(addressTuple)};
    int b2 {std::get<1>(addressTuple)};
    int b3 {std::get<0>(addressTuple)};
    outputStream << b3 << '.' << b2 << '.' << b1 << '.' << b0 << std::endl;
  }
}

void outputFiltered(std::ostream& outputStream, const containerType& container, int byte3, int byte2, int byte1, int byte0)
{
  for(auto addressTuple : container)
  {
    int b0 {std::get<3>(addressTuple)};
    int b1 {std::get<2>(addressTuple)};
    int b2 {std::get<1>(addressTuple)};
    int b3 {std::get<0>(addressTuple)};
    if ( byte3 ==  b3 &&
        (byte2 == -1 || byte2 == b2) &&
        (byte1 == -1 || byte1 == b1) &&
        (byte0 == -1 || byte0 == b0)   )
    {
      outputStream << b3 << '.' << b2 << '.' << b1 << '.' << b0 << std::endl;
    }
  }
}

void outputFilteredAny(std::ostream& outputStream, const containerType& container, const uint8_t byte)
{
  for(auto addressTuple : container)
  {
    int b0 {std::get<3>(addressTuple)};
    int b1 {std::get<2>(addressTuple)};
    int b2 {std::get<1>(addressTuple)};
    int b3 {std::get<0>(addressTuple)};
    if (byte == b0 || byte == b1 ||
        byte == b2 || byte == b3   )
    {
      outputStream << b3 << '.' << b2 << '.' << b1 << '.' << b0 << std::endl;
    }
  }
}

void process(std::istream& inputStream, std::ostream& outputStream)
{
  /* User input */
  containerType addresses{userInput(inputStream)};
  /* Output full sorted IP list */
  outputSorted(outputStream, addresses, false);
  /* Filter 1.*.*.* */
  outputFiltered(outputStream, addresses, 1);
  /* Filter 46.70.*.* */
  outputFiltered(outputStream, addresses, 46, 70);
  /* Filter any containing 46 */
  outputFilteredAny(outputStream, addresses, 46);
}


