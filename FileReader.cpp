// Aaron Squire and Eric Markstein
// 3/19/23
// This translation unit defines the methods for the FileReader class
#include "FileReader.h"

FileReader::FileReader(string fileName) {
    ifstream infile {fileName}; // Opens input fstream

    // Check file
    if (!infile) {
        stringstream stream;
        stream << "Cannot open file: " << fileName;
        throw runtime_error(stream.str().c_str());
    }

    // Placing the keys needed in the dictionary, to ensure sure names are exact
    // Negative one is used to ensure every one is coded
    inputs["maximum_simulated_time"] = -1;
    inputs["number_of_sections_before_intersection"] = -1;
    inputs["green_north_south"] = -1;
    inputs["yellow_north_south"] = -1;
    inputs["green_east_west"] = -1;
    inputs["yellow_east_west"] = -1;
    inputs["prob_new_vehicle_northbound"] = -1;
    inputs["prob_new_vehicle_southbound"] = -1;
    inputs["prob_new_vehicle_eastbound"] = -1;
    inputs["prob_new_vehicle_westbound"] = -1;
    inputs["proportion_of_cars"] = -1;
    inputs["proportion_of_SUVs"] = -1;
    inputs["proportion_right_turn_cars"] = -1;
    inputs["proportion_left_turn_cars"] = -1;
    inputs["proportion_right_turn_SUVs"] = -1;
    inputs["proportion_left_turn_SUVs"] = -1;
    inputs["proportion_right_turn_trucks"] = -1;
    inputs["proportion_left_turn_trucks"] = -1;

    string line;
    string keyWhiteSpace;
    string key;
    double value;
    size_t i = 0;
    while (getline(infile, line)) {
        // Removes leading whitespace
        while ((line[i] == ' ' || line[i] == '\t') && i < line.size()) {
            i++;
        }

        // Tests if entire line is whitespace
        if (i != line.size()) {
            int position = line.find(":");

            // Removes trailing whitespace after key and before colon
            keyWhiteSpace = line.substr(i, position - i);
            key = "";
            i = keyWhiteSpace.find_last_not_of(" \t");
            if (i == std::string::npos) {
                key = keyWhiteSpace;
            }
            else {
                key = keyWhiteSpace.substr(0, i + 1);
            }
            value = stod(line.substr(position + 1));

            // Tests that the input key is actually one of the keys
            if (inputs.count(key) == 0) {
                stringstream stream3;
                stream3 << "'" << key << "' is not a valid input name";
                throw runtime_error(stream3.str().c_str());
            } else {
                inputs[key] = value;
            }
        }
        i = 0;
    }

    // Iterates through inputs to make sure each one was included in the input file
    for (std::map<string,double>::iterator it = inputs.begin(); it != inputs.end(); ++it) {
        if ((it->second == -1) && (it->first != ("proportion_left_turn_cars")) && (it->first != ("proportion_left_turn_SUVs")) && (it->first != ("proportion_left_turn_trucks"))) {
            stringstream stream4;
            stream4 << "'" << it->first << "' was not given a value";
            throw runtime_error(stream4.str().c_str());
        }
    }
}

double FileReader::get(string key) {
    return inputs[key];
}