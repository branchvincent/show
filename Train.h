/****************************************************************************
*																			*
*	File:		Train.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jul 11, 2016												*
*																			*
*	Purpose:	This file defines the Train class.							*
*																			*
****************************************************************************/

#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include <list>
#include <queue>
#include <algorithm>
#include "Task.h"
#include "Operator.h"
#include "Statistics.h"
#include <Python.h> //Python.h>

using namespace std;
using namespace params;

// Type definitions

//bool cmpPrty2(Task* t1, Task* t2)
//{
//    if (t1->getPriority() == t2->getPriority())
//        return t1->getExpTime() > t2->getExpTime();
//    else
//        return t1->getPriority() < t2->getPriority();
//}
//
//typedef priority_queue<Task*,vector<Task*>,decltype(&cmpPrty)> Queue2;

/****************************************************************************
*																			*
*	Definition of Train class												*
*																			*
****************************************************************************/

//  Notes
//  - Shared task to op with current lowest priority
//  - Add fatigue for just human operators
//  - Add shared task ID as a subset
//  - Pass all queues to each operator for interruptions

class Train
{
//  Friend class
    
//    friend Operator;
    
//	Public member functions
	
	public:
	
	//	Constructor
    
		Train(int tNum = CURR_TRAIN++);
//		Train(string name, int tNum = 0) : stats(), ops()
//		{
//			ops.push_back(Operator(name, OP_TASKS[0], stats, tNum));
//		}
	
	// 	Inspector
		
        int getQueueSize() {return ops[0].getQueueSize();}
        Task* getNextDepature();
        float getNextDeptTime();
        bool isBusy() const;
//        bool opIsIdle() const;
        Operator& getIdleOp();
		float getUtil(int i, int j) {return ops[i].getUtil(j);}
	
    // 	Mutators
		
        void procArr(Task* task);
		void procDep(Task* task, bool stop);
        void clear() {for (int i = 0; i < ops.size(); i++) ops[i].clear();};
        void endRep();
//        void plot();
	
    //  Other member functions
    
        void output();
        void output(ostream& out) const;
    
//	Data members

	private:
//      Params& params;
        Statistics stats;
        vector<Operator> ops;
		int trainNum;
};

