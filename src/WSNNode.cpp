/*
 * WSNNode.cpp
 *
 *  Created on: May 8, 2014
 *      Author: Fanjing-LAB
 */

#include <cmath>
#include <cstdlib>
#include <iostream>
#include "WSNNode.h"

#define NETW_OFFSET 0

double WSNNode::initialRelayEnergy = 82;
double WSNNode::deadRelayEnergy = 0;
double WSNNode::initialSensorEnergy = 50; // initial energy of the sensor node
double WSNNode::deadSensorEnergy = 0; // death threshold of the sensor node
int WSNNode::N = 3;
GlobalStatistics WSNNode::gs = GlobalStatistics();

static int getHexagonLevel(int id);
static int getHexagonIndex(int id);
static int getRelayNodeSize(int i,int v,int N, double w);
static int getNextHop(int i,int j,int u,int v);

WSNNode::WSNNode(int n) {
	// TODO Auto-generated constructor stub
	id = n;
	i = getHexagonLevel(n);
	j = getHexagonIndex(n);
	if (i != 0) {
		v = j % i;
		u = j / i;
	} else {
		v = 0;
		j = 0;
	}
    relayNodeSize = getRelayNodeSize(i,v,N,1.0); // FIXME the fourth argument is temporarily set to 1.0
    relayNodeEnergy = new double[relayNodeSize];
    for(int i = 0;i<relayNodeSize;i++){
        relayNodeEnergy[i] = initialRelayEnergy;
    }
    activatedRelayNode = 0;
    sensorNodeEnergy = initialSensorEnergy;
}

WSNNode::~WSNNode() {
	// TODO Auto-generated destructor stub
	delete(relayNodeEnergy);
}

int WSNNode::startSensor(int t) {
	bool flag = consumeSensorEnergy();
    if(id!=0+NETW_OFFSET&&flag){
    	if(flag){
    		std::cout<<"ERROR:id==0+NETW_OFFSET"<<std::endl;
    	}
        return getNextHop(i,j,u,v);
	}else{
		return -1;
	}
}
bool WSNNode::consumeSensorEnergy() {
	double consumedEnergy = 1.1725/10000;
	if(sensorNodeEnergy >consumedEnergy+deadSensorEnergy) {
		sensorNodeEnergy-=consumedEnergy;
		return true;
	}
	else {
		return false;
	}
}

void WSNNode::record() {
    gs.record("sensor node remainder energy: i,j,u,v,energy",
            5,(double)i,(double)j,(double)u,(double)v,(double)sensorNodeEnergy);
    gs.record("activated relay node remainder energy: i,j,u,v,n,energy",
            6,(double)i,(double)j,(double)u,(double)v,(double)activatedRelayNode,(double)relayNodeEnergy[activatedRelayNode]);
    for(int loop = 0; loop<relayNodeSize;loop++){
        gs.record("relay node remainder energy: i,j,u,v,n,energy",
                6,(double)i,(double)j,(double)u,(double)v,(double)loop,(double)relayNodeEnergy[loop]);
    }
}

WSNNode::WSNNode() {
	WSNNode(0);
}

bool WSNNode::consumeTransmitEnergy(double distance , int bits) {
	double consumedEnergy = 1.9225/10000;
	if(relayNodeEnergy[activatedRelayNode]>consumedEnergy+deadRelayEnergy) {
		relayNodeEnergy[activatedRelayNode]-=consumedEnergy;
	} else {
		activatedRelayNode++;
		if(activatedRelayNode<relayNodeSize) {
			relayNodeEnergy[activatedRelayNode]-=consumedEnergy;
		} else {
			return false;
		}
	}
	return true;
}
int WSNNode::startTransimit() {
	bool flag = consumeTransmitEnergy(0,0);
    if(id!=0+NETW_OFFSET&&flag){
    	if(flag){
    		std::cout<<"ERROR:id==0+NETW_OFFSET"<<std::endl;
    	}
    	return getNextHop(i,j,u,v);
    }else{
    	return -1;
    }
}

void WSNNode::output() {
	gs.output("WSN_XY.log");
}
inline int getHexagonLevel(int id) {
    if(id == 0)
        return 0;
    else
        return (int) (sqrt((id-1)/3.0+0.25)+0.5);
}

inline int getHexagonIndex(int id) {
    if(id == 0){
        return 0;
    }
    else{
        int n = getHexagonLevel(id);
        return id-3*n*(n-1)-1;
    }
}

inline int getRelayNodeSize(int i,int v, int N, double w) {
    if(v==0)
        return 3*(N-i+1)*(N-i)*w;
    else
        return (N-i)*w;
}

inline int getNextHop(int i, int j, int u, int v) {
    if(i==1)
        return 0+NETW_OFFSET;
    if(v!=0&&rand()%100>49){
        return 3*(i-1)*((i-1)-1)+(i-1)*u+(v-1)+1+NETW_OFFSET;
    }else
        return 3*(i-1)*((i-1)-1)+(i-1)*u+(v-0)+1+NETW_OFFSET;
}

