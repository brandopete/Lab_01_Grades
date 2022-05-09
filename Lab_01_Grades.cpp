#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <cmath>

using namespace std;


char setLetterGrade(double testScore, double examAverage)
{
    char letterGrade = 'z';
    if((testScore >= examAverage - 5) && (testScore <= examAverage + 5))
    {
        letterGrade = 'C';
    }
    else if((testScore > examAverage + 5) && (testScore <= examAverage + 15))
    {
        letterGrade = 'B';
    }
    else if((testScore > examAverage + 15))
    {
        letterGrade = 'A';
    }
    else if((testScore < examAverage -5) && (testScore >= examAverage - 15))
    {
        letterGrade = 'D';
    }
    else if(testScore < examAverage - 15)
    {
        letterGrade = 'E';
    }

    return letterGrade;

}


int main(int argc, char* argv[])
{

    int num_students;
    int num_exams;

    cout << "Input file: " << argv[1] << endl;

    ifstream in(argv[1]);

    in >> num_students >> num_exams;
    //Skip the rest of the line
    in.ignore(numeric_limits<int>::max(), '\n');

    //Initialize 2D Array for student scores
    int **examGrades = new int*[num_students];
    for(int i = 0; i < num_students; ++i)
    {
        examGrades[i] = new int[num_exams];
    }

    //Initialize 1D Array for student names
    string* studentNames = new string[num_students];

    //Parse Array
    string line;
    for(int j = 0; j < num_students; ++j) {
        getline(in, line);
        size_t p = 0;
        while (!isdigit(line[p++]));    // line[p] is the first digit

        //Read Data from operator
        string scores = line.substr(p - 1, string::npos);
        string name = line.substr(0, p - 1);
        studentNames[j] = name;


        istringstream iss(scores);
        for(int k = 0; k < num_exams; ++k){
            int grade;
            iss >> grade;
            examGrades[j][k] = grade;
        }

    }

    ofstream out(argv[2]);

    //Print out Exam grades and Student Names table
    out << "Student Scores:" << endl;
    for (int i = 0; i < num_students; ++i)
    {
        out << std::setw(20) << studentNames[i] << " ";
        for(int j = 0; j < num_exams; ++j)
        {
            int gradeInt;
            //cout << examGrades[i][j] << " ";
            out << std::fixed << std::setprecision(0) << std::setw(6) << examGrades[i][j];
        }
        out << "\n";
    }

    //Calculate Exam Averages
    out << "Exam Averages:" << endl;
    double examTestAverage;
    double* examTestAverages = new double[num_exams];
    int currScore = 0;
    double tempScore = 0;
    for(int i = 0; i < num_exams; ++i)
    {
        for(int j = 0; j < num_students; ++j)
        {
            currScore = examGrades[j][i];
            tempScore += currScore;
        }
        int a = i + 1;
        examTestAverage = round(10 * (tempScore/num_students)) / 10;
        out << std::setw(12) << "Exam " << a << " Average = " << std::fixed << std::setprecision(1) << std::setw(6) << examTestAverage << endl;
        tempScore = 0;
        examTestAverages[i] = examTestAverage;
    }

    //Print out Exam grades and Student Names table with Grade Letter
    out << "Student Exam Grades:" << endl;
    for (int i = 0; i < num_students; ++i)
    {
        out << std::setw(20) << studentNames[i] << " ";
        for(int j = 0; j < num_exams; ++j)
        {
            int gradeInt;
            //cout << examGrades[i][j] << " ";
            out << std::fixed << std::setprecision(0) << std::setw(6) << examGrades[i][j] << "(" << setLetterGrade((examGrades[i][j]), examTestAverages[j]) << ")";
        }
        out << "\n";
    }

    //Print out Exam Averages
    //int examLetterGradesCount[num_exams][num_exams];
    int aCount = 0;
    int bCount = 0;
    int cCount = 0;
    int dCount = 0;
    int eCount = 0;
    char retChar = 'x';
    out << "Exam Grades:" << endl;
    for(int i = 0; i < num_exams; ++i)
    {
        for(int j = 0; j < num_students; ++j)
        {
            //cout << setLetterGrade(examGrades[j][i], examTestAverages[i]);
            retChar = setLetterGrade(examGrades[j][i], examTestAverages[i]);
            if(retChar == 'A'){
                aCount += 1;
            }
            else if(retChar == 'B')
            {
                bCount += 1;
            }
            else if(retChar == 'C')
            {
                cCount += 1;
            }
            else if(retChar == 'D')
            {
                dCount += 1;
            }
            else if(retChar == 'E')
            {
                eCount += 1;
            }
        }
        out << std::setw(12) << "Exam " << (i + 1) << " " << std::setw(6) << aCount << "(A)" << std::setw(6) << bCount << "(B)" << std::setw(6) << cCount << "(C)" << std::setw(6) << dCount << "(D)" << std::setw(6) << eCount << "(E)" << endl;
        aCount = 0;
        bCount = 0;
        cCount = 0;
        dCount = 0;
        eCount = 0;
        //cout << std::setw(12) << "Exam " << (i + 1) << " ";
    }

    //Calculate Student Final Grades
    out << "Student Final Grades:" << endl;
    double examAverage;
    double* examAverages = new double[num_students];
    double* appendStudentGrade = new double[num_students];
    double classAverage;
    double totalScores = 0.0;
    double temp = 0.0;
    for (int i = 0; i < num_students; ++i)
    {
        for(int j = 0; j < num_exams; ++j)
        {
            examAverages[i] = examGrades[i][j];
            temp += examAverages[i];
        }
        examAverage = temp/num_exams;
        appendStudentGrade[i] = examAverage;
        totalScores += examAverage;
        classAverage = totalScores/num_students;


        //cout << std::setw(20) << studentNames[i] << std::fixed << std::setprecision(1) << std::setw(6) << examAverage << "(" << setLetterGrade(examAverage, classAverage) << ")" << endl;
        temp = 0;

    }

    /*for(int i = 0; i < num_students; ++i)
    {
        cout << studentNames[i] << endl;
    }*/

    //cout << classAverage << endl;
    for(int i = 0; i < num_students; ++i){
        out << std::setw(20) << studentNames[i] << std::fixed << std::setprecision(1) << std::setw(6) << appendStudentGrade[i] << "(" << setLetterGrade(appendStudentGrade[i], classAverage) << ")" << endl;
    }

    //Print out Class Average
    out << "Class Average Score = " << std::fixed << std::setprecision(1) << std::setw(6) << classAverage << endl;

    for(int i = 0; i < num_students; ++i)
    {
        delete [] examGrades[i];

    }
    /*for(int i = 0; i < num_students; ++i)
    {
        delete [] studentNames[i];
    }*/
    delete [] examGrades;
    delete [] studentNames;
    delete [] examAverages;
    delete [] appendStudentGrade;
    delete [] examTestAverages;

    return 0;
}
