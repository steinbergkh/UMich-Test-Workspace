#include "Proj_test.h"
#include "test_bundle.h"
#include "test_case.h"
#include <iostream>
#include <string>

using namespace std;

int run_all_tests(){
	// NOTE: Change path to the location of your test files
	string path = "/Users/Username/Downloads/THIS/SHOULD/BE/A/PATH";
	
	// NOTE: Change main_program_exe to the location of your main project's executable
	string main_program_exe = "/Users/Username/Library/Developer/Xcode/DerivedData/THIS/SHOULD/BE/A/PATH/main";
	
	
	//  ------- Don't touch these ----------- 
	Test_Case::set_folder_path(path);
	Test_Bundle test_bundle(main_program_exe);
	// --------------------------------------
	
	
	// ADD TESTS BELOW //
	
	// There are two ways to add a test case:
	// 1. Write out each file name individually
	test_bundle.add_test("Main Test 1 - Testing output", /* test name */
						 "main_out.txt",				 /* my output file */
						 "main_in.txt",					 /* test case input file */
						 "main_out_correct.txt");		 /* correct output file */ 
	
	
	// 2. This way will add the complete file names following the above naming convention
	test_bundle.add_test("Main Test 2 - Testing output", /* test name */
						 "main");						 /* test case file name */
	
	
	
	// Do not add more tests after the following function or they won't run!
	test_bundle.run_all_tests();
	cout << endl;
	return 0;
}

