// ip_filter_boost_test.cpp in Otus Homework #2

#define BOOST_TEST_MODULE IP_FILTER_BOOST_TEST

#include <boost/test/unit_test.hpp>
#include "process.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <numeric>


BOOST_AUTO_TEST_SUITE(user_input_test)

BOOST_AUTO_TEST_CASE(test_split_lengths)
{
  /* Test split function: compairing input & output strings lengths */
  const size_t TEST_COUNT{10};
  std::string inputString{};
  stringVector outputVector{};
  std::srand(std::time(nullptr));

  std::cout << "TEST_SPLIT_LENGTHS" << std::endl;

  for (size_t testNumber{}; testNumber < TEST_COUNT; testNumber++)
  {
    int b0{std::rand() % 255};
    int b1{std::rand() % 255};
    int b2{std::rand() % 255};
    int b3{std::rand() % 255};
    int text2{std::rand() % 2055};
    int text3{std::rand() % 877};
    std::stringstream tempStream{};
    tempStream << b3 << '.' << b2 << '.' << b1 << '.' << b0 << '\t'
               << text2 << '\t' << text3 << '\n';
    inputString = tempStream.str();
    outputVector = split(inputString, '\t');

    if (inputString.length() - 2 !=
        outputVector[0].length() +
        outputVector[1].length() +
        outputVector[2].length()    )
    {
      std::cout << "input length: " << inputString.length() << " | " <<
                   "reply length + 2: " << 2 + outputVector[0].length() +
                   outputVector[1].length() + outputVector[2].length() << std::endl;
    }

    BOOST_CHECK(outputVector.size() == 3);

    BOOST_CHECK(inputString.length() - 2 ==
                outputVector[0].length() +
                outputVector[1].length() +
                outputVector[2].length()  );
  }
}

BOOST_AUTO_TEST_CASE(test_split_content)
{
  /* Test split function: check whether concatenating output strings results in the input string */
  const size_t TEST_COUNT{10};
  std::string inputString{};
  stringVector outputVector{};
  std::srand(std::time(nullptr));

  std::cout << std::endl << "TEST_SPLIT_CONTENT" << std::endl;

  for (size_t testNumber{}; testNumber < TEST_COUNT; testNumber++)
  {
    int b0{std::rand() % 255};
    int b1{std::rand() % 255};
    int b2{std::rand() % 255};
    int b3{std::rand() % 255};
    int text2{std::rand() % 9999};
    int text3{std::rand() % 9999};
    std::stringstream tempStream{};
    tempStream << b3 << '.' << b2 << '.' << b1 << '.' << b0 << '\t'
               << text2 << '\t' << text3 << '\n';
    inputString = tempStream.str();
    outputVector = split(inputString, '\t');

    if (inputString !=
        outputVector[0] + '\t' +
        outputVector[1] + '\t' +
        outputVector[2]  )
    {
      std::cout << "       input: " << inputString <<
                   "concat reply: " <<
                   outputVector[0] + '\t' + outputVector[1] + '\t' +
                   outputVector[2]  << std::endl;
    }

    BOOST_CHECK(outputVector.size() == 3);

    BOOST_CHECK(inputString ==
                outputVector[0] + '\t' +
                outputVector[1] + '\t' +
                outputVector[2]  );
  }
}

BOOST_AUTO_TEST_CASE(test_wrong_input)
{
  /* Wrong delimiters */
  const size_t TEST_COUNT{10};
  std::string inputString{};
  stringVector outputVector{};
  std::srand(std::time(nullptr));

  std::cout << "TEST_WRONG_INPUT" << std::endl;

  for (size_t testNumber{}; testNumber < TEST_COUNT; testNumber++)
  {
    int b0{std::rand() % 255};
    int b1{std::rand() % 255};
    int b2{std::rand() % 255};
    int b3{std::rand() % 255};
    int text2{std::rand() % 9999};
    int text3{std::rand() % 9999};
    char delimiter {32 + rand() % 15};
    std::stringstream tempStream{};
    std::string testString{};
    tempStream << b3 << '.' << b2 << '.' << b1 << '.' << b0;
    testString = tempStream.str();
    tempStream << delimiter << text2 << delimiter << text3 << '\n';
    inputString = tempStream.str();
    outputVector = split(inputString, '\t');

    if (outputVector[0] != testString)
    {
      std::cout << "input: " << inputString << "reply: " <<
                   outputVector[0] << std::endl;
    }

    BOOST_CHECK(testString == outputVector[0]);
  }

  /* Empty string input */
  inputString = "";
  outputVector = split(inputString, '\t');

  BOOST_CHECK(outputVector.size() == 1);

  BOOST_CHECK(inputString == outputVector[0]);
}

BOOST_AUTO_TEST_SUITE_END() // user_input_test

BOOST_AUTO_TEST_SUITE(address_parsing_test)

