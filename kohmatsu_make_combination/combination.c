#include "./libft.h"
#include "./get_next_line.h"
#include "./mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>

#define WIDTH 512
#define HEIGHT 512
#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_EXIT		17
#define KEY_ESC			53

#define NUMBER 6

#define SPHERE 1
#define PLAIN 2
#define CYLINDER 3

typedef struct	s_game
{
	void	*mlx;
	void	*win;
}				t_game;

typedef struct    s_vec3
{
    double     x;
    double     y;
    double     z;
} t_vec3;

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
	int	kind;
} t_object;

//mlx系
int		deal_key(int key_code, t_game *game)
{
	if (key_code == KEY_ESC)
		exit(0);
	return (0);
}

int 	window_close(t_game *game)
{
		exit(0);
}

//ベクトル演算系
t_vec3	vec3_init(double x, double y , double z)
{
	t_vec3 new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 ret;
	ret.x = vec1.x + vec2.x;
	ret.y = vec1.y + vec2.y;
	ret.z = vec1.z + vec2.z;
	return (ret);
}

t_vec3	vec3_sub(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 ret;
	ret.x = vec1.x - vec2.x;
	ret.y = vec1.y - vec2.y;
	ret.z = vec1.z - vec2.z;
	return (ret);
}

double	vec3_mag(t_vec3 vec)//ベクトルの大きさ
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3	vec3_normalize(t_vec3 vec)//ベクトルを正規化
{
	double bunbo;
	t_vec3 ret;

	bunbo = vec3_mag(vec);
	ret.x = vec.x / bunbo;
	ret.y = vec.y / bunbo;
	ret.z = vec.z / bunbo;
	return (ret);
}

t_vec3	vec3_mul(t_vec3 vec, double scalar)
{
	t_vec3 ret;

	ret.x = scalar * vec.x;
	ret.y = scalar * vec.y;
	ret.z = scalar * vec.z;
	return (ret);
}

double	vec3_dot(t_vec3 vec1, t_vec3 vec2)//内積
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

//色系
t_fcolor	rgb_init(int r, int g, int b)
{
	t_fcolor ret;

	ret.red = r;
	ret.green = g;
	ret.blue = b;
	return (ret);
}

int	rgb_to_int(int r, int g, int b)//rgbを16進数のやつに変化(R, G, B) = (255, 0, 0)ならば0xFF0000(256*256*255 + 256 * 0 + 0)へ
{
	return ((int)(r * pow(256, 2) + g * pow(256, 1) + b));
}

//material系
t_material material_init(double kDif, double kSpe, double shininess)
{
	t_material ret;

	ret.kDif = kDif;
	ret.kSpe = kSpe;
	ret.shininess = shininess;
	return (ret);
}

void	get_t_value(t_vec3 start_vec, t_vec3 dir_vec, t_object *object_list, double *t, int i)//交差判定
{
	if (object_list[i].kind == SPHERE)
	{
		t_vec3 camera2sphere_vec = vec3_sub(start_vec, object_list[i].vec); //カメラから球へのベクトル
		double a = vec3_mag(dir_vec) * vec3_mag(dir_vec);
		double b = 2 * vec3_dot(camera2sphere_vec, dir_vec);
		double c = vec3_dot(camera2sphere_vec, camera2sphere_vec) - object_list[i].diameter * object_list[i].diameter;
		double t1, t2;
		// 判別式
		double D = b * b - 4 * a * c;
		if (D >= 0)
		{
			//交差判定
			if (D == 0) //接する時
				t[i] = -b / (2 * a);//媒介変数tの長さ
			else if (D > 0) //交わる時
			{
				t1 = (-b + sqrt(D)) / (2 * a);
				t2 = (-b - sqrt(D)) / (2 * a);
				if (t1 > 0 && t2 > 0) //両方正なら小さい方をtとする。
				{
					if (t1 > t2)
						t[i] = t2;
					else
						t[i] = t1;
				}
				else//片方正なら、それをtとする。
				{
					if (t1 > 0)
						t[i] = t1;
					else
						t[i] = t2;
				}
			}
		}
		else
			t[i] = 0;
	}
	else if (object_list[i].kind == PLAIN)
	{
		if (vec3_dot(dir_vec, object_list[i].normal_vec) == 0)
			t[i] = 0;
		else if (vec3_dot(vec3_sub(object_list[i].vec, start_vec), object_list[i].normal_vec) / vec3_dot(dir_vec, object_list[i].normal_vec) < 0)
			t[i] = 0;
		else
			t[i] = (vec3_dot(vec3_sub(object_list[i].vec, start_vec), object_list[i].normal_vec) / vec3_dot(dir_vec, object_list[i].normal_vec));
	}
}

int	get_min_index(double *t, int number)
{
	int i;
	double min;
	int min_index;

	for(i = 0; i < number; i++)
	{
		if (t[i] != 0)
		{
			min = t[i];
			min_index = i;
			break ;
		}
		min = 0;
		min_index = 0;
	}
	if (min != 0)
	{
		for(i = 0; i < number; i++)
		{
			if (t[i] < min && t[i] != 0)
			{
				min = t[i];
				min_index = i;
			}
		}
	}
	return (min_index);
}

