/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:59:41 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/14 15:19:48 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

/**
 * @brief  this is the reaper, it collects the souls of philosophers
 * @note   once the time of a philosophers has come to die the reaper
 * 		   will do his work and print a message of the philosophers death
 * 		   and starts the death_routine
 * @param  *arg: sadly this arg is needed, still don't know how to get rid if it
 * @retval returns NULL if finished
 */
void	reaper(void)
{
	int		i;
	t_input	*input;
	t_philo	**philos;

	input = get_input();
	philos = get_philos();
	pthread_mutex_lock(input->time_lock);
	input->start_time = get_time();
	pthread_mutex_unlock(input->time_lock);
	pthread_mutex_lock(input->wait_lock);
	input->wait = false;
	pthread_mutex_unlock(input->wait_lock);
	ft_sleep(input->tt_die / 2);
	while (true)
	{
		i = 0;
		while (philos[i] != NULL)
		{
			pthread_mutex_lock(philos[i]->time_lock);
			pthread_mutex_lock(philos[i]->eat_lock);
			if (get_time() - philos[i]->time_philo > input->tt_die && philos[i]->eating == false)
			{
				pthread_mutex_unlock(philos[i]->eat_lock);
				pthread_mutex_unlock(philos[i]->time_lock);
				death_routine(philos[i]);
				return ;
			}
			pthread_mutex_unlock(philos[i]->eat_lock);
			pthread_mutex_unlock(philos[i]->time_lock);
			if (every_philo_finished() == true)
			{
				death_routine(NULL);
				return ;
			}
			i++;
		}
	}
}
