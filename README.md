# SysCalls
### Programs written in `C` to automate tasks on large files.

-> For the first question :
	1. gcc Q1.c
	2. ./a.out <path_to_input_file>

-> For the second question :
	1. gcc Q2.c
	2. ./a.out <path_to_newFile> <path_to_oldFile> <path_to_folder>

Implementation :

	-> For first question:

		I read <BUFF_SIZE> bytes from input file and store it into buffer
		variable. But before writing I call this function again (ie.
		recursively). Now this happens until there is nothing left to
		read, then write occurs using LIFO, therefore reverse of file is
		is present in Output file.

	-> For second question:

		Similar to previous question, I read recursively. Now in place 
		of writing to another file, I compare it with normal front
		read Buffer variable. If they aren't same I return FALSE. 
