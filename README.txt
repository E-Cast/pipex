gcc pipex.c -Wall -Werror -Wextra

./a.out infile "grep test" outfile
should output the same as
< infile grep test > outfile

working on
./a.out infile "grep test" "wc -l" outfile
should output the same as
< infile grep test | wc -l > outfile