BOOST_AUTO_TEST_CASE(test_conversion_correctness)
{
  const size_t TEST_COUNT{10};
  std::string inputString{};
  stringVector outputVector{};
  ipTuple outputTuple;
  std::srand(std::time(nullptr));

  std::cout << std::endl << "TEST_CONVERSION_CORRECTNESS" << std::endl;

  for (size_t testNumber{}; testNumber < TEST_COUNT; testNumber++)
  {
    int b0{std::rand() % 255};
    int b1{std::rand() % 255};
    int b2{std::rand() % 255};
    int b3{std::rand() % 255};
    int text2{std::rand() % 9999};
    int text3{std::rand() % 9999};
    std::stringstream tempStream{};
    tempStream << b3 << '.' << b2 << '.' << b1 << '.' << b0 << '\t'
               << text2 << '\t' << text3 << '\n';
    inputString = tempStream.str();
    outputVector = split(inputString, '\t');
    outputTuple = stringToTuple(outputVector[0]);

    if (outputTuple != std::tie(b3, b2, b1, b0))
    {
      std::cout << "input: " << inputString <<
                   "reply: " << (int)std::get<0>(outputTuple) << '.'
                             << (int)std::get<1>(outputTuple) << '.'
                             << (int)std::get<2>(outputTuple) << '.'
                             << (int)std::get<3>(outputTuple) << std::endl;
    }

    BOOST_CHECK(outputTuple == std::tie(b3, b2, b1, b0));
  }
}

BOOST_AUTO_TEST_CASE(test_wrong_delimiters_1)
{
  const size_t TEST_COUNT{10};
  std::string inputString{};
  stringVector outputVector{};
  ipTuple outputTuple;
  std::srand(std::time(nullptr));

  std::cout << std::endl << "TEST_WRONG_DELIMITERS_1" << std::endl;

  for (size_t testNumber{}; testNumber < TEST_COUNT; testNumber++)
  {
    int b0{std::rand() % 255};
    int b1{std::rand() % 255};
    int b2{std::rand() % 255};
    int b3{std::rand() % 255};
    int text2{std::rand() % 9999};
    int text3{std::rand() % 9999};
    std::stringstream tempStream{};
    tempStream << b3 << '\\' << b2 << '\\' << b1 << '\\' << b0 << '\t'
               << text2 << '\t' << text3 << '\n';
    inputString = tempStream.str();
    outputVector = split(inputString, '\t');
    outputTuple = stringToTuple(outputVector[0]);

    if (outputTuple != std::tie(b3, b2, b1, b0))
    {
      std::cout << "input: " << inputString <<
                   "reply: " << (int)std::get<0>(outputTuple) << '.'
                             << (int)std::get<1>(outputTuple) << '.'
                             << (int)std::get<2>(outputTuple) << '.'
                             << (int)std::get<3>(outputTuple) << std::endl;
    }
    BOOST_CHECK(outputTuple == std::tie(b3, b2, b1, b0));
  }
}

BOOST_AUTO_TEST_CASE(test_wrong_delimiters_2)
{
  const size_t TEST_COUNT{10};
  std::string inputString{};
  stringVector outputVector{};
  ipTuple outputTuple;
  std::srand(std::time(nullptr));

  std::cout << std::endl << "TEST_WRONG_DELIMITERS_2" << std::endl;

  for (size_t testNumber{}; testNumber < TEST_COUNT; testNumber++)
  {
    int b0{std::rand() % 255};
    int b1{std::rand() % 255};
    int b2{std::rand() % 255};
    int b3{std::rand() % 255};
    int text2{std::rand() % 9999};
    int text3{std::rand() % 9999};
    std::stringstream tempStream{};
    tempStream << b3 << ':' << b2 << ':' << b1 << ':' << b0 << '\t'
               << text2 << '\t' << text3 << '\n';
    inputString = tempStream.str();
    outputVector = split(inputString, '\t');
    outputTuple = stringToTuple(outputVector[0]);

    if (outputTuple != std::tie(b3, b2, b1, b0))
    {
      std::cout << "input: " << inputString <<
                   "reply: " << (int)std::get<0>(outputTuple) << '.'
                             << (int)std::get<1>(outputTuple) << '.'
                             << (int)std::get<2>(outputTuple) << '.'
                             << (int)std::get<3>(outputTuple) << std::endl;
    }

    BOOST_CHECK(outputTuple == std::tie(b3, b2, b1, b0));
  }
}

