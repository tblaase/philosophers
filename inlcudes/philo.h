/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:12:08 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/02 19:41:48 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>

// DEFINES

// INFORMATION FROM INPUT
typedef struct s_input
{
	long long		n_philos;
	long long		tt_die;
	long long		tt_eat;
	long long		tt_sleep;
	long long		n_must_eat[2];
	bool			death;
	pthread_mutex_t	**forks;
	pthread_mutex_t	print_lock;
	char			*state[7];
}			t_input;

// INFORMATION OF EACH PHILOSOPHER
typedef struct s_philo
{
	int				philo_n;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	pthread_t		thread_id;
}			t_philo;

// ENUM FOR PRINT STATEMENTS
typedef enum e_print_statement
{
	is_eating = 0,
	grabbed_fork = 1,
	is_sleeping = 2,
	is_thinking = 3,
	is_dead = 4,
}	t_print_statement;

// UTILS_ONE
long long	ft_atol(char *str);
void		*ft_calloc(size_t nelem, size_t elsize);
long		get_time(void);
void		print_state(t_input *input, t_philo *philo, int state, long time);

// UTILS_TWO
int			ft_sleep(long long ms);

// EXIT
int			destroy_forks(void);
void		free_philos(void);
int			destroy_philo(t_philo *philo); // maybe not needed
int			death_routine(t_philo *philo);

// INIT
t_philo		**init_philos(bool init);
t_philo		**get_philos(void);

// INPUT
t_input		*set_input(char **argv);
t_input		*get_input(void);

// ROUTINE
void		*routine(void *arg);

// THREADS
int			thread_creation(t_input *input, t_philo **philos);
int			thread_join(void);

#endif
