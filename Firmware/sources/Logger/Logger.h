/*
 * Logger.h
 *
 *  Created on: 12 рту. 2016 у.
 *      Author: Alexey
 */

#ifndef SOURCES_LOGGER_LOGGER_H_
#define SOURCES_LOGGER_LOGGER_H_

#include <Arduino.h>
#include <SimpleList.h>

class Logger {
	public:
		static void append(String log);
		static String getFirst(void);
		static String getLast(void);
		static String getAll(void);
		static void clear(void);
	private:
		static SimpleList<String> list;
};

#endif /* SOURCES_LOGGER_LOGGER_H_ */
