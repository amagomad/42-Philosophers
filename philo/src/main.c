#include "../includes/philo.h"

int main(int argc, char **argv)
{
    t_all_data all;

    if (!parse_arguments(argc, argv, &all))
        return (exit_with_error("Invalid arguments\n"));
    all.philo_array = malloc(sizeof(t_philosopher) * all.params.total_philos);
    if (!all.philo_array)
        return (exit_with_error("Malloc returned NULL\n"));
    if (!initialize_all(&all) || !create_philosopher_threads(&all))
    {
        free(all.philo_array);
        return (0);
    }
    wait_for_termination(&all);

    return (0);
}