BOOST_AUTO_TEST_CASE(test_wrong_delimiters_3)
{
  const size_t TEST_COUNT{10};
  std::string inputString{};
  stringVector outputVector{};
  ipTuple outputTuple;
  std::srand(std::time(nullptr));

  std::cout << std::endl << "TEST_WRONG_DELIMITERS_3" << std::endl;

  for (size_t testNumber{}; testNumber < TEST_COUNT; testNumber++)
  {
    int b0{std::rand() % 255};
    int b1{std::rand() % 255};
    int b2{std::rand() % 255};
    int b3{std::rand() % 255};
    int text2{std::rand() % 9999};
    int text3{std::rand() % 9999};
    std::stringstream tempStream{};
    tempStream << b3 << '.' << b2 << ':' << b1 << '\\' << b0 << '\t'
               << text2 << '\t' << text3 << '\n';
    inputString = tempStream.str();
    outputVector = split(inputString, '\t');
    outputTuple = stringToTuple(outputVector[0]);

    if (outputTuple != std::tie(b3, b2, b1, b0))
    {
      std::cout << "input: " << inputString <<
                   "reply: " << (int)std::get<0>(outputTuple) << '.'
                             << (int)std::get<1>(outputTuple) << '.'
                             << (int)std::get<2>(outputTuple) << '.'
                             << (int)std::get<3>(outputTuple) << std::endl;
    }
    BOOST_CHECK(outputTuple == std::tie(b3, b2, b1, b0));
  }
}

BOOST_AUTO_TEST_CASE(test_illegal_addresses)
{
  const size_t TEST_COUNT{10};
  std::string inputString{};
  stringVector outputVector{};
  ipTuple outputTuple;
  std::srand(std::time(nullptr));

  std::cout << std::endl << "TEST_ILLEGAL_ADDRESSES" << std::endl;

  for (size_t testNumber{}; testNumber < TEST_COUNT; testNumber++)
  {
    int b0{255 + std::rand() % 100};
    int b1{255 + std::rand() % 1000};
    int b2{std::rand() % 255 - 255};
    int b3{std::rand() % 255};
    int text2{std::rand() % 9999};
    int text3{std::rand() % 9999};
    std::stringstream tempStream{};
    tempStream << b3 << '.' << b2 << ':' << b1 << '\\' << b0 << '\t'
               << text2 << '\t' << text3 << '\n';
    inputString = tempStream.str();
    outputVector = split(inputString, '\t');
    outputTuple = stringToTuple(outputVector[0]);

    if (outputTuple != ipTuple(0, 0, 0, 0))
    {
      std::cout << "input: " << inputString <<
                   "reply: " << (int)std::get<0>(outputTuple) << '.'
                             << (int)std::get<1>(outputTuple) << '.'
                             << (int)std::get<2>(outputTuple) << '.'
                             << (int)std::get<3>(outputTuple) << std::endl;

    }
    BOOST_CHECK(outputTuple == ipTuple(0, 0, 0, 0));
  }
}

BOOST_AUTO_TEST_SUITE_END() // address_parsing_test

BOOST_AUTO_TEST_SUITE(descending_sorting_test)

BOOST_AUTO_TEST_CASE(check_sorted_records_count)
{
  const size_t TEST_COUNT{10};
  std::cout << std::endl << "CHECK_SORTED_RECORDS_COUNT" << std::endl;

  for (size_t testIdx{0}; testIdx < TEST_COUNT; testIdx++)
  {
    int addressCount{std::rand() % 1000};

    std::srand(std::time(nullptr));

    std::stringstream sendStream{};
    std::stringstream receiveStream{};

    for (size_t inputStringIdx{}; inputStringIdx < addressCount; inputStringIdx++)
    {
      int b0{std::rand() % 255};
      int b1{std::rand() % 255};
      int b2{std::rand() % 255};
      int b3{std::rand() % 255};
      int text2{std::rand() % 9999};
      int text3{std::rand() % 9999};
      sendStream << b3 << '.' << b2 << '.' << b1 << '.' << b0 << '\t'
                 << text2 << '\t' << text3 << '\n';
    }
    auto tmpAddresses {userInput(sendStream)};
    outputSorted(receiveStream, tmpAddresses, false);

    std::string nextString {};
    stringVector sortedVector{};
    while(std::getline(receiveStream, nextString))
    {
      sortedVector.push_back(nextString);
    }

    if (addressCount != sortedVector.size())
    {
      std::cout << "input size  : "  << addressCount << std::endl
                << "sorted size : "  << sortedVector.size() << std::endl;
    }
    BOOST_CHECK(addressCount == sortedVector.size());
  }
}

BOOST_AUTO_TEST_CASE(check_sorting_correctness)
{
  const size_t TEST_COUNT{10};
  std::cout << std::endl << "CHECK_SORTING_CORRECTNESS" << std::endl;

  for (size_t testIdx{0}; testIdx < TEST_COUNT; testIdx++)
  {
    int addressCount{1 + std::rand() % 100};

    std::srand(std::time(nullptr));

    std::stringstream sendStream{};
    std::stringstream receiveStream{};

    for (size_t inputStringIdx{}; inputStringIdx < addressCount; inputStringIdx++)
    {
      int b0{std::rand() % 255};
      int b1{std::rand() % 255};
      int b2{std::rand() % 255};
      int b3{std::rand() % 255};
      int text2{std::rand() % 9999};
      int text3{std::rand() % 9999};
      sendStream << b3 << '.' << b2 << '.' << b1 << '.' << b0 << '\t'
                 << text2 << '\t' << text3 << '\n';
    }
    auto tmpAddresses {userInput(sendStream)};
    outputSorted(receiveStream, tmpAddresses, false);

    std::string nextString {};
    stringVector sortedVector{};
    while(std::getline(receiveStream, nextString))
    {
      sortedVector.push_back(nextString);
    }

    size_t wrongRecordsCount{};

    for (size_t i{1}; i < sortedVector.size(); i++)
    {
      std::stringstream tmpStreamCur{sortedVector[i]};
      char tmpChar;
      int b0cur{}, b1cur{}, b2cur{}, b3cur{};
      tmpStreamCur >> b3cur >> tmpChar >> b2cur >> tmpChar >> b1cur >> tmpChar >> b0cur;
      std::stringstream tmpStreamPrev{sortedVector[i - 1]};
      int b0prev{}, b1prev{}, b2prev{}, b3prev{};
      tmpStreamPrev >> b3prev >> tmpChar >> b2prev >> tmpChar >> b1prev >> tmpChar >> b0prev;
      if ((b3cur - b3prev > 0 ) ||
          (b3prev == b3cur && (b2cur - b2prev > 0)) ||
          (b3prev == b3cur && b2prev == b2cur && (b1cur - b1prev > 0)) ||
          (b3prev == b3cur && b2prev == b2cur && b1prev == b1cur && (b0cur - b0prev > 0)) )
      {
        std::cout << "wrong order: " << tmpStreamCur.str() <<
                     " follows " << tmpStreamPrev.str() << std::endl;
        wrongRecordsCount++;
      }
    }

    BOOST_CHECK(wrongRecordsCount == 0);
  }
}

BOOST_AUTO_TEST_SUITE_END() // descending_sorting_test

BOOST_AUTO_TEST_SUITE(filter_1_octet_test)

BOOST_AUTO_TEST_CASE(check_filter_1_octet_filtered)
{
  const size_t TEST_COUNT{10};
  std::cout << std::endl << "CHECK_FILTER_1_OCTET_FILTERED" << std::endl;

  for (size_t testIdx{0}; testIdx < TEST_COUNT; testIdx++)
  {
    int addressCount{1 + std::rand() % 100};
    std::srand(std::time(nullptr));
    std::stringstream sendStream{};
    std::stringstream sortedStream{};
    std::stringstream filteredStream{};

    int filterValue{std::rand() % 255};

    for (size_t inputStringIdx{}; inputStringIdx < addressCount; inputStringIdx++)
    {
      int b0{std::rand() % 255};
      int b1{std::rand() % 255};
      int b2{std::rand() % 255};
      int b3{std::rand() % 255};
      int text2{std::rand() % 9999};
      int text3{std::rand() % 9999};
      sendStream << b3 << '.' << b2 << '.' << b1 << '.' << b0 << '\t'
                 << text2 << '\t' << text3 << '\n';
    }
    auto tmpAddresses {userInput(sendStream)};
    outputSorted(sortedStream, tmpAddresses, false);
    outputFiltered(filteredStream, tmpAddresses, filterValue);

    std::string nextString {};
    stringVector sortedVector{};
    stringVector filteredVector{};
    while(std::getline(sortedStream, nextString))
    {
      sortedVector.push_back(nextString);
    }
    while(std::getline(filteredStream, nextString))
    {
      filteredVector.push_back(nextString);
    }

    size_t wrongRecordsCount{};

    for (size_t i{0}; i < filteredVector.size(); i++)
    {
      std::stringstream tmpStreamCur{filteredVector[i]};
      char tmpChar;
      int b0{}, b1{}, b2{}, b3{};
      tmpStreamCur >> b3 >> tmpChar >> b2 >> tmpChar >> b1 >> tmpChar >> b0;
      if (b3 != filterValue)
      {
        std::cout << "wrong filter output: " << tmpStreamCur.str() << std::endl;
        std::cout << "       filter value: " << filterValue << std::endl;
        wrongRecordsCount++;
      }
    }
    BOOST_CHECK(wrongRecordsCount == 0);
  }
}

