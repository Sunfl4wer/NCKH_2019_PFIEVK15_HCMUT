/****************************************************************************
**
** Copyright 2015 by Emotiv. All rights reserved
**
** Example - FacialExpressionDemo
**
** This example demonstrates how an application can use the ExpressivTM
** detection suite to control an animated head model called BlueAvatar.
** The model emulates the facial expressions made by the user wearing an
** Emotiv headset.
** FacialExpressionDemo connects to Emotiv EmoEngineTM and retrieves EmoStatesTM
** for all attached users. The EmoState is examined to determine which
** facial expression best matches the user’s face.
** FacialExpressionDemo communicates the detected expressions to the separate
** BlueAvatar application by sending a UDP packet which follows a simple,
** pre-defined protocol
****************************************************************************/

#include <iostream>
#include <map>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include <cstdlib>
#include <stdio.h>

#include "IEmoStateDLL.h"
#include "Iedk.h"
#include "IedkErrorCode.h"
#include "SerialClass.h"

int main(int argc, char **argv) {
	EmoEngineEventHandle eEvent = IEE_EmoEngineEventCreate();
	EmoStateHandle eState = IEE_EmoStateCreate();
	const LPCWSTR portName = L"COM3";

	Serial* SP = new Serial(portName);    // adjust as needed

	try {
		
		//Connect with EmoEngine
		if (IEE_EngineConnect() != EDK_OK) {
		throw std::runtime_error("Emotiv Driver start up failed.");
		}
		else {
		std::cout << "Emotiv Driver started!" << std::endl;
		}
		
		/*
		//Connect with Emotive Control Panel
		if (IEE_EngineRemoteConnect("127.0.0.1", 3008) != EDK_OK) {
			std::cout << "Fail to connect to Emotiv Control Panel!" << std::endl;
			throw std::runtime_error("Please open Emotiv Control Panel and restart the program!");
		}
		else {
			std::cout << "Emotiv Control Panel connected successfully!" << std::endl;
		}
		*/
		//Connect with Arduino
		if (!SP->IsConnected()) {
			std::cout << "Fail to connect to Arduino!" << std::endl;
			throw std::runtime_error("Please check your Arduino connection and restart the program!");
		}
		else {
			std::cout << "Arduino connected successfully!" << std::endl;
		}

		while (true) {

			int state = IEE_EngineGetNextEvent(eEvent);

			if (state == EDK_OK) {

				IEE_Event_t eventType = IEE_EmoEngineEventGetType(eEvent);
				switch (eventType) {

					// Send the FacialExpression animation
					//if EmoState has been updated
				case IEE_EmoStateUpdated:
				{
					IEE_EmoEngineEventGetEmoState(eEvent, eState);

					if (IS_FacialExpressionIsBlink(eState)) {
						std::cout << "Blink detected \n";
					}else{
						if (IS_FacialExpressionIsLeftWink(eState)) {
							std::cout << "Left Wink detected \n";
							std::cout << "Led is ON \n";
							SP->WriteData("1", 1);
						}
						else {
							if (IS_FacialExpressionIsRightWink(eState)) {
								std::cout << "Right Wink detected \n";
								std::cout << "Led is OFF \n";
								SP->WriteData("2", 1);
							}
						}
					}
					break;
				}

				default:
					break;
				}
			}else{
				if(state != EDK_NO_EVENT){
					std::cout << std::endl << "Internal error in Emotiv Engine!"
						<< std::endl;
					break;
					}
				}
			}

		}
		catch (const std::runtime_error& e) {
			std::cerr << e.what() << std::endl;
			std::cout << "Press 'Enter' to exit..." << std::endl;
			getchar();
		}

		IEE_EngineDisconnect();
		IEE_EmoStateFree(eState);
		return 0;
	}

