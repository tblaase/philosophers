/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:02:48 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/14 15:19:04 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

static int	init_forks(void)
{
	int				i;
	int				check;
	t_philo			**philos;
	t_input			*input;

	input = get_input();
	philos = get_philos();
	input->forks = ft_calloc(input->n_philos, sizeof(pthread_mutex_t));
	i = 0;
	while (philos[i] != NULL)
	{
		check = pthread_mutex_init(&input->forks[i], NULL);
		if (check != 0)
		{
			printf("Error when initialising forks\n");
			return (EXIT_FAILURE);
		}
		philos[i]->fork_r = i;
		i++;
	}
	philos[0]->fork_l = philos[--i]->fork_r;
	while (i > 0)
	{
		philos[i]->fork_l = philos[i - 1]->fork_r;
		i--;
	}
	return (EXIT_SUCCESS);
}

t_philo	**init_philos(bool init)
{
	static t_philo	**philos;
	int				i;
	t_input			*input;

	if (init == false)
		return (philos);
	input = get_input();
	philos = ft_calloc(input->n_philos + 1, sizeof(t_philo *));
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < input->n_philos)
	{
		philos[i] = ft_calloc(1, sizeof(t_philo));
		if (philos[i] == NULL)
		{
			free_philos();
			return (NULL);
		}
		philos[i]->philo_n = i + 1;
		philos[i]->eating = false;
		philos[i]->time_lock = ft_calloc(1, sizeof(pthread_mutex_t));
		philos[i]->eat_lock = ft_calloc(1, sizeof(pthread_mutex_t));
		pthread_mutex_init(philos[i]->time_lock, NULL);
		pthread_mutex_init(philos[i]->eat_lock, NULL);
		i++;
	}
	if (init_forks() == EXIT_FAILURE)
	{
		free_philos();
		return (NULL);
	}
	return (philos);
}

t_philo **get_philos(void)
{
	return (init_philos(false));
}