BOOST_AUTO_TEST_CASE(check_filter_1_octet_rejected)
{
  const size_t TEST_COUNT{10};
  std::cout << std::endl << "CHECK_FILTER_1_OCTET_REJECTED" << std::endl;

  for (size_t testIdx{0}; testIdx < TEST_COUNT; testIdx++)
  {
    int addressCount{1 + std::rand() % 100};
    std::srand(std::time(nullptr));
    std::stringstream sendStream{};
    std::stringstream sortedStream{};
    std::stringstream filteredStream{};

    int filterValue{std::rand() % 255};

    for (size_t inputStringIdx{}; inputStringIdx < addressCount; inputStringIdx++)
    {
      int b0{std::rand() % 255};
      int b1{std::rand() % 255};
      int b2{std::rand() % 255};
      int b3{std::rand() % 255};
      int text2{std::rand() % 9999};
      int text3{std::rand() % 9999};
      sendStream << b3 << '.' << b2 << '.' << b1 << '.' << b0 << '\t'
                 << text2 << '\t' << text3 << '\n';
    }
    auto tmpAddresses {userInput(sendStream)};
    outputSorted(sortedStream, tmpAddresses, false);
    outputFiltered(filteredStream, tmpAddresses, filterValue);

    std::string nextString {};
    stringVector sortedVector{};
    stringVector filteredVector{};
    while(std::getline(sortedStream, nextString))
    {
      sortedVector.push_back(nextString);
    }
    while(std::getline(filteredStream, nextString))
    {
      filteredVector.push_back(nextString);
    }

    size_t wrongRecordsCount{};

    stringVector rejectedVector{};
    for (size_t i{0}; i < sortedVector.size(); i++)
    {
      if (std::find(filteredVector.begin(), filteredVector.end(), sortedVector[i])
          == filteredVector.end())
      {
        rejectedVector.push_back(sortedVector[i]);
        std::stringstream tmpStreamCur{sortedVector[i]};
        char tmpChar;
        int b0{}, b1{}, b2{}, b3{};
        tmpStreamCur >> b3 >> tmpChar >> b2 >> tmpChar >> b1 >> tmpChar >> b0;
        if (b3 == filterValue)
        {
          std::cout << "wrong string rejected: " << tmpStreamCur.str() << std::endl;
          std::cout << "         filter value: " << filterValue << std::endl;
          wrongRecordsCount++;
        }
      }
    }
    if (sortedVector.size() !=
        filteredVector.size() + rejectedVector.size())
    {
      std::cout << "wrong number of filtered/rejected records: "
                << "sotred count: " << sortedVector.size() << std::endl
                << "filtered count: " << filteredVector.size() << std::endl
                << "rejected count: " << rejectedVector.size() << std::endl;
    }
    BOOST_CHECK (sortedVector.size() ==
                 filteredVector.size() + rejectedVector.size());
    BOOST_CHECK(wrongRecordsCount == 0);
  }
}

BOOST_AUTO_TEST_SUITE_END() // filter_1_octet_test

BOOST_AUTO_TEST_SUITE(filter_2_octets_test)

BOOST_AUTO_TEST_CASE(check_filter_2_octets_filtered)
{
  const size_t TEST_COUNT{10};
  std::cout << std::endl << "CHECK_FILTER_2_OCTETS_FILTERED" << std::endl;

  for (size_t testIdx{0}; testIdx < TEST_COUNT; testIdx++)
  {
    int addressCount{1 + std::rand() % 100};
    std::srand(std::time(nullptr));
    std::stringstream sendStream{};
    std::stringstream sortedStream{};
    std::stringstream filteredStream{};

    int filterValue1{std::rand() % 255};
    int filterValue2{std::rand() % 255};


    for (size_t inputStringIdx{}; inputStringIdx < addressCount; inputStringIdx++)
    {
      int b0{std::rand() % 255};
      int b1{std::rand() % 255};
      int b2{std::rand() % 255};
      int b3{std::rand() % 255};
      int text2{std::rand() % 9999};
      int text3{std::rand() % 9999};
      sendStream << b3 << '.' << b2 << '.' << b1 << '.' << b0 << '\t'
                 << text2 << '\t' << text3 << '\n';
    }
    auto tmpAddresses {userInput(sendStream)};
    outputSorted(sortedStream, tmpAddresses, false);
    outputFiltered(filteredStream, tmpAddresses, filterValue1, filterValue2);

    std::string nextString {};
    stringVector sortedVector{};
    stringVector filteredVector{};
    while(std::getline(sortedStream, nextString))
    {
      sortedVector.push_back(nextString);
    }
    while(std::getline(filteredStream, nextString))
    {
      filteredVector.push_back(nextString);
    }

    size_t wrongRecordsCount{};

    for (size_t i{0}; i < filteredVector.size(); i++)
    {
      std::stringstream tmpStreamCur{filteredVector[i]};
      char tmpChar;
      int b0{}, b1{}, b2{}, b3{};
      tmpStreamCur >> b3 >> tmpChar >> b2 >> tmpChar >> b1 >> tmpChar >> b0;
      if (b3 != filterValue1 || b2 != filterValue2)
      {
        std::cout << "wrong filter output: " << tmpStreamCur.str() << std::endl;
        std::cout << "      filter values: " << filterValue1 << "," << filterValue2 << std::endl;
        wrongRecordsCount++;
      }
    }
    BOOST_CHECK(wrongRecordsCount == 0);
  }
}

