/*
 * GlobalStatics.h
 *
 *  Created on: 1405051354
 *      Author: Fanjing
 */

#ifndef GLOBALSTATISTICS_H_
#define GLOBALSTATISTICS_H_

#include<map>
#include<list>
#include<string>
#include<stdarg.h>

#include"GlobalStatisticsUnit.h"
/*
 *
 */
typedef std::list<GlobalStatisticsUnit> GlobalStatisticsList;
typedef std::map<string,GlobalStatisticsList> GlobalStatisticsMap;
class GlobalStatistics {
public:
    GlobalStatistics();
    virtual ~GlobalStatistics();

public:
    void record(string name, int size, ...);
    void output(string name);
private:
     GlobalStatisticsMap globalStatisticsMap;

};

#endif /* GLOBALSTATISTICS_H_ */
