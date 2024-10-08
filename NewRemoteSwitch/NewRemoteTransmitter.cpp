/*
 * NewRemoteSwitch library v1.2.0 (20140128) made by Randy Simons http://randysimons.nl/
 * See NewRemoteTransmitter.h for details.
 *
 * License: GPLv3. See license.txt
 */

#include "NewRemoteTransmitter.h"


NewRemoteTransmitter::NewRemoteTransmitter(unsigned long address, unsigned char pin, unsigned int periodusec, unsigned char repeats, void (*pinWrite_callback)(bool state)) {
	_address = address;
	_periodusec = periodusec;
	_repeats = (1 << repeats) - 1; // I.e. _repeats = 2^repeats - 1
    
    pinWrite = pinWrite_callback;
}

void NewRemoteTransmitter::sendGroup(bool switchOn) {
	for (int8_t i = _repeats; i >= 0; i--) {
		_sendStartPulse();

		_sendAddress();

		// Do send group bit
		_sendBit(true);

		// Switch on | off
		_sendBit(switchOn);

		// No unit. Is this actually ignored?..
		_sendUnit(0);

		_sendStopPulse();
	}
}

void NewRemoteTransmitter::sendUnit(unsigned char unit, bool switchOn) {
	for (int8_t i = _repeats; i >= 0; i--) {
		_sendStartPulse();

		_sendAddress();

		// No group bit
		_sendBit(false);

		// Switch on | off
		_sendBit(switchOn);

		_sendUnit(unit);

		_sendStopPulse();
	}
}

void NewRemoteTransmitter::sendDim(unsigned char unit, unsigned char dimLevel) {
	for (int8_t i = _repeats; i >= 0; i--) {
		_sendStartPulse();

		_sendAddress();

		// No group bit
		_sendBit(false);

		// Switch type 'dim'
		pinWrite(1);
		_delay_us(_periodusec);
		pinWrite(0);
		_delay_us(_periodusec);
		pinWrite(1);
		_delay_us(_periodusec);
		pinWrite(0);
		_delay_us(_periodusec);

		_sendUnit(unit);

		for (int8_t j=3; j>=0; j--) {
		   _sendBit(dimLevel & 1<<j);
		}

		_sendStopPulse();
	}
}

void NewRemoteTransmitter::sendGroupDim(unsigned char dimLevel) {
	for (int8_t i = _repeats; i >= 0; i--) {
		_sendStartPulse();

		_sendAddress();

		// No group bit
		_sendBit(true);

		// Switch type 'dim'
		pinWrite(1);
		_delay_us(_periodusec);
		pinWrite(0);
		_delay_us(_periodusec);
		pinWrite(1);
		_delay_us(_periodusec);
		pinWrite(0);
		_delay_us(_periodusec);

		_sendUnit(0);

		for (int8_t j=3; j>=0; j--) {
		   _sendBit(dimLevel & 1<<j);
		}

		_sendStopPulse();
	}
}

void NewRemoteTransmitter::_sendStartPulse(){
	pinWrite(1);
	_delay_us(_periodusec);
	pinWrite(0);
	_delay_us(_periodusec * 10 + (_periodusec >> 1)); // Actually 10.5T insteat of 10.44T. Close enough.
}

void NewRemoteTransmitter::_sendAddress() {
	for (int8_t i=25; i>=0; i--) {
	   _sendBit((_address >> i) & 1);
	}
}

void NewRemoteTransmitter::_sendUnit(unsigned char unit) {
	for (int8_t i=3; i>=0; i--) {
	   _sendBit(unit & 1<<i);
	}
}

void NewRemoteTransmitter::_sendStopPulse() {
	pinWrite(1);
	_delay_us(_periodusec);
	pinWrite(0);
	_delay_us(_periodusec * 40);
}

void NewRemoteTransmitter::_sendBit(bool isBitOne) {
	if (isBitOne) {
		// Send '1'
		pinWrite(1);
		_delay_us(_periodusec);
		pinWrite(0);
		_delay_us(_periodusec * 5);
		pinWrite(1);
		_delay_us(_periodusec);
		pinWrite(0);
		_delay_us(_periodusec);
	} else {
		// Send '0'
		pinWrite(1);
		_delay_us(_periodusec);
		pinWrite(0);
		_delay_us(_periodusec);
		pinWrite(1);
		_delay_us(_periodusec);
		pinWrite(0);
		_delay_us(_periodusec * 5);
	}
}
