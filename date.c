/*
 * Functions for comparing dates.
 *   areDatesEqual - are two dates the same?
 *   isDateBefore - is the first date before the second?
 *   isDateAfter - is the first date after the second?
 */

#include "date.h"                  /* date type and prototypes */

int areDatesEqual(const Date *xptr, const Date *yptr)   
{
  return xptr->year  == yptr->year  &&
         xptr->month == yptr->month &&
         xptr->day   == yptr->day;
}

int isDateBefore(const Date *xptr, const Date *yptr) 
{
  if (xptr->year < yptr->year)         
    return 1;
  if (xptr->year > yptr->year)
    return 0;

  return (xptr->month < yptr->month ||
         (xptr->month == yptr->month && xptr->day < yptr->day));
}

int isDateAfter(const Date *xptr, const Date *yptr)       
  { return !isDateBefore(xptr, yptr) && !areDatesEqual(xptr, yptr); }
