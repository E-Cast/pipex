#include <stdio.h>
#include "libft.h"

char	*make_segment(char *str, int start, int end)
{
	char	*segment;
	int		str_inx;
	int		seg_inx;
	char	quote;

	segment = ft_calloc((end - start) + 1, sizeof(char));
	if (segment == NULL)
		return (NULL); //terminate
	str_inx = start;
	seg_inx = 0;
	quote = 0;
	while (str_inx < end)
	{
		if (quote == 0 && (str[str_inx] == '\'' || str[str_inx] == '\"'))
			quote = str[str_inx];
		else if (quote != 0 && (str[str_inx] == '\'' || str[str_inx] == '\"'))
			quote = 0;
		else
			segment[seg_inx++] = str[str_inx];
		str_inx++;
	}
	my_strrealloc(&segment);
	return (segment);
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
			*array = make_segment(str, start, ix);
			array++;
			start = ix + 1;
		}
		else if (quote == 0 && (str[ix] == '\'' || str[ix] == '\"'))
			quote = str[ix];
		else if (quote != 0 && (str[ix] == '\'' || str[ix] == '\"'))
			quote = 0;
		ix++;
	}
	if (start != ix)
		*array = make_segment(str, start, ix);
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

	array = ft_calloc(count_segments(argv[argc - 1]) + 1, sizeof(char *));
	if (array == NULL)
		return (1); //terminate
	segment_str(array, argv[argc - 1]);
	printf("%s\n%s\n", array[0], array[1]);
}
