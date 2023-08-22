/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:29:46 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/23 00:41:34 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	add_new_philo(t_data *data)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (0);
	new_philo->prev = data->last_philo;
	new_philo->next = data->first_philo;
	if (data->last_philo)
		data->last_philo->next = new_philo;
	else
		data->first_philo = new_philo;
	data->last_philo = new_philo;
	data->first_philo->prev = new_philo;
	return (1);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->start_time = get_time_stamp();
	data->simulation_running = 1;
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = -1;
	data->first_philo = NULL;
	data->last_philo = NULL;
	return (data);
}

void	init_philo_data(t_data *data)
{
	t_philo *philo;
	int i;

	philo = data->first_philo;
	i = 0;
	while (i < data->nb_philo)
	{
		philo->id = i + 1;
		philo->simulation_running = 1;
		philo->start_time = data->start_time;
		philo->time_to_die = data->time_to_die;
		philo->time_to_eat = data->time_to_eat;
		philo->time_to_sleep = data->time_to_sleep;
		philo->nb_eat = data->nb_eat;
		philo->nb_eat_done = 0;
		philo->dead = 0;
		pthread_mutex_init(&philo->fork, NULL);
		philo = philo->next;
		i++;
	}
}