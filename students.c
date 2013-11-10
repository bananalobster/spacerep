#include <iostream>
#include <map>
#include <list>

using namespace std;

typedef map<string, int> MarMap;
typedef map<string, int>::iterator MarMapIt;
typedef map<string, int>::const_iterator MarMapCIt;

class Student
{
private:
    string name_, surname_;
    MarMap marks_;
public:
    Student(string name, string surname):
        name_(name),
        surname_(surname)
    {
    }
    ~Student()
    {
        name_ = "";
        surname_ = "";
        marks_.clear();
    }
    void AddMark(string subject, int mark)
    {
        marks_[subject] = mark;
    }
    void Display()
    {
        cout << name_ << " " << surname_ << endl;
    }
};

class StudentList
{
private:
    list< Student > students_;
    list< Student >::iterator it_;
    void DisplayStudentRecursive_()
    {
        if (!(it_ == students_.end()))
        {
            it_->Display();
            it_++;
            DisplayStudentRecursive_();
        } else
        {
            it_ = students_.begin();
        };
    }
public:
    StudentList():
        it_(students_.begin())
    {
    }
    ~StudentList()
    {
        students_.clear();
    }
    void AddStudent(string name, string surname)
    {
        students_.push_front(Student(name, surname));
    }
    void DisplayList()
    {
        DisplayStudentRecursive_();
    }
};

int main()
{
    StudentList students;
    students.AddStudent("Lobster", "FromHell");
    students.AddStudent("Rukudo", "Mukuro");
    students.DisplayList();

    return 0;
}
