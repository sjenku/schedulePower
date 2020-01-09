//
//  Students.cpp
//  some
//
//  Created by jenia kushnarenko on 21/01/2020.
//  Copyright © 2020 jenia kushnarenko. All rights reserved.
//

#include "Students.hpp"


UINT Student::base = 100;
UINT Student::counter = 0;

Student::Student()
{
    name = nullptr;
    counter += 1;
    id = counter + base;
    nxt_p = nullptr;
    topPossibilities_p = 0;
}

void Student::setName(char *name)
{
    int len = (int)strlen(name);
    this->name = (char *)calloc(len, sizeof(char));
    
    strcpy(this->name, name);
}

bool Student::isHaveAllLessons()
{
    return (gotLessonsTimes.count() >= no_asked_l) ? true : false;
}

UINT Student::isOverLoad()
{
    int result =  gotLessonsTimes.count() - no_asked_l;
   return  (result > 0) ?  OVERLOAD : (result == 0) ? EQUAL : NO_OVERLOAD;
}

UINT Student::getAskedLessonNum()
{
    return no_asked_l;
}

void Student::printStu()
{
    if (name != nullptr)
    std::cout<<"Name: "<<name<<std::endl;
    std::cout<<"ID: "<<id<<std::endl;
    possibilitiesTimes.printTimes();
    std::cout<<"lessons not got: "<<std::endl;
    notGotLessonsTimes.printTimes();
    
}

UINT Student::getId(void)
{
    return id;
}

UINT Student::getPossibilitiesCount()
{
    return possibilitiesTimes.count();
}

char * Student::getName()
{
    return name;
}

 void Student::appendTimeToGotLesson(Time time)
{
    gotLessonsTimes.appendTime(time);
}

void Student::appendTimeToNotGotLesson(Time time)
{
    notGotLessonsTimes.appendTime(time);
}


void Student::setTimesToPossibilities(Times times)
{
    times.putTimesTo(possibilitiesTimes);
}

void Student::setNumberOfLessonsShouldGet(UINT num)
{
    no_asked_l = num;
}

Students::Students()
{
    head_p = nullptr;
}

Student * Students::findStudentByID(UINT id)
{
    Student *tmp;
    tmp = head_p;
        for(;tmp;tmp = tmp->nxt_p)
        {
            if((*tmp).getId() == id) return tmp;
        }
    return nullptr;
}

Times Student::fetchStudentGotLessonsTimes()
{
    return gotLessonsTimes;
}

Student * Students::CreateNewStudent()
{
    Student *stu = new(Student);
     Student *tmp;
    if (head_p == nullptr)
    {
        head_p = stu;
    }
    else
    {
        for(tmp = head_p;tmp->nxt_p;tmp = tmp->nxt_p);
        tmp->nxt_p = stu;
    }
    return stu;
}

void Students::CreateNewStudent(char * name,UINT numberOfLessons,Times lessons)
{
    Student *stu;
    stu = this->CreateNewStudent();
    (*stu).setName(name);
    (*stu).setNumberOfLessonsShouldGet(numberOfLessons);
    (*stu).setTimesToPossibilities(lessons);
}

void Student::deleteTimeFromGotLessons(Time time)
{
    gotLessonsTimes.deleteTime(time);
}

Times Student::fetchStudentPossibilitiesTimes()
{
    return possibilitiesTimes;
}

Student * Students::studentAtIndex(UINT index)
{
    Student *tmp;
    int i = 0;
    for(tmp = head_p;i<index && tmp;tmp = tmp->nxt_p,i++);
    return tmp;
}

UINT Students::count()
{
    Student *tmp;
    UINT count = 0;
    for(tmp = head_p;tmp;tmp = tmp->nxt_p)
    {
        count += 1;
    }
    return count;
}

void Students::printStudents()
{
    Student *tmp;
    for(tmp = head_p;tmp;tmp = tmp->nxt_p)
    {
        printf("------STUDENT------");
        (*tmp).printStu();
    }
}


