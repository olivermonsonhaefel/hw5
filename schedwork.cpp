#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
		const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
		int row, int col, std::vector<int> shiftCount
);

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
		std::vector<int> shiftCount = {};
		for(int i = 0; i < avail.size(); i++) {
			std::vector<Worker_T> test(dailyNeed, -1);
			sched.push_back(test);
		}
		for(int i = 0; i < avail[0].size(); i++) {
			shiftCount.push_back(0);
		}
		return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0, shiftCount);
}

bool scheduleHelper(
		const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
		int row, int col, std::vector<int> shiftCount
) {
	if(col >= dailyNeed) {
		col = 0;
		row ++;
	}
	if(row >= avail.size()) {
		return true;
	}
	for(int i = col > 0 ? sched[row][col-1]+1 : 0; i < avail[row].size(); i++) {
		if(!avail[row][i]) continue;
		sched[row][col] = i;
		shiftCount[i] += 1;

		if(shiftCount[i] <= maxShifts) {
			if(scheduleHelper(avail, dailyNeed, maxShifts, sched, row, col+1, shiftCount)) return true;
		}
		shiftCount[i] -= 1;
		sched[row][col] = -1;
	}
	return false;
}