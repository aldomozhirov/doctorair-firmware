/*
 * Field.h
 *
 *  Created on: 26 июля 2016 г.
 *      Author: Alexey
 */

#ifndef SOURCES_FIELD_H_
#define SOURCES_FIELD_H_

/*
 * Field.h
 *
 *  Created on: 25 июля 2016 г.
 *      Author: Alexey
 */

#ifndef SOURCES_MEMORY_FIELD_FIELD_H_
#define SOURCES_MEMORY_FIELD_FIELD_H_

#include "Memory.h"

template <class T>
class Field {

	public:

	Field(Memory& _memory) {
		memory = &_memory;
		mem_block = memory->alloc(sizeof(T));
		buffer = new byte[sizeof(T)];
	}

	int getMemBlock() {
		return mem_block;
	}

	T getValue() {
		memory->read(mem_block, buffer);
		T& val = (T&)(*buffer);
		return val;
	}

	void setValue(T value) {
		byte *raw = new byte[sizeof(T)];
		(T&)(*raw) = value;
		memory->write(mem_block, raw);
		delete [] raw;
	}

	protected:
		Memory* memory;
		int mem_block;
		byte* buffer;
};

#endif /* SOURCES_MEMORY_FIELD_FIELD_H_ */


#endif /* SOURCES_FIELD_H_ */
