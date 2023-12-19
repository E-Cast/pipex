#include "pipex.h"

int	main(int argc, char **argv)
{
	int infile;
	int outfile;

	infile = open(argv[1], O_RDONLY | O_CLOEXEC);
	if (infile == -1)
	{
		close(infile);
		exit(EXIT_FAILURE);
	}
	outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY |O_CLOEXEC, 0644);
	if (outfile == -1)
	{
		close(infile);
		close(outfile);
		exit(EXIT_FAILURE);
	}

	write(outfile, "Hello World", 11);

    close(infile);
    close(outfile);
}
