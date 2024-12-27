#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

//

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

//

typedef struct s_params
{
	int                 total_philos;       // nb philosophers
	int                 time_to_die;        // time to die
	int                 time_to_eat;        // time to eat
	int                 time_to_sleep;      // time to sleep
	int                 required_meals;     // nb to eat per philo
	long int            start_time;         // program start time (for timestamp calculations)
	pthread_mutex_t     printing_mutex;     // mutex for printing messages
	pthread_mutex_t     death_mutex;        // mutex for checking death/stop condition
	pthread_mutex_t     meal_time_mutex;    // mutex for protecting last meal time
	pthread_mutex_t     finish_mutex;       // mutex for protecting the "finished" state
	int                 philosophers_finished;
	int                 stop_flag;          // flag to stop the simulation if a philosopher dies or all have eaten
}   t_params;

typedef struct s_philosopher
{
	int                 philo_id;            // philo identifier
	pthread_t           main_thread;         // main thread of the philosopher
	pthread_t           death_monitor_thread;// thread for death monitoring
	pthread_mutex_t     *right_fork;         // pointer to the right fork
	pthread_mutex_t     left_fork;           // left fork
	t_params            *params;             // pointer to the global parameters
	long int            last_meal_time;      // timestamp of last meal
	unsigned int        meal_count;          // how many times this philosopher has eaten
	int                 is_finished;         // 1 if the philosopher has finished (if required_meals != -1)
}   t_philosopher;

typedef struct s_all_data
{
	t_philosopher       *philo_array;        // array of all philosophers
	t_params            params;              // global parameters
}   t_all_data;

//

int         parse_arguments(int argc, char **argv, t_all_data *data);
int         initialize_all(t_all_data *data);
int         exit_with_error(char *msg);
void        print_status(char *msg, t_philosopher *ph);
long int    get_current_time(void);
void        custom_usleep(long int time_in_ms);
int         create_philosopher_threads(t_all_data *data);
void        perform_actions(t_philosopher *ph);
int         check_stop_condition(t_philosopher *ph, int set_flag);
int			check_stop_condition2(t_all_data *data);
void		wait_for_termination(t_all_data *data);
char		**check_split(char **av);
long int	ft_atoi(const char *str);
void		free_split(char **split);
void		characters_arg(char *str);

// utils

int			ft_strlen(char *str);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(long int num, int fd);
void    	ft_putchar_fd(char c, int fd);
int         str_length(char *str);

// utils_2

char		**allocate_final_array(int size);
void		fill_final_array(char **final, const char *av, int *i, int *arg);
char		**ft_split(int ac, char **av);

#endif