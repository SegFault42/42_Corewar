#include "./includes/libft.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}
