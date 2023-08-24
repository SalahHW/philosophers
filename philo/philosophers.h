/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:21:36 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/24 22:34:33 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				simulation_running;
	size_t			start_time;
	int				nb_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nb_eat;
	int				finished_eat;
	pthread_t		health;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				nb_eat_done;
	size_t			last_meal;
	pthread_mutex_t	fork;
	pthread_t		thread;
	t_data			*data;
	struct s_philo	*next;
}					t_philo;

// parser.c
int					parse_arg(int argc, char **argv);
// error.c
int					print_error(char *str);
// init.c
void				init_data(int argc, char **argv, t_data *data);
// utils.c
int					ft_atoi(const char *str);
// time.c
size_t				get_time_stamp(void);
void				my_usleep(size_t time);
// routine.c
void				*philo_routine(void *arg);
// routine_utils.c
int					check_philo_health(t_philo *philo);
int					has_finished_eat(t_philo *philo);

#endif
