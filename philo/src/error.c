/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagomad <amagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/03/10 16:20:02 by amagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_stop_condition2(t_all_data *data)
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

static void	ft_free(t_all_data *data)
{
	int	i;

	i = 0;
	while (i < data->params.total_philos)
	{
		pthread_join(data->philo_array[i].main_thread, NULL);
		pthread_mutex_destroy(&data->philo_array[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&data->params.printing_mutex);
	pthread_mutex_destroy(&data->params.death_mutex);
	pthread_mutex_destroy(&data->params.meal_time_mutex);
	pthread_mutex_destroy(&data->params.finish_mutex);
	free(data->philo_array);
}

void	wait_for_termination(t_all_data *data)
{
	while (!check_stop_condition2(data))
		custom_usleep(1, &data->params);
	if (data->params.stop_flag == 2)
		printf("Each philosopher ate %d time(s)\n", \
			data->params.required_meals);
	ft_free(data);
}
