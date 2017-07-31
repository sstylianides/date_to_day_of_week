/*
 author: Stephan Stylianides
 Objective: This program will prompt the user for a date (mm/dd/yyyy). The program
            will then take that date and convert the date entered into a very large
            number representing a particular date. This very large number will be
            stored in a variable of type long integer which will be referred to as N.
            The program will then take the value stored in variable N and determine
            the number representing the day of the week that the date falls on. That
            is, if the number calculated by the algorithm is zero, then the day is
            Sunday. If the number calculated is a 1, then the day is Monday, etc. The
            program will ensure that the month entered is between 1 and 12, the day
            entered is between 1 and 31, and the year entered is greater than 1900,
            and that the actual day exists in history taking into account leap years.
 ------------------------------------------------------------------------------------ */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>


// from page 190
int f(int year, int month)
{
    if(month <=2) year--;

    return year;
}

// from page 190
int g(int month)
{
    if(month<=2) month+=13;
    else month++;

    return month;
}

// from page 190
long calc_date_number(int month, int day, int year)
{
    int calc1, calc2;
    calc1=(1461 * f(year, month))/4;
    calc2=(153*g(month))/5;
    return calc1 + calc2 + day;
}

int calc_day_number(int month, int day, int year)
{
    return (calc_date_number(month, day, year) - 621049)%7;
}

void display_day_of_week(int month, int day, int year)
{
    char *days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    int end_number=0;

    end_number=calc_day_number(month, day, year);

    if(end_number==0) printf("\nThe day of the week is: Sunday.\n");
    else printf("\nThe day of the week is: %s.\n", days[end_number]);
}

// this prevents inputting dates from the future
int now(int stop_value)
{
    char *var;
    time_t rawtime;
    struct tm * timeinfo;
    int counter=0;
    int today=0;
    char *temp="/0";

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    var=strtok(asctime(timeinfo), " ");


    while(var!=NULL)
    {
        if(counter==stop_value && stop_value!=1) today =atoi(var);
        if(counter==stop_value && stop_value==1) temp=var;
        var=strtok(NULL, " ");
        counter++;
    }

    if(temp == "Jan") today=1;
    else if(temp == "Feb") today=2;
    else if(temp == "Mar") today=3;
    else if(temp == "Apr") today=4;
    else if(temp == "May") today=5;
    else if(temp == "Jun") today=6;
    else if(temp == "Jul") today=7;
    else if(temp == "Aug") today=8;
    else if(temp == "Sep") today=9;
    else if(temp == "Oct") today=10;
    else if(temp == "Nov") today=11;
    else if(temp == "Dec") today=12;

    return today;
}

int main ()
{
    //Declare and initalize and the variables
    char string [10];
    char *date;
    int month=0, day=0, year=0;
    int i=-1;

    //intro statement
    printf("Welcome to the Date to Day-of-Week program.\n\nThe program will give the day of the week for any date from 1/1/1900\n");

    //make sure it's a valid month
    while(i==-1)
    {
        i=0;
        printf("Enter date (mm/dd/yyyy): ");
        scanf("%s", string);
        date = strtok(string, "/");
        while(atoi(date)<1 || atoi(date)>12)
        {
            printf("Invalid month. Please re-enter date.\n");
            printf("Enter date (mm/dd/yyyy): ");
            scanf("%s", string);
        }
        month=atoi(date);

        //make sure it's a valid day
        while(date!=NULL)
        {
            date=strtok(NULL, "/");

            if(i==0)
            {
                if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
                {
                    if(atoi(date)>31)
                    {
                        printf("Invalid day. Please re-enter date.\n");
                        i=-1;
                    }
                }

                if(month==4 || month==6 || month==9 || month==11)
                {
                    if(atoi(date)>30)
                    {
                        printf("Invalid day. Please re-enter date.\n");
                        i=-1;
                    }
                }

                if(i!=-1) day=atoi(date);
             }
            else if (i==1)
            {
                if(month==2)
                {
                    if((day>28 && atoi(date)%4!=0) || (day>29 && atoi(date)%4==0))
                    {
                        printf("Invalid day. Please re-enter date.\n");
                        i=-1;
                    }
                }
                // make sure it's a valid year
                if(atoi(date)<1900 || atoi(date)>now(4))
                {
                    printf("Invalid year. Please re-enter date.\n");
                    i=-1;
                }

                if(day>now(2) && atoi(date)>=now(4) && month>=now(1))
                {
                    printf("Invalid date. Please re-enter date.\n");
                    i=-1;
                }

                if(i!=-1) year=atoi(date);
            }

            if (i==-1) date=NULL;
            else i++;
        }
    }

        display_day_of_week(month, day, year);

        // end of program
        printf("\nThank you for using the Date to Day-of-Week program.");
        printf("\n\n");


        getchar();
        return 0;
}
