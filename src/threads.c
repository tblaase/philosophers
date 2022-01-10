/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:21:26 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/10 19:53:39 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

int	thread_join(void)
{
	int		i;
	int		check;
	t_philo	**philos;

	i = 0;
	check = 0;
	philos = get_philos();
	while (philos[i] != NULL && check == 0)
		check = pthread_detach(philos[i++]->thread_id);
	return (EXIT_SUCCESS);
}

int	thread_creation(t_input *input, t_philo **philos)
{
	int	i;

	i = 0;
	input->wait = true;
	while (i < input->n_philos)
	{
		input->i_p = i;
		pthread_create(&philos[i]->thread_id, NULL, &routine, NULL);
		usleep(100);
		i++;
	}
	reaper();
	return (EXIT_SUCCESS);
}
