/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashxo <nashxo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/03/03 12:25:47 by nashxo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitor_death(void *data)
{
	t_philosopher	*ph;

	ph = (t_philosopher *)data;
	custom_usleep(ph->params->time_to_die + 1);
	pthread_mutex_lock(&ph->params->meal_time_mutex);
	pthread_mutex_lock(&ph->params->finish_mutex);
	if (!check_stop_condition(ph, 0)
		&& !ph->is_finished
		&& (get_current_time() - ph->last_meal_time) \
		>= (long)ph->params->time_to_die)
	{
		pthread_mutex_unlock(&ph->params->meal_time_mutex);
		pthread_mutex_unlock(&ph->params->finish_mutex);
		pthread_mutex_lock(&ph->params->printing_mutex);
		print_status("died\n", ph);
		pthread_mutex_unlock(&ph->params->printing_mutex);
		check_stop_condition(ph, 1);
	}
	else
	{
		pthread_mutex_unlock(&ph->params->meal_time_mutex);
		pthread_mutex_unlock(&ph->params->finish_mutex);
	}
	return (NULL);
}

static int	handle_meal_count(t_philosopher *ph)
{
	if ((int)++ph->meal_count == ph->params->required_meals)
	{
		pthread_mutex_lock(&ph->params->finish_mutex);
		ph->is_finished = 1;
		ph->params->philosophers_finished++;
		if (ph->params->philosophers_finished == ph->params->total_philos)
		{
			pthread_mutex_unlock(&ph->params->finish_mutex);
			check_stop_condition(ph, 2);
		}
		else
			pthread_mutex_unlock(&ph->params->finish_mutex);
		return (1);
	}
	return (0);
}

void	*philosopher_routine(void *data)
{
	t_philosopher	*ph;

	ph = (t_philosopher *)data;
	if (ph->philo_id % 2 == 0)
		custom_usleep(ph->params->time_to_eat / 10);
	while (!check_stop_condition(ph, 0))
	{
		pthread_create(&ph->death_monitor_thread, NULL, monitor_death, data);
		perform_actions(ph);
		pthread_detach(ph->death_monitor_thread);
		if (handle_meal_count(ph))
			return (NULL);
	}
	return (NULL);
}

int	create_philosopher_threads(t_all_data *data)
{
	int	i;

	i = 0;
	while (i < data->params.total_philos)
	{
		data->philo_array[i].params = &data->params;
		if (pthread_create(&data->philo_array[i].main_thread, NULL, \
			philosopher_routine, &data->philo_array[i]) != 0)
		{
			printf("ERROR: Pthread failed\n");
			return (-1);
		}
		i++;
	}
	return (1);
}
