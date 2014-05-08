/*
 * GlobalStatics.cpp
 *
 *  Created on: 1405051354
 *      Author: Fanjing
 */

#include "GlobalStatistics.h"
#include <fstream>
#include <iostream>

GlobalStatistics::GlobalStatistics() {
    // TODO Auto-generated constructor stub
}

GlobalStatistics::~GlobalStatistics() {
    // TODO Auto-generated destructor stub
    for (GlobalStatisticsMap::iterator it = globalStatisticsMap.begin();
            it != globalStatisticsMap.end(); it++) {
        for (GlobalStatisticsList::iterator lit = it->second.begin();
                lit != it->second.end(); lit++) {
            delete (&lit);
        }
    }
}

void GlobalStatistics::record(string name, int size, ...) {
    // TODO Auto-generated destructor stub
    GlobalStatisticsMap::iterator it;
    GlobalStatisticsUnit *unit = new GlobalStatisticsUnit(size);
    double val;
    va_list vl;
    va_start(vl,size);
    for(int i = 0; i<size; i++){
        val = va_arg(vl,double);
        unit->setData(val,i);
    }
    va_end(vl);
    it = globalStatisticsMap.find(name);
    if(it==globalStatisticsMap.end()){
        GlobalStatisticsList list;
        globalStatisticsMap.insert(std::pair<string,GlobalStatisticsList>(name,list));
    }
    globalStatisticsMap[name].push_back(*unit);
}

void GlobalStatistics::output(string name) {
    std::fstream fs;
    fs.open (name.c_str(),std::fstream::out);
    for(GlobalStatisticsMap::iterator it = globalStatisticsMap.begin();it!=globalStatisticsMap.end();it++){
        fs<<it->first<<std::endl;
        for(GlobalStatisticsList::iterator lit = it->second.begin();lit!=it->second.end();lit++){
            fs<<lit->toString()<<std::endl;
        }
    }
    fs.close();
}