void	my_put_pixel(t_vec3 camera_vec, t_vec3 dir_vec, t_vec3 light_vec, t_object *object_list, double *t,
			int i, double light_power, double ambient_power, t_game *game, double x, double y)
{
	//拡散反射
	t_vec3 crosspoint_vec = vec3_add(camera_vec, vec3_mul(dir_vec, t[i]));//視線と物体の交点の位置ベクトル
	t_vec3 incident_vec = vec3_normalize(vec3_sub(light_vec, crosspoint_vec));//入射ベクトル(入射って言ってるけど、向きに注意)
	if (object_list[i].kind == SPHERE)
		object_list[i].normal_vec = vec3_normalize(vec3_sub(crosspoint_vec, object_list[i].vec));//法線ベクトル
	double dot_1;
	if (vec3_dot(incident_vec, object_list[i].normal_vec) < 0)
		dot_1 = 0;
	else
		dot_1 = vec3_dot(incident_vec, object_list[i].normal_vec);
	double diffusion = dot_1 * light_power * object_list[i].material.kDif;

	// 鏡面反射
	t_vec3 reverse_dir_vec = vec3_normalize(vec3_mul(dir_vec, -1));//視線ベクトルの逆向き
	t_vec3 regular_reflection_vec = vec3_normalize(vec3_sub(vec3_mul(vec3_mul(object_list[i].normal_vec, vec3_dot(incident_vec, object_list[i].normal_vec)), 2), incident_vec));
	double dot_2;
	if (vec3_dot(reverse_dir_vec, regular_reflection_vec) < 0)
		dot_2 = 0;
	else
		dot_2 = vec3_dot(reverse_dir_vec, regular_reflection_vec);
	double specular = pow(dot_2, object_list[i].material.shininess) * light_power * object_list[i].material.kSpe;

	int R = (int)(object_list[i].color.red * (diffusion + specular) + ambient_power);
	int G = (int)(object_list[i].color.green * (diffusion + specular) + ambient_power);
	int B = (int)(object_list[i].color.blue * (diffusion + specular) + ambient_power);
	if (t[i] > 0)
		mlx_pixel_put(game->mlx, game->win, x, y, rgb_to_int(R, G, B));
	else
		mlx_pixel_put(game->mlx, game->win, x, y, rgb_to_int(100, 149, 237));//いい感じの青
}

int		main_loop(t_game *game)
{
	double epsilon = 1.0 / 512; //微小距離
	t_vec3 camera_vec = vec3_init(0, 0, -5); //視点位置のベクトル
	double light_power = 1.0;
	double ambient_power = 0.1;
	t_vec3 light_vec = vec3_init(-5, -5, -5); //光源の位置ベクトル
	t_object *object_list = (t_object *)malloc(sizeof(t_object) * NUMBER);
	//1個目の球
	object_list[0].vec = vec3_init(-1, 0, 5); //球の中心座標
	object_list[0].diameter = 1.0; //球の直径
	object_list[0].color = rgb_init(255, 0, 0);
	object_list[0].material = material_init(0.69, 0.3, 8);
	object_list[0].kind = SPHERE;

	//2個目の球
	object_list[1].vec = vec3_init(0, 0, 10); //球の中心座標
	object_list[1].diameter = 1.0; //球の直径
	object_list[1].color = rgb_init(0, 255, 0);
	object_list[1].material = material_init(0.69, 0.3, 8);
	object_list[1].kind = SPHERE;

	//3個目の球
	object_list[2].vec = vec3_init(1, 0, 15); //球の中心座標
	object_list[2].diameter = 1.0; //球の直径
	object_list[2].color = rgb_init(0, 0, 255);
	object_list[2].material = material_init(0.69, 0.3, 8);
	object_list[2].kind = SPHERE;

	//4個目の球
	object_list[3].vec = vec3_init(2, 0, 20); //球の中心座標
	object_list[3].diameter = 1.0; //球の直径
	object_list[3].color = rgb_init(255, 0, 255);
	object_list[3].material = material_init(0.69, 0.3, 8);
	object_list[3].kind = SPHERE;

	//5個目の球
	object_list[4].vec = vec3_init(3, 0, 25); //球の中心座標
	object_list[4].diameter = 1.0; //球の直径
	object_list[4].color = rgb_init(255, 255, 0);
	object_list[4].material = material_init(0.69, 0.3, 8);
	object_list[4].kind = SPHERE;

	//平面
	object_list[5].vec = vec3_init(0, 1, 0);
	object_list[5].color = rgb_init(0, 255, 255);
	object_list[5].material = material_init(0.69, 0.3, 8);
	object_list[5].normal_vec = vec3_init(0, -1, 0);
	object_list[5].kind = PLAIN;

	int i;
	int min_index;
	for (double y = 0; y < HEIGHT; y++)
	{
		for (double x = 0; x < WIDTH; x++)
		{
			double *t = (double *)malloc(sizeof(double) * NUMBER);
			t_vec3 screen_vec = vec3_init(2 * x / WIDTH - 1.0, 2 * y / HEIGHT - 1.0, 0); //スクリーン上の点の三次元空間におけるベクトル
			t_vec3 dir_vec = vec3_normalize(vec3_sub(screen_vec, camera_vec)); //方向ベクトル(視線ベクトル)

			for (i = 0; i < NUMBER; i++)
				get_t_value(camera_vec, dir_vec, object_list, t, i);
			min_index = get_min_index(t, NUMBER);
			my_put_pixel(camera_vec, dir_vec, light_vec, object_list, t, min_index, light_power, ambient_power, game, x, y);
			free(t);
		}
	}
	free(object_list);
	return (0);
}

int main(void)
{
	t_game game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "mlx 42");
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 1, &deal_key, &game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 1, &window_close, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
}
