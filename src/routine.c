/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:59:25 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/17 20:31:40 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

/**
 * @brief  start routine of each philo
 * @note   philos will wait for all philos to be created
 * @param  *input: input struct
 * @param  *philo: philo struct
 * @retval None
 */
static void	philo_start(t_input *input, t_philo *philo)
{
	pthread_mutex_lock(philo->running_lock);
	philo->running = true;
	pthread_mutex_unlock(philo->running_lock);
	pthread_mutex_lock(input->wait_lock);
	while (input->wait == true)
	{
		pthread_mutex_unlock(input->wait_lock);
		usleep(1);
		pthread_mutex_lock(input->wait_lock);
	}
	pthread_mutex_lock(philo->time_lock);
	philo->time_philo = get_time();
	pthread_mutex_unlock(philo->time_lock);
	pthread_mutex_unlock(input->wait_lock);
	if (philo->philo_n % 2 == 0)
		ft_sleep(input->tt_eat / 2);
}

/**
 * @brief  philo has two forks now and is eating, sleeping, thinking
 * @note
 * @param  *input: input struct
 * @param  *philo: philo struct
 * @retval
 */
static void	philo_eat_sleep_think(t_input *input, t_philo *philo)
{
	pthread_mutex_unlock(input->death_lock);
	print_state(input, philo, is_eating);
	pthread_mutex_lock(philo->eat_lock);
	philo->eating = true;
	pthread_mutex_unlock(philo->eat_lock);
	pthread_mutex_lock(philo->time_lock);
	philo->time_philo = get_time();
	pthread_mutex_unlock(philo->time_lock);
	ft_sleep(input->tt_eat);
	pthread_mutex_unlock(&input->forks[philo->fork_l]);
	pthread_mutex_unlock(&input->forks[philo->fork_r]);
	pthread_mutex_lock(philo->eat_lock);
	philo->eating = false;
	pthread_mutex_unlock(philo->eat_lock);
	print_state(input, philo, is_sleeping);
	ft_sleep(input->tt_sleep);
	print_state(input, philo, is_thinking);
}

/**
 * @brief  only because of norminette
 * @note
 * @param  *input: input struct
 * @param  *philo: philo struct
 * @retval either eat or -1, -1 will break the while loop
 */
static bool	philo_do_stuff_help(t_input *input, t_philo *philo)
{
	pthread_mutex_lock(&input->forks[philo->fork_l]);
	print_state(input, philo, grabbed_fork);
	pthread_mutex_lock(input->death_lock);
	if (input->death == false)
	{
		philo_eat_sleep_think(input, philo);
		return (EXIT_SUCCESS);
	}
	pthread_mutex_unlock(input->death_lock);
	pthread_mutex_unlock(&input->forks[philo->fork_l]);
	pthread_mutex_unlock(&input->forks[philo->fork_r]);
	return (EXIT_FAILURE);
}

/**
 * @brief  the while loop of a living philo
 * @note   runns until one philo dies or he ate enough
 * @param  *input: input struct
 * @param  *philo: philo struct
 * @retval None
 */
static void	philo_do_stuff(t_input *input, t_philo *philo)
{
	int	eat;

	eat = 0;
	while ((input->n_must_eat[0] == true && eat < input->n_must_eat[1]
			&& eat < INT_MAX)
		|| (input->n_must_eat[0] == false && eat < INT_MAX))
	{
		pthread_mutex_lock(&input->forks[philo->fork_r]);
		print_state(input, philo, grabbed_fork);
		if (input->n_philos == 1)
		{
			pthread_mutex_unlock(&input->forks[philo->fork_r]);
			ft_sleep(input->tt_die + 1);
			break ;
		}
		if (philo_do_stuff_help(input, philo) == EXIT_FAILURE)
			break ;
		else
			eat++;
	}
}

/**
 * @brief  whole life cycle of a philosopher
 * @note
 * @param  *arg: gets the correct philo of that thread
 * @retval NULL
 */
void	*routine(void *arg)
{
	t_input	*input;
	t_philo	*philo;

	if (arg != NULL)
	{
		input = get_input();
		philo = (t_philo *)arg;
		philo_start(input, philo);
		philo_do_stuff(input, philo);
		pthread_mutex_lock(philo->running_lock);
		philo->running = false;
		pthread_mutex_unlock(philo->running_lock);
	}
	return (NULL);
}
