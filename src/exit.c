/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:05:06 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/03 20:30:54 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

int	destroy_forks(void)
{
	t_input	*input;
	int		i;
	int		check;

	i = 0;
	check = 0;
	input = get_input();
	while (i < input->n_philos && check == 0)
		check = pthread_mutex_destroy(&input->forks[i++]);
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

int	death_routine(t_philo *philo)
{
	t_input	*input;
	t_philo	**philos;
	int		i;

	i = 0;
	input = get_input();
	philos = get_philos();
	input->death = true;
	printf("%d %s", philo->philo_n, input->state[is_dead]);
	if (destroy_forks() == EXIT_FAILURE)
	{
		while (philos[i] != NULL)
			pthread_join(philos[i++]->thread_id, NULL);
		free_philos();
		return (EXIT_FAILURE);
	}
	while (philos[i] != NULL)
		pthread_join(philos[i++]->thread_id, NULL);
	free_philos();
	return (EXIT_SUCCESS);
}
