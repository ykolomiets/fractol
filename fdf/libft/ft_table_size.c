/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 10:26:04 by ykolomie          #+#    #+#             */
/*   Updated: 2017/09/30 10:26:26 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_table_size(char **table)
{
	int	size;

	size = 0;
	while (table[size])
		size++;
	return (size);
}