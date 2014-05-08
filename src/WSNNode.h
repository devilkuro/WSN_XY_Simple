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
	WSNNode(int num);
	virtual ~WSNNode();

public:
	bool startSensor(int n);
	bool startTransimit();

private:
	double *relayNodeEnergy;
	int relayNodeSize;
	int activatedRelayNode;
	int sensorNodeEnergy;
	int sensorInterval;
	int i,j,u,v,N;
	static GlobalStatistics gs;
};

#endif /* WSNNODE_H_ */
