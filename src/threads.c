/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:21:26 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/28 16:58:44 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

int	thread_join(t_philo **philos)
{
	(void)philos;
	return (EXIT_SUCCESS);
}

int	thread_creation(t_input *input, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < input->n_philos)
	{
		if (i % 2 == 0)
		{
			pthread_create(&philos[i]->thread_id, NULL, &routine, &philos[i]);
			i++;
		}
	}
	i = 0;
	while (i < input->n_philos)
	{
		if (i % 2 != 0)
		{
			pthread_create(&philos[i]->thread_id, NULL, &routine, &philos[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
