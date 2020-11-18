/*
Student Name:
Student Number:
Project Number: 3
Compile Status: [SUCCESS/FAIL]
Running Status: [SUCCESS/FAIL]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "SeatOperations.h"


using namespace std;

SeatOperations::SeatOperations(int N, int M) {
    this->N = N;
    this->M = M;
    lines[0].resize(this->N);
    lines[1].resize(this->M);
}

void SeatOperations::addNewPerson(int personType, const string &ticketInfo) {
    Person newPerson;
    newPerson.existence = 1;
    newPerson.type = personType;
    newPerson.seatNumber = stoi(
            ticketInfo.substr(1, ticketInfo.length()));
    int firstLoc = newPerson.seatNumber;
    if (ticketInfo.substr(0, 1) == "A") {
        newPerson.line = 0;

        firstLoc = (newPerson.seatNumber - 1) % N;
        newPerson.initial = "A" + to_string(firstLoc + 1);
    } else {
        newPerson.line = 1;

        firstLoc = (newPerson.seatNumber - 1) % M;
        newPerson.initial = "B" + to_string(firstLoc + 1);

    }
    Person temp = lines[newPerson.line].at(firstLoc);
    lines[newPerson.line].at(firstLoc) = newPerson;

    if (temp.existence == 1) {
        changer(temp, firstLoc);
    }

}

void SeatOperations::printAllSeats(ofstream &outFile) {

    for (int i = 0; i < lines[0].size(); i++) {
        if (lines[0].at(i).existence ==
            0) {
            outFile << 0 << endl;
        } else {
            outFile << lines[0].at(i).type << " " << lines[0].at(i).initial
                    << endl;
        }
    }

    for (int i = 0; i < lines[1].size(); i++) {
        if (lines[1].at(i).existence == 0) {
            outFile << 0 << endl;
        } else {
            outFile << lines[1].at(i).type << " " << lines[1].at(i).initial << endl;
        }
    }
}

void SeatOperations::changer(Person &removed, int loc) {
    int newLoc = loc;
    if (removed.type == 1) {
        if (removed.line == 0) {

            newLoc = (removed.seatNumber - 1) % M;
            removed.line = 1;
            Person temp = lines[1].at(newLoc);
            lines[1].at(newLoc) = removed;

            if (temp.existence == 1) {
                changer(temp, newLoc);
            }


        } else {
            newLoc = (removed.seatNumber - 1) % N;
            removed.line = 0;
            Person temp = lines[0].at(newLoc);
            lines[0].at(newLoc) = removed;
            if (temp.existence == 1) {
                changer(temp, newLoc);
            }

        }

    } else if (removed.type == 2) {
        if (newLoc + 1 == N && removed.line == 0) {

            removed.line = 1;
            Person temp = lines[1].at(0);
            lines[1].at(0) = removed;


            if (temp.existence == 1) {
                changer(temp, 0);
            }

        } else if (newLoc + 1 == M &&
                   removed.line == 1) {

            removed.line = 0;
            Person temp = lines[0].at(0);
            lines[0].at(0) = removed;

            if (temp.existence == 1) {
                changer(temp, 0);
            }


        } else {

            newLoc = ++loc;
            Person temp = lines[removed.line].at(newLoc);
            lines[removed.line].at(newLoc) = removed;

            if (temp.existence == 1) {
                changer(temp, newLoc);
            }


        }
    } else {

        int newLoc = stoi(removed.initial.substr(1, removed.initial.length())) +
                     (removed.type3LastOperation + 1) * (removed.type3LastOperation + 1);
        int final = (newLoc - 1) % lines[removed.line].size();
        while (newLoc > lines[removed.line].size()) {
            newLoc -= lines[removed.line].size();
            removed.line = 1 - removed.line;
            final = (newLoc - 1) % lines[removed.line].size();
        }

        if (lines[removed.line].at(final).existence == 0) {
            lines[removed.line].at(final) = removed;
            lines[removed.line].at(final).type3LastOperation++;
        } else {
            Person temp = lines[removed.line][final];
            lines[removed.line][final] = removed;
            lines[removed.line][final].type3LastOperation++;
            changer(temp, final);

        }
    }
}

// YOU CAN ADD YOUR HELPER FUNCTIONS