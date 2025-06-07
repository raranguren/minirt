/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:47:32 by bduval            #+#    #+#             */
/*   Updated: 2025/06/07 23:35:02 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define ERROR(msg) error(msg)
# define PERROR(msg) print_error(msg, __FILE__, __LINE__, __func__)
# define PERROR2(msg1, msg2) print_error2(msg1, msg2,  __FILE__, __LINE__)

# define ICI	printf("ICI\n");

// Screen dimensions
# define WIN_WIDTH		720
# define WIN_HEIGHT		720
# define UI_WIDTH		0

# define COLOR_BG		0x00111111

//Objects types
# define CAMERA		0b00000001
# define LIGHT		0b00000010
# define AMB_LIGHT	0b00000100
# define SHAPE		0b00001000
# define SPHERE		0b00011000
# define PLANE		0b00101000
# define CYLINDER	0b00111000
# define CONE		0b01001000
//(Using values 0 to 127 to avoid needing unsigned char)

//GUI textures
# define CAMERA_BG		"textures/ui_camera.xpm"
# define LIGHT_BG		"textures/ui_light.xpm"
# define AMB_LIGHT_BG	"textures/ui_amb_light.xpm"
# define SPHERE_BG		"textures/ui_sphere.xpm"
# define PLANE_BG		"textures/ui_plane.xpm"
# define CYLINDER_BG	"textures/ui_cylinder.xpm"
# define CONE_BG		"textures/ui_cone.xpm"

//Error messages
# define ERROR_ARGUMENTS	"\
You must provide only a scene description \
file with .rt extension as argument"

# define AMB_LIGHT_WAITED_VALUES	"\
Format for ambiance light parameter is the following :\n\
(A) (lighting ratio [0->1]) (r,g,b color [0->255])"

# define LIGHT_WAITED_VALUES	"\
Format for light parameter is the following :\n\
(L) (x,y,z coorinates) (normalized brightness [0->1]) (r,g,b color [0->255])"

# define CAM_WAITED_VALUES	"\
Format for camera parameter is the following :\n\
(C) (x,y,z coorinates) (x,y,z normalized orientation [-1->1]) (FOV [0 -> 180])"

# define PLANE_WAITED_VALUES	"\
Format for plane parameter is the following :\n\
(pl) (x,y,z point of plan coorinates) (x,y,z orientation [-1->1]) \
(r,g,b color [0->255])"

# define CYLINDER_WAITED_VALUES	"\
Format for cylinder parameter is the following :\n\
(cy) (x,y,z center coords.) (x,y,z orientation [-1->1]) (w,h dimensions [>0]) \
(r,g,b color [0->255])"

# define CONE_WAITED_VALUES	"\
Format for cone parameter is the following :\n\
(cy) (x,y,z center coords.) (x,y,z orientation [-1->1]) (w,h dimensions [>0]) \
(r,g,b color [0->255])"

# define SPHERE_WAITED_VALUES	"\
Format for sphere parameter is the following :\n\
(sp) (x,y,z center coorinates) (diameter) (r,g,b color [0->255])"

//SETS
# define SPLIT						" \t\n,"
# define STR_CHAR_MAX				"255"
# define STR_DOUBLE_MAX_20_FIRST	"17976931348623157000"

#endif
