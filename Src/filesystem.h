
#ifndef filesystem

//debug mode
//#define DEBUG

//pause and details defines by mode
#ifdef DEBUG
#define PAUSE_DETAILS {printf("Done .Please press <enter> to continue..."); rewind(stdin); getchar();} //pause the code for details
#else
#define PAUSE_DETAILS {} //not pause the code for details
#endif // DEBUG

//defines
#define filesystem
#define _CRT_SECURE_NO_WARNINGS
#define MAX_CHOICE_CHARS 10   //Be careful about change
#define MAX_FILE_NAME_LEN 21
#define MAX_FILE_IN_FOLDER 100
#define DEFAULT_FOLDER_ATTR 29 //the deafult of basic folder
#define DEFAULT_FILE_ATTR 4  //the deafult of basic file
#define UNITY 1  
#define TWOPWR(x) ( UNITY << (x) )  //return 2^x
#define GETBIT(m, k) (((m) & TWOPWR(k))!=0 )  //m- parameter, k-bit index
#define SETBIT(m, k) ((m) | TWOPWR(k))       // turn on bit //m- parameter, k-bit index
#define RESETBIT(m, k) ((m) & ~TWOPWR(k))   // turn off bit //m- parameter, k-bit index

//Errors codes
enum Error_idx { CODE_01 = 1, CODE_02, CODE_03, CODE_04, CODE_05, CODE_06, CODE_07, CODE_08 , CODE_09 };  //look at Classification_of_errors file

 //includes
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

//typedefs
typedef struct file {
	char* name;
	char attr;
	struct file* files;
}s_file;

/*-------Functions---------*/

//Error function- return error code number
int Error(int code_number);

//help function
void help();

//cd function - open a folder by name
s_file* cd(char* dir_name, s_file* open_folder_ptr);

//root function- return pointer to root
s_file* Root(s_file* root);

// mkdir function-Create a new folder. If work return 0 / if dont work return error code number
int mkdir(char* dir_name, s_file* open_folder_ptr);

// mkfile function-Create a new file. If work return 0 / if dont work return error code number
int mkfile(char* dir_name, s_file* open_folder_ptr);

// dir function- Prints all visible files in a folder. If work return 0 / if dont work return error code number
int dir(s_file* open_folder_ptr);

// chmod function- change file mode. If work return 0 / if dont work return error code number
int chmod(char* file_name, char* mode, s_file* open_folder_ptr);

// rm recursion function- delete folder or file. If work return 0 / if dont work return error code number
int rm(char* file_name, s_file* open_folder_ptr);

//format function- format all folders and file and return pointer to root
s_file* format (s_file* root);


#endif // !filesystem