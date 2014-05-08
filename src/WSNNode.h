/*
 * WSNNode.h
 *
 *  Created on: May 8, 2014
 *      Author: Fanjing-LAB
 */

#ifndef WSNNODE_H_
#define WSNNODE_H_

#include "GlobalStatistics.h"

class WSNNode {
public:
	WSNNode();
	WSNNode(int n);
	virtual ~WSNNode();

public:
	int startSensor(int t);
	int startTransimit();
	void output();
	void record();

	static GlobalStatistics gs;

	static double initialRelayEnergy; // initial energy of the relay node
	static double deadRelayEnergy; // death threshold of the relay node
	static double initialSensorEnergy; // initial energy of the sensor node
	static double deadSensorEnergy; // death threshold of the sensor node
	static int N;
private:

    bool consumeSensorEnergy();
    bool consumeTransmitEnergy(double distance , int bits);

	double *relayNodeEnergy;
	int relayNodeSize;
	int activatedRelayNode;
	double sensorNodeEnergy;
	int i,j,u,v,id;

};

#endif /* WSNNODE_H_ */
