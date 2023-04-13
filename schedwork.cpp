#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

unsigned int backtrack(const AvailabilityMatrix& avail, vector<size_t>& remainingShifts, const size_t dailyNeed, const size_t numDays, DailySchedule& sched, size_t dayRow);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();

    // Add your code below

		const size_t numWorkers = avail[0].size(); // k
		const size_t numDays = avail.size(); // n

		vector<size_t> remainingShifts(numWorkers, maxShifts); // create a vector of numWorkers size that has their # of shifts available

		return backtrack(avail, remainingShifts, dailyNeed, numDays, sched, 0);

}

unsigned int backtrack(const AvailabilityMatrix& avail, vector<size_t>& remainingShifts, const size_t dailyNeed, const size_t numDays, DailySchedule& sched, size_t dayRow)
{

	if (dayRow == numDays) // base case
	{
		return 1;
	}

	// check every worker

	for (size_t workerID = 0; workerID < dailyNeed; workerID++)
	{
		if(remainingShifts[workerID] >= 1 && avail[dayRow][workerID])
		{
			if(dayRow == sched.size())
			{
				vector<Worker_T> var;
				sched.push_back(var);
			}

			sched[dayRow].push_back(workerID); // schedule shift

			remainingShifts[workerID] = remainingShifts[workerID] - 1; // update max shifts remaining for worker
			

			if(backtrack(avail, remainingShifts, dailyNeed, numDays, sched, dayRow + 1))
			{
				return 1;
			}

			sched[dayRow].pop_back();

			remainingShifts[workerID] = remainingShifts[workerID] + 1;

		}
	}
	
	return 0; // if we make it to this point, there is no schedule that works
}



	
	
