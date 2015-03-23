#include "test_case.h"
#include "Proj_test.h"
#define _POSIX_SOURCE  /* for kill() */

#include <unistd.h>    /* for fork, exec, kill */
#include <sys/types.h> /* for pid_t            */
#include <sys/wait.h>  /* for waitpid          */
#include <csignal>    /* for SIGTERM, SIGKILL */
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

// constants for printing output messages
static const string running_out_begin = "\n----- RUNNING TEST - ";
static const string running_out_end = " -----";


string Test_Case::path = "";
int Test_Case::num_test_cases = 0;

int Test_Case::compare_files(){
	string my_line;
	string correct_line;
	
	int num_lines = 1;
	int status = 0;
	
	// open output files
	ifstream fp_my_output;
	fp_my_output.open(get_my_ouput().c_str());
	
	ifstream fp_correct_output;
	fp_correct_output.open(get_correct_output_file().c_str());
	
	// Error checking for output files
	if ((!fp_my_output) && (!fp_correct_output)){
		cout << "Cannot open either " << get_my_ouput() << " or " << get_correct_output_file() << " for reading" << endl;
		return 0;
	} 
	else if (!fp_my_output) {
		cout << "Cannot open " << get_my_ouput() << " for reading" << endl;
		fp_correct_output.close();
		return 0;
	} 
	else if (!fp_correct_output){
		cout << "Cannot open " << get_correct_output_file() << " for reading" << endl;
		fp_my_output.close();
		return 0;
	}
	else {
		while(getline(fp_my_output, my_line) && getline(fp_correct_output, correct_line)){
			if (my_line != correct_line){
				cout << "Files differ at line " << num_lines << ": " << endl;
				cout << setw(20) << "Your output: " << my_line << endl;
				cout <<  setw(20) << "Correct output: " << correct_line << endl;
				status = -1;
			}
			else{
				++num_lines;
			}
		}
		if(status != -1){
			cout << "Files are identical" << endl;
			status = 1;
		}
		else{
			cout << endl;
			status = 0;
		}
	}
	fp_my_output.close();
	fp_correct_output.close();
	return status;
}

void Test_Case::redirectStdinStdout(){
	// redirect stdout
	const char* outfile = get_my_ouput().c_str();
	fflush(stdout);
	fgetpos(stdout, &pos_out);
	fd_out = dup(fileno(stdout));
	freopen(outfile, "w", stdout);
	
	// redirect stdin
	const char* infile = get_input_file().c_str();
	fflush(stdin);
	fgetpos(stdin, &pos_in);
	fd_in = dup(fileno(stdin));
	freopen(infile, "r", stdin);
}

void Test_Case::revertStdinStdout(){
	// revert stdout
	fflush(stdout);
	dup2(fd_out, fileno(stdout));
	close(fd_out);
	clearerr(stdout);
	fsetpos(stdout, &pos_out);
	
	// revert stdin
	fflush(stdin);
	dup2(fd_in, fileno(stdin));
	close(fd_in);
	clearerr(stdin);
	fsetpos(stdin, &pos_in);
}

bool Test_Case::run_test(const string& exe){
	int system_status = 0; 
	bool test_status = false;
	
	// Check if input file can be opened
	ifstream in(get_input_file());
	if (!in){
		cout << "Cannot open " << get_input_file() << " for reading" << endl;
		return(0);
	}
	in.close();
	
	// clear output file
	ofstream out(get_my_ouput());
	if (!out){
		cout << "Cannot open " << get_my_ouput() << " for writing" << endl;
		return(0);
	}
	out.close();
	
	
	// Start running test
	cout << running_out_begin << get_test_name() <<  running_out_end << endl; 
	redirectStdinStdout();
	system_status = run_process(exe);
	revertStdinStdout();
	
	
	if (system_status == -1){
		cout << "\t ERROR: COULD NOT RUN " << get_test_name() << endl;
	}
	else if(system_status){
		cout << "\t ERROR RUNNING " << get_test_name() << endl;
	}
	else {
		test_status = compare_files();
		string test_status_string;
		if (test_status){
			test_status_string = "PASSED";
		}
		else{
			test_status_string = "FAILED";
		}
		cout << get_test_name() << ": " << test_status_string << endl;
	}
	out.close();
	in.close();
	
	int test_name_length = int(running_out_begin.length() + running_out_end.length() + get_test_name().length());
	while (--test_name_length){
		cout << '-';
	}
	cout << endl;	
	
	// returns 1 if files are identical
	return test_status;	
}


/*
 * fork a child process, execute vlc, and return it's pid.
 * returns -1 if fork failed.
 */
pid_t Test_Case::spawn_test_case(const char* exe_command){
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		return -1;
	}
	
	/* when you call fork(), it creates two copies of your program:
	 * a parent, and a child. you can tell them apart by the return
	 * value from fork().  If fork() returns 0, this is is the child
	 * process.  If fork() returns non-zero, we are the parent and the
	 * return value is the PID of the child process. */
	if (pid == 0) {
		/* this is the child process.  now we can call one of the exec
		 * family of functions to execute the program.  when you call exec,
		 * it replaces the currently running process (the child process)
		 * with whatever we pass to exec.  So our child process will now
		 * be running the program.  exec() will never return except in an
		 * error case, since it is now running the process code and not our
		 * code. */
		execlp(exe_command, exe_command, (char*)NULL);
		perror(exe_command);
		abort();
		
	} else {
		/* parent, return the child's PID back to main. */
		return pid;
	}
}


int Test_Case::run_process(const string& exe_command){
	pid_t process_id = spawn_test_case(exe_command.c_str());
	
	if (process_id == -1) {
		printf("failed to fork child process\n");
		return 1;
	}
	
	sleep(3);
	
	/* kill will send the specified signal to the specified process.
	 * in this case, we send a TERM signal to the process, requesting 
	 that it terminate.  If that doesn't work, we send a KILL signal.
	 * If that doesn't work, we give up. */
	if (kill(process_id, SIGTERM) < 0) {
		perror("kill with SIGTERM");
		if (kill(process_id, SIGKILL) < 0) {
			perror("kill with SIGKILL");
		}
	}
	
	/* this shows how we can get the exit status of our child process.
	 * it will wait for the the process to exit, then grab it's return
	 * value. */
	int status = 0;
	waitpid(process_id, &status, 0);
	
	return 0;
}

