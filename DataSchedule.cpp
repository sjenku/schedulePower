//
//  DataSchedule.cpp
//  some
//
//  Created by jenia kushnarenko on 17/01/2020.
//  Copyright © 2020 jenia kushnarenko. All rights reserved.
//
#include "DataSchedule.hpp"


Schedule::Schedule()
{
    for(int coloum = 0;coloum<SCHEDULE_DAY;coloum++)
    {
        for(int row = 0;row<SCHEDULE_MIN;row++)
        {
            this->scheduleTable[coloum][row] = 0;
        }
    }
}

void Schedule::setStudents(Students students)
{
    this->students = students;
}

void Schedule::displaySchedule()
{
   // TODO:Finish display;for that need to change how manage students;
    UINT count = lessonsStartTime.count();
    UINT id;
    Time lesson;
    Student *student;
    for(int i = 0;i<count;i++)
    {
        lesson = lessonsStartTime.timeAtIndex(i);
        id = this->idAtTime(lesson);
        student = this->students.findStudentByID(id);
        if ((*student).getName() != nullptr)
            std::cout<<"Name:"<<(*student).getName()<<std::endl;
        printf("Day: %d Hour: %d Min: %d\n",lesson.day,lesson.hour,lesson.minute);
    }
}

UINT Schedule::transferHourMinToColoum(UINT hour, UINT min)
{
    return (hour*60) + min;
}

UINT Schedule::idAtTime(Time time)
{
    return scheduleTable[time.day - 1][transferHourMinToColoum(time.hour, time.minute)];
}

UINT Schedule::isEmptyFromTo(Time timeF,Time timeT) //return SUCCESS id empty,else
                                                    //return MULTI_ID if there more then one
                                                    //otherwise return ID.
{
    UINT amountOfId = 0;
    UINT savedID = 0;
    int until = ((timeT.hour - timeF.hour) * 60) + (timeT.minute - timeF.minute) - 1;
    for(int i = 0;i<=until ;i++)
    {
       UINT spotID = this->scheduleTable[timeF.day - 1][transferHourMinToColoum(timeF.hour, timeF.minute) + i];
      if (spotID != 0 && savedID != spotID) {
          amountOfId += 1;
          savedID = spotID;
      }
    }
    if (amountOfId == 1) return savedID;
    else if (amountOfId > 1) return MULTI_ID;
    else return SUCCESS;
}


 UINT Schedule::insertTimeToSchedule(Time time,Student *student) //return SUCCESS if inserted,else                                                       //return id that accupate the spot                                                      //in the schedule.
{
    
    
    UINT result = isEmptyFromTo(time, time.endTime());
    UINT id = (*student).getId();
    if (result == id) {
         return result;
    }
    else if (result == SUCCESS)
    {
        Time timeT = time.endTime();
        int diff = ((timeT.hour - time.hour) * 60) + (timeT.minute - time.minute) - 1;
        lessonsStartTime.appendTime(time);    //insert to schedule start time
        (*student).appendTimeToGotLesson(time);   //Insert lesson to student
        for(int i = 0;i<=diff;i++)   //Fill The Schedule
         {
            this->scheduleTable[time.day - 1][transferHourMinToColoum(time.hour, time.minute) + i] = id;
         }
       
        //--------this is for point on the next choise possability without checking again spots that acupate by the same student------//
        
        Time tmpTime = Time();
        student->topPossibilities_p += 1;
    Times possibilitesTimes = student->fetchStudentPossibilitiesTimes();
        for(int i = student->topPossibilities_p;i<(student->getPossibilitiesCount() - 1) && time.biggerFrom(tmpTime);i++)
        {
            tmpTime = possibilitesTimes.timeAtIndex(i);
            student->topPossibilities_p += 1;
        }
        
    return result;
    }
 return result;
    
}

void Schedule::deleteTimeFromSchedule(Time time,Student *student)
{
    //before delete check if time exist at lessonsStartTime.
    int count = lessonsStartTime.count();
    bool found = false;
    
    for(int i = 0; i<count && found == false;i++)
    {
        if (time.equalTo(lessonsStartTime.timeAtIndex(i)) == true) found = true;
    }
    
    if (found)   //if found delete
    {
        Time timeT = time.endTime();
        int diff = ((timeT.hour - time.hour) * 60) + (timeT.minute - time.minute) - 1;
        lessonsStartTime.deleteTime(time);
        (*student).deleteTimeFromGotLessons(time);
        for(int i = 0;i<=diff;i++)
        {
            this->scheduleTable[time.day - 1][transferHourMinToColoum(time.hour, time.minute) + i] = 0;
        }
    }
}

