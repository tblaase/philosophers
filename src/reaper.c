/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:59:41 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/03 20:16:37 by tblaase          ###   ########.fr       */
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
void	*reaper(void *arg)
{
	int		i;
	t_input	*input;
	t_philo	**philos;

	input = get_input();
	philos = get_philos();
	while (true)
	{
		i = 0;
		while (philos[i] != NULL)
		{
			if (philos[i]->time_philo - get_time() > input->tt_die)
			{
				death_routine(philos[i]);
				return (NULL);
			}
		}
	}
}
