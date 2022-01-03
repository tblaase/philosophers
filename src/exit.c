/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:05:06 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/28 18:01:57 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

int	destroy_forks(void)
{
	t_philo	**philos;
	int		i;
	int		check;

	i = 0;
	check = 0;
	philos = get_philos();
	while (philos[i] != NULL && check == 0)
		check = pthread_mutex_destroy(philos[i]->fork_r);
	if (check != 0)
	{
		printf("Error when destroying forks\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	free_philos(void)
{
	t_philo	**philos;
	int		i;

	philos = get_philos();
	i = 0;
	while (philos[i] != NULL)
	{
		free(philos[i]);
		philos[i++] = NULL;
	}
	free(philos);
	philos = NULL;
}

int	destroy_philo(t_philo *philo) // maybe not needed
{
	(void)philo;
	return (EXIT_SUCCESS);
}

int	death_routine(t_philo *philo)
{
	(void)philo;
	return (EXIT_SUCCESS);
}