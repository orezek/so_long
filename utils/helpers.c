/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:31:52 by orezek            #+#    #+#             */
/*   Updated: 2024/01/07 17:32:28 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../so_long.h"

int	ft_free_array(char **array)
{
	char	**tmp_ptr;

	tmp_ptr = array;
	while (*array != NULL)
	{
		free(*array);
		array++;
	}
	free(tmp_ptr);
}
