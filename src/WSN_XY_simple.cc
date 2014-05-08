/*
 * WSN_XY_simple.cc
 *
 *  Created on: May 8, 2014
 *      Author: Fanjing-LAB
 */

#include "WSNNode.h"

int main(){
	int statisticsInterval = 1000;
	int nodeNum = 37;
	WSNNode **node = new WSNNode*[nodeNum];
	for(int i = 0; i< nodeNum;i++){
		node[i] = new WSNNode(i);
	}
	bool flag = true;
	for(int n = 0;flag;n++){
		for(int i = 1;i<nodeNum&&flag;i++){
			if(n%statisticsInterval==0){
				node[i]->record();
			}
			int debug = 21;
			if(i==debug){
				i=debug;
			}
			for(int j = node[i]->startSensor(n);j!=0;){
				if(j<0){
					flag = false;
					break;
				}else{
					j=node[j]->startTransimit();
				}
			}
		}
	}
	node[0]->output();

	for(int i = 0; i< nodeNum;i++){
		delete(node[i]);
	}
}
