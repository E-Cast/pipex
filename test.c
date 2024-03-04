#include <stdio.h>
#include "libft.h"

char	*make_segment(char *str, int start, int end)
{
	int	ix;

	ix = start;
	while (ix < end)
	{
		
		ix++;
	}
}

char	**segment_str(char **array, char *str)
{
	char	quote;
	int		start;
	int		ix;

	quote = 0;
	start = 0;
	ix = 0;
	while (str[ix] != 0)
	{
		if (str[ix] == ' ' && quote == 0)
		{
			*array = ft_substr(str, start, ix - start);
			*array++;
			start = ix + 1;
		}
		else if (quote == 0 && (str[ix] == '\'' || str[ix] == '\"'))
			quote = str[ix];
		else if (quote != 0 && (str[ix] == '\'' || str[ix] == '\"'))
			quote = 0;
		ix++;
	}
	if (start != ix)
		*array = ft_substr(str, start, ix - start);
	return (array);
}

int	count_segments(char *str)
{
	int		count;
	char	quote;
	int		ix;

	count = 1;
	quote = 0;
	ix = 0;
	while (str[ix] != 0)
	{
		if (str[ix] == ' ' && quote == 0)
			count++;
		else if (quote == 0 && (str[ix] == '\'' || str[ix] == '\"'))
			quote = str[ix];
		else if (quote != 0 && (str[ix] == '\'' || str[ix] == '\"'))
			quote = 0;
		else if ((quote == '\"' || quote == 0) && str[ix] == '\\')
			ix++;
		ix++;
	}
	return (count);
}

int	main(int argc, char **argv)
{
	char	**array;
	int		index;

	printf("%s\n%i\n", argv[argc - 1], count_segments(argv[argc - 1]));
	array = ft_calloc(count_segments(argv[argc - 1]) + 1, sizeof(char *));
	segment_str(array, argv[argc - 1]);
	index = 0;
	while (array && array[index])
		printf("%s\n", array[index++]);
}
