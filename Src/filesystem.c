#include "filesystem.h"

//error function
int Error(int code_number)
{
	switch (code_number)
	{
	case CODE_01:
		printf("Error- problem with the main parameters\n");
		return CODE_01;
		break;

	case CODE_02:
		printf("Error- malloc problem\n");
		return CODE_02;
		break;

	#ifdef DEBUG
	case CODE_03:
		printf("Error- the ptr you send isn't a folder\n");   //needed only in debug run
		return CODE_03;
		break;
	#endif // DEBUG

	case CODE_04:
		printf("Directory does not exist\n");
		return CODE_04;
		break;

	case CODE_05:
		printf("No more space\n");
		return CODE_05;
		break;

	case CODE_06:
		printf("File already exists\n");
		return CODE_06;
		break;

	case CODE_07:
		printf("Iilegal option, press <help>\n");
		return CODE_07;
		break;

	case CODE_08:
		printf("Mode error, mode need to be until 4 chars\n");
		return CODE_08;
		break;

	case CODE_09:
		printf("File does not exist\n");
		return CODE_09;
		break;

	default:
		printf("Iilegal error\n");
		return -1;
		break;
	}
}

//help function
void help()
{
	printf("Write one of the following commands:\n");
	printf("cd <dir_name>\n");
	printf("root\n");
	printf("mkdir <dir_name>\n");
	printf("mkfile <file_name>\n");
	printf("rm <file_name>\n");
	printf("chmod <file_name,mode>\n");
	printf("format\n");
	printf("dir\n");
	printf("help\n");
	printf("bye\n");
}

//root function- return pointer to root
s_file* Root(s_file* root)
{
	PAUSE_DETAILS
		return root;
}


// mkdir function-Create a new folder. If work return 0 / if dont work return error code number
int mkdir(char* dir_name, s_file* open_folder_ptr)
{
	#ifdef DEBUG
	if (!(GETBIT(open_folder_ptr->attr,0)))   //check if the ptr is'n a folder (the first bit of byte is 1)
	{
		return Error(CODE_03);
	}
	#endif // DEBUG

	for (int i = 0; i < MAX_FILE_IN_FOLDER; i++)
	{
		if ((open_folder_ptr->files[i].name) != NULL)
		{
			if (!(strcmp(open_folder_ptr->files[i].name, dir_name)))
			{
				return Error(CODE_06);
			}
		}
	}

	for (int i = 0; i < MAX_FILE_IN_FOLDER; i++)
	{
		if ((open_folder_ptr->files[i].name) == NULL)
		{
			open_folder_ptr->files[i].attr = DEFAULT_FOLDER_ATTR;
			open_folder_ptr->files[i].files = calloc(sizeof(s_file), MAX_FILE_IN_FOLDER);
			if (!(open_folder_ptr->files[i].files))  //calloc check
			{
				return Error(CODE_02);
			}
			open_folder_ptr->files[i].name = calloc(sizeof(char), MAX_FILE_NAME_LEN);
			if (!(open_folder_ptr->files[i].name))  //calloc check
			{
				return Error(CODE_02);
			}
			strcpy (open_folder_ptr->files[i].name, dir_name);
			PAUSE_DETAILS
			return 0;
		}
	}
	return Error(CODE_05);
}

// mkfile Function-Create a new file. If work return 0 / if dont work return error code number
int mkfile(char* dir_name, s_file* open_folder_ptr)
{
	#ifdef DEBUG
	if (!(GETBIT(open_folder_ptr->attr, 0)))   //check if the ptr is'n a folder (the first bit of byte is 1)
	{
		return Error(CODE_03);
	}
	#endif // DEBUG

	for (int i = 0; i < MAX_FILE_IN_FOLDER; i++)
	{
		if ((open_folder_ptr->files[i].name) != NULL)
		{
			if (!(strcmp(open_folder_ptr->files[i].name, dir_name)))
			{
				return Error(CODE_06);
			}
		}
	}

	for (int i = 0; i < MAX_FILE_IN_FOLDER; i++)
	{
		if ((open_folder_ptr->files[i].name) == NULL)
		{
			open_folder_ptr->files[i].attr = DEFAULT_FILE_ATTR;
			open_folder_ptr->files[i].files = calloc(sizeof(s_file), MAX_FILE_IN_FOLDER);   // Not necessary. If erasing, files (array) are removed from a file. Problematic for other functions. 
			if (!(open_folder_ptr->files[i].files)) //calloc check
			{
				return Error(CODE_02);
			}
			open_folder_ptr->files[i].name = calloc(sizeof(char), MAX_FILE_NAME_LEN);
			if (!(open_folder_ptr->files[i].name))  //calloc check
			{
				return Error(CODE_02);
			}
			strcpy(open_folder_ptr->files[i].name, dir_name);
			PAUSE_DETAILS
				return 0;
		}
	}
	return Error(CODE_05);
}

//cd function - open a folder by name
s_file* cd(char* dir_name, s_file* open_folder_ptr)
{
	#ifdef DEBUG
	if (!(GETBIT(open_folder_ptr->attr, 0)))   //check if the ptr is'n a folder (the first bit of byte is 1)
	{
		Error(CODE_03);
		return open_folder_ptr;
	}
	#endif // DEBUG

	for (int i = 0; i < MAX_FILE_IN_FOLDER; i++)
	{
		if (open_folder_ptr->files[i].name != NULL)
		{
			if ((!(strcmp(open_folder_ptr->files[i].name, dir_name))) && (GETBIT(open_folder_ptr->files[i].attr, 0)))
			{
				PAUSE_DETAILS
					return (&(open_folder_ptr->files[i]));
			}
		}
	}
	Error(CODE_04);
	return open_folder_ptr;
}

