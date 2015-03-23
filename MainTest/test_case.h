//
//  test_case.h
//  proj4
//
//  Created by Katie Steinberg on 3/19/15.
//  Copyright (c) 2015 Katie Steinberg. All rights reserved.
//

#ifndef __proj4__test_case__
#define __proj4__test_case__

#include <stdio.h>
#include <string>
#include <sys/types.h> /* for pid_t */

static const std::string file_name_out = "_out.txt";
static const std::string file_name_in = "_in.txt";
static const std::string file_name_out_correct = "_out_correct.txt";

class Test_Case{
public:
	Test_Case(std::string test_name_, std::string my_output_, std::string input_file_, std::string correct_output_):
	test_name(test_name_), my_output_file(my_output_), input_file(input_file_),  
	correct_output_file(correct_output_) {
		++num_test_cases;
	}
	
	// standard filenames
	Test_Case(std::string test_name_, std::string file_name):
	test_name(test_name_), my_output_file(file_name+file_name_out), input_file(file_name + file_name_in),  
	correct_output_file(file_name + file_name_out_correct) {
		++num_test_cases;
	}
	
	~Test_Case(){ --num_test_cases; };
	
	static void set_folder_path(std::string folder_path){ path = folder_path; }
	static std::string get_folder_path(){ return path; };
	
	std::string get_test_name(){ return test_name; }
	std::string get_my_ouput(){ return path + my_output_file; }
	std::string get_input_file(){ return path + input_file; }
	std::string get_correct_output_file(){ return path + correct_output_file; }
	int get_num_test_cases(){return num_test_cases;}
	bool run_test(const std::string& exe);
private:
	// for each test case
	std::string test_name;
	std::string my_output_file;
	std::string input_file;
	std::string correct_output_file;
	
	// statics
	static std::string path;
	static int num_test_cases;
	
	// private functions
	int compare_files();
	pid_t spawn_test_case(const char* exe_command);
	int run_process(const std::string& exe);
	
	// for redirecting input/output
	int fd_out;
	fpos_t pos_out;
	int fd_in;
	fpos_t pos_in;
	
	// functions for redirecting input/output
	void redirectStdinStdout();
	void revertStdinStdout();
};

#endif /* defined(__proj4__test_case__) */
