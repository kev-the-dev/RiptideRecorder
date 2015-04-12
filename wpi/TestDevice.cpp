/*
 * TestDevice.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: kma1660
 */

#include "TestDevice.h"
#include <iostream>

TestDevice::TestDevice(std::string x) : Device(x){
	ret = 0.054534;
}
float TestDevice::get() {
	ret+= 1.4343678786786;
	//std::cout << "Getting " << name << ", returning " << ret << std::endl;
	return ret;
}
void TestDevice::set(float x) {
	std::cout << "Set " << name << " to " << x << std::endl;
}

