/*
 * WSN_XY_simple.cc
 *
 *  Created on: May 8, 2014
 *      Author: Fanjing-LAB
 */

#include<iostream>
#include "WSNNode.h"
#include "GlobalStatistics.h"

int main(){
	GlobalStatistics gs = GlobalStatistics();
	int statisticsInterval = 1000;
	int size=6;
	WSNNode().N = size;
	int nodeNum = 3*(size+1)*size+1;
	WSNNode *node = new WSNNode[nodeNum];
	for(int i = 0; i< nodeNum;i++){
		node[i].setId(i);
	}
	bool flag = true;
	for(int n = 0;flag;n++){
		if (n % 400 == 0) {
			// fig.1
			double totalRelayEnergy = 0;
			double totalSensorEnergy = 0;
			for (int i = 1; i < nodeNum; i++) {
				for (int j = 0; j < node[i].relayNodeSize; j++) {
					totalRelayEnergy += node[i].relayNodeEnergy[j];
				}
				totalSensorEnergy += node[i].sensorNodeEnergy;
			}
			gs.record("figure 1: recordId,total1,total2", 3, (double) (n / 400),
					totalRelayEnergy, totalSensorEnergy);
			// fig.2 & fig.3
			double *sensorECR = new double[size];
			double *relayECR = new double[size];
			for(int i = 0;i<size;i++){
				sensorECR[i] = 0;
				relayECR[i] = 0;
			}
			for (int i = 1; i < nodeNum; i++) {
				for (int j = 0; j < node[i].relayNodeSize; j++) {
					relayECR[node[i].i] += node[i].relayNodeEnergy[j];
				}
				sensorECR[node[i].i] += node[i].sensorNodeEnergy;
			}
			gs.record("figure 2: rid,i,secr...", 6, (double) (n / 400),
					relayECR[1], relayECR[2], relayECR[3], relayECR[4],
					relayECR[5]);
			gs.record("figure 3: rid,i,recr...", 6, (double) (n / 400),
					sensorECR[1], sensorECR[2], sensorECR[3], sensorECR[4],
					sensorECR[5]);
			delete (sensorECR);
			delete (relayECR);
			// fig.4
			double *secr = new double [6];
			for(int i = 0;i<6;i++){
				secr[i] = 0;
			}
			for (int i = 1; i < 7; i++) {
				for (int j = 0; j < node[i].relayNodeSize; j++) {
					secr[node[i].j] += node[i].relayNodeEnergy[j];
				}
			}
			gs.record("figure 4: rid,recr...",7,(double) (n / 400),
					secr[0], secr[1],secr[2], secr[3], secr[4], secr[5]);
			delete(secr);
			// fig.5 See Mark01

		}
		for(int i = 1;i<nodeNum&&flag;i++){
			if(n%statisticsInterval==0){
				std::cout<<"Round: "<<n<<std::endl;
				node[i].record();
			}
			int debug = 36;
			if(i==debug){
				i=debug;
			}
			for(int j = node[i].startSensor(n);j!=0;){
				if(j<0){
					//Mark01
					double *FsensorECR = new double[size];
					double *FrelayECR = new double[size];
					for(int i = 0;i<size;i++){
						FsensorECR[i] = 0;
						FrelayECR[i] = 0;
					}
					for (int i = 1; i < nodeNum; i++) {
						for (int j = 0; j < node[i].relayNodeSize; j++) {
							FrelayECR[node[i].i] += node[i].relayNodeEnergy[j];
						}
						FsensorECR[node[i].i] += node[i].sensorNodeEnergy;
					}
					gs.record("figure 5: rid,i,tecr...", 6, (double) (n / 400),
							FrelayECR[1]+FsensorECR[1], FrelayECR[2]+FsensorECR[2], FrelayECR[3]+FsensorECR[3], FrelayECR[4]+FsensorECR[4],
							FrelayECR[5]+FsensorECR[5]);
					delete (FsensorECR);
					delete (FrelayECR);

					flag = false;
					break;
				}else{
					j=node[j].startTransimit();
				}
			}
		}
	}
	node[0].output();
	gs.output("WS_XY_simple.log");

	delete[](node);
}
