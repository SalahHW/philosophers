/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:41:08 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/28 22:58:14 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_time_stamp(void)
{
	struct timeval	time;
	size_t			timestamp;

	gettimeofday(&time, NULL);
	timestamp = (size_t)time.tv_sec * 1000 + (size_t)time.tv_usec / 1000;
	return (timestamp);
}

int	my_msleep(size_t time, t_data *data)
{
	size_t	start_time;
	int		sim_running;

	start_time = get_time_stamp();
	pthread_mutex_lock(&data->sim_running_mutex);
	sim_running = data->simulation_running;
	pthread_mutex_unlock(&data->sim_running_mutex);
	while (get_time_stamp() - start_time < time && sim_running)
	{
		pthread_mutex_lock(&data->sim_running_mutex);
		sim_running = data->simulation_running;
		pthread_mutex_unlock(&data->sim_running_mutex);
		if (!sim_running)
			return (0);
	}
	return (1);
}
