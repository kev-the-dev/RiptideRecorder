/*
 * Device.h
 *
 *  Created on: Apr 2, 2015
 *      Author: kma1660
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include <string>

class Device {
public:
	Device(std::string x);
	std::string name;
	virtual float get() = 0;
	virtual void set(float x) = 0;
	virtual ~Device();
};

#endif /* DEVICE_H_ */
