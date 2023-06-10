#include "Mountains.h"
#include "Exception.h"
#include <fstream>
#include <thread>
#include <map>
#include <algorithm>
#define BOOST_TEST_MODULE MountainsTest
#define BOOST_TEST_MAIN 
#define BOOST_CHECK_EQUAL
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
namespace bdata = boost::unit_test::data;
/**
* @breif unit tests for the mountain class
*/
std::map<std::string, std::vector<std::string>> allMountains;

BOOST_AUTO_TEST_SUITE(MountainsTest)
/**
* @brief BOOST unit test case for check if the string is not empty when it comes to getting a string from the mountain constuctor
*/
BOOST_AUTO_TEST_CASE(testGetRandomMountain)
{
    Mountains mountains;
    string mountain = mountains.getRandomMountain();
    BOOST_TEST_CHECK(mountain != "");
}
/**
* @brief BOOST unit test case for being able to open a file and write into the file 
*/
BOOST_AUTO_TEST_CASE(testaddTiming_File_open) 
{
    Mountains m;
    string name = "Jeff";
    int duration = 2;
    int score = 3;
    m.addTiming(name, duration, score);
    ifstream file("scoreCount.csv");
    BOOST_CHECK(file.is_open()); 
    file.close();
}
/**
* @brief BOOST unit test case for reading the mountain file 
*/
BOOST_AUTO_TEST_CASE(fileReadTest) 
{
    mt19937 gen(std::rand());
    ifstream file("mikeFiles.csv");
    string line;
    while (std::getline(file, line))
    {
        std::vector<std::string> lines;
        std::string type = line.substr(0, line.find(','));
        std::string mount = line.substr(line.find(',') + 1);
        while (mount.find(',') != std::string::npos) {
            lines.push_back(mount.substr(0, mount.find(',')));
            mount = mount.substr(mount.find(',') + 1);
        }
        lines.push_back(mount);
        allMountains[type] = lines;
    }
    file.close();
    BOOST_TEST(allMountains.size() > 0);
  
}
/**
* @brief BOOST unit test case for checking if the getRandomMountain generator, generates a random mountain
*/
BOOST_AUTO_TEST_CASE(random_getRandomMountainTest)
{
    Mountains mountains;
    string first = mountains.getRandomMountain();//obtaing the first random mountain
    int differences = 0; //initate the counter
    for (int i = 0; i < 100; i++) //generate 100 mountains
    {
        string randomMountain = mountains.getRandomMountain(); //obtaing another random mountain
        if (randomMountain != first) //compare them both 
        {
            differences++;
        }
    }
    BOOST_CHECK_MESSAGE(differences > 50, 
        "The getRandomMountain function does not appear to generate random mountains"); // check if the threshold number is greater than 80
}
/**
* @brief BOOST unit test case for checking is the range of the mountain is valid 
*/
BOOST_AUTO_TEST_CASE(checkRangeTest) 
{
    Mountains t;
    t.testMountain("Alps", "Dom");
    t.testMountain("Carpathians", "Rysy");
    t.testMountain("Icelandic", "Helka");
    t.testMountain("Pyrenees", "Aneto");
    BOOST_CHECK(t.checkRange("Alps", "Dom"));
    BOOST_CHECK(t.checkRange("Carpathians", "Rysy"));
    BOOST_CHECK(t.checkRange("Icelandic", "Helka"));
    BOOST_CHECK(t.checkRange("Pyrenees", "Aneto"));

    BOOST_CHECK(!t.checkRange("Alps", "Rysy"));
    BOOST_CHECK(!t.checkRange("Carpathians", "Aneto"));
    BOOST_CHECK(!t.checkRange("Icelandic", "Dom"));
    BOOST_CHECK(!t.checkRange("Pyrenees", "Helka"));

}
BOOST_AUTO_TEST_SUITE_END()

/**
* @brief BOOST unit test suite for testing the exception for incoreectFileFormat 
*/
BOOST_AUTO_TEST_SUITE(IncorrectFileFormatExceptionTests)
BOOST_AUTO_TEST_CASE(IncorrectTest) {
    string filename = "incorrect.txt";
    IncorrectFileFormatException exception(filename);
    string expected = "Error: The file incorrect.txt does not have a .csv extension.";
    BOOST_CHECK_EQUAL(exception.what(), expected);
}
BOOST_AUTO_TEST_SUITE_END()





