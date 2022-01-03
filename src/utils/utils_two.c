/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:09:48 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/03 20:52:03 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inlcudes/philo.h"

int	ft_sleep(long long ms)
{
	int		check;
	long	start_time;

	check = 0;
	start_time = get_time();
	while (start_time + ms > get_time() && check == 0)
		check = usleep(100);
	if (check != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
