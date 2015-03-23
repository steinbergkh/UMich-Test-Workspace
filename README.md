# UMich C++ Xcode Testing Workspace

A testing workspace to use for C++ projects in EECS classes at the University of Michigan. This Xcode workspace will run your program using the supplied input files and compare your output to the supplied correct output.

## Installation
- Download the project files (download ZIP button --->)
- Move the project folder to your desired directory before starting the steps below

## Usage
### Initial set up
__Note:__ Make sure you've already moved the project folder to your desired directory or you're going to have to do these steps all over again!

#### Set the main project executable path
- In the Navigator toolbar (left side) expand the folder called "Products" and click on the executable labeled "main"
- In the Utilities toolbar (right side) copy the Full Path of the executable
- Paste this as the value of the string "main_program_exe" in the file "Proj_test.cpp"

#### Set the path of the folder containing your test files
- In the Navigator toolbar (left side) expand the folder under "main" called "Test Files" and click on one of the text files listed
- In the Utilities toolbar (right side) copy the Full Path up to the name of the text file (including the __/__ at the end)

   For example: **/Users/steinbergkh/Documents/EECS-381/Project1/test-files/**main_out.txt

- Paste this as the value of the string "path" in the file "Proj_test.cpp"

### Adding test case files to the project
In order to add a test input/output file to the project, you must add it in the
same location as the other tests. The easiest way to do this is by right clicking
on the folder labeled "Test Files" selecting "Add Files to Project" and checking
the box labeled "Copy items if needed."

### Adding a test case
There are two ways to add a test case to the test suite:
1. Write out each file name (your output file, input file, and the correct output
   file) individually
2. Using only the beginning of the test case file name. This adds each file the
as if you used the above method, but using the following convention for filenames:
  - My output file: __case_name__\_out.txt
  - Input file: __case_name__\_in.txt
  - Correct output file: __case_name__\_out_correct.txt

### Adding project files to the project
#### If the file already exists
Add the project file to the folder labeled "main" by right clicking on it and
selecting "Add Files to Project" If the file is a source file (.cpp), make sure
to check the box labeled "main" under Target Membership in the Utilities toolbar.

#### Creating a new file
Add the project file to the folder labeled "main" by right clicking on it and
selecting "New File". Select the C++ File under "OS X > Source". Check the box if
you also will need a header file. Make sure to add the source file to the target
"main", but __not__ to the target "MainTest".


## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request
