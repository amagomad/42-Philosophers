/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashxo <nashxo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/03/03 12:24:21 by nashxo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	initialize_mutex(t_all_data *data)
{
	pthread_mutex_init(&data->params.printing_mutex, NULL);
	pthread_mutex_init(&data->params.death_mutex, NULL);
	pthread_mutex_init(&data->params.meal_time_mutex, NULL);
	pthread_mutex_init(&data->params.finish_mutex, NULL);
}

int	initialize_all(t_all_data *data)
{
	int	i;

	data->params.start_time = get_current_time();
	data->params.stop_flag = 0;
	data->params.philosophers_finished = 0;
	initialize_mutex(data);
	i = 0;
	while (i < data->params.total_philos)
	{
		data->philo_array[i].philo_id = i + 1;
		data->philo_array[i].last_meal_time = data->params.start_time;
		data->philo_array[i].meal_count = 0;
		data->philo_array[i].is_finished = 0;
		data->philo_array[i].right_fork = NULL;
		pthread_mutex_init(&data->philo_array[i].left_fork, NULL);
		if (data->params.total_philos == 1)
			return (1);
		if (i == data->params.total_philos - 1)
			data->philo_array[i].right_fork = &data->philo_array[0].left_fork;
		else
			data->philo_array[i].right_fork = \
				&data->philo_array[i + 1].left_fork;
		i++;
	}
	return (1);
}
