/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calmouht <calmouht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:02:18 by calmouht          #+#    #+#             */
/*   Updated: 2024/01/03 20:02:51 by calmouht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int				id;
	long			last_eat;
	int				times_ate;
	int				time_to_eat;
	int				death;
	pthread_mutex_t	*left_a;
	pthread_mutex_t	*right_a;
	pthread_t		thread;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	int					death;
	int					ph_num;
	int					t_death;
	int					t_eat;
	int					t_spleep;
	int					times_to_eat;
	long				curr_time;
	long				first_time;
	int					finished;
	int					philo_ate;
	pthread_mutex_t		lock;
	pthread_mutex_t		*forks;
	t_philo				*philosopher;
}						t_data;

int						ft_atoi(const char *str);
long					the_time(long timedebut);
void					usleeper(long time, t_data *data);
void					get_init_time(t_data *data);
int						ft_isdigit(int a);
int						checks_err(int ac, char **av);
int						init_data(t_data *data, char **av);
void					init_philosopher(t_data *data);
void					forks(t_data *data, t_philo *philo);
void					drop_forks(t_philo *philo);
long					ft_l_atoi(const char *str);
void					free_arr(t_data *data);
int						finish(t_data *data);
void					print_think(long curr, t_philo *philo);
void					print_rest(long curr, t_philo *philo);
void					create_threads(t_data *data);
void					free_all(t_data *data);

#endif
