/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:41:08 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/22 23:19:13 by sbouheni         ###   ########.fr       */
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

size_t	get_program_time(size_t start_time)
{
	size_t program_time;

	program_time = get_time_stamp() - start_time;
	return (program_time);
}

void	my_usleep(size_t time)
{
	size_t	start_time;

	start_time = get_time_stamp() / 1000;
	while ((get_time_stamp() / 1000) - (start_time / 1000) < time)
		get_time_stamp();
}