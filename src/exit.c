/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:05:06 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/18 11:11:43 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

/**
 * @brief  will correctly free the input struct and its contents
 * @note
 * @retval None
 */
void	free_input(void)
{
	t_input	*input;

	input = get_input();
	pthread_mutex_destroy(input->death_lock);
	pthread_mutex_destroy(input->wait_lock);
	pthread_mutex_destroy(input->print_lock);
	free(input->death_lock);
	free(input->wait_lock);
	free(input->print_lock);
	free(input);
}

/**
 * @brief  will destroy and free the forks
 * @note
 * @retval None
 */
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

/**
 * @brief  will free all the philosophers and their locks that were created
 * @note
 * @retval None
 */
void	free_philos(void)
{
	t_philo	**philos;
	int		i;

	philos = get_philos();
	i = 0;
	while (philos[i] != NULL)
	{
		pthread_mutex_destroy(philos[i]->running_lock);
		pthread_mutex_destroy(philos[i]->eat_lock);
		pthread_mutex_destroy(philos[i]->time_lock);
		free(philos[i]->running_lock);
		free(philos[i]->eat_lock);
		free(philos[i]->time_lock);
		free(philos[i]);
		i++;
	}
	free(philos);
}

/**
 * @brief  is called at the end of the simulation
 * @note   is called upon death or when all phillosophers are finished
 * @param  *philo: the philo who died or NULL if all finished
 * @retval None
 */
void	death_routine(t_philo *philo)
{
	t_input	*input;
	long	death_time;

	input = get_input();
	pthread_mutex_lock(input->death_lock);
	input->death = true;
	pthread_mutex_unlock(input->death_lock);
	ft_sleep(2);
	death_time = get_time();
	if (philo != NULL)
		printf("%ld	%d %s", death_time - input->start_time,
			philo->philo_n, input->state[is_dead]);
	while (every_philo_finished() == false)
		usleep(10);
	thread_join();
	free_philos();
	destroy_forks();
	free_input();
}
