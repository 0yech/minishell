/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:43:53 by estettle          #+#    #+#             */
/*   Updated: 2025/01/17 14:36:37 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Includes
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>

// Libft
# include "libft.h"
# include "ft_printf.h"

// Enums
typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

#endif //MINISHELL_H
