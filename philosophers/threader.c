/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:21:46 by calmouht          #+#    #+#             */
/*   Updated: 2024/01/03 20:00:35 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finish(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->ph_num)
	{
		if (the_time(data->curr_time)
			- (data->philosopher[j].last_eat) >= data->t_death)
		{
			printf("%ld %d died\n", the_time(data->philosopher[j].data
					->curr_time), data->philosopher[j].id);
			data->philosopher[j].data->death = 1;
			return (1);
		}
		j++;
	}
	return (0);
}

int	checks_err(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (0);
	i = 1;
	j = 0;
	while (av[i])
	{
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 0)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	if (av[5] && ft_atoi(av[5]) <= 0)
		return (0);
	if ((ft_atoi(av[1]) > 200 || ft_atoi(av[1]) < 1))
		return (0);
	return (1);
}

void	free_arr(t_data *data)
{
	pthread_mutex_destroy(data->forks);
	pthread_mutex_destroy(&data->lock);
	free(data->philosopher);
	free(data->forks);
}

void	free_all(t_data *data)
{
	free_arr(data);
	free(data);
}
