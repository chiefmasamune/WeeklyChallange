#include <stdio.h>
#include <ctype.h>

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
	char buf = '\0';
	int count = 0;

	while ((buf = fgetc(f)) != EOF) //Could be faster to use getline or fgets, but then have to mess around a lot more with buffers
		if (buf == '\n') 
			count++;

	return count;
}

//Could be refined to handle poor grammar and such, but I'm going to (foolishly) believe the user will provide good data.
int count_words()
{
	char buf = '\0';
	int count = 0, flag = 0;

	while ((buf = fgetc(f)) != EOF)
	{
		if (buf < 0)
		{
			flag = 1; //POSIX definition of a word is some amount of non-whitespace characters delimited by whitespace characters, so yeah. 
			continue;
		}
		else if (isspace(buf))
		{
			if (flag == 1) //Make sure consecutive whitespace isn't counted as multiple words
			{
				count++;
				flag = 0;
			}
		}
		else
			flag = 1; //Mark that previous character wasn't whitespace, which I'm going to assume means it's a normal character.
	}

	return count;
}



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
	if (argc == 1)
		printf("Please pass a flag (-c, -l, -w) and/or a file.\n");
	else if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			//flag passed in, but no filepath, so get data from stdin
		}
		else //Byte, line, and word count for the file
		{
			if (open_file(argv[1]) != 0)
				return 1;

			int c = 0, l = 0, w = 0;

			c = count_bytes();
			rewind(f);
			l = count_lines();
			rewind(f);
			w = count_words();
			printf("Bytes: %d, lines: %d, words: %d\n", c, l, w);
		}
	}
	else if (argc == 3)
	{
		if (argv[1][0] == '-') //Run the specified operation on the file
		{
			if (open_file(argv[2]) != 0)
				return 1;

			switch (argv[1][1]) {
			case 'c':
				printf("%d characters in file.\n", count_bytes());
				break;
			case 'l':
				printf ("%d lines in file.\n", count_lines());
				break;
			case 'w':
				printf("%d words in file.\n", count_words());
				break;
			default:
				printf ("Please enter a valid flag: -c, -l, -w\n");
			}
		}
		else
			printf("Second argument should be passed in as a flag; -c, -l, -w\n");

	}
	else
		printf("Please pass one flag (-c, -l, -w) and/or a file, only.\n");

	fclose(f);
	return 0;
}