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
			 file << it->first->GetName();
			if (it != --Values.end()) file << ",";
		 }
		 file << "\n";

		 for (unsigned int i = 0; i<length;i++) {
			 for (it = Values.begin(); it != Values.end(); it++) {
				 if (i >= it->second.size()) {
					 file << 0;
				 }
				 else file << it->second[i];

				 if (it != --Values.end()) file << ",";
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

		std::vector<Device*> list;

		//Get the first line to establish the list of devices
		std::getline(file,line);
		while ((pos = line.find(delimiter)) != std::string::npos) {
			token = line.substr(0, pos);
			list.push_back(NULL);
			for (it = Values.begin(); it != Values.end(); it++) if (token == it->first->GetName()) {
				list.back() = it->first;
				break;
			};
		    line.erase(0, pos + delimiter.length());
		}

		//Grab last
		list.push_back(NULL);
		for (it = Values.begin(); it != Values.end(); it++) if (line == it->first->GetName()) {
			list.back() = it->first;
			break;
		};

		//Now, for each line append value to each device
		unsigned int i;
		length = 0;
		while (std::getline(file,line)) {
			length++;
			i = 0;
			while ((pos = line.find(delimiter)) != std::string::npos) {
				token = line.substr(0, pos);
				line.erase(0, pos + delimiter.length());
				if (i >= list.size()) break; //break from loop if this line has more cols than first line
				if (list[i] != NULL) Values[list[i]].push_back( (float) std::atof(token.c_str()) );
				i++;
			}
			//Grab last
			if (i >= list.size()) break; //break from loop if this line has more cols than first line
			if (list[i] != NULL) Values[list[i]].push_back( (float) std::atof(line.c_str()));
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
