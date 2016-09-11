/*
 * Logger.cpp
 *
 *  Created on: 12 рту. 2016 у.
 *      Author: Alexey
 */

#include "Logger.h"

SimpleList<String> Logger::list;

void Logger::append(String log) {
	unsigned long time = millis();
	int h = time/1000/60/60;
	int m = time/1000/60 - h*60;
	int s = time/1000 - h*60*60 - m*60;
	int ms = time - h*60*60*1000 - m*60*1000 - s*1000;
	String format_time = String(h) + ":" + String(m) + ":" + String(s) + ":" + String(ms);
	if (list.size() > LIMIT)
		list.clear();
	list.push_back(format_time + " - " + log);
}

String Logger::getFirst(void){
	return *list.begin();
}

String Logger::getLast(void){
	return *list.end();
}

String Logger::getAll(void){
	String out;
	for (SimpleList<String>::iterator itr = list.begin(); itr != list.end();)
	{
		out += *itr + "\n";
	    ++itr;
	}
	return out;
}

void Logger::clear(void){
	list.clear();
}
