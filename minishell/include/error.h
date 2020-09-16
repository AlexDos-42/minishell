/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:11:46 by alesanto          #+#    #+#             */
/*   Updated: 2020/02/05 14:18:08 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERROR_PLAYER "Error\nNumbre of players on map : %d\n"
# define ERROR_RES "Error\nRES GOES WRONG : x %d: y %d\n"
# define ERROR_RESO "Error\nResolution isn't correct\n"
# define ERROR_MUR "Error\nTexture info isn't correct\n"
# define ERROR_COLOR "Error\nCOLOR GOES WRONG\n"
# define ERROR_TEXTURE "Error\nTEXTURE GOES WRONG\n"
# define ERROR_FD "Error\nFD GOES WRONG\n"
# define ERROR_ARGC "Error\nArgc == %d insted of 1\n"
# define ERROR_MALLOC "Error\nMalloc of %s didn't work\n"
# define ERROR_LENLINE "Error\nline %d has %d char instead of %d\n"
# define ERROR_MAP "Error\nMap error : %c isn't valide\n"
# define ERROR_PARS "Error\nOne line of the scene is incorrect information\n"
# define ERROR_GNL "Error\n%retour du GNL = %d\n"
# define ERROR_GO "GAME OVER\n"
# define ERROR_DOUBLE "Error\nYou can't have more than one %c\n"
# define ERROR_MAPLAST "Error\nIncorrect line in information file\n"
# define ERROR_MAPP "Error\nThe map require all the others parameters\n"
# define ERROR_MISS "Error\nInformation is missing\n"

#endif
