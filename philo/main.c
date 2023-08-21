/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:19:22 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/21 23:18:54 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	i = 0;
	if (parse_arg(argc, argv) == -1)
		return (-1);
	data = init_data(argc, argv);
	if (!data)
		return (-1);
	while (i < data->nb_philo)
	{
		add_new_philo(data);
		i++;
	}
	init_philo_data(data);
	if (!pthread_create(&data->health, NULL, health_routine, data))
	{
		i = 0;
		philo = data->first_philo;
		while (i < data->nb_philo)
		{
			if (!pthread_create(&philo->thread, NULL, philo_routine, philo))
			{
				philo = philo->next;
				i++;
			}
		}
	}
	i = 0;
	philo = data->first_philo;
	while (i < data->nb_philo)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	}
	pthread_join(data->health, NULL);
}
