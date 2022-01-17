/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:21:26 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/17 20:36:05 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

/**
 * @brief  joins all the threads after they are finished
 * @note
 * @retval none
 */
void	thread_join(void)
{
	int		i;
	int		check;
	t_philo	**philos;

	i = 0;
	check = 0;
	philos = get_philos();
	while (philos[i] != NULL && check == 0)
		check = pthread_join(philos[i++]->thread_id, NULL);
}

/**
 * @brief  creates all the threads with the correct philo value
 * @note
 * @param  *input: input struct
 * @param  **philos: philos structs
 * @retval success or failure
 */
int	thread_creation(t_input *input, t_philo **philos)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	input->wait = true;
	while (i < input->n_philos && check == 0)
	{
		check = pthread_create(&philos[i]->thread_id, NULL,
				&routine, philos[i]);
		usleep(100);
		i++;
	}
	if (check != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
