#include <iostream>
#include <thread>
#include <chrono>
#include "motorcontrol.h"


int exec_py_script(std::string path){
	return system(path.c_str())/256;
}
void reset_mc(){
	system("sudo ./resetmicrocontroller.sh");
}
void MotorController::SendCommand(command _cmd, int address){
	std::string cmd;
	switch (_cmd){
		case STOP:
			cmd = STOPN;
			break;
		case SET_FULL_SPEED:
			cmd = SFSN;
			break;
		case TURN_LEFT:
			cmd = TLN;
			break;
		case TURN_RIGHT:
			cmd = TRN;
			break;
		case GO_STRAIGHT:
			cmd = GSN;
			break;
		case GO_BACK:
			cmd = GBN;
			break;
		case SHARP_TURN_RIGHT:
			cmd = STRN;
			break;
		case SHARP_TURN_LEFT:
			cmd = STLN;
			break;
		case DISABLE:
			cmd = DN;
			break;
		case ENABLE:
			cmd = EN;
			break;
	}
	std::string space = " ";
	std::string p = MOTORCOMMAND + space + std::to_string(address) + space + cmd;
	int res;
	int count = 0;
	do{
		res = exec_py_script(p);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		if(count >= 2){
			reset_mc();
		}
		if(count == 3){
			std::cout << "ERROR! Microcontroller can't be reached!\n";
			break;
		}
		count++;
	}while(res != 0);
	
 }