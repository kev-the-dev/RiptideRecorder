/*
 * TestDevice.h
 *
 *  Created on: Apr 2, 2015
 *      Author: kma1660
 */

#ifndef DEVICES_TESTDEVICE_H_
#define DEVICES_TESTDEVICE_H_

#include "RiptideRecorder/Device.h"
#include <string>

class TestDevice : public Device {
public:
	TestDevice(std::string x);
	virtual float get();
	virtual void set(float x);
	float ret;
};

#endif /* DEVICES_TESTDEVICE_H_ */
