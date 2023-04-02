/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combination.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:17:39 by tasano            #+#    #+#             */
/*   Updated: 2023/04/02 12:10:30 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef struct s_fcolor {
    double     red;
    double     green;
    double     blue;
}               t_fcolor;

typedef struct     s_material {
    double        kDif;      // 拡散反射係数  // これを物体の色とする
    double        kSpe;      // 鏡面反射係数
    float          shininess; // 光沢度
}                   t_material;

typedef struct s_object
{
	t_fcolor color;
	t_material material;
	t_vec3 vec;
	t_vec3 normal_vec;
	double diameter;
	double height;
	int	kind;
	int	cylinder_front_or_back;
} t_object;

typedef struct s_orthonormal {
	t_vec3	x_unit_vector;
	t_vec3	y_unit_vector;
} t_orthonormal;


t_fcolor		rgb_init(int r, int g, int b);
int				rgb_to_int(int r, int g, int b);
t_fcolor		add_color(t_fcolor c1, t_fcolor c2, double multi);
t_material		material_init(double kDif, double kSpe, double shininess);
void			get_t_value(t_vec3 start_vec, t_vec3 dir_vec, \
							t_object *object_list, double *t, int i);
int				deal_key(int key_code, t_game *game);
int				window_close(t_game *game);
int		main_loop(t_game *game);
