/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:20:57 by calmouht          #+#    #+#             */
/*   Updated: 2024/01/03 20:00:21 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->left_a);
	printf("%ld %d has taken a fork\n", the_time(data->curr_time), philo->id);
	pthread_mutex_lock(philo->right_a);
	printf("%ld %d has taken a fork\n", the_time(data->curr_time), philo->id);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_a);
	pthread_mutex_unlock(philo->right_a);
}

void	print_think(long current, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	printf("%ld %d is thinking\n", the_time(current), philo->id);
	pthread_mutex_unlock(&philo->data->lock);
}

void	print_rest(long curr, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	philo->last_eat = the_time(curr);
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_lock(&philo->data->lock);
	printf("%ld %d is eating\n", the_time(curr), philo->id);
	pthread_mutex_unlock(&philo->data->lock);
	usleeper(philo->data->t_eat, philo->data);
	pthread_mutex_lock(&philo->data->lock);
	philo->data->times_to_eat--;
	pthread_mutex_unlock(&philo->data->lock);
	drop_forks(philo);
	pthread_mutex_lock(&philo->data->lock);
	printf("%ld %d is sleeping\n", the_time(curr), philo->id);
	pthread_mutex_unlock(&philo->data->lock);
	usleeper(philo->data->t_spleep, philo->data);
}
