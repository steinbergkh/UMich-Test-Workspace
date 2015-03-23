#ifndef TEST_BUNDLE_H
#define TEST_BUNDLE_H

#include <stdio.h>
#include <vector>
#include <string>
#include "test_case.h"

class Test_Bundle{
public:
	Test_Bundle(std::string executable_):num_test_cases(0), executable(executable_){};
	void add_test(std::string test_name_, std::string my_output_, std::string input_file_, std::string correct_output_);
	void add_test(std::string test_name_, std::string file_name_);
	~Test_Bundle();
	void run_all_tests();
	
private:
	std::vector<Test_Case*> test_cases;
	int num_test_cases;
	std::string executable;
	
	void print_test_bundle_status(int num_passed);
	
	// For set up purposes
	static const std::string default_path;
	static const std::string default_exe_path;
};


#endif /* defined(TEST_BUNDLE_H) */
