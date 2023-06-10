#include <iostream>
#include <string>
#include <fstream>
#include "Mountains.h"
#include "Exception.h"
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>
#include <random>
#include <future>
using namespace std;

/**
* @brief Compares the duration of two pairs.
* @param pair1: the first pair to compare. 
* @param pair2: the second pair to compare.
* @return true if the duration of the first pair is smaller than the second pair.
*/
bool compareDuration(const pair <int, int>& pair1, const pair <int, int>& pair2) 
{
	return pair1.second < pair2.second; 
}
/**
* @brief Checks if the user input is invalid and prompts the user to enter a valid input.
* @param input1: user input to check.
*/
void invalid(int input1)  
{

	if (input1 < 1 || input1 > 4) {
		cout << "invalid Input Please Try again" << endl;
		do {
			cout << "Please enter a number between 1 and 4" << endl;
			cin >> input1;
			if (input1 < 1 || input1 > 4) {
				cout << "invalid Please Try again" << endl;
			}
		} while (input1 < 1 || input1 > 4);	
	}
}
/**
* @brief Prompts the user to enter thier answer and checks if the input is valid.
* @param input1: users answer.
* @return 0;
* @throws invalid_argument, if the input is not a string. 
*/
int usersInputs(int& input1 ) 
{
	cout << "where does this mountain belong ? " << endl;
	cout << "1.Alps , 2.Carpathians , 3.Icelandic Highlands , 4.Pyrenees" << endl;
	try {
		cin >> input1;
		if (cin.fail()) {
			throw invalid_argument("invalid input, please enter a number");
		}
	}
	catch (const invalid_argument& e) {
		/**
		* @brief handles the input error
		* @exception numeric_limits<streamsize>::max(), '\n', discards the input and recall function again 
		*/
		cout << e.what() << endl;
		cin.clear(); // clear the error flag
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignores and discards the input
		usersInputs(input1); //call the function again
	}
	invalid(input1);
	return 0;
}
/**
* @brief converts the answer to string.
* @param input1: the user's answer.
* @param inputRange: representing string of the user's answer.
*/
void answers(int& input1, string& inputRange) 
{
	switch (input1) {
	case 1:
		inputRange = "Alps";
		break;
	case 2:
		inputRange = "Carpathians";
		break;
	case 3:
		inputRange = "Icelandic Highlands";
		break;
	case 4:
		inputRange = "Pyrenees";
		break;
	case 5:
		inputRange = "Invalid";
		break;
	}
}
/**
* @brief check if the user's answer is correct and prints the results.
* @param randomMountain: A string representing the randomly selected mountain. 
* @param inputRange: A string representing the user's answer.
* @param mount: An object of the Mountain class.
*/
void range(string& randomMountain, string& inputRange, Mountains& mount ) 
{
	if (mount.checkRange(randomMountain, inputRange) == true) { 
		cout << "Correct" << endl;
	}
	else {
		cout << "Incorrect" << endl;
	}
}
/**
* @brief the Main function that runs the game.
* @return 0.
*/
int main()
{ 
	Mountains mountainObject;
	int input1;
	string inputRange;
	string userName;
	int questions;
	cout << "Enter Name" << endl;
	cin >> userName;
	cout << "how many questions do you want to answer?" << endl;
	cin >> questions;
	while (true)
	{
		int counter = 1; 
		int answersCorrect = 0; 
		int answersIncorrect = 0;
		vector<int> timing;
		map<int,int> speed;
		do 
		{
			cout << "Question " << counter << ":" << endl;
			string randomMountain = mountainObject.getRandomMountain();
			cout << randomMountain << endl;
			auto start = chrono::high_resolution_clock::now();
			usersInputs(input1);
			auto end = chrono::high_resolution_clock::now(); 
			int duration = chrono::duration_cast<chrono::seconds>(end - start).count();
			cout << duration << " seconds " << endl;
			if (duration > 10) { 
				input1 = 5;
				cout << "You took too long" << endl;
			}
			answers(input1, inputRange);
			range(randomMountain, inputRange, mountainObject); 
			counter++; 
			timing.push_back(duration);
			if (mountainObject.checkRange(randomMountain, inputRange) == true) { 
				answersCorrect++; 
				speed.insert(make_pair(counter, duration)); 
			}
			else {
				answersIncorrect++; 
			}	
			
		} while (counter <= questions);
		cout << "You got " << answersCorrect << " correct " << "and " << answersIncorrect << " incorrect" << endl; 
		int total = 0;
		for (int i = 0; i < timing.size() - 1; i++)
		{
			total += timing[i]; 
		}
		int average = total / timing.size();
		mountainObject.addTiming(userName, average, answersCorrect);
		vector<pair<int, int>> vec(speed.begin(), speed.end()); 
		sort(vec.begin(), vec.end(), compareDuration);
		cout << "----------------------Your Fastest correct Score------------------------" << endl;
		for (const auto& pair : vec) {
			cout << "question" << pair.first << " " << "time" << pair.second << endl;
		}
		cout << "-----------------------players----------------------------------" << endl;
		mountainObject.readScoreCount(userName, average, answersCorrect);
		cout << "--------------------------------------------------------------------------------" << endl;
		cout << "Do you want to play again? (type y to playagain or type any key to exit)" << endl;
		char input2;
		cin >> input2;
		if (input2 == 'y') {
			continue;
		}
		else {
			break;
		}
	}
	return 0;
}

 