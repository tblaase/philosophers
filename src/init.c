/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:02:48 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/05 22:31:20 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

static int	init_forks(void)
{
	int				i;
	int				check;
	// pthread_mutex_t	fork;
	t_philo			**philos;
	t_input			*input;

	input = get_input();
	philos = get_philos();
	input->forks = ft_calloc(input->n_philos, sizeof(*input->forks));
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
		// printf("initialised mutex on fork_r of philo %d\n", philos[i - 1]->philo_n);
		// printf("locking fork_r of philo %d now\n", philos[i - 1]->philo_n);
		// pthread_mutex_lock(&fork);
		// printf("unlocking fork_r of philo %d again\n", philos[i - 1]->philo_n);
	}
	philos[0]->fork_l = philos[--i]->fork_r;
	// printf("philo %d fork_l is now fork_r of philo %d\n", philos[0]->philo_n, philos[i]->philo_n);
	while (i > 0)
	{
		// printf("philo %d fork_l is now fork_r of philo %d\n", philos[i]->philo_n, philos[i - 1]->philo_n);
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
	// input->forks = ft_calloc(1, sizeof(pthread_mutex_t **));
	// if (init_forks(input) == EXIT_FAILURE)
	// 	return (NULL);
	philos = ft_calloc(input->n_philos + 1, sizeof(t_philo *));
	if (philos == NULL)
		return (NULL);
	// else
	// {
	i = 0;
	while (i < input->n_philos)
	{
		philos[i] = ft_calloc(1, sizeof(t_philo));
		if (philos[i] == NULL)
		{
			free_philos();
			return (NULL);
		}
		// philos[i]->fork_r = input->forks[i];
		philos[i]->philo_n = i + 1;
		// if (i == 0)
		// 	philos[i]->fork_l = input->forks[input->n_philos - 1];
		// else
		// 	philos[i]->fork_l = input->forks[i - 1];
		i++;
	}
	if (init_forks() == EXIT_FAILURE)
	{
		free_philos(); // change it to return NULL to save some lines
		return (NULL);
	}
	// }
	return (philos);
}

t_philo **get_philos(void)
{
	return (init_philos(false));
}