#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		++i;
	if (s[i] == '\0')
		return (ft_strdup(""));
	j = strlen(s) - 1;
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		--j;
	return (ft_strsub(s, i, j - i + 1));
}
