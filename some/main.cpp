//
//  main.cpp
//  some
//
//  Created by jenia kushnarenko on 16/01/2020.
//  Copyright © 2020 jenia kushnarenko. All rights reserved.
//

#include "DataSchedule.hpp"

using namespace std;

void GenerateSchedule();

int main(int argc, const char * argv[]) {
    // insert code here...
    Times lessons;
    GenerateSchedule();
  
    return 0;
}


void GenerateSchedule()
{
    Schedule schedule;
    Times lessonsLiam,lessonsYotam,lessonsNoam;
    Students students;
    lessonsLiam.appendTimesFromTo(1, 0, 0, 0, 4, 1);
    lessonsYotam.appendTimesFromTo(1, 0, 0, 0, 4, 1);
    lessonsNoam.appendTimesFromTo(1, 0, 0, 0, 5, 1);
    students.CreateNewStudent("Noam", 1, lessonsNoam);
    students.CreateNewStudent("Liam",2, lessonsLiam);
    students.CreateNewStudent("Yotam",2,lessonsYotam);
    schedule.setStudents(students);
//    schedule.generateScheduleStudents();
    schedule.generateScheduleSecondOption();
//    schedule.garbageCleaner();
    schedule.displaySchedule();
    
    
}
