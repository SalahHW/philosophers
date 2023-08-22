/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:19:22 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/22 21:39:58 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void create_philo(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		add_new_philo(data);
		i++;
	}
}

static void launch_philo_threads(t_data *data)
{
	t_philo *philo;
	int i;
	
	i = 0;
	philo = data->first_philo;
	while (i < data->nb_philo)
	{
		pthread_create(&philo->thread, NULL, philo_routine, philo);
		philo = philo->next;
		i++;
	}
}

static void join_philo_threads(t_data *data)
{
	t_philo *philo;
	int i;
	
	i = 0;
	philo = data->first_philo;
	while (i < data->nb_philo)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (parse_arg(argc, argv) == -1)
		return (-1);
	data = init_data(argc, argv);
	if (!data)
		return (-1);
	create_philo(data);
	init_philo_data(data);
	pthread_create(&data->health, NULL, health_routine, data);
	launch_philo_threads(data);
	join_philo_threads(data);
	pthread_join(data->health, NULL);
}