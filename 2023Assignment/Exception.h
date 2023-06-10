#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
/**
* @breif a Exception class for handling incorrect file formats
*/
class IncorrectFileFormatException : public std::runtime_error {
public:
    IncorrectFileFormatException(const std::string& filename) :
        std::runtime_error("Error: The file " + filename + " does not have a .csv extension.") {}
};
