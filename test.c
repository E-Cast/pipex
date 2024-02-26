#include "pipex.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// int	main(int argc, char **argv, char **envp)
// {
// 	int	pipe1[2];
// 	int	pipe2[2];
// 	int	infd;
// 	int	outfd;
// 	pid_t	pid1;
// 	pid_t	pid2;
// 	pid_t	pid3;

// 	(void) argc;
// 	(void) argv;
// 	pipe(pipe1);
// 	pipe(pipe2);
// 	infd = open("/dev/null", O_RDONLY);
// 	outfd = open("output", O_CREAT | O_WRONLY | O_TRUNC, 0664);
// 	pid1 = fork();
// 	if (pid1 == 0)
// 	{
// 		dup2(infd, STDIN_FILENO);
// 		dup2(pipe1[1], STDOUT_FILENO);
// 		close(infd);
// 		close(pipe1[1]);
// 		close(pipe1[0]);
// 		close(pipe2[1]);
// 		close(pipe2[0]);
// 		close(outfd);
// 		execve("/usr/bin/wc", ft_split("wc -l", ' '), envp);
// 	}
// 	pid2 = fork();
// 	if (pid2 == 0)
// 	{
// 		dup2(pipe1[0], STDIN_FILENO);
// 		dup2(pipe2[1], STDOUT_FILENO);
// 		close(infd);
// 		close(pipe1[1]);
// 		close(pipe1[0]);
// 		close(pipe2[1]);
// 		close(pipe2[0]);
// 		close(outfd);
// 		execve("/usr/bin/tee", ft_split("tee file", ' '), envp);
// 	}
// 	pid3 = fork();
// 	if (pid3 == 0)
// 	{
// 		dup2(pipe2[0], STDIN_FILENO);
// 		dup2(outfd, STDOUT_FILENO);
// 		close(infd);
// 		close(pipe1[1]);
// 		close(pipe1[0]);
// 		close(pipe2[1]);
// 		close(pipe2[0]);
// 		close(outfd);
// 		execve("/usr/bin/wc", ft_split("wc -l", ' '), envp);
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	int	pipe1[2];
	// int	pipe2[2];
	int	infd;
	int	outfd;
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid3;

	(void) argc;
	(void) argv;
	pipe(pipe1);
	// pipe(pipe2);
	infd = open("/dev/null", O_RDONLY);
	outfd = open("output", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(infd, STDIN_FILENO);
		dup2(pipe1[1], STDOUT_FILENO);
		close(infd);
		close(pipe1[1]);
		close(pipe1[0]);
		close(outfd);
		execve("/usr/bin/wc", ft_split("wc -l", ' '), envp);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipe1[0], STDIN_FILENO);
		dup2(pipe1[1], STDOUT_FILENO);
		close(infd);
		close(pipe1[1]);
		close(pipe1[0]);
		close(outfd);
		execve("/usr/bin/tee", ft_split("tee file", ' '), envp);
	}
	pid3 = fork();
	if (pid3 == 0)
	{
		dup2(pipe1[0], STDIN_FILENO);
		dup2(outfd, STDOUT_FILENO);
		close(infd);
		close(pipe1[1]);
		close(pipe1[0]);
		close(outfd);
		execve("/usr/bin/wc", ft_split("wc -l", ' '), envp);
	}
}
