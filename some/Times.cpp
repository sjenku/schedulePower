//
//  Times.cpp
//  some
//
//  Created by jenia kushnarenko on 21/01/2020.
//  Copyright © 2020 jenia kushnarenko. All rights reserved.
//

#include "Times.hpp"



//Constructer Lesson
Time::Time()
{
    p_nxt = nullptr;
    day = 0;
    minute = 0;
    duration = 0;
    hour = 0;
}

Time::Time(UINT day,UINT hour,UINT minute,UINT duration)
{
    p_nxt = nullptr;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
    this->duration = duration;
}

Time Time::endTime()
{
    UINT hourFromDuration = (this->duration / 60) + hour;
    UINT minuteFromDuration = (this->duration % 60) + minute;
    Time timeNew(day,hourFromDuration,minuteFromDuration,0);
    
    return timeNew;
}

bool Time::biggerFrom(Time time)
{
   return  ((this->day - time.day) * 60 * 24 + (this->hour - time.hour) * 60 + (this->minute - time.minute)) > 0 ? true : false;
}

bool Time::equalTo(Time time)
{
   if ((this->day == time.day) && (this->hour == time.hour) && (this->minute == time.minute)
       && (this->duration == time.duration)) return true;
   else  return false;
}


Times::Times()
{
    head_p = nullptr;
    
}

Time Times::timeAtIndex(UINT index)
{
    Time *tmp = head_p;
    int i = 0;
    while (tmp && i<index)
    {
        tmp = tmp->p_nxt;
        i += 1;
    }
    return *tmp;
}


UINT Times::count(void)
{
    Time *tmp;
    UINT counter = 0;
    for(tmp = head_p;tmp;tmp = tmp->p_nxt)
    {
        counter += 1;
    }
    return counter;
}

void Times::appendTime(Time t)
{
    Time *t_p;
    t_p = new(Time);
    (*t_p).day = t.day;
    (*t_p).hour = t.hour;
    (*t_p).minute = t.minute;
    (*t_p).duration = t.duration;
    if (head_p == nullptr)
    {
        head_p = t_p;
    }
    else
    {
        Time *tmp;
        for(tmp = head_p;tmp->p_nxt;tmp = tmp->p_nxt);
        tmp->p_nxt = t_p;
    }
}

void Times::appendTimesFromTo(UINT day,UINT hourF,UINT minF,UINT hourT,UINT minT,UINT duration)
{
    int until = ((hourT - hourF) * 60) + (minT - minF) - duration;
    for (int i = 0; i<=until;i++)
    {
        this->appendTime(Time(day,hourF,minF,duration));
           minF += 1;
           if (minF == 60)
           {
               minF = 0;
               hourF += 1;
           }
    }
}

void Times::printTimes()
{
    Time *tmp;
    for(tmp = head_p;tmp;tmp = tmp->p_nxt)
    {
        std::cout<<"Day: "<<(*tmp).day<<" Hour: "<<(*tmp).hour<<" M: "<<(*tmp).minute<<" Duration: "<<(*tmp).duration<<std::endl;
    }
}

void Times::putTimesTo(Times &buff)
{
    Time *tmp;
    for(tmp = this->head_p;tmp;tmp = tmp->p_nxt)
    {
        buff.appendTime(*tmp);
    }
}

void Times::deleteTime(Time time)
{
    Time *tmp;
    Time *toDelete;
    tmp = head_p;
    if ((*tmp).equalTo(time))
    {
        head_p = tmp->p_nxt;
    }
    else
    {
        for(;tmp;tmp = tmp->p_nxt)
        {
            if (tmp->p_nxt != nullptr)
            {
               if ((*(tmp->p_nxt)).equalTo(time) == true)
               {
                   toDelete = tmp->p_nxt;
                   tmp->p_nxt = toDelete->p_nxt;
                   toDelete->p_nxt = nullptr;
                   free(toDelete);
               }
            }
        }
    }
}
