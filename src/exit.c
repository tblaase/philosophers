/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:05:06 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/10 20:00:09 by tblaase          ###   ########.fr       */
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
		//
		perror("Error");
		//
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
	// t_philo	**philos;
	// int		i;

	// i = 0;
	input = get_input();
	// philos = get_philos();
	pthread_mutex_lock(input->death_lock);
	input->death = true;
	pthread_mutex_unlock(input->death_lock);
	if (philo != NULL)
		printf("%ld %d %s", get_time() - input->start_time, philo->philo_n, input->state[is_dead]);
	// printf("joining threads now\n");
	// while (philos[i] != NULL)
	// 	pthread_join(philos[i++]->thread_id, NULL);
	thread_join();
	// printf("successfully joined threads\n");
	if (destroy_forks() == EXIT_FAILURE)
	{
		free_philos();
		return (EXIT_FAILURE);
	}
	free_philos();
	return (EXIT_SUCCESS);
}
