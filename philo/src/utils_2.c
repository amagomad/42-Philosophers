#include "../includes/philo.h"

static void	free_split(char **split)
{
	int		i;

	i = 1;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	*allocate_word(const char *av, int i, int j)
{
	char	*word;
	int		k;

	k = 0;
	word = malloc(sizeof(char) * (j + 1));
	if (!word)
		return (NULL);
	while (k < j)
	{
		word[k] = av[i + k];
		k++;
	}
	word[k] = '\0';
	return (word);
}

char	**allocate_final_array(int size)
{
	char	**final;

	final = malloc(sizeof(char *) * (size + 1));
	if (!final)
		return (NULL);
	final[0] = "./philosophers";
	return (final);
}

void	fill_final_array(char **final, const char *av, int *i, int *arg)
{
	int		j;

	while (av[*i] != '\0')
	{
		while (av[*i] == ' ' && av[*i])
			(*i)++;
		if (av[*i] == '\0')
			break ;
		j = 0;
		while (av[*i + j] && av[*i + j] != ' ')
			j++;
		final[*arg] = allocate_word(av, *i, j);
		if (!final[*arg])
		{
			free_split(final);
			exit(EXIT_FAILURE);
			return ;
		}
		*i += j;
		(*arg)++;
	}
	final[*arg] = NULL;
}