// why do we use & when writing to or reading from a binary file ?
// because whe need the adress of the variable we want to write/read
// when do we use operator '->' with struct ?
// when the struct variable is a pointer to a struct(dynamic or just a ptr)

#include <iostream>
#include <fstream>

const unsigned int FN_LENGTH = 11;
const unsigned int STUDENTS_COUNT = 5;
const unsigned int AGES[STUDENTS_COUNT] = { 19, 21, 33, 20, 22 };
const unsigned int NAME_LENGTHS[STUDENTS_COUNT] = { 8, 10, 8, 9, 7 };
const char NAMES[STUDENTS_COUNT][10] = { "Antonio", "Ekaterina", "Stefany", "Katerina", "Robert" };
const char FNS[STUDENTS_COUNT][FN_LENGTH] = { "0MI0600123", "2MI0800100", "3MI0404321", "1MI0400555", "5MI0811011" };

struct Student
{
    unsigned int age;
    char* name;
    char fn[FN_LENGTH];
};

struct StudentCollection
{
    Student* data;
};

void initStudents(StudentCollection& students, unsigned int studentsCount)
{
    for (int i = 0; i < studentsCount; ++i)
    {
        students.data[i].age = AGES[i];
        strcpy_s(students.data[i].fn, FNS[i]);
        // including '\0'
        unsigned int nameLen = NAME_LENGTHS[i];
        students.data[i].name = new char[nameLen];
        strcpy_s(students.data[i].name, nameLen, NAMES[i]);
    }
}

void printStudents(const StudentCollection& students, unsigned int studentsCount)
{
    for (int i = 0; i < studentsCount; ++i)
    {
        std::cout << students.data[i].name << std::endl;
        std::cout << students.data[i].age << std::endl;
        std::cout << students.data[i].fn << std::endl << std::endl;
    }
}

void writeStudentToFile(const Student& s, std::ofstream& file)
{
    file.write((const char*)&s.age, sizeof(s.age));
    unsigned int nameLen = strlen(s.name);
    file.write((const char*)&nameLen, sizeof(nameLen));
    file.write(s.name, nameLen);
    file.write(s.fn, sizeof(s.fn));
}

void writeStudentsToFile(const StudentCollection& students, unsigned int studentsCount)
{
    std::ofstream file("students.dat", std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        return;
    }


    for (int i = 0; i < studentsCount; ++i)
    {
        writeStudentToFile(students.data[i], file);
    }

    file.close();
}

void readStudentFromFile(Student& s, std::ifstream& file)
{
    // age, nameLen, name(in heap), fn
    file.read((char*)&s.age, sizeof(s.age));
    unsigned int nameLen;
    file.read((char*)&nameLen, sizeof(nameLen));
    s.name = new char[nameLen + 1];
    file.read(s.name, nameLen);
    s.name[nameLen] = '\0';
    file.read(s.fn, sizeof(s.fn));
}

void readStudentsFromFile(StudentCollection& students, unsigned int studentsCount)
{
    std::ifstream file("students.dat", std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "File can't be opened!" << std::endl;
        return;
    }

    for (int i = 0; i < studentsCount; ++i)
    {
        readStudentFromFile(students.data[i], file);
    }

    file.close();
}

void releaseMemory(StudentCollection& students, unsigned int studentsCount)
{
    for (int i = 0; i < studentsCount; ++i)
    {
        delete[] students.data[i].name;
    }
    delete[] students.data;
}

int main()
{
    StudentCollection students;
    StudentCollection students2;

    students.data = new Student[STUDENTS_COUNT];
    students2.data = new Student[STUDENTS_COUNT];

    initStudents(students, STUDENTS_COUNT);

    //printStudents(students, STUDENTS_COUNT);

    writeStudentsToFile(students, STUDENTS_COUNT);

    readStudentsFromFile(students2, STUDENTS_COUNT);
    printStudents(students2, STUDENTS_COUNT);

    releaseMemory(students, STUDENTS_COUNT);
    releaseMemory(students2, STUDENTS_COUNT);
}