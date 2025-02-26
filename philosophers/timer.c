/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:22:25 by calmouht          #+#    #+#             */
/*   Updated: 2024/01/03 22:56:55 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	the_time(long timedebut)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - timedebut);
}

void	usleeper(long time, t_data *data)
{
	long	start;

	start = the_time(data->curr_time);
	while ((the_time(data->curr_time) - start) < time)
		usleep(50);
}

void	get_init_time(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	data->curr_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
}
