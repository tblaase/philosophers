/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:59:41 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/17 20:30:28 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

/**
 * @brief  start routine of the reaper
 * @note   reaper will set the wait to false so the philosophers stop waiting
 * 		   and then the reaper will wait for half time_to_die so each
 * 		   philosopher is up and running, in that timespan no philo can die
 * 		   after that the reaper is starting his work
 * @param  *input: input struct
 * @retval None
 */
static void	reaper_start(t_input *input)
{
	input->start_time = get_time();
	pthread_mutex_lock(input->wait_lock);
	input->wait = false;
	pthread_mutex_unlock(input->wait_lock);
	ft_sleep(input->tt_die / 2);
}

/**
 * @brief  locks all the needed locks
 * @note
 * @param  **philos: philos struct
 * @param  i: position of the philo to deal with
 * @retval None
 */
static void	reaper_lock(t_philo **philos, int i)
{
	pthread_mutex_lock(philos[i]->time_lock);
	pthread_mutex_lock(philos[i]->eat_lock);
	pthread_mutex_lock(philos[i]->running_lock);
}

/**
 * @brief  unlocks all the needed locks
 * @note
 * @param  **philos: philos struct
 * @param  i: position of the philo to deal with
 * @retval None
 */
static void	reaper_unlock(t_philo **philos, int i)
{
	pthread_mutex_unlock(philos[i]->eat_lock);
	pthread_mutex_unlock(philos[i]->time_lock);
	pthread_mutex_unlock(philos[i]->running_lock);
}

/**
 * @brief  checks the state of each philosopher
 * @note   if one philo should die all have finished eating,
 * 		   death routine is called and false is returned
 * @param  *input: input struct
 * @param  **philos: philo structs
 * @retval true if all philos are alive, false if one died
 */
static bool	check_every_philo(t_input *input, t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i] != NULL)
	{
		reaper_lock(philos, i);
		if (get_time() - philos[i]->time_philo >= input->tt_die
			&& philos[i]->eating == false && philos[i]->running == true)
		{
			reaper_unlock(philos, i);
			death_routine(philos[i]);
			return (false);
		}
		reaper_unlock(philos, i);
		if (every_philo_finished() == true)
		{
			death_routine(NULL);
			return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @brief  this is the reaper, it collects the souls of philosophers
 * @note   once the time of a philosophers has come to die the reaper
 * 		   will do his work and print a message of the philosophers death
 * 		   and starts the death_routine
 * @param  *input: input struct
 * @param  **philos: philo structs
 * @retval returns NULL if finished
 */
void	reaper(void)
{
	t_input	*input;
	t_philo	**philos;

	input = get_input();
	philos = get_philos();
	reaper_start(input);
	while (true)
	{
		if (check_every_philo(input, philos) == false)
			break ;
	}
}
