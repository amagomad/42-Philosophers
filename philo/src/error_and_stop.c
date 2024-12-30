#include "../includes/philo.h"

int check_stop_condition2(t_all_data *data)
{
    pthread_mutex_lock(&data->params.death_mutex);
    if (data->params.stop_flag)
    {
        pthread_mutex_unlock(&data->params.death_mutex);
        return (1);
    }
    pthread_mutex_unlock(&data->params.death_mutex);
    return (0);
}

void wait_for_termination(t_all_data *data)
{
    int		i;

    // Wait until a philosopher dies or everyone is done
    while (!check_stop_condition2(data))
        custom_usleep(1);

    // Join all philosopher threads
    i = -1;
    while (++i < data->params.total_philos)
        pthread_join(data->philo_array[i].main_thread, NULL);

    // Destroy global printing mutex
    pthread_mutex_destroy(&data->params.printing_mutex);

    // Destroy each philosopher's left fork mutex
    i = -1;
    while (++i < data->params.total_philos)
        pthread_mutex_destroy(&data->philo_array[i].left_fork);

    // If stop_flag == 2, it means everyone ate the required_meals
    if (data->params.stop_flag == 2)
        printf("Each philosopher ate %d time(s)\n", data->params.required_meals);

    // Free the philosophers array
    free(data->philo_array);
}