// dir function- Prints all visible files in a folder. If work return 0 / if dont work return error code number
int dir(s_file* open_folder_ptr)
{
	#ifdef DEBUG
	if (!(GETBIT(open_folder_ptr->attr, 0)))   //check if the ptr is'n a folder (the first bit of byte is 1)
	{
		return Error(CODE_03);
	}
	#endif // DEBUG

	printf("name\t\t dir\t read\t write\t execute\n");
	printf("------------------------------------------------\n");

	for (int i = 0; i < MAX_FILE_IN_FOLDER; i++)
	{
		if ((open_folder_ptr->files[i].name != NULL) && (!GETBIT(open_folder_ptr->files[i].attr, 1)))  //check file exist and visible
		{
			printf("%s\t\t ", open_folder_ptr->files[i].name);
			printf("%d\t ", (GETBIT(open_folder_ptr->files[i].attr, 0))); //dir
			printf("%d\t ", (GETBIT(open_folder_ptr->files[i].attr, 2))); //read
			printf("%d\t ", (GETBIT(open_folder_ptr->files[i].attr, 3))); //write
			printf("%d\n", (GETBIT(open_folder_ptr->files[i].attr, 4)));  //execute
		}
	}
	PAUSE_DETAILS
	return 0;
}

// chmod function- change file mode. If work return 0 / if dont work return error code number
int chmod(char* file_name, char* mode, s_file* open_folder_ptr)
{
	int size_of_mode = strlen(mode);
	if (size_of_mode > 4)   // if dont need the check- can remove, but need to change "char temp_mode[6];" to "char temp_mode[5];" in the main.c
	{
		return Error(CODE_08);
	}

	for (int i = 0; i < MAX_FILE_IN_FOLDER; i++)
	{
		if (open_folder_ptr->files[i].name != NULL)
		{
			if (!(strcmp(open_folder_ptr->files[i].name, file_name)))   // && (((open_folder_ptr->attr) & 128) == 0) -if needed to work just on files (not folders) 
			{
				//shout down all to default attr
				open_folder_ptr->files[i].attr = RESETBIT(open_folder_ptr->files[i].attr, 2);
				open_folder_ptr->files[i].attr = RESETBIT(open_folder_ptr->files[i].attr, 3);
				open_folder_ptr->files[i].attr = RESETBIT(open_folder_ptr->files[i].attr, 4);
				open_folder_ptr->files[i].attr = SETBIT(open_folder_ptr->files[i].attr, 1); 

				for (int j = 0; j < size_of_mode; j++)  //until maximum chars in mode
				{
					switch (mode[j])
					{
					case 'r':
						open_folder_ptr->files[i].attr = SETBIT(open_folder_ptr->files[i].attr, 2);  //changes the file/folder to readable
						continue;
					
					case 'w':
						open_folder_ptr->files[i].attr = SETBIT(open_folder_ptr->files[i].attr, 3); //changes the attr of the writing to possible
						continue;

					case 'x':
						open_folder_ptr->files[i].attr = SETBIT(open_folder_ptr->files[i].attr, 4); //turns the file/folder into executable
						continue;

					case 'v':
						open_folder_ptr->files[i].attr = (RESETBIT(open_folder_ptr->files[i].attr, 1)); //turns the file/folder to visable
						continue;
					}
				}
				PAUSE_DETAILS
					return 0;
			}
		}
	}
	return Error(CODE_09);
}

//format function- format all folders and file and return pointer to root
s_file* format(s_file* root)
{
	for (int index = 0; index < MAX_FILE_IN_FOLDER; index++)
	{
		if (root->files[index].name != NULL)
		{
			format(&(root->files[index]));
		}

		root->files[index].attr = 0; //attr reset to 0

		free(root->files[index].name);
		root->files[index].name = NULL;

		if (root->files[index].files != NULL) //name reset to null
		{
			free(root->files[index].files);
			root->files[index].files = NULL; //files reset to null
		}
	}
	PAUSE_DETAILS
	return root;
}

// rm recursion function- delete folder or file. If work return 0 / if dont work return error code number
int rm(char* file_name, s_file* open_folder_ptr)
{
	for (int index = 0; index < MAX_FILE_IN_FOLDER; index++)
	{
		if (open_folder_ptr->files[index].name != NULL)  // check not null name
		{
			if (!(strcmp(open_folder_ptr->files[index].name , file_name)))  // check name
			{
				format(&(open_folder_ptr->files[index]));  // use format Function

				open_folder_ptr->files[index].attr = 0; //attr reset to 0

				free(open_folder_ptr->files[index].name);
				open_folder_ptr->files[index].name = NULL;

				if (open_folder_ptr->files[index].files != NULL) //name reset to null
				{
					free(open_folder_ptr->files[index].files);
					open_folder_ptr->files[index].files = NULL; //files reset to null
				}

				PAUSE_DETAILS
				return 0;
			}
		}
	}
	return Error(CODE_09);
}