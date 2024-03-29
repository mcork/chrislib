/* 
 * File:   osc.h
 * Author: Christophe Soares
 *
 * Edited on 6 de Outubro de 2009, 19:46, from oscpack
 * Copyright 2009 . All rights reserved.
 */

#include <map>
#include <OpenCV/cv.h>
#include <OpenCV/highgui.h>


#include <stdio.h>
#include <string>


#include <iostream>

#include "OscOutboundPacketStream.h"
#include "UdpSocket.h"


#define ADDRESS "127.0.0.1"
#define PORT 3333

#define OUTPUT_BUFFER_SIZE 2048

#define OSC_STRICT 1



///////////////////////////////////////////////////////////////////////



struct TouchData
{
	int ID;
	int tagID;
	float X;
	float Y;
	
	float height;
	float width;
	float angle;
	
	float area;
	
	float dX;
	float dY;
	
	float weight;
	
};

///////////////////////////////////////////////////////////////////////



class OSCApp {
private:
	UdpTransmitSocket *transmitSocket;
public:
	// Keep track of all finger presses.
	TouchData activeFinger, activeFinger2;
	bool empty;
	
	int frameSeq;	
	
	
	
public:
	OSCApp();
	~OSCApp();
	void connectSocket();
	void connectSocket(std::string ip_address, int port);
	void fingerDown(TouchData data);
	void fingerUpdate(TouchData data);
	void fingerUp(TouchData data);
	void frame();
	void frameMulti();
	void clearFingers();
	void setActiveFinger(struct TouchData);
	void setActiveFinger(struct TouchData temp, struct TouchData temp2 );
	struct TouchData getActiveFinger();
	bool isEmpty();
};