BOOST_AUTO_TEST_CASE(check_filter_2_octets_rejected)
{
  const size_t TEST_COUNT{10};
  std::cout << std::endl << "CHECK_FILTER_2_OCTETS_REJECTED" << std::endl;

  for (size_t testIdx{0}; testIdx < TEST_COUNT; testIdx++)
  {
    int addressCount{1 + std::rand() % 100};
    std::srand(std::time(nullptr));
    std::stringstream sendStream{};
    std::stringstream sortedStream{};
    std::stringstream filteredStream{};

    int filterValue1{std::rand() % 255};
    int filterValue2{std::rand() % 255};



    for (size_t inputStringIdx{}; inputStringIdx < addressCount; inputStringIdx++)
    {
      int b0{std::rand() % 255};
      int b1{std::rand() % 255};
      int b2{std::rand() % 255};
      int b3{std::rand() % 255};
      int text2{std::rand() % 9999};
      int text3{std::rand() % 9999};
      sendStream << b3 << '.' << b2 << '.' << b1 << '.' << b0 << '\t'
                 << text2 << '\t' << text3 << '\n';
    }
    auto tmpAddresses {userInput(sendStream)};
    outputSorted(sortedStream, tmpAddresses, false);
    outputFiltered(filteredStream, tmpAddresses, filterValue1, filterValue2);

    std::string nextString {};
    stringVector sortedVector{};
    stringVector filteredVector{};
    while(std::getline(sortedStream, nextString))
    {
      sortedVector.push_back(nextString);
    }
    while(std::getline(filteredStream, nextString))
    {
      filteredVector.push_back(nextString);
    }

    size_t wrongRecordsCount{};

    stringVector rejectedVector{};
    for (size_t i{0}; i < sortedVector.size(); i++)
    {
      if (std::find(filteredVector.begin(), filteredVector.end(), sortedVector[i])
          == filteredVector.end())
      {
        rejectedVector.push_back(sortedVector[i]);
        std::stringstream tmpStreamCur{sortedVector[i]};
        char tmpChar;
        int b0{}, b1{}, b2{}, b3{};
        tmpStreamCur >> b3 >> tmpChar >> b2 >> tmpChar >> b1 >> tmpChar >> b0;
        if (b3 == filterValue1 && b2 == filterValue2)
        {
          std::cout << "wrong string rejected: " << tmpStreamCur.str() << std::endl;
          std::cout << "        filter values: " << filterValue1 << "," << filterValue2 << std::endl;
          wrongRecordsCount++;
        }
      }
    }
    if (sortedVector.size() !=
        filteredVector.size() + rejectedVector.size())
    {
      std::cout << "wrong number of filtered/rejected records: "
                << "sotred count: " << sortedVector.size() << std::endl
                << "filtered count: " << filteredVector.size() << std::endl
                << "rejected count: " << rejectedVector.size() << std::endl;
    }
    BOOST_CHECK (sortedVector.size() ==
                 filteredVector.size() + rejectedVector.size());
    BOOST_CHECK(wrongRecordsCount == 0);
  }
}

BOOST_AUTO_TEST_SUITE_END() // filter_2_octets_test

BOOST_AUTO_TEST_SUITE(filter_1_any_test)

BOOST_AUTO_TEST_CASE(check_filter_1_any_filtered)
{
  const size_t TEST_COUNT{10};
  std::cout << std::endl << "CHECK_FILTER_1_ANY_FILTERED" << std::endl;

  for (size_t testIdx{0}; testIdx < TEST_COUNT; testIdx++)
  {
    int addressCount{1 + std::rand() % 100};
    std::srand(std::time(nullptr));
    std::stringstream sendStream{};
    std::stringstream sortedStream{};
    std::stringstream filteredStream{};

    int filterValue{std::rand() % 255};

    for (size_t inputStringIdx{}; inputStringIdx < addressCount; inputStringIdx++)
    {
      int b0{std::rand() % 255};
      int b1{std::rand() % 255};
      int b2{std::rand() % 255};
      int b3{std::rand() % 255};
      int text2{std::rand() % 9999};
      int text3{std::rand() % 9999};
      sendStream << b3 << '.' << b2 << '.' << b1 << '.' << b0 << '\t'
                 << text2 << '\t' << text3 << '\n';
    }
    auto tmpAddresses {userInput(sendStream)};
    outputSorted(sortedStream, tmpAddresses, false);
    outputFilteredAny(filteredStream, tmpAddresses, filterValue);

    std::string nextString {};
    stringVector sortedVector{};
    stringVector filteredVector{};
    while(std::getline(sortedStream, nextString))
    {
      sortedVector.push_back(nextString);
    }
    while(std::getline(filteredStream, nextString))
    {
      filteredVector.push_back(nextString);
    }

    size_t wrongRecordsCount{};

    for (size_t i{0}; i < filteredVector.size(); i++)
    {
      std::stringstream tmpStreamCur{filteredVector[i]};
      char tmpChar;
      int b0{}, b1{}, b2{}, b3{};
      tmpStreamCur >> b3 >> tmpChar >> b2 >> tmpChar >> b1 >> tmpChar >> b0;
      if (b3 != filterValue && b2 != filterValue &&
          b1 != filterValue && b0 != filterValue)
      {
        std::cout << "wrong filter output: " << tmpStreamCur.str() << std::endl;
        wrongRecordsCount++;
      }
    }
    BOOST_CHECK(wrongRecordsCount == 0);
  }
}

