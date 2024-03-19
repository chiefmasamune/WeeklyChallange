#include <stdio.h>

FILE *f = NULL;

int count_bytes()
{
	char buf[1024];
	int count = 0, chunk = 0;

	while (chunk = fread(&buf, sizeof(char), 1024, f))
		count += chunk;

	return count;
}

int count_lines()
{
	char buf = '\0'; //Assuming a single line of the file won't be longer than 1 kilobyte
	int count = 0;

	while ((buf = fgetc(f)) != EOF) //Could be faster to use getline or fgets, but then have to mess around a lot more with buffers
		if (buf == '\n' || buf == '\r') //Check newline for Windows and carriage return for Linux
			count++;

	return count;
}

/*
int count_
*/

int open_file(const char *path)
{
	int opened = fopen_s(&f, path, "r");
	if (opened != 0)
	{
		printf("Error opening file: %s\n", path);
		return -1;
	}

	return 0;
}

int main (int argc, char **argv)
{
	//Make sure there is a flag for now. 
	if (argc < 3) 
	{
		printf ("Call this program with a flag (-c, -l, -w, -m).\n");
		return 1;
	}
	
	if (open_file(argv[2]) != 0)
		return 1;

	switch (argv[1][1]) {
	case 'c':
		printf("%d characters in file.\n", count_bytes(argv[2]));
		break;
	case 'l':
		printf ("%d lines in file.\n", count_lines(argv[2]));
		break;
	default:
		printf ("Please enter a valid flag: -c, -l, -w , -m\n");
	}

	fclose(f);
	return 0;
}