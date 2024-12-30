#include "../includes/philo.h"

int		main(int ac, char **av)
{
	t_all_data	all;
	
	if (parse_arguments(ac, av, &all) < 0)
	{
		printf("ERROR: Invalid arguments\n");
		exit(EXIT_FAILURE);
	}
	all.philo_array = malloc(sizeof(t_philosopher) * all.params.total_philos);
	if (!all.philo_array)
	{
		printf("ERROR: Malloc Fail\n");
		exit(EXIT_FAILURE);
	}
	if (!initialize_all(&all) || !create_philosopher_threads(&all))
	{
		free(all.philo_array);
		return (1);
	}
	wait_for_termination(&all);
	return (0);
}