BOOST_AUTO_TEST_CASE(check_filter_1_any_rejected)
{
  const size_t TEST_COUNT{10};
  std::cout << std::endl << "CHECK_FILTER_1_ANY_REJECTED" << std::endl;

  for (size_t testIdx{0}; testIdx < TEST_COUNT; testIdx++)
  {
    int addressCount{1 + std::rand() % 100};
    std::srand(std::time(nullptr));
    std::stringstream sendStream{};
    std::stringstream sortedStream{};
    std::stringstream filteredStream{};

    int filterValue{std::rand() % 255};

    for (size_t inputStringIdx{}; inputStringIdx < addressCount; inputStringIdx++)
    {
      int b0{std::rand() % 255};
      int b1{std::rand() % 255};
      int b2{std::rand() % 255};
      int b3{std::rand() % 255};
      int text2{std::rand() % 9999};
      int text3{std::rand() % 9999};
      sendStream << b3 << '.' << b2 << '.' << b1 << '.' << b0 << '\t'
                 << text2 << '\t' << text3 << '\n';
    }
    auto tmpAddresses {userInput(sendStream)};
    outputSorted(sortedStream, tmpAddresses, false);
    outputFilteredAny(filteredStream, tmpAddresses, filterValue);

    std::string nextString {};
    stringVector sortedVector{};
    stringVector filteredVector{};
    while(std::getline(sortedStream, nextString))
    {
      sortedVector.push_back(nextString);
    }
    while(std::getline(filteredStream, nextString))
    {
      filteredVector.push_back(nextString);
    }

    size_t wrongRecordsCount{};

    stringVector rejectedVector{};
    for (size_t i{0}; i < sortedVector.size(); i++)
    {
      if (std::find(filteredVector.begin(), filteredVector.end(), sortedVector[i])
          == filteredVector.end())
      {
        rejectedVector.push_back(sortedVector[i]);
        std::stringstream tmpStreamCur{sortedVector[i]};
        char tmpChar;
        int b0{}, b1{}, b2{}, b3{};
        tmpStreamCur >> b3 >> tmpChar >> b2 >> tmpChar >> b1 >> tmpChar >> b0;
        if (b3 == filterValue || b2 == filterValue ||
            b1 == filterValue || b0 == filterValue   )
        {
          std::cout << "wrong string rejected: " << tmpStreamCur.str() << std::endl;
          std::cout << "        filter values: " << filterValue << std::endl;
          wrongRecordsCount++;
        }
      }
    }
    if (sortedVector.size() !=
        filteredVector.size() + rejectedVector.size())
    {
      std::cout << "wrong number of filtered/rejected records: "
                << "sotred count: " << sortedVector.size() << std::endl
                << "filtered count: " << filteredVector.size() << std::endl
                << "rejected count: " << rejectedVector.size() << std::endl;
    }
    BOOST_CHECK (sortedVector.size() ==
                 filteredVector.size() + rejectedVector.size());
    BOOST_CHECK(wrongRecordsCount == 0);
  }
}

BOOST_AUTO_TEST_SUITE_END() // filter_1_any_test

BOOST_AUTO_TEST_SUITE(time_complexity)

