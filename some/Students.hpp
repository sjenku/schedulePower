//
//  Students.hpp
//  some
//
//  Created by jenia kushnarenko on 21/01/2020.
//  Copyright © 2020 jenia kushnarenko. All rights reserved.
//

#ifndef Students_hpp
#define Students_hpp

#include "Times.hpp"


class Student
{
    UINT id,no_asked_l;
    static UINT counter,base;
    Times possibilitiesTimes;
    Times gotLessonsTimes;
    Times notGotLessonsTimes;
    char *name;
public:
    Student();
    Student *nxt_p;
    UINT topPossibilities_p;
    char * getName();
    UINT getId(void);
    UINT isOverLoad();
    UINT getAskedLessonNum();
    bool isHaveAllLessons();
    UINT getPossibilitiesCount();
    void setNumberOfLessonsShouldGet(UINT num);
    void setTimesToPossibilities(Times times);
    void appendTimeToGotLesson(Time time);
    void appendTimeToNotGotLesson(Time time);
    void deleteTimeFromGotLessons(Time time);
    Times fetchStudentGotLessonsTimes();
    Times fetchStudentPossibilitiesTimes();
    void setName(char* name);
    void printStu();
};

class Students
{
    Student *head_p;
public:
    Students();
    Student * CreateNewStudent();
    void CreateNewStudent(char * name,UINT numberOfLessons,Times lessons);
    Student * studentAtIndex(UINT index);
    UINT count();
    void printStudents();
    Student * findStudentByID(UINT id);
};

#endif /* Students_hpp */
