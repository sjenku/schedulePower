//
//  Times.hpp
//  some
//
//  Created by jenia kushnarenko on 21/01/2020.
//  Copyright © 2020 jenia kushnarenko. All rights reserved.
//

#ifndef Times_hpp
#define Times_hpp

#define UINT unsigned int
#define MAX_NAME     12
#define SCHEDULE_DAY 7
#define SCHEDULE_MIN 1440 //min per day
#define SUCCESS      9999
#define MULTI_ID     9998
#define OVERLOAD     9997
#define NO_OVERLOAD  9996
#define EQUAL        9995


#include <stdio.h>
#include <iostream>

class Time
{
public:
    Time * p_nxt;
    Time();
    Time(UINT day,UINT hour,UINT minute,UINT duration);
    UINT day,hour,minute,duration;
    Time endTime(void);
    bool biggerFrom(Time time);
    bool equalTo(Time time);
};

class Times
{
    Time * head_p;
public:
    Times();
    void appendTime(Time);
    void printTimes();
    void appendTimesFromTo(UINT day,UINT hourF,UINT minF,UINT HourT,UINT minT,UINT duration);
    void putTimesTo(Times &buff);
    UINT count(void);
    Time timeAtIndex(UINT index);
    void deleteTime(Time time);
};

#endif /* Times_hpp */
