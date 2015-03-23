//
//  test_bundle.h
//  proj4
//
//  Created by Katie Steinberg on 3/19/15.
//  Copyright (c) 2015 Katie Steinberg. All rights reserved.
//

#ifndef __proj4__test_bundle__
#define __proj4__test_bundle__

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
};


#endif /* defined(__proj4__test_bundle__) */
