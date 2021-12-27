/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:12:08 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/27 16:19:23 by tblaase          ###   ########.fr       */
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
}			t_input;

// INFORMATION OF EACH PHILOSOPHER
typedef struct s_philo
{
	int				philo_n;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
}			t_philo;

// UTILS_ONE
long long	ft_atol(char *str);
void		*ft_calloc(size_t nelem, size_t elsize);
t_input		*set_input(char **argv);
t_input		*get_input(void);

// UTILS_TWO
long		get_time(void);
#endif
