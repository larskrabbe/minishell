#include	"environment.h"
#define TRUE 1
#define FALSE 0

// Functions from libft used for the environment variables

// ft_strlen
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*(s + i) != '\0')
		i++;
	return (i);
}

// ft_strncmp
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((n > 0) && (*s1 == *s2) && (*s1 != '\0'))
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

// ft_split
char	**ft_free(char **res)
{
	int	i;

	i = 0;
	while (res[i] != NULL)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

static int	ft_word_count(char const *s, char c)
{
	int				in_word;
	int				word_count;
	unsigned int	i;

	i = 0;
	word_count = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			in_word = TRUE;
			while ((in_word) && (++i))
			{
				if ((s[i] == c) || s[i] == '\0')
				{
					word_count++;
					in_word = FALSE;
				}
			}
		}
		i++;
	}
	return (word_count);
}

static char	**ft_gen(const char *s, char c, char **res, int res_st_i)
{
	unsigned int	i;
	int				in_word;
	int				word_start;

	i = 0;
	while (i < ft_strlen(s))
	{
		word_start = i;
		in_word = TRUE;
		while (s[i] != c && in_word && ++i)
		{
			if ((s[i] == c) || (s[i] == '\0'))
			{
				res[res_st_i] = ft_substr(s, word_start, i - word_start);
				if (res[res_st_i] == NULL)
					return (ft_free(res));
				res_st_i++;
				in_word = FALSE;
			}
		}
		i++;
	}
	res[res_st_i] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**sarray;
	int		sarray_start_index;

	sarray_start_index = 0;
	if (!s)
		return (NULL);
	sarray = (char **) malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (!sarray)
		return (NULL);
	sarray = ft_gen(s, c, sarray, sarray_start_index);
	return (sarray);
}

// ft_strjoin
char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*newstr;
	unsigned int	i;
	unsigned int	j;

	if (!s1 || !s2)
		return (NULL);
	newstr = (char *) malloc(sizeof(*s1) * (ft_strlen(s1)+ ft_strlen(s2) + 1));
	if (!newstr)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
	{
		newstr[i] = s1[i];
	}
	j = -1;
	while (s2[++j] != '\0')
	{
		newstr[i++] = s2[j];
	}
	newstr[i] = '\0';
	return (newstr);
}
