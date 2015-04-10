/*
 * PlayBackCommand.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: kma1660
 */

#include "PlayBackCommand.h"

PlayBackCommand::PlayBackCommand(Macro* m) {
	macro = m;
}
PlayBackCommand::PlayBackCommand(Macro* m,std::string f) {
	FileName = f;
	macro = m;
}
void PlayBackCommand::Initialize() {
	if (macro->recordCommand->IsRunning()) macro->recordCommand->Cancel();

	if(!FileName.empty()) macro->ReadFile(FileName);

	macro->PlayReset();
}

void PlayBackCommand::Execute() {
	macro->PlayBack();
}

bool PlayBackCommand::IsFinished() {
	return macro->IsFinished();
}

void PlayBackCommand::End() {
	macro->PlayReset();
}
void PlayBackCommand::Interrupted() {
	End();
}
