#include <stdio.h>

int count_bytes(const char *path)
{
	char buf[1024];
	int count = 0, chunk = 0;
	FILE *f = NULL;
	int opened = fopen_s(&f, path, "r");
	if (opened != 0) 
	{
		printf ("Error opening file: %s\n", path);
		return -1;
	}

	while (chunk = fread(&buf, sizeof(char), 1024, f))
		count += chunk;

	fclose(f);

	return count;
}

/*int count_lines(char *path)
{

}

int count_
*/

int main (int argc, char **argv)
{
	int result = 0;
	//Make sure there is a flag for now. 
	if (argc < 3) 
	{
		printf ("Call this program with a flag (-c, -l, -w, -m).\n");
		return 1;
	}
	
	switch (argv[1][1]) {
	case 'c':
		result = count_bytes(argv[2]);
		if (result > -1)
			printf("%d characters in file.\n", result);
		break;
	default:
		printf ("Please enter a valid flag: -c, -l, -w , -m\n");
		return 1;
	}


	return 0;
}