#include <iostream>
#include <iomanip>
#include "Student.h"



Student::Student(const string &name, int regNo) : Person(name){
    Person::name = name;
    Student::name = name;
    Student::regNo = regNo;
    marks.clear();
}

int Student::getRegNo() const {
    return regNo;
}

void Student::addMark(const string &module, float mark) {

    if(mark >= 0 && mark <= 100){
        Student::marks.insert(pair<string, float>(module, mark));
    }
}

float Student::getMark(const string &module) const throw(NoMarkException){
    if(Student::marks.count(module) > 0){
        return Student::marks.find(module)->second;
    }
    else{
        throw NoMarkException();
    }
}

float Student::getAverageMark() const {
    map<string, float>theMap = Student::marks;
    map<string, float>::const_iterator it;
    float numOfMarks = 0;
    float totalMarks = 0;
    float average = 0;

    for(it = theMap.begin(); it != theMap.end(); ++it){
        totalMarks += it->second;
        numOfMarks++;
    }
    if(numOfMarks == 0){
        cout << theMap.begin()->second << endl;
        return 0;
    }
    else{
        average = totalMarks/numOfMarks;
        return average;
    }
}

ostream& operator<<(ostream &o, const Student &s){
    // If student has no marks
    // If student has marks
    o << setw(10) << s.name << ", " << s.regNo << s.getAverageMark();


    return o;
}