#include "../includes/philo.h"

void	characters_arg(char **av)
{
	int		i;
	int		j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while(av[i][j])
		{
			if (av[i][j] >= '0' && av[i][j] <= '9')
				j++;
			else if (av[i][j] == '+' || av[i][j] == ' ')
				j++;
			else
			{
				printf("ERROR: Invalid arguments\n");
				exit(EXIT_FAILURE);
			}
		}
		i++;
	}
}

long int	ft_atoi(const char *str)
{
	int		nb;
	int		i;

	nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	if (nb > INT_MAX || nb < INT_MIN)
		return (-1);
	return (nb);
}

int	parse_arguments(int ac, char **av, t_all_data *data)
{
	if ((ac != 5 && ac != 6))
		return (-1);
	characters_arg(av);
	data->params.total_philos = ft_atoi(av[1]);
	data->params.time_to_die  = ft_atoi(av[2]);
	data->params.time_to_eat  = ft_atoi(av[3]);
	data->params.time_to_sleep = ft_atoi(av[4]);
	data->params.required_meals = -1;
	if (ac - 1 == 5)
		data->params.required_meals = ft_atoi(av[5]);
	if (data->params.total_philos <= 0 || data->params.time_to_die <= 0 \
		|| data->params.time_to_eat <= 0 || data->params.time_to_sleep <= 0)
		return (-1);
	return (1);
}
