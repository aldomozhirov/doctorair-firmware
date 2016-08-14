/*
 * Memory
 *
 *  Created on: 25 июля 2016 г.
 *      Author: Alexey
 */

#ifndef SOURCES_MEMORY_MEMORY_
#define SOURCES_MEMORY_MEMORY_

#include <EEPROM.h>
#include <Arduino.h>

class Memory {

	public:
		Memory();
		int alloc(int size);
		void write(int elem, byte* data);
		void read(int elem, byte* buffer);
		int getHead();
		int getTail();
		int getEntities();

	protected:
		int* addresses;
		int* sizes;
		int entities;
		int head;
		int tail;

};

#endif /* SOURCES_MEMORY_MEMORY_ */
