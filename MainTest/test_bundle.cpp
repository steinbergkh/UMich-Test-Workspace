#include "test_bundle.h"
#include "test_case.h"
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
#include <utility>

using namespace std;
using placeholders::_1;

// statics used for set up purposes
const string Test_Bundle::default_path = "/Users/Username/Downloads/THIS/SHOULD/BE/A/PATH";
const string Test_Bundle::default_exe_path = "/Users/Username/Library/Developer/Xcode/DerivedData/THIS/SHOULD/BE/A/PATH/main";


void Test_Bundle::add_test(string test_name_, string my_output_, string input_file_, string correct_output_){
	++num_test_cases;
	Test_Case* new_test = new Test_Case(test_name_, my_output_, input_file_, correct_output_);
	test_cases.push_back(new_test);
}

void Test_Bundle::add_test(string test_name_, string file_name_){
	++num_test_cases;
	Test_Case* new_test = new Test_Case(test_name_, file_name_);
	test_cases.push_back(new_test);
}

Test_Bundle::~Test_Bundle(){
	for(int i = 0; i < num_test_cases; ++i){
		delete test_cases[i];
	}
}

void Test_Bundle::run_all_tests(){
	bool defaults_changed = true;
	if(Test_Case::get_folder_path() == Test_Bundle::default_path){
		cout << "ERROR: Folder path for testing files has not been set in Proj_test.cpp file" << endl;
		defaults_changed = false;
	}
	if (executable == Test_Bundle::default_exe_path){
		cout << "ERROR: Executable path for main project executable has not been set in Proj_test.cpp file" << endl;
		defaults_changed = false;
	}
	if (!defaults_changed){
		return;
	}
	if (test_cases.empty()){
		cout << "ERROR: This bundle does not contain any test cases" << endl;
		return;
	}
	// counts number of tests that passed
	int num_passed = int(count_if(test_cases.begin(), test_cases.end(), bind(&Test_Case::run_test, _1, executable)));
	print_test_bundle_status(num_passed);
}

void Test_Bundle::print_test_bundle_status(int num_passed){
	int num_failed = num_test_cases - num_passed;
	if (num_failed > 0){
		cout << "\n\n **********************************\n \t\t FAILED " << num_failed << " TESTS" << endl;
	}
	else {
		cout << "\n\nPASSED ALL TESTS" << endl;
	}
	cout << "\n\n";
}

