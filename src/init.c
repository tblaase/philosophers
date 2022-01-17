/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:02:48 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/17 20:28:04 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

/**
 * @brief  prints the error message of the fork creation
 * @note
 * @retval only to save some lines
 */
static int	error_forks(void)
{
	printf("Error when initialising forks\n");
	return (EXIT_FAILURE);
}

/**
 * @brief  will initialise the n forks of the n philosophers
 * @note   will hand the correct positions of the forks in the array
 * 		   to all of the philosophers
 * @retval failure or success
 */
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
			return (error_forks());
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

/**
 * @brief  is run in the loop of init_philos
 * @note   will create the single philosophers and create all of their locks
 * 		   will set all of their starting values
 * @param  i: the position in the philos structs of the philosopher to deal with
 * @retval failure or success
 */
static int	init_single_philo(int i)
{
	t_philo	**philos;

	philos = get_philos();
	philos[i] = ft_calloc(1, sizeof(t_philo));
	if (philos[i] == NULL)
	{
		free_philos();
		return (EXIT_FAILURE);
	}
	philos[i]->philo_n = i + 1;
	philos[i]->eating = false;
	philos[i]->time_lock = ft_calloc(1, sizeof(pthread_mutex_t));
	philos[i]->eat_lock = ft_calloc(1, sizeof(pthread_mutex_t));
	philos[i]->running_lock = ft_calloc(1, sizeof(pthread_mutex_t));
	if (philos[i]->time_lock == NULL || philos[i]->eat_lock == NULL
		|| philos[i]->eat_lock == NULL)
	{
		free_philos();
		return (EXIT_FAILURE);
	}
	pthread_mutex_init(philos[i]->running_lock, NULL);
	pthread_mutex_init(philos[i]->time_lock, NULL);
	pthread_mutex_init(philos[i]->eat_lock, NULL);
	return (EXIT_SUCCESS);
}

/**
 * @brief  will initialise all philos
 * @note
 * @param  init: decides wether to initialise it or just to get the static value
 * @retval NULL on error, else the value of philos
 */
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
		if (init_single_philo(i) == EXIT_FAILURE)
			return (NULL);
		i++;
	}
	if (init_forks() == EXIT_FAILURE)
	{
		free_philos();
		return (NULL);
	}
	return (philos);
}

/**
 * @brief  to easily get the value of philos in every function
 * @note
 * @retval value of philos
 */
t_philo	**get_philos(void)
{
	return (init_philos(false));
}
