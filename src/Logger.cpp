/*
 * Logger.cpp
 *
 *  Created on: Mar 29, 2021
 *      Author: keith & Christian
 */
#include <iostream>
#include "../includes/Logger.h"
using namespace std;

/***
 * creates a logger object, if lt=FILE then log to the file given by fn
 * if lt=LOG_CONSOLE the send log info to console via cout
 * @param lt either LOG_FILE or LOG_CONSOLE
 * @param fn if above is LOG_FILE then this is where info logged to
 *           otherwise it is not used
 */
Logger::Logger(LOG_TYPE lt, std::string fn){
	lock_guard<mutex> lock(mtx);
	this->lt=lt;
	this->fn = fn;
	if(lt == LOG_FILE){
		fs.open(fn);
	}
}
/***
 * Information to log, either to a file or to console
 * @param info to log
 */
void Logger::Log(std::string info){
	lock_guard<mutex> lock(mtx);
	if(lt == LOG_FILE){
		fs<<info<<endl;
	}
	else{
		cout<<info<<endl;
	}
}

/***
 * close any open streams
 */
Logger::~Logger(){
	if(lt == LOG_FILE){
		fs.close();
	}
}
