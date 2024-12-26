#include "../includes/philo.h"

static void	characters_arg(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else if (str[i] == '-' || str[i] == '+' || str[i] == ' ')
			i++;
		else
		{
			printf("ERROR : Invalid arguments\n");
			exit(EXIT_FAILURE);
		}
	}
}

char	**check_split(char **av)
{
	char	**final;
	int		i;
	int		arg;

	arg = 1;
	i = ft_strlen(av[1]);
	if (i >= 3)
	{
		final = allocate_final_array(i);
		i = 0;
		fill_final_array(final, av[1], &i, &arg);
	}
	else
		exit(EXIT_SUCCESS);
	return (final);
}

int	ft_atoi(const char *str)
{
	int		nb;
	int		sign;
	int		i;

	sign = 1;
	nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * sign);
}

int     is_numeric(char **av, int i, int j)
{
	while (av[j])
	{
		while (av[j][i])
		{
			if (av[j][i] < '0' || av[j][i] > '9' || str_length(av[j]) > 10)
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int     parse_arguments(int ac, char **av, t_all_data *data)
{
	int     i;

	i = 0;
	if (ac == 2)
	{
		characters_arg(av[1]);
		av = check_split(av);
		ac = 0;
		while (av[i++])
			ac++;
	}
	if ((ac != 5 && ac != 6) || is_numeric(av, 0, 1) != 1)
		return (-1);
	data->params.total_philos = ft_atoi(av[1]);
	data->params.time_to_die  = ft_atoi(av[2]);
	data->params.time_to_eat  = ft_atoi(av[3]);
	data->params.time_to_sleep = ft_atoi(av[4]);
	data->params.required_meals = -1;
	if (ac - 1 == 5)
		data->params.required_meals = ft_atoi(av[5]);
	if (data->params.total_philos <= 0 || data->params.time_to_die <= 0 \
		|| data->params.time_to_eat <= 0 || data->params.time_to_sleep <= 0)
		return (0);
	return (1);
}
