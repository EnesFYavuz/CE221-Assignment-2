#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Student.h"

using namespace std;

vector<Student>studentVec;
vector<Student>::iterator it;
int index = 0;

// Iterates through the vector, returns the regNo if it is equal to the regNo in the arguments
bool searchForReg(int regNo){
    it = find_if(studentVec.begin(), studentVec.end(), [&regNo](const Student& student){
        return student.getRegNo() == regNo;
    });
    if(it != studentVec.end()){
        index = distance(studentVec.begin(), it);
        // Found student with regNo
        return true;
    }
    else{
        return false;
    }
}

// Iterates through vector, gets the name of each student, prints out the average of all their grades
void printNameAvg(vector<Student>studVec, float mark){
    cout << endl;
    cout << "Averages" << endl;
    for(unsigned int i = 0; i < studVec.size(); i++){
        cout << studVec.at(i).getName() << "    " << studVec.at(i).getAverageMark() << endl;
    }
}

// Iterates through vector, tries to get the mark of the student in that particular module, then prints name and mark
// If it can't, then the student doesn't have a mark so a NoMarkException is caught
void printStudentsOfModule(vector<Student>studVec, string moduleNum, float mark){
    for(unsigned int i = 0; i < studVec.size(); i++){
        try{
            mark = studVec.at(i).getMark(moduleNum);
            cout << studVec.at(i).getName() << "  " << mark << endl;
        }
        catch(NoMarkException){
            cerr << "No mark found for this student... Moving onto the next student... " << endl;
        }
    }
}


int main(){
    string studFileName;
    cout << "Student File Extractor" << endl;
    cout << "Please enter name of the file to open: " << endl;
    getline(cin, studFileName);
    ifstream studsFile;
    cout << "Opening file: '" << studFileName << "'" << endl;
    studsFile.open(studFileName);

    // Split the line
    if(studsFile){
        string line;
        istringstream stream(line);
        string regNoString, nameString;
        int regNo;

        while(getline(studsFile, line)){
            regNoString = line.substr(0, 5);
            // Converts string to int
            regNo = stoi(regNoString);
            nameString = line.substr(6);

            // DEBUG
            //cout << "RegNo: " << regNo << endl;
            //cout << "Name: " << nameString << endl;

            // Create a new student and add it to a collection of students
            Student student(nameString, regNo);
            studentVec.push_back(student);
        }
        cout << "Finished adding students to vector" << endl;
    }
    else{
        cout << "File '" << studFileName << "' could not be opened";
    }

    /*
     * DEBUG -> Used to test if students were correctly entered into vector
    for (int i = 0; i < studentVec.size(); i++) {
        cout << studentVec.at(i).getName() << endl;
    }
     */
    studsFile.close();

    // Open marks file
    string marksFileName;
    cout << endl;
    cout << "Student marks extractor: " << endl;
    cout << "Please enter name of the file to open: " << endl;
    getline(cin, marksFileName);
    ifstream marksFile;
    cout << "Opening file: '" << marksFileName << "'" << endl;
    marksFile.open(marksFileName);

    if(marksFile){
        string line;
        istringstream stream(line);
        string regNoString, moduleNumString, markString;
        float mark;
        int regNo;

        while(getline(marksFile, line)){
            regNoString = line.substr(0, 5);
            // Converts string to int
            regNo = stoi(regNoString);

            moduleNumString= line.substr(6, 5);

            markString = line.substr(12);
            mark = stof(markString);

            // DEBUG
            //cout << "RegNo: " << regNo << endl;
            //cout << "Module: " << moduleNumString << endl;
            //cout << "Mark: " << mark << endl;

            // Search vector to see if there is a student with that regno
            // Add module and mark to map
            if(searchForReg(regNo)){
                studentVec.at(index).addMark(moduleNumString, mark);
                //cout << "Student found with regNo: " << regNo << endl;
            }
            else{
                cout << "No student found with regNo: " << regNo << endl;
            }

        }
        //cout << studentVec.at(4) << " has this mark for CE301: " << studentVec.at(4).getMark("CE301") << endl;

        for(int i = 0; i < studentVec.size(); i++){
            cout << endl;
            cout << studentVec.at(i).getRegNo() << "  " << studentVec.at(i).getName() << endl;
            try{
                cout << "CE151: " << studentVec.at(i).getMark("CE151") << endl;
            }
            catch(NoMarkException e){
                //cerr << e.what() << endl;
            }
            try{
                cout << "CE301: " << studentVec.at(i).getMark("CE301") << endl;
            }
            catch(NoMarkException e){
                //cerr << e.what() << endl;
            }
            try{
                cout << "CE204: " << studentVec.at(i).getMark("CE204") << endl;
            }
            catch(NoMarkException e){
                //cerr << e.what() << endl;
            }
            try{
                cout << "CE212: " << studentVec.at(i).getMark("CE212") << endl;
            }
            catch(NoMarkException e){
                //cerr << e.what() << endl;
            }
            try{
                cout << "CE152: " << studentVec.at(i).getMark("CE152") << endl;
            }
            catch(NoMarkException e){
                //cerr << e.what() << endl;
            }
            try{
                cout << "CE153: " << studentVec.at(i).getMark("CE153") << endl;
            }
            catch(NoMarkException e){
                //cerr << e.what() << endl;
            }
            try{
                cout << "CE312: " << studentVec.at(i).getMark("CE312") << endl;
            }
            catch(NoMarkException e){
                //cerr << e.what() << endl;
            }
            try{
                cout << "CE202: " << studentVec.at(i).getMark("CE202") << endl;
            }
            catch(NoMarkException e){
                //cerr << e.what() << endl;
            }

            try{
                cout << "CE202: " << studentVec.at(i).getMark("CE221") << endl;
            }
            catch(NoMarkException e){
                //cerr << e.what() << endl;
            }
        }

        // keep asking the user to select an option, until they choose to exit the program
        while(true){
            cout << "PrintNameAvg (1)       or PrintStudentsOfModule(2)     or Exit(3)" << endl;
            string funcChoice;
            getline(cin, funcChoice);

            // If the input was "1" then print the average marks of the student
            if((funcChoice == "1")){
                string markToUseString;
                float markToUse;

                cout << "Enter a mark to use: " << endl;
                getline(cin, markToUseString);
                markToUse = stof(markToUseString);

                printNameAvg(studentVec, markToUse);
            }

            // If the input was "2" then print all the students that have marks for that module
            if((funcChoice == "2")){
                string moduleString;
                string markStringTwo;
                float markToUse;

                cout << "Enter a module number: " << endl;
                getline(cin, moduleString);
                cout << "Enter a mark: " << endl;
                getline(cin, markStringTwo);
                markToUse = stof(markStringTwo);
                cout << "Students with marks for: '" << moduleString << "'" << endl;
                printStudentsOfModule(studentVec, moduleString, markToUse);
            }

            // Exit the program with the error code 0 (No error occurred)
            if((funcChoice == "3")){
                cout << "Program ending...";
                exit(0);
            }
        }
    }
    else{
        cout << "Could not open file : '" << marksFileName << "'" << endl;
    }

    marksFile.close();
}