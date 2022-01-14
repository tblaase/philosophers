/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:10:08 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/14 13:39:30 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

int	main(int argc, char **argv)
{
	t_input	*input;
	t_philo	**philos;

	input = NULL;
	if (argc < 5 || argc > 6)
		return (print_error());
	input = set_input(argv);
	if (input == NULL)
		return (EXIT_FAILURE);
	else
	{
		philos = init_philos(true);
		if (philos == NULL || philos[0] == NULL)
		{
			printf("Error while creating philosophers\n");
			return (EXIT_FAILURE);
		}
		if (thread_creation(input, philos) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	reaper();
	return (EXIT_SUCCESS);
}
