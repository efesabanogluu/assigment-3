#ifndef CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
#define CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Person{
    int existence = 0;
    int type=0;
    int line=0, seatNumber=0;
    int type3LastOperation=0;
    int type3Remain=0;
    string initial = "";
};

class SeatOperations{

private:
    vector<Person> lines[2];
    int N, M;

public:
    SeatOperations(int N, int M);
    void addNewPerson(int personType, const string& ticketInfo);
    void printAllSeats(ofstream& outFile);
    void changer(Person &newPerson , int loc);
    // YOU CAN ADD YOUR HELPER FUNCTIONS

};

#endif //CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
