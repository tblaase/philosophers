/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:59:41 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/05 22:23:03 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

static bool	every_philo_finished(void)
{
	t_philo	**philos;
	t_input	*input;
	int		finished;
	int		i;

	finished = 0;
	i = 0;
	philos = get_philos();
	input = get_input();
	while (philos[i] != NULL)
	{
		if (philos[i]->running == false)
			finished++;
		i++;
	}
	if (finished == input->n_philos)
		return (true);
	return (false);
}

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
	// int		finished;
	t_input	*input;
	t_philo	**philos;

	input = get_input();
	philos = get_philos();
	input->start_time = get_time();
	input->wait = false;
	// printf("wait is now false, starting simulation\n");
	ft_sleep(input->tt_die / 2);
	while (true)
	{
		i = 0;
		while (philos[i] != NULL)
		{
			// printf("reaper is running\n");
			if (get_time() - philos[i]->time_philo > input->tt_die)
			{
				// printf("time_philo of %d = %ld\n", philos[i]->philo_n, philos[i]->time_philo - input->start_time);
				// printf("get_time() - philos[i]->time_philo = %ld\n", get_time() - philos[i]->time_philo);
				// printf("philo %d died, running death routine now\n", philos[i]->philo_n);
				// printf("death_time of %d is %ld\n", philos[i]->philo_n, get_time() - input->start_time);
				death_routine(philos[i]);
				return ;
			}
			// if (philos[i]->running == false)
			// {
			// 	finished++;
			// 	printf("philo %d finished\n", philos[i]->philo_n);
				if (every_philo_finished() == true)
				{
					// printf("every philo finished eating\n");
					death_routine(NULL);
					return ;
				}
			// }
			i++;
		}
	}
}
