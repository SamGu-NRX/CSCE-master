// DOCUMENTATION GOES HERE
// Sam Gu CSCE 1040.001

#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "bubble.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

/*
  1. void bubble(student *array[], int size)
  2. typedef struct student_info {
        char  *first;
        char  *last;
        int   exam1;
        int   exam2;
        int   exam3;
        int   exam4;
        float mean;
    } student;
*/

typedef struct classStats
{
   float mean;
   float min;
   float max;
   float median;
   char *name;
} classStats;

int main(int argc, char *argv[])
{
   // Reading the class name from redirected input
   string className;
   getline(cin, className);

   student *students[19];

   // Reading student data and calculating mean for each student
   for (int i = 0; i < 19; i++) {
      
      students[i] = (student *)malloc(sizeof(student));

      // if (students[i] == NULL) {
      //    fprintf(stderr, "Memory allocation failed for student %d\n", i);
      //    exit(1);
      // }

      students[i]->first = (char *)malloc(50 * sizeof(char));
      students[i]->last = (char *)malloc(50 * sizeof(char));

      // if (!students[i]->first || !students[i]->last) {
      //    fprintf(stderr, "Memory allocation failed for names of student %d\n", i);
      //    exit(1);
      // }

      // Reading names and exam scores
      cin >> students[i]->first >> students[i]->last >> students[i]->exam1 >>
          students[i]->exam2 >> students[i]->exam3 >> students[i]->exam4;

      students[i]->mean = (students[i]->exam1 + students[i]->exam2 +
                           students[i]->exam3 + students[i]->exam4) /
                          4.0;
   }

   bubble(students, 19);

   // Compute class statistics
   classStats stats;
   stats.name = (char *)className.c_str();
   stats.min = students[0]->mean;
   stats.max = students[18]->mean;

   // Compute class mean
   float totalMean = 0;
   for (int i = 0; i < 19; i++) {
      totalMean += students[i]->mean;
   }
   stats.mean = totalMean / 19;

   // Compute median
   if (19 % 2 == 0) {
      stats.median = (students[8]->mean + students[9]->mean) / 2.0;
   } else {
      stats.median = students[9]->mean;
   }

   // Print out the results
   cout << className << " MEAN: " << fixed << setprecision(2) << stats.mean
        << " MIN: " << stats.min << " MAX: " << stats.max
        << " MEDIAN: " << stats.median << endl;

   // Print each student's information
   for (int i = 0; i < 19; i++) {
      cout << left << setw(15) << students[i]->first << setw(15) << students[i]->last
           << fixed << setprecision(2) << students[i]->mean << endl;
   }

   // Free allocated memory
   for (int i = 0; i < 19; i++) {
      free(students[i]->first);
      free(students[i]->last);
      free(students[i]);
   }

   return 0;
}
