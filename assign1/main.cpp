/*
 * CS106L Assignment 1: SimpleEnroll
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 *
 * Welcome to Assignment 1 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 * Students must implement: parse_csv, write_courses_offered,
 * write_courses_not_offered
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string COURSES_OFFERED_PATH = "student_output/courses_offered.csv";
const std::string COURSES_NOT_OFFERED_PATH = "student_output/courses_not_offered.csv";

/**
 * Represents a course a student can take in ExploreCourses.
 * You must fill in the types of the fields in this struct.
 * Hint: Remember what types C++ streams work with?!
 */
struct Course {
  /* STUDENT TODO DONE */std::string title;
  /* STUDENT TODO DONE */std::string number_of_units;
  /* STUDENT TODO DONE */std::string quarter;
};

/**
 * (STUDENT TODO DONE) Look at how the main function (at the bottom of this file)
 * calls `parse_csv`, `write_courses_offered`, and `write_courses_not_offered`.
 * Modify the signatures of these functions so that they work as intended, and then delete this
 * comment!
 */

/**
 * Note:
 * We need to #include utils.cpp _after_ we declare the Course struct above
 * so that the code inside utils.cpp knows what a Course is.
 * Recall that #include literally copies and pastes file contents.
 */
#include "utils.cpp"

/**
 * This function should populate the `courses` vector with structs of type
 * `Course`. We want to create these structs with the records in the courses.csv
 * file, where each line is a record!
 *
 * Hints:
 * 1) Take a look at the split function we provide in utils.cpp
 * 2) Each LINE is a record! *this is important, so we're saying it again :>)*
 * 3) The first line in the CSV defines the column names, so you can ignore it!
 *
 * @param filename The name of the file to parse.
 * @param courses  A vector of courses to populate.
 */
void parse_csv(std::string filename, std::vector<Course>& courses) {
  /* (STUDENT TODO DONE) Your code goes here... */
  std::ifstream file(filename);
  if (file.is_open()) {
    std::string line;
    std::getline(file,line);  //jump the fitst line
    while(std::getline(file,line)){
      auto split_record = split(line,',');
      std::string tmp_title =  split_record[0];
      std::string tmp_units =  split_record[1];
      std::string tmp_quart =  split_record[2];
      Course course_record{tmp_title,tmp_units,tmp_quart};
      courses.push_back(course_record);
    }
  }
  file.close();
}

/**
 * This function has TWO requirements.
 *
 * 1) Write the courses that are offered to the file
 * "student_output/courses_offered.csv"
 *
 * 2) Delete the courses that are offered from the `all_courses` vector.
 * IMPORTANT: do this after you write out to the file!
 *
 * HINTS:
 * 1) Keep track of the classes that you need to delete!
 * 2) Use the delete_elem_from_vector function we give you!
 * 3) Remember to write the CSV column headers at the beginning of the output!
 *    See courses.csv for reference.
 *
 * @param all_courses A vector of all courses gotten by calling `parse_csv`.
 *                    This vector will be modified by removing all offered courses.
 */
void write_courses_offered(std::vector<Course>& all_courses) {
  /* (STUDENT TODO DONE) Your code goes here... */
  std::ofstream file("student_output/courses_offered.csv");
  file << "Title,Number of Units,Quarter" << "\n";
  std::vector<Course> to_delete;
  for(Course course : all_courses){
    if(course.quarter != "null"){
      file << course.title << "," << course.number_of_units << "," << course.quarter << "\n";
      to_delete.push_back(course);
    }
  }
  for(Course& course : to_delete){
      delete_elem_from_vector(all_courses,course);
  }
  file.close();
}

/**
 * This function writes the courses NOT offered to the file
 * "student_output/courses_not_offered.csv".
 *
 * This function is ALWAYS called after the `write_courses_offered` function.
 * `unlisted_courses` will trivially contain classes that are not offered
 * since you delete offered classes from `all_courses` in the
 * `write_courses_offered` function.
 *
 * HINT: This should be VERY similar to `write_courses_offered`
 *
 * @param unlisted_courses A vector of courses that are not offered.
 */
void write_courses_not_offered(std::vector<Course> unlisted_courses) {
  /* (STUDENT TODO DONE) Your code goes here... */
  std::ofstream file("student_output/courses_not_offered.csv");
  
  file << "Title,Number of Units,Quarter" << "\n";
  for(Course course : unlisted_courses){
    file << course.title << "," << course.number_of_units << "," << course.quarter << "\n";

  }
  file.close();
}

int main() {
  /* Makes sure you defined your Course struct correctly! */
  static_assert(is_valid_course<Course>, "Course struct is not correctly defined!");

  std::vector<Course> courses;

  parse_csv("courses.csv", courses);

  /* Uncomment for debugging... */
  //print_courses(courses);
  write_courses_offered(courses);
  std::cout << "111111" <<std::endl; 
  write_courses_not_offered(courses);
  return run_autograder();
}