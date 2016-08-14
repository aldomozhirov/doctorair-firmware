/*
 * Memory.cpp
 *
 *  Created on: 25 июля 2016 г.
 *      Author: Alexey
 */

#include "Memory.h"

Memory::Memory() {
	head = 0;
	tail = 0;
	entities = 0;
	addresses = new int[10];
	sizes = new int[10];
}

int Memory::alloc(int size) {
	addresses[entities] = tail;
	sizes[entities] = size;
	tail+=size;
	entities++;
	return entities - 1;
}

void Memory::write(int elem, byte* data) {
	for(byte i = 0; i < sizes[elem]; i++) {
		EEPROM.write(addresses[elem]+i, data[i]);
	}
}

void Memory::read(int elem, byte* buffer) {
	for(byte i = 0; i < sizes[elem]; i++)
		buffer[i] = EEPROM.read(addresses[elem]+i);
}

int Memory::getHead() {
	return head;
}

int Memory::getTail() {
	return tail;
}

int Memory::getEntities() {
	return entities;
}

