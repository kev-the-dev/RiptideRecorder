/*
 * Macro.cpp
 *
 *  Created on: Apr 4, 2015
 *      Author: kma1660
 */

#include "Macro.h"
#include "Commands/RecordCommand.h"
#include "Commands/PlayBackCommand.h"

Macro::Macro(std::vector<Device*> devices) {
	for(std::vector<Device*>::iterator dev = devices.begin(); dev != devices.end(); ++dev) {
		Values[*dev].clear();
	}
	length = 0;
	position = 0;

	recordCommand = new RecordCommand(this);
	playCommand = new PlayBackCommand(this);
};
void Macro::Reset() {
	for (it = Values.begin(); it != Values.end(); it++) {
		it->second = std::vector<float> ();
	}
	length = 0;
	position = 0;
}
void Macro::PlayReset() {
	position = 0;
}
void Macro::Record() {
	for (it = Values.begin(); it != Values.end(); it++) {
		it->second.push_back(it->first->get());
	}
	length++;
}
void Macro::PlayBack() {
	if (position>=length) return;
	for (it = Values.begin(); it != Values.end(); it++) {
		if (position >= it->second.size()) {
			it->first->set(0);
			continue;
		}
		it->first->set(it->second[position]);
	}
	position++;
}
void Macro::WriteFile(std::string filename) {
	 std::ofstream file;
	 file.open(filename.c_str());
	 if (file.is_open()) {
		for (it = Values.begin(); it != Values.end(); it++) {
			file << it->first->name;
			for (unsigned int i = 0; i < it->second.size(); i++) {
				file << "," << it->second[i];
			}
			file << "\n";
		}
		file.close();
	 }
}
void Macro::ReadFile(std::string filename) {
	std::ifstream file;
	file.open(filename.c_str());
	if (file.is_open()) {
		std::string line;
		std::string delimiter = ",";
		std::string token;
		size_t pos = 0;
		Reset();
		while(std::getline(file,line)) { //for each line of the csv file
			if ((pos = line.find(delimiter)) != std::string::npos) { //Find the first value (the string before the first comma on this line)
			    token = line.substr(0, pos);
				for (it = Values.begin(); it != Values.end(); it++) { //attempt to find the device with this line's name
					if (token == it->first->name) {
					    line.erase(0, pos + delimiter.length());
						while ((pos = line.find(delimiter)) != std::string::npos) { //for each additional value on this line, append the value to the device's values vector
							token = line.substr(0, pos);
						    it->second.push_back( (float) std::atof(token.c_str()) );
						    line.erase(0, pos + delimiter.length());
						}
						it->second.push_back( (float) std::atof(line.c_str()) );
						length = (it->second.size() > length) ? it->second.size() : length;
						break; //stop looking for device if one was found
					}
				}
			}
		}
	} else {

	}
}
bool Macro::IsFinished() {
	return position >= length;
}
Command* Macro::GetPlayCommand() {
	return playCommand;
}
Command* Macro::GetPlayCommand(std::string FileName) {
	return new PlayBackCommand(this,FileName);
}
Command* Macro::GetRecordCommand() {
	return recordCommand;
}
void Macro::StartRecording() {
	recordCommand->Start();
}
void Macro::StopRecording() {
	recordCommand->Cancel();
}
void Macro::StartPlay() {
	playCommand->Start();
}
void Macro::StopPlay() {
	playCommand->Cancel();
}
