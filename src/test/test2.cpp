/****************************************************************************
*																			*
*	File:		run.cpp													    *
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file executes the discrete event simulation for the    *
*               specified parameters.                                       *
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include <stdlib.h>
#include "DateTime.h"
#include "Utility.h"

using namespace std;

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

int main()
{
//  Read in parameter file

    DateTime t1("01-31 18:00");
    DateTime t2("01-31 18:01");
    DateTime t3(t1.getRawTime());
    
    if (t1 < t2)
    {
        cout << t1 << " is before " << t2 << endl;
        cout << t2.secondsAfter(t1) << endl;
        cout << t2 - t1 << endl;
    }
    else
    {
        cout << t2 << " is before " << t1 << endl;
        cout << t1.secondsAfter(t2) << endl;
        cout << t1 - t2 << endl;
    }

    cout << t1 << endl;
    t2 = t1 + 60;
    cout << t1 << endl;
    cout << t2 << endl;
    // tm t = t2.getDateTime();
    t2 += 10*60;
    cout << t2 << endl;
    // cout << t1.getTimeString() << endl;

    time_t t = 6;
    cout << util::minToSec(t) << endl;
    cout << t1.getDateTimeString() << endl;

    // cout << t << endl;

	return 0;
}