ostream& operator<<(ostream& out, const Train& s) {s.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	Train														*
*																			*
*	Purpose:	To construct a new Train									*
*																			*
****************************************************************************/

Train::Train(int tNum) : stats(), ops()
{
	if (tNum == 0)
		ops.push_back(Operator("Dispatcher", DP_TASKS[0], stats, tNum));
	else
	{
		for (int i = 0; i < NUM_OPS; i++)
			ops.push_back(Operator(OP_NAMES[i], OP_TASKS[i], stats, tNum));
	}
}


/****************************************************************************
*																			*
*	Function:	getNextDepature												*
*																			*
*	Purpose:	To get the task with the soonest depature					*
*																			*
****************************************************************************/

Task* Train::getNextDepature()
{
//	Initialize variables
    
    float currDepTime;
    float minTime = ops[0].getDepTime();
    int minIndex = 0;
    
//  Get depature time and index of soonest depature
    
    for (int i = 0; i < ops.size(); i++)
    {
    //  Get depature time
        
        currDepTime = ops[i].getDepTime();
        
    //  Check for new minimum
        
        if (currDepTime < minTime)
        {
            minTime = currDepTime;
            minIndex = i;
        }
    }

//  Return task with minimum depature time
    
    return ops[minIndex].getCurrTask();
}

/****************************************************************************
*																			*
*	Function:	getNextDeptTime                                             *
*																			*
*	Purpose:	To get the depature time for the next task 					*
*																			*
****************************************************************************/

float Train::getNextDeptTime()
{
//  Get next departing task
    
    Task* task = getNextDepature();
    
//  Get depature time
    
    if (task != NULL)
        return task->getDepTime();
    else
        return INFINITY;
}

/****************************************************************************
*																			*
*	Function:	isBusy                                                      *
*																			*
*	Purpose:	To determine if at least one operator is busy               *
*																			*
****************************************************************************/

bool Train::isBusy() const
{
//  Check for a busy operator
    
    for (int i = 0; i < ops.size(); i++)
        if (ops[i].isBusy())
            return true;

//  If not found, return false
    
    return false;
}

/****************************************************************************
*																			*
*	Function:	isIdle                                                      *
*																			*
*	Purpose:	To determine if at least one operator is idle               *
*																			*
****************************************************************************/

//bool Train::opIsIdle() const
//{
////  Check for an idle operator
//    
//    for (int i = 0; i < ops.size(); i++)
//        if (ops[i].isIdle())
//            return true;
//    
////  If not found, return false
//    
//    return false;
//}

/****************************************************************************
*																			*
*	Function:	getIdleOp                                                   *
*																			*
*	Purpose:	To return the operator that is availabe                     *
*																			*
****************************************************************************/

Operator& Train::getIdleOp()
{
//  Check for an idle operator
    
    for (int i = 0; i < ops.size(); i++)
        if (ops[i].isIdle())
            return ops[i];
    
//  If not found, return error
    
    cout << "Error: No idle operator. Exiting..." << endl;
    cerr << "Error: No idle operator. Exiting..." << endl;
    exit(1);
}

/****************************************************************************
*																			*
*	Function:	procArr                                                     *
*																			*
*	Purpose:	To process a task arrival								 	*
*																			*
****************************************************************************/

void Train::procArr(Task* task)
{	
//	Get task attributes
    
	float currTime = task->getArrTime();
    vector<int> opNums = task->getOpNums();
//	int type = task->getType();
    if (DEBUG_ON) cout << "\t Task arriving at " << currTime << endl;
    
//	Add task to the appropriate queue
    
//    if (opNum > ops.size())
//    {
//        cerr << "Error: Incompatible operator ID. Exiting..." << opNum << endl;
//        exit(1);
//    }
	
//	vector<int> opNums;
//	for (int i = 0; i < ops.size(); i++)
//	{
//		vector<int> op_tasks = ops[i].getTaskNums();
//		if (find(op_tasks.begin(), op_tasks.end(), type) != op_tasks.end())
//			opNums.push_back(i);
//	}
	
	ops[0].procArr(task);
	
//	if (opNums.size() == 0)
//	{
//		cerr << "Error: Task has no associated assistants. Exiting..." << endl;
//		exit(1);
//	}
//    else if (opNums.size() == 1)
//        ops[opNums[0]].procArr(task);
//    else
//    {
//    //  Find shortest queue (include current task)
//        
////        cout << "SHARED TASK ARRIVING" << endl;
////        
////        for (int i = 0; i < ops.size(); i++)
////        {
////            if (ops[i].isBusy())
////                cout << ops[i].getName() << " is busy with " << 1+ops[i].getQueueSize() << " tasks including " << *(ops[i].getCurrTask()) << endl;
////            else
////                cout << ops[i].getName() << " is idle." << endl;
////        }
//        
//        int queueSize;
//        int minSize = ops[0].getQueueSize() + ops[0].isBusy();
//        int minIndex = 0;
//        
//        int end = (int)opNums.size() - 1;
//        int j = 0;
//        
//        for (int i = opNums[0]; i <= opNums[end]; i++)
//        {
//        //  Get queue size
//            
//            if (find(OPS.begin(), OPS.end(), i) != OPS.end())
//            {
//                queueSize = ops[j].getQueueSize() + ops[j].isBusy();
//                
//            //  Check for new minimum
//                
//                if (queueSize < minSize)
//                {
//                    minSize = queueSize;
//                    minIndex = j;
//                }
//                j++;
//            }
//        }
//        
////        cout << "Operator size = " << ops.size() << endl;
////        cout << "Index = " << minIndex << endl;
////        cout << "Going to " << ops[minIndex].getName() << endl;
//		
//        ops[minIndex].procArr(task);
//    }
	
//  Update stat

    int type = task->getType();
    int timeInt = currTime/INT_SIZE;
	stats.incNumTasksIn(type, timeInt, 1);
    
	return;
}

/****************************************************************************
*																			*
*	Function:	procDep                                                     *
*																			*
*	Purpose:	To process the task depature                                *
*																			*
****************************************************************************/

void Train::procDep(Task* task, bool stop)
{
//  Process depature from appropriate operator
    
    bool taskFound = false;
    
    for (int i = 0; i < ops.size(); i++)
        if (task == ops[i].getCurrTask())
        {
            taskFound = true;
            ops[i].procDep(task, stop);
        }
    
//  If task was not found, output error
    
    if (!taskFound)
    {
        cerr << "Error: Could not process task depature. Exiting..." << endl;
        exit(1);
    }
    
//  Update stats
    
    int timeInt = task->getDepTime()/INT_SIZE;
    stats.incNumTasksOut(task->getType(), timeInt, 1);

	return;
}

/****************************************************************************
*																			*
*	Function:	endRep                                                      *
*																			*
*	Purpose:	To end the replication                                      *
*																			*
****************************************************************************/

void Train::endRep()
{
//  Update stats
    
    stats.endRep();
    
//  Clear operators
    
    for (int i = 0; i < ops.size(); i++)
        ops[i].endRep();
    
    return;
}

/****************************************************************************
*																			*
*	Function:	plot                                                        *
*																			*
*	Purpose:	To plot each operator's utilization                         *
*																			*
****************************************************************************/

//void Train::plot()
//{
////  Initialize Python
//    
//    Py_Initialize();
//	
////  Plot each utilization
//    
//    for (int i = 0; i < ops.size(); i++)
//        ops[i].plot();
//	
////  Finalize Python
//    
//    Py_Finalize();
//	
//    return;
//}

/****************************************************************************
*																			*
*	Function:	output                                                      *
*																			*
*	Purpose:	To output...                                                *
*																			*
****************************************************************************/

void Train::output(ostream& out) const
{
//  Output global stats
    
//    out << stats << endl;
    
//  Output operators

    out << ops[0] << endl;
    
//    for (int i = 0; i < ops.size(); i++)
//        out << ops[i] << endl;
//    
    return;
}

/****************************************************************************
*																			*
*	Function:	output                                                      *
*																			*
*	Purpose:	To output...                                                *
*																			*
****************************************************************************/

void Train::output()
{
//  Output global stats
    
    string file = OUTPUT_PATH + "/stats_total.csv";
    ofstream fout(file);
    if (!fout)
    {
        cout << "Error: Cannot open " << file << ". Exiting..." << endl;
        cerr << "Error: Cannot open " << file << ". Exiting..." << endl;
        exit(1);
    }
    
    fout << stats;
    
//  Output operators
    
    for (int i = 0; i < ops.size(); i++)
        ops[i].output();

    return;
}

#endif
