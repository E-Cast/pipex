#include <fcntl.h>
#include "pipex.h"

int	main(int argc, char **argv)
{
	int infile;
	int outfile;

	if (argc < 3)
		return 0;
	infile = open(argv[1], O_RDONLY | O_CLOEXEC); 
	if (infile == -1)
	{
		close(infile);
		exit(EXIT_FAILURE);
	}
	outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY | O_CLOEXEC, 0644);
	if (outfile == -1)
	{
		close(infile);
		close(outfile);
		exit(EXIT_FAILURE);
	}
	printf("Hello\n%i", argc);
	char *const args[] = {"grep", "test", NULL};
	char *const envp[] = {NULL};
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execve("/bin/grep", args, envp);
	// write(outfile, "Hello World", 11);
	printf("World\n");
    close(infile);
    close(outfile);
}
