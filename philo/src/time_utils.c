/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagomad <amagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/03/10 16:21:14 by amagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_stop_condition(t_philosopher *ph, int set_flag)
{
	pthread_mutex_lock(&ph->params->death_mutex);
	if (set_flag)
		ph->params->stop_flag = set_flag;
	if (ph->params->stop_flag)
	{
		pthread_mutex_unlock(&ph->params->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&ph->params->death_mutex);
	return (0);
}

long int	get_current_time(void)
{
	struct timeval	current;
	long int		ms_time;

	if (gettimeofday(&current, NULL) == -1)
	{
		printf("ERROR: Gettimeofday failed\n");
		return (-1);
	}
	ms_time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (ms_time);
}

void	custom_usleep(long int time_in_ms, t_params *params)
{
	long int	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < time_in_ms)
	{
		pthread_mutex_lock(&params->death_mutex);
		if (params->stop_flag)
		{
			pthread_mutex_unlock(&params->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&params->death_mutex);
		usleep(100);
	}
}
