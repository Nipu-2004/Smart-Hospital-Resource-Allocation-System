#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define NUM_SPECIALTIES 4
#define NUM_WARDS       4
#define MAX_BEDS        20
#define MAX_PATIENTS    100
#define NAME_LEN        50
#define ID_LEN          15



void initializeSystem(void);
void displayMainMenu(void);
void clearInputBuffer(void);
int  readIntInRange(const char *prompt, int lo, int hi);
int findSpecialtyIndexByID(int id);
int findWardIndexByID(int id);
void registerPatient(void);



/*Doctor Specialties*/
const int    specialtyID[NUM_SPECIALTIES]   = {1, 2, 3, 4};
const char   specialtyName[NUM_SPECIALTIES][30] = {
    "General Practice (OPD)", "Paediatrics", "Cardiology", "Neurology"
};
const double baseFee[NUM_SPECIALTIES]      = {1500.00, 2500.00, 4500.00, 5000.00};
const int    consultTime[NUM_SPECIALTIES]  = {15, 20, 30, 30};
const int    dailyCap[NUM_SPECIALTIES]     = {30, 20, 12, 10};

/*Hospital Wards*/
const int    wardID[NUM_WARDS]        = {1, 2, 3, 4};
const char   wardName[NUM_WARDS][30]  = {
    "General Ward", "Paediatric Ward", "Surgical Ward", "ICU (Intensive Care Unit)"
};
const double dailyBedRate[NUM_WARDS]  = {3000.00, 6000.00, 12000.00, 25000.00};
const int    bedCapacity[NUM_WARDS]   = {20, 10, 10, 5};

/*Bed Occupancy Matrix*/
int bedOccupancy[NUM_WARDS][MAX_BEDS];

/*Specialty Queue Counters*/
int queueCount[NUM_SPECIALTIES];

/*Patient Parallel Arrays*/
char   patientID[MAX_PATIENTS][ID_LEN];
char   patientName[MAX_PATIENTS][NAME_LEN];
int    patientAge[MAX_PATIENTS];
int    urgencyLevel[MAX_PATIENTS];
int    specialtyIndex[MAX_PATIENTS];
int    isAdmitted[MAX_PATIENTS];
int    wardIndex[MAX_PATIENTS];
int    bedNumber[MAX_PATIENTS];
int    daysAdmitted[MAX_PATIENTS];

int patientCount = 0;
int nextPatientNumber = 1001;



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

void displayMainMenu(void) {
    printf("\n============================================================\n");
    printf("        SMART HOSPITAL & RESOURCE ALLOCATION SYSTEM\n");
    printf("============================================================\n");
    printf(" 1. Register New Patient\n");
    printf(" 2. View Bed Occupancy Matrix\n");
    printf(" 3. View Patients in Priority (Triage) Order\n");
    printf(" 4. Generate Performance Reports\n");
    printf(" 5. Save & Exit\n");
    printf("------------------------------------------------------------\n");
}



void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int readIntInRange(const char *prompt, int lo, int hi) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) {
            clearInputBuffer();
            if (value >= lo && value <= hi) {
                return value;
            }
        } else {
            clearInputBuffer();
        }
        printf("  -> Invalid input. Please enter a value between %d and %d.\n", lo, hi);
    }
}

int findSpecialtyIndexByID(int id) {
    for (int i = 0; i < NUM_SPECIALTIES; i++) {
        if (specialtyID[i] == id) return i;
    }
    return -1;
}

int findWardIndexByID(int id) {
    for (int i = 0; i < NUM_WARDS; i++) {
        if (wardID[i] == id) return i;
    }
    return -1;
}

void registerPatient(void) {
    if (patientCount >= MAX_PATIENTS) {
        printf("\nPatient records are full (max %d). Cannot register more.\n", MAX_PATIENTS);
        return;
    }
    int p = patientCount;

    printf("\n------------- New Patient Registration -------------\n");
    printf("Patient Name: ");
    fgets(patientName[p], NAME_LEN, stdin);
    patientName[p][strcspn(patientName[p], "\n")] = '\0';

    patientAge[p] = readIntInRange("Patient Age: ", 0, 120);
    urgencyLevel[p] = readIntInRange("Triage Level (1=Normal, 2=Urgent, 3=Critical): ", 1, 3);

    printf("\nAvailable Specialties:\n");
    for (int i = 0; i < NUM_SPECIALTIES; i++) {
        printf("  %d. %-25s (LKR %.2f)\n", specialtyID[i], specialtyName[i], baseFee[i]);
    }
    int specId = readIntInRange("Select Specialty ID: ", 1, NUM_SPECIALTIES);
    specialtyIndex[p] = findSpecialtyIndexByID(specId);

    snprintf(patientID[p], ID_LEN, "PAT-%d", nextPatientNumber++);
    patientCount++;

    printf("Registered patient %s successfully.\n", patientID[p]);
}

int main(void) {
    initializeSystem();
    int choice;
    int running = 1;
    printf("Welcome to the Smart Hospital & Resource Allocation System\n");

    while (running) {
        displayMainMenu();
        choice = readIntInRange("Enter your choice (1-5): ", 1, 5);

        switch (choice) {
            case 1: registerPatient(); break;
            case 2: printf("Bed occupancy - coming soon\n"); break;
            case 3: printf("Priority order - coming soon\n"); break;
            case 4: printf("Reports - coming soon\n"); break;
            case 5:
                printf("\nGoodbye!\n");
                running = 0;
                break;
        }
    }
    return 0;
}
