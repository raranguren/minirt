/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:47:32 by bduval            #+#    #+#             */
/*   Updated: 2025/06/19 16:03:12 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

//# define ERROR(msg) error(msg)
//# define PERROR(msg) print_error(msg, __FILE__, __LINE__, __func__)
//# define PERROR2(msg1, msg2) print_error2(msg1, msg2,  __FILE__, __LINE__)

//# define ICI	printf("ICI\n");

# ifndef BONUS
#  define BONUS 0
# endif

// Screen dimensions
# define WIN_WIDTH		720
# define WIN_HEIGHT		720

// Interface
# define TEXT_FONT "-misc-fixed-medium-r-normal--20-200-75-75-c-100-iso10646-1"
# define TEXT_COLOR	0xaaaaaa
# define UI_WIDTH		360
# define MARGIN_LEFT	38
# define MARGIN_TOP	372
# define COL_WIDTH	100
# define ROW_HEIGHT	78

// Refraction indice for specular light
#define REFRACT	10000

// Error tolerance
# define EPSLN	2e-2

// Background
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
# define CAMERA_BG		"ui_textures/ui_camera.xpm"
# define LIGHT_BG		"ui_textures/ui_light.xpm"
# define AMB_LIGHT_BG	"ui_textures/ui_amb_light.xpm"
# define SPHERE_BG		"ui_textures/ui_sphere.xpm"
# define PLANE_BG		"ui_textures/ui_plane.xpm"
# define CYLINDER_BG	"ui_textures/ui_cylinder.xpm"
# define CONE_BG		"ui_textures/ui_cone.xpm"

//Welcome messages

# define WELCOME_MESSAGE "\
miniRT by bduval & rarangur - mandatory version\n\
"

# define BONUS_WELCOME_MESSAGE "\
miniRT by bduval & rarangur - BONUS version\n\
  - full Phong reflection\n\
  - color disruption: checkerboard pattern ('#' after the color of shapes)\n\
  - colored multi-spot lights (can have more than one 'C' in the .rt file)\n\
  - bump maps textures (add the .xpm file name after the color of a shape)\n\
"

//Error messages
# define ERROR_ARGUMENTS	"\
Usage : ./miniRT[_bonus] <filename.rt>\n\
        ./miniRT[_bonus] -h"

# define AMB_LIGHT_WAITED_VALUES	"\
Syntax for ambient light :\n\
(A) (brightness ratio [0->1]) (r,g,b color [0->255])\n\
\n\
Example :\n\
A   0.2 255,255,255"

# define LIGHT_WAITED_VALUES	"\
Syntax for light :\n\
(L) (x,y,z coordinates) (rightness ratio [0->1]) (r,g,b color [0->255])\n\
\n\
Example :\n\
L   134.59,75.13,41.62  0.7 255,255,255"

# define CAM_WAITED_VALUES	"\
Syntax for camera :\n\
(C) (x,y,z coordinates) (x,y,z normalized orientation [-1->1]) \
(FOV [0 -> 180])\n\
(FOV values between 60 and 75 recommended)\n\
\n\
Example :\n\
C   87.94,0,-3.93   -0.99,0,0.17    70"

# define PLANE_WAITED_VALUES	"\
Syntax for plane :\n\
(pl) (x,y,z point of plane coordinates) (x,y,z orientation [-1->1]) \
(r,g,b color [0->255])\n\
\n\
Example :\n\
pl  0,-60,0 0,1,0   255,0,225"

# define CYLINDER_WAITED_VALUES	"\
Syntax for cylinder :\n\
(cy) (x,y,z center coords.) (x,y,z orientation [-1->1]) (w,h dimensions [>0]) \
(r,g,b color [0->255])\n\
\n\
Example :\n\
cy  -0.42,0,28.2    0,0,1   14.2    21.42   10,0,255"

# define CONE_WAITED_VALUES	"\
Syntax for cone (_bonus only):\n\
(co) (x,y,z center coords.) (x,y,z orientation [-1->1]) (w,h dimensions [>0]) \
(r,g,b color [0->255])\n\
\n\
Example :\n\
co  -0.42,0,28.2   0,0,1  14.2    21.42   10,255,40"

# define SPHERE_WAITED_VALUES	"\
Syntax for sphere :\n\
(sp) (x,y,z center coords.) (diameter) (r,g,b color [0->255])\n\
\n\
Example :\n\
sp  6,0,7.19    20  255,0,0"

# define BONUS_WAITED_VALUES	"\n\
Optional parameters (_bonus only):\n\
Add # after the shape color (r,g,b) to use color disruption (checkered)\n\
Or add the path to a .xpm file to use as bump map\n"

//SETS
# define SPLIT						" \t\n,"

#endif
