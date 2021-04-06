//============================================================================
// Name        : 410_proj_thread_log.cpp
// Author      : Christian Ross
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <thread>
#include <iostream>
#include <vector>
#include "../includes/constants.h"
#include "../includes/Logger.h"

using namespace std;

// declare globals
Logger l(LOG_CONSOLE);
Logger l2(LOG_FILE);
bool stop=false;
vector<thread> threads;
/***
 * 
 *  log info to both file and console (you can do this with 2 Logger objects)
 *  this function should run until main (or another thread) asks it to quit
 * @param info  to log
 * returns void
 */
void fun(string info){
	while(!stop){
		l.Log(info);
		l2.Log(info);
	}
}
int main() {
	
	//start as many threads as you have cores (see std::thread::hardware_concurrency())
	//save these threads in a vector
	int t = std::thread::hardware_concurrency();
	for(int i = 0;i<t;i++){
		threads.push_back(thread(fun, to_string(i)));
	}


	// let threads run a bit (5 seconds)
	this_thread::sleep_for(chrono::milliseconds(5000));
	
	// ask them all to stop
	stop=true;

	for(int i = 0;i<t;i++){
		threads[i].join();
	}
	return 0;
}
