/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashxo <nashxo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:29:18 by amagomad          #+#    #+#             */
/*   Updated: 2025/03/03 12:24:45 by nashxo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(char *msg, t_philosopher *ph)
{
	long int	timestamp;

	timestamp = get_current_time() - ph->params->start_time;
	if (timestamp >= 0 && timestamp <= 2147483647 \
		&& !check_stop_condition(ph, 0))
	{
		printf("%ld ", timestamp);
		printf("Philo %d %s", ph->philo_id, msg);
	}
}

void	sleep_and_think(t_philosopher *ph)
{
	pthread_mutex_lock(&ph->params->printing_mutex);
	print_status("is sleeping\n", ph);
	pthread_mutex_unlock(&ph->params->printing_mutex);
	custom_usleep(ph->params->time_to_sleep);
	pthread_mutex_lock(&ph->params->printing_mutex);
	print_status("is thinking\n", ph);
	pthread_mutex_unlock(&ph->params->printing_mutex);
}

void	perform_actions(t_philosopher *ph)
{
	pthread_mutex_lock(&ph->left_fork);
	pthread_mutex_lock(&ph->params->printing_mutex);
	print_status("has taken a fork\n", ph);
	pthread_mutex_unlock(&ph->params->printing_mutex);
	if (!ph->right_fork)
	{
		custom_usleep(ph->params->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(ph->right_fork);
	pthread_mutex_lock(&ph->params->printing_mutex);
	print_status("has taken a fork\n", ph);
	pthread_mutex_unlock(&ph->params->printing_mutex);
	pthread_mutex_lock(&ph->params->printing_mutex);
	print_status("is eating\n", ph);
	pthread_mutex_lock(&ph->params->meal_time_mutex);
	ph->last_meal_time = get_current_time();
	pthread_mutex_unlock(&ph->params->meal_time_mutex);
	pthread_mutex_unlock(&ph->params->printing_mutex);
	custom_usleep(ph->params->time_to_eat);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(&ph->left_fork);
	sleep_and_think(ph);
}