BOOST_AUTO_TEST_CASE(time_complexity_parts)
{
  std::cout << std::endl << "TIME_COMPLEXITY_PARTIAL" << std::endl;
  int addressCount{10000};
  std::cout << std::endl << "Input records count: " << addressCount << std::endl;
  const size_t TEST_COUNT {10};
  std::vector<std::vector<long unsigned int>> times{};
  times.resize(5);
  for (size_t testIdx{}; testIdx < TEST_COUNT; testIdx++)
  {
    std::srand(std::time(nullptr));
    std::stringstream sendStream{};
    std::stringstream receiveStream{};

    int filterValue1{std::rand() % 255};
    int filterValue2{std::rand() % 255};
    int filterValue3{std::rand() % 255};
    int filterValue4{std::rand() % 255};

    for (size_t inputStringIdx{}; inputStringIdx < addressCount; inputStringIdx++)
    {
      int b0{std::rand() % 255};
      int b1{std::rand() % 255};
      int b2{std::rand() % 255};
      int b3{std::rand() % 255};
      int text2{std::rand() % 9999};
      int text3{std::rand() % 9999};
      sendStream << b3 << '.' << b2 << '.' << b1 << '.' << b0 << '\t'
                 << text2 << '\t' << text3 << '\n';
    }

    auto startTime = std::chrono::high_resolution_clock::now();
    auto tmpAddresses {userInput(sendStream)};
    auto finishTime = std::chrono::high_resolution_clock::now();
    times[0].push_back(std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime).count());

    startTime = std::chrono::high_resolution_clock::now();
    outputSorted(receiveStream, tmpAddresses, false);
    finishTime = std::chrono::high_resolution_clock::now();
    times[1].push_back(std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime).count());

    startTime = std::chrono::high_resolution_clock::now();
    outputFiltered(receiveStream, tmpAddresses, filterValue1);
    finishTime = std::chrono::high_resolution_clock::now();
    times[2].push_back(std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime).count());

    startTime = std::chrono::high_resolution_clock::now();
    outputFiltered(receiveStream, tmpAddresses, filterValue2, filterValue3);
    finishTime = std::chrono::high_resolution_clock::now();
    times[3].push_back(std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime).count());

    startTime = std::chrono::high_resolution_clock::now();
    outputFilteredAny(receiveStream, tmpAddresses, filterValue4);
    finishTime = std::chrono::high_resolution_clock::now();
    times[4].push_back(std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime).count());
  }
  auto averageDuration {std::accumulate(times[0].begin(), times[0].end(), 0) / TEST_COUNT};
  std::cout << "User input duration, us: average = "
            << averageDuration
            << std::endl;

  averageDuration = std::accumulate(times[1].begin(), times[1].end(), 0) / TEST_COUNT;
  std::cout << "Sorted output duration, us: average = "
            << averageDuration
            << std::endl;

  averageDuration = std::accumulate(times[2].begin(), times[2].end(), 0) / TEST_COUNT;
  std::cout << "Filtered by 1 first octet output duration, us: average = "
            << averageDuration
            << std::endl;

  averageDuration = std::accumulate(times[3].begin(), times[3].end(), 0) / TEST_COUNT;
  std::cout << "Filtered by 2 first octets output duration, us: average = "
            << averageDuration
            << std::endl;

  averageDuration = std::accumulate(times[4].begin(), times[4].end(), 0) / TEST_COUNT;
  std::cout << "Filteres by any 1 octet output duration, us: average = "
            << averageDuration
            << std::endl;
}

BOOST_AUTO_TEST_CASE(time_complexity_full)
{
  std::cout << std::endl << "TIME_COMPLEXITY_FULL" << std::endl;
  const size_t TEST_COUNT {6};
  std::vector<long unsigned int> times{};
  for (size_t testIdx{}; testIdx < TEST_COUNT; testIdx++)
  {
    int addressCount{std::pow(10, testIdx + 1)};
    std::cout << std::endl << "Input records count: " << addressCount << std::endl;

    std::srand(std::time(nullptr));
    std::stringstream sendStream{};
    std::stringstream receiveStream{};

    int filterValue1{std::rand() % 255};
    int filterValue2{std::rand() % 255};
    int filterValue3{std::rand() % 255};
    int filterValue4{std::rand() % 255};

    for (size_t inputStringIdx{}; inputStringIdx < addressCount; inputStringIdx++)
    {
      int b0{std::rand() % 255};
      int b1{std::rand() % 255};
      int b2{std::rand() % 255};
      int b3{std::rand() % 255};
      int text2{std::rand() % 9999};
      int text3{std::rand() % 9999};
      sendStream << b3 << '.' << b2 << '.' << b1 << '.' << b0 << '\t'
                 << text2 << '\t' << text3 << '\n';
    }

    auto startTime = std::chrono::high_resolution_clock::now();
    auto tmpAddresses {userInput(sendStream)};
    outputSorted(receiveStream, tmpAddresses, false);
    outputFiltered(receiveStream, tmpAddresses, filterValue1);
    outputFiltered(receiveStream, tmpAddresses, filterValue2, filterValue3);
    outputFilteredAny(receiveStream, tmpAddresses, filterValue4);
    auto finishTime {std::chrono::high_resolution_clock::now()};
    auto duration {std::chrono::duration_cast<std::chrono::microseconds>(finishTime - startTime).count()};
    times.push_back(duration);

    std::cout << "Total duration: ";
    if (duration > 1000000)
      std::cout << duration * 1.0 / 1000000 << "s" << std::endl;
    else if (duration > 1000)
      std::cout << duration * 1.0 / 1000 << "ms" << std::endl;
    else
      std::cout << duration << "us" << std::endl;
  }
}

BOOST_AUTO_TEST_SUITE_END() // filter_1_any_test

