/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nashxo <nashxo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/03/03 12:28:34 by nashxo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// ================== LIBS ==================

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

// ================== STRUCTURES ==================

typedef struct s_params
{
	int					total_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					required_meals;
	long int			start_time;
	pthread_mutex_t		printing_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		meal_time_mutex;
	pthread_mutex_t		finish_mutex;
	int					philosophers_finished;
	int					stop_flag;
}	t_params;

typedef struct s_philosopher
{
	int					philo_id;
	pthread_t			main_thread;
	pthread_t			death_monitor_thread;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		left_fork;
	t_params			*params;
	long int			last_meal_time;
	unsigned int		meal_count;
	int					is_finished;
}	t_philosopher;

typedef struct s_all_data
{
	t_philosopher		*philo_array;
	t_params			params;
}	t_all_data;

// ================== FUNCTIONS ==================

int			parse_arguments(int argc, char **argv, t_all_data *data);
int			initialize_all(t_all_data *data);
void		print_status(char *msg, t_philosopher *ph);
long int	get_current_time(void);
void		custom_usleep(long int time_in_ms);
int			create_philosopher_threads(t_all_data *data);
void		perform_actions(t_philosopher *ph);
int			check_stop_condition(t_philosopher *ph, int set_flag);
int			check_stop_condition2(t_all_data *data);
void		wait_for_termination(t_all_data *data);
long int	ft_atoi(const char *str);
void		characters_arg(char **av);

// ================== UTILS ==================

int			ft_strlen(char *str);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(long int num, int fd);
void		ft_putchar_fd(char c, int fd);
int			str_length(char *str);

#endif