//get some time
Time Schedule::findIdStartTimeLesson(Time time,Student *student)
{
    UINT coloumSomeSpot = transferHourMinToColoum(time.hour, time.minute);
    UINT rowSomeSpot = time.day - 1;
    Times studentGotLessons = (*student).fetchStudentGotLessonsTimes();
    UINT amountOfLessons = studentGotLessons.count();
    Time lesson;
    UINT coloumStudentLesson,rowStudentLesson,durationLesson;
    for(int i = 0;i<amountOfLessons;i++)
    {
        lesson = studentGotLessons.timeAtIndex(i);
        coloumStudentLesson = transferHourMinToColoum(lesson.hour, lesson.minute);
        rowStudentLesson = lesson.day - 1;
        durationLesson = lesson.duration - 1;
        
        if ((coloumStudentLesson <= coloumSomeSpot) && (rowStudentLesson == rowSomeSpot) &&
            ((coloumStudentLesson + durationLesson) >= coloumSomeSpot))
        {
            return lesson;
        }
        
    }
    return Time();
}



void Schedule::generateScheduleSecondOption()
{
    UINT amountOfStudents = students.count();
       UINT amountOfPossabilitiesRes = 0,amountOfPossabilitiesStu = 0;
       int result,reservedResult;
       Student *student;
       Student *reservedStudent;
       Times student_lessons_possibilites,reserved_lessons_possibilites;
       Time lessonTime,anotherTime,fetchTime;
       for(int i = 0;i < amountOfStudents;i++)
       {
           student = students.studentAtIndex(i);
           student_lessons_possibilites = student->fetchStudentPossibilitiesTimes();
           amountOfPossabilitiesStu = student_lessons_possibilites.count();
           for(int j = 0 ;j<amountOfPossabilitiesStu && !student->isHaveAllLessons();j++)
           {
               lessonTime = student_lessons_possibilites.timeAtIndex(j);
               result = insertTimeToSchedule(lessonTime, student);
               if ((result != SUCCESS) && (result != MULTI_ID) && (result != student->getId())) //someOne else at the spot
               {
                   reservedStudent = students.findStudentByID(result);
                   reserved_lessons_possibilites = reservedStudent->fetchStudentPossibilitiesTimes();
                   amountOfPossabilitiesRes = reserved_lessons_possibilites.count();
                   if (reservedStudent->topPossibilities_p < amountOfPossabilitiesRes)
                   {
                       int index = reservedStudent->topPossibilities_p;
                       anotherTime = reserved_lessons_possibilites.timeAtIndex(index);
                       reservedResult =  insertTimeToSchedule(anotherTime, reservedStudent);
                       fetchTime = findIdStartTimeLesson(lessonTime, reservedStudent);
                       if (reservedResult == SUCCESS)
                       {
                           deleteTimeFromSchedule(fetchTime, reservedStudent);
                         reservedResult = insertTimeToSchedule(lessonTime, student);
                           if (reservedResult != SUCCESS)
                           {
                               insertTimeToSchedule(fetchTime, reservedStudent);
                           }
                       }
                   }
               }
           }
       }
}




 void Schedule::generateScheduleStudents()
{
    UINT amountOfStudents = students.count();
    UINT amountOfPossabilities = 0;
    UINT overload = 0;
    int result;
    Student *student;
    Student *reservedStudent;
    Times student_lessons_possibilites;
    Time lessonTime;
    for(int i = 0;i < amountOfStudents;i++)
    {
        student = students.studentAtIndex(i);
        student_lessons_possibilites = (*student).fetchStudentPossibilitiesTimes();
        amountOfPossabilities = student_lessons_possibilites.count();
        for(int j = amountOfPossabilities - 1;j>-1;j--)//TODO::Change Here Carefully!
        {
            lessonTime = student_lessons_possibilites.timeAtIndex(j);
           result = this->insertTimeToSchedule(lessonTime, student);

            if ((result != student->getId()) && (result != MULTI_ID) && (result != SUCCESS))
                //that's mean someone else is on that spot
            {
              reservedStudent = students.findStudentByID(result);
                overload = reservedStudent->isOverLoad();
              if (overload == OVERLOAD )
               {
                   //deletePrevTime
                   Time fetchedStartTime = this->findIdStartTimeLesson(lessonTime, reservedStudent);

                   this->deleteTimeFromSchedule(fetchedStartTime, reservedStudent);
                   //check if empty...
                   result = this->isEmptyFromTo(lessonTime, lessonTime.endTime());
                   if (result == SUCCESS)
                   this->insertTimeToSchedule(lessonTime, student);
                   else
                   this->insertTimeToSchedule(fetchedStartTime, reservedStudent);
               }
            }
        }

    }
}



void Schedule::garbageCleaner()
{
    int amountOfStudent = students.count();
    Student *student;
    Times studentsGotLessons;
    Time timeToDelete;
    UINT amountOfLessonsToDeleteForStu = 0;
    
    for(int i = 0;i<amountOfStudent;i++)
    {
        student = students.studentAtIndex(i);
        if (student->isOverLoad() == OVERLOAD)
        {
            studentsGotLessons = student->fetchStudentGotLessonsTimes();
            amountOfLessonsToDeleteForStu = studentsGotLessons.count() - student->getAskedLessonNum();
            for(int i = 0;i<amountOfLessonsToDeleteForStu;i++)
            {
                timeToDelete = studentsGotLessons.timeAtIndex(i);
                this->deleteTimeFromSchedule(timeToDelete, student);
            }
        }
    }
}
