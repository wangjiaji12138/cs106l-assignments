#include <string>
#include <iostream>
class class_simple
{
private:
    std::string teacher;
    int stu_num;
    void insertStudent(int update_num);
public:
    class_simple();
    class_simple(std::string teacher,int stu_num);

    std::string getTeacher() const;
    int getStu_num() const;

    void setTeacher(std::string teacher);
};
