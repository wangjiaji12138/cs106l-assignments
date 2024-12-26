#include "class.h"
#include <string>
#include <iostream>

class_simple::class_simple()
    : teacher("Jimmy Wang"),stu_num(0) {}

class_simple::class_simple(std::string teacher,int stu_num)
    : teacher(teacher),stu_num(stu_num) {}


std::string class_simple::getTeacher() const{
    return this->teacher;
}
int class_simple::getStu_num() const{
    return this->stu_num;
}

void class_simple::setTeacher(std::string teacher){
    this->teacher = teacher;
}

void class_simple::insertStudent(int update_num){
    this->stu_num +=update_num;
}