/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:21:09 by bduval            #+#    #+#             */
/*   Updated: 2025/05/22 23:37:49 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

typedef struct s_coord
{
	double	x;
	double	y;
	double	z;
}	t_coord;

typedef t_coord			t_vector;
typedef t_coord			t_point;

typedef struct s_ray
{
	t_point		start;
	t_vector	direction;
}	t_ray;

typedef struct s_obj	t_obj;
typedef t_obj			t_cam;
typedef t_obj			t_light;
typedef t_point			(*t_collision_fn)(t_obj*, t_ray*);
typedef t_vector		(*t_normal_fn)(t_obj*, t_ray*);

// objects in scene: | A | C | L | sp| pl| cy|
// -----------------------------------------------
// | pos             |   | x | x | x | x | x |
// | orientation     |   | x |   |   | x | x | 
// | diameter        |   |   |   | x |   | x | 1 union
// | ratio           | x |   |   |   |   |   | 1
// | height          |   |   |   |   |   | x | 2 union
// | brightness      |   |   | x |   |   |   | 2
// | fov             |   | x |   |   |   |   | 2
// | color           | x |   | x | x | x | x |
typedef struct s_obj
{
	char			type;
	t_coord			pos;
	t_vector		orientation;
	union
	{
		int			color;
		struct
		{
			uint8_t	r;
			uint8_t	g;
			uint8_t	b;
		};
	};
	union
	{
		double		diameter;
		double		ratio;
	};
	union
	{
		double		height;
		double		brightness;
		double		fov;
	};
	t_obj			*next;
	t_collision_fn	*collision_fn;
	t_normal_fn		*normal_fn;
}	t_obj;

typedef struct s_scene
{
	t_obj		*objs;
	t_cam		*cam;
	t_light		*amb_light;
	t_light		*light;
	t_obj		*selected;
}	t_scene;

typedef struct s_all
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*img;
	t_obj	scene;
}	t_all;

#endif
