#include "filesystem.h"

void main(int argc, char *argv[])
{
	if (argc == 1)
	{
		return Error(CODE_01);
	}

	// root build
	s_file root;
	root.name = calloc(sizeof(char), MAX_FILE_NAME_LEN);
	if (!(root.name))  //calloc check
	{
		return Error(CODE_02);
	}
	strcpy(root.name, argv[1]);
	root.files = calloc(sizeof(s_file), MAX_FILE_IN_FOLDER);
	if (!(root.files))  //calloc check
	{
		return Error(CODE_02);
	}
	root.attr = DEFAULT_FOLDER_ATTR; // DEFAULT_FOLDER_ATTR

	s_file* open_folder_ptr = &root;  // pointer to the last opened folder

	char choice[MAX_CHOICE_CHARS];
	char temp_name[MAX_FILE_NAME_LEN];
	char temp_mode[6]; //do not change (maximum 4 modes, 1 for testing, 1 for \0)
	do
	{
		fseek(stdin, 0, SEEK_END);  //must clean baffer befor the scanf
		scanf("%s", choice);

		if (!strcmp(choice, "help"))
		{
			help();
			continue;
		}

		else if (!strcmp(choice, "cd")) //open a folder by name
		{
			scanf("%s", temp_name);
			open_folder_ptr = cd(temp_name, open_folder_ptr);
			continue;
		}

		
		else if (!strcmp(choice, "root"))
		{
			open_folder_ptr = Root(&root);
			continue;
		}

		else if (!strcmp(choice, "mkdir"))
		{
			scanf("%s", temp_name);
			mkdir(temp_name, open_folder_ptr);
			continue;
		}

		else if (!strcmp(choice, "mkfile"))
		{
			scanf("%s", temp_name);
			mkfile(temp_name, open_folder_ptr);
			continue;
		}

		else if (!strcmp(choice, "dir"))
		{
			dir(open_folder_ptr);
			continue;
		}

		else if (!strcmp(choice, "chmod"))
		{
			scanf("%s", temp_name);
			scanf("%s", temp_mode);
			chmod(temp_name, temp_mode, open_folder_ptr);
			continue;
		}

		else if (!strcmp(choice, "format"))
		{
			open_folder_ptr = format(&root);
			continue;
		}

		else if (!strcmp(choice, "rm"))
		{
			scanf("%s", temp_name);
			rm(temp_name, open_folder_ptr);
			continue;
		}

		else
		{
			if (strcmp(choice, "bye"))
			{
				Error(CODE_07);
				continue;
			}
		}

	} while (strcmp(choice, "bye"));

	free(root.name);
	free(root.files);
	printf("Good bye. Have a nice day!\n");
	return 0;
	
	


}