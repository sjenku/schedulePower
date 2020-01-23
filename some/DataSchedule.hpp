//
//  DataSchedule.hpp
//  some
//
//  Created by jenia kushnarenko on 17/01/2020.
//  Copyright © 2020 jenia kushnarenko. All rights reserved.
//

#ifndef DataSchedule_hpp
#define DataSchedule_hpp
#endif /* DataSchedule_hpp */


#include "Students.hpp"



class Schedule
{
    UINT scheduleTable[SCHEDULE_DAY][SCHEDULE_MIN];
    Times lessonsStartTime;
    Students students;
public:
    Schedule();
    void setStudents(Students students);
    UINT transferHourMinToColoum(UINT hour,UINT min);
    void displaySchedule();
    UINT idAtTime(Time time); //return Id Number if Student accupaite else return 0.
    UINT insertTimeToSchedule(Time time,Student *student);
    UINT isEmptyFromTo(Time timeF,Time timeT);
    Time findIdStartTimeLesson(Time time,Student *student);
    void generateScheduleStudents();
    void deleteTimeFromSchedule(Time time,Student *student);
    void generateScheduleSecondOption();
    void garbageCleaner();
};

