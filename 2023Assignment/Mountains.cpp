#include "Mountains.h"
#include "Exception.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <random>
#include <chrono>
using namespace std;

/**
* @brief Mountain class constructor that reads a csv file information and forms a data structure with it and checks wheather the file type is correct
* @throws IncorrectFileFormatException from the Exception.h, if the file name doesnt match the varable ".csv".
*/
Mountains::Mountains()
{
    ifstream file("mikeFiles.csv");
    try {
        string extent = ".csv";
        string filename = "mikeFiles.csv";
        if (filename.substr(filename.size() - extent.size()) != extent) {
            cout << " the file doesnt have csv" << endl;
            throw IncorrectFileFormatException(filename);
        }
        else {
            cout << "file has csv" << endl;
        }
    } catch (exception& e) {
        /**
        * @breif handles the file error.
        * @exception outputs an error message and exits the program.
        */
        cerr << "Exception opening/reading/closing file: " << e.what() << endl;
        exit(1);
    }
    gen = mt19937(rand());
    string line;
    while (getline(file, line))
    {
        vector <string> lines;
        string type = line.substr(0, line.find(','));
        string mount = line.substr(line.find(',') + 1);
        while (mount.find(',') != string::npos) {
            lines.push_back(mount.substr(0, mount.find(',')));
            mount = mount.substr(mount.find(',') + 1);
        }
        lines.push_back(mount);
        allMountains[type] = lines;
    }
    file.close();
}

/**
* @brief Function to get a reandom number from the data structure.
* @return A random mountain string.
*/
string Mountains::getRandomMountain()
{
      uniform_int_distribution <int> Distribution(0, allMountains.size() -1); 
      int random = Distribution(gen);
      auto pointer = allMountains.begin();
      advance(pointer, random);
      auto randomMountain = *pointer; 
      uniform_int_distribution <int> Distribution2(0, randomMountain.second.size()- 1); 
      return randomMountain.second[Distribution2(gen)];
}
/**
* @brief Function to check if a given mountain name is within the range.
* @param mountain: the name of the mountain to check. 
* @param range: the range to check against.
* @return True if the mountain belongs to the range, false if not.
*/
bool Mountains::checkRange(string mountain, string range)
{
    if (allMountains.find(range) != allMountains.end()) {
        std::vector<std::string> vec = allMountains[range]; 
        if (std::find(vec.begin(), vec.end(), mountain) != vec.end()) { 
            return true;
        }
    }
    return false;
}
/**
* @brief Function to add the player records to a csv file.
* @param String name: name of the player.
* @param Int duration: average time taken to answer the questions.
* @param Int score: the score achived for the timing record.
*/
void Mountains::addTiming(string name, int duration, int score) 
{
    ofstream file;
    file.open("scoreCount.csv", ios::app);
    file << name << "," << duration << "," << score << endl;
    file.close();
}
/**
* @brief Function that reads the addTiming csv file and prints to the console.
* @param String name: name of the player
* @param Int duration: average time take to answer the questions 
* @param Int score: the score achived for the timing record 
*/
void Mountains::readScoreCount(string name, int duration, int score)
{
	ifstream file("scoreCount.csv");
	string line;
	while (getline(file, line))
	{
		string name = line.substr(0, line.find(','));
		string duration = line.substr(line.find(',') + 1, line.find(','));
		string score = line.substr(line.find(',') + 1);
		cout << name << " " << duration << " " << score << endl;
	}
	file.close();
}


