#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<map>
#include<random>
#include<algorithm>
using namespace std;

/**
* @brief A Mountain class, which holds and manages information about mountains. 
*/
class Mountains
{
private: 
	/**
	* @brief A map that stores information about all mountains, including thier ranges. 
	*/
	map <string, vector<string>> allMountains;
	/**
	* @brief A random device number generator.
	*/
	random_device rand;//random 
	/**
	* @brief A generator used to generate a random number.
	*/
	mt19937 gen;//generator
public:
	/**
	* @brief Constructs a new mountain object that will read a file  
	* @Complexity: 0(n) 
	*/
	//Time Complexity: 0(n)  
	Mountains();
	/**
	* @brief Gets the name of a random mountain of the Map allMountains.
	* @return The name of a random Mountain.
	* @Complexity: 0(1) 
	*/
	//Time Complexity: 0(1) 
	std::string getRandomMountain();
	/**
	* @brief checks if a mountain is within a ceratin range.
	* @param mountain: the name of the mountain.
	* @param Range: the range to check.
	* @return True if the mountain is within the range, false if its not 
	* @Complexity: 0(n)
	*/
	//Time Complexity: 0(n)
	bool checkRange(std::string mountain, std::string range);
	/**
	* @brief Adds the players record of a game to the csv file.
	* @param name: the name of the player.
	* @param duration: the aveavage time take to answer the questions.
	* @param score: the score of the game.
	* @Complexity: 0(1)
	*/
	//Time Complexity: 0(1)
	void addTiming(string name, int duration, int score);
	/**
	* @brief Reads the csv file.
	* @param name: the name of the player.
	* @param duration: the duration of the game.
	* @param score: the score of the game.
	* @Complexity: 0(n)
	*/
	//Time Complexity: 0(n)
	void readScoreCount(string name, int duration, int score);

	/**
	* @brief (for Testing Purposes) adding a new member to Mountains to test the checkRange method in the mountains.cpp
	* @param mountain: adding a string mountain from the map 
	* @param range: the name of range it belongs 
	* @Complexity 0(1)
	*/     
	//Time Complexity 0(1)
	void testMountain(const std::string& mountain, const std::string& range) {
		allMountains[range].push_back(mountain);
	}
};
 
