/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:05:06 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/14 15:38:42 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

void	free_input(void)
{
	t_input	*input;

	input = get_input();
	pthread_mutex_destroy(input->print_lock);
	pthread_mutex_destroy(input->running_lock);
	pthread_mutex_destroy(input->time_lock);
	pthread_mutex_destroy(input->wait_lock);
	pthread_mutex_destroy(input->death_lock);
	pthread_mutex_destroy(input->i_p_lock);
	free(input->print_lock);
	free(input->running_lock);
	free(input->time_lock);
	free(input->wait_lock);
	free(input->death_lock);
	free(input->i_p_lock);
	free(input);
}

void	destroy_forks(void)
{
	t_input	*input;
	int		i;
	int		check;

	i = 0;
	check = 0;
	input = get_input();
	while (i < input->n_philos && check == 0)
	{
		check = pthread_mutex_destroy(&input->forks[i++]);
		usleep(10);
	}
	free(input->forks);
	if (check != 0)
		printf("Error when destroying forks\n");
}

void	free_philos(void)
{
	t_philo	**philos;
	int		i;

	philos = get_philos();
	i = 0;
	while (philos[i] != NULL)
	{
		pthread_mutex_destroy(philos[i]->time_lock);
		pthread_mutex_destroy(philos[i]->eat_lock);
		free(philos[i]->time_lock);
		free(philos[i]->eat_lock);
		free(philos[i]);
		philos[i++] = NULL;
	}
	free(philos);
	philos = NULL;
}

void	death_routine(t_philo *philo)
{
	t_input	*input;
	long	death_time;

	input = get_input();
	pthread_mutex_lock(input->death_lock);
	input->death = true;
	pthread_mutex_unlock(input->death_lock);
	usleep(1000);
	death_time = get_time();
	if (philo != NULL)
		printf("%ld	%d %s", death_time - input->start_time, philo->philo_n, input->state[is_dead]);
	while (every_philo_finished() == false)
		usleep(10);
	thread_join();
	destroy_forks();
	free_philos();
	free_input();
}
