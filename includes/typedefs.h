/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:21:09 by bduval            #+#    #+#             */
/*   Updated: 2025/06/02 14:00:06 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

typedef struct s_quadratic
{
		double	a;
		double	b;
		double	c;
		double	delta;
		double	solution_1;
		double	solution_2;

}	t_quadratic;

typedef struct s_coord
{
	union
	{
		double	x;
		double	a;
		double	solution_1;
	};
	union
	{
		double	y;
		double	b;
		double	solution_2;
	};
	union
	{
		double	z;
		double	c;
	};
	union
	{
		double	delta;
		double	norm;
	};
}	t_coord;

typedef struct s_color
{
	union
	{
		int32_t	argb;
		struct
		{
			uint8_t	a;
			uint8_t	r;
			uint8_t	g;
			uint8_t	b;
		};
	};
}	t_color;

typedef t_coord			t_vector;
typedef t_coord			t_point;

typedef struct s_obj	t_obj;
typedef t_obj			t_light;
typedef t_obj			t_cam;
//typedef t_point			(*t_collision_fn)(t_obj*, t_ray*);
//typedef t_vector		(*t_normal_fn)(t_obj*, t_ray*);

typedef struct s_ray
{
	t_point		start;
	t_vector	direction;
	t_vector	bump;
	t_vector	normal;
	t_color		color;
	double		shortest_impact_dist;
	double		direct_light;
	double		specular_light;
	t_obj		*impact_object;
}	t_ray;

// objects in scene: | A | C | L | sp| pl| cy|
// -----------------------------------------------
// | pos             |   | x | x | x | x | x |
// | orientation     |   | x |   |   | x | x |
// | diameter        |   |   |   | x |   | x | 1 union
// | ratio           | x |   |   |   |   |   | 1
// | height          |   |   |   |   |   | x | 2 union
// | radius          |   |   |   |   | x |   | 2 union
// | brightness      |   |   | x |   |   |   | 2
// | fov             |   | x |   |   |   |   | 2
// | color           | x |   | x | x | x | x |
typedef struct s_obj
{
	char			type;
	t_coord			pos;
	union
	{
		t_vector		orientation;
		t_vector		forward;
	};
	t_color			color;
	union
	{
		double		diameter;
		double		ratio;
	};
	union
	{
		double		height;
		double		radius;
		double		brightness;
		double		fov;
	};
	t_obj			*next;
	int				(*collision_fn)(t_obj *, t_ray *);
	t_vector		(*normal_fn)(t_obj *obj, t_point p);
		double			fov_scale;
	union
	{
		double			aspect_ratio;
		double			reflection;
	};
	t_vector		right;
	t_vector		up;
}	t_obj;

typedef struct s_scene
{
	t_obj		*obj;
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
	t_scene	scene;
}	t_all;

#endif
