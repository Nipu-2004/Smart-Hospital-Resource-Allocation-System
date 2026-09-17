#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define NUM_SPECIALTIES 4
#define NUM_WARDS       4
#define MAX_BEDS        20



void initializeSystem(void);



/*Doctor Specialties*/
const int    specialtyID[NUM_SPECIALTIES]   = {1, 2, 3, 4};
const char   specialtyName[NUM_SPECIALTIES][30] = {
    "General Practice (OPD)", "Paediatrics", "Cardiology", "Neurology"
};
const double baseFee[NUM_SPECIALTIES]      = {1500.00, 2500.00, 4500.00, 5000.00};
const int    consultTime[NUM_SPECIALTIES]  = {15, 20, 30, 30};
const int    dailyCap[NUM_SPECIALTIES]     = {30, 20, 12, 10};

/*Lookup Data: Hospital Wards*/
const int    wardID[NUM_WARDS]        = {1, 2, 3, 4};
const char   wardName[NUM_WARDS][30]  = {
    "General Ward", "Paediatric Ward", "Surgical Ward", "ICU (Intensive Care Unit)"
};
const double dailyBedRate[NUM_WARDS]  = {3000.00, 6000.00, 12000.00, 25000.00};
const int    bedCapacity[NUM_WARDS]   = {20, 10, 10, 5};

/*Bed Occupancy Matrix*/
int bedOccupancy[NUM_WARDS][MAX_BEDS];

/* Specialty Queue Counters*/
int queueCount[NUM_SPECIALTIES];



void initializeSystem(void) {
    for (int w = 0; w < NUM_WARDS; w++) {
        for (int b = 0; b < MAX_BEDS; b++) {
            bedOccupancy[w][b] = 0;
        }
    }
    for (int s = 0; s < NUM_SPECIALTIES; s++) {
        queueCount[s] = 0;
    }
}

int main(void) {
    initializeSystem();
    printf("Welcome to the Smart Hospital & Resource Allocation System\n");
    return 0;
}
