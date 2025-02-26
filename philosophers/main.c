/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:15:07 by calmouht          #+#    #+#             */
/*   Updated: 2024/01/03 20:02:54 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*threads(void *walo)
{
	int		i;
	t_philo	*philo;
	long	cur;

	i = 0;
	philo = (t_philo *)walo;
	cur = philo->data->curr_time;
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->death != 0)
		{
			pthread_detach(philo->thread);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->lock);
		print_think(cur, philo);
		forks(philo->data, philo);
		print_rest(cur, philo);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (checks_err(ac, av) == 0)
		return (1);
	data = malloc(sizeof(t_data));
	get_init_time(data);
	if (init_data(data, av) == 0)
	{
		free(data);
		return (1);
	}
	data->philosopher = malloc(data->ph_num * sizeof(t_philo));
	init_philosopher(data);
	create_threads(data);
	while (1)
	{
		pthread_mutex_lock(&data->lock);
		if (finish(data) == 1)
			break ;
		if (data->times_to_eat <= 0)
			break ;
		pthread_mutex_unlock(&data->lock);
	}
	free_all(data);
}

int	init_data(t_data *data, char **av)
{
	data->ph_num = ft_atoi(av[1]);
	data->t_death = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_spleep = ft_atoi(av[4]);
	if (data->t_death < 60 || data->t_eat < 60 || data->t_spleep < 60)
		return (0);
	if (av[5])
		data->times_to_eat = ft_atoi(av[5]) * data->ph_num;
	else
		data->times_to_eat = 2147483646;
	data->forks = malloc(data->ph_num * sizeof(pthread_mutex_t));
	return (1);
}

void	init_philosopher(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		data->philosopher[i].times_ate = 0;
		data->philosopher[i].id = i + 1;
		data->philosopher[i].left_a = &data->forks[i];
		data->philosopher[i].right_a = &data->forks[(i + 1) % data->ph_num];
		data->philosopher[i].time_to_eat = data->times_to_eat;
		data->philosopher[i].data = data;
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->lock, NULL);
		i++;
	}
}

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		pthread_create(&data->philosopher[i].thread, NULL, 
			threads, &data->philosopher[i]);
		usleep(50);
		i++;
	}
}
