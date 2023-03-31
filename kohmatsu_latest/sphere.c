#include "./libft.h"
#include "./get_next_line.h"
#include "./mlx/mlx.h"
#include <math.h>
#include <stdio.h>

#define WIDTH 512
#define HEIGHT 512
#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_EXIT		17
#define KEY_ESC			53
// # define KEY_W			13
// # define KEY_A			0
// # define KEY_S			1
// # define KEY_D			2

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
int	rgb_to_int(int r, int g, int b)//rgbを16進数のやつに変化(R, G, B) = (255, 0, 0)ならば0xFF0000(256*256*255 + 256 * 0 + 0)へ
{
	return ((int)(r * pow(256, 2) + g * 256 + b));
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

int		main_loop(t_game *game)
{
	t_vec3 camera_vec = vec3_init(0, 0, -5); //視点位置のベクトル
	t_vec3 sphere_vec = vec3_init(0, 0, 5); //球の中心座標
	double sphere_r = 1.0; //球の半径
	t_vec3 light_vec = vec3_init(-5, -5, -5); //光源の位置ベクトル
	double light_power = 1.0;
	double ambient_power = 0.1;
	t_material material = material_init(0.69, 0.3, 8);

	for (double y = 0; y < HEIGHT; y++)
	{
		for (double x = 0; x < WIDTH; x++)
		{
			t_vec3 screen_vec = vec3_init(2 * x / WIDTH - 1.0, 2 * y / HEIGHT - 1.0, 0); //スクリーン上の点の三次元空間におけるベクトル
			t_vec3 dir_vec = vec3_normalize(vec3_sub(screen_vec, camera_vec)); //方向ベクトル(視線ベクトル)

			//球を描画
			t_vec3 camera2sphere_vec = vec3_sub(camera_vec, sphere_vec); //カメラから球へのベクトル

			double a = vec3_mag(dir_vec) * vec3_mag(dir_vec);
            double b = 2 * vec3_dot(camera2sphere_vec, dir_vec);
            double c = vec3_dot(camera2sphere_vec, camera2sphere_vec) - sphere_r * sphere_r;
			double t;//媒介変数
            // 判別式
			double D = b * b - 4 * a * c;
			if (D >= 0)
			{
				//拡散反射
				if (D == 0) //接する時
					t = -b / (2 * a);//媒介変数tの長さ
				else if (D > 0) //交わる時
				{
					double t1 = (-b + sqrt(D)) / (2 * a);
					double t2 = (-b - sqrt(D)) / (2 * a);
					if (t1 > 0 && t2 > 0) //両方正なら小さい方をtとする。
					{
						if (t1 > t2)
							t = t2;
						else
							t = t1;
					}
					else//片方正なら、それをtとする。
					{
						if (t1 > 0)
							t = t1;
						else
							t = t2;
					}
				}
				t_vec3 crosspoint_vec = vec3_add(camera_vec, vec3_mul(dir_vec, t));//視線と物体の交点の位置ベクトル
				t_vec3 incident_vec = vec3_normalize(vec3_sub(light_vec, crosspoint_vec));//入射ベクトル(入射って言ってるけど、向きに注意)
				t_vec3 normal_vec = vec3_normalize(vec3_sub(crosspoint_vec, sphere_vec));//法線ベクトル
				double dot_1;
				if (vec3_dot(incident_vec, normal_vec) < 0)
					dot_1 = 0;
				else
					dot_1 = vec3_dot(incident_vec, normal_vec);
				double diffusion = dot_1 * light_power * material.kDif;

				// 鏡面反射
				t_vec3 reverse_dir_vec = vec3_normalize(vec3_mul(dir_vec, -1));//視線ベクトルの逆向き
				t_vec3 regular_reflection_vec = vec3_normalize(vec3_sub(vec3_mul(vec3_mul(normal_vec, vec3_dot(incident_vec, normal_vec)), 2), incident_vec));
				double dot_2;
				if (vec3_dot(reverse_dir_vec, regular_reflection_vec) < 0)
					dot_2 = 0;
				else
					dot_2 = vec3_dot(reverse_dir_vec, regular_reflection_vec);
				double specular = pow(dot_2, material.shininess) * light_power * material.kSpe;
				// ambient_power = 0;
				// double specular = 0;

				int R = (int)(255 * (diffusion + specular) + ambient_power);
				int G = (int)(255 * (diffusion + specular) + ambient_power);
				int B = (int)(255 * (diffusion + specular) + ambient_power);
				mlx_pixel_put(game->mlx, game->win, x, y, rgb_to_int(R, G, B));
			}
            else
            {
               mlx_pixel_put(game->mlx, game->win, x, y, rgb_to_int(100, 149, 237));//いい感じの青
            }
		}
	}
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

// #include <stdio.h>
// int main(void)
// {
// 	t_vec3 tmp;

// 	tmp = vec3_init(2, 1, 2);
// 	t_vec3 ret = vec3_normalize(tmp);
// 	printf("x: %f\n", ret.x);
// 	printf("y: %f\n", ret.y);
// 	printf("z: %f\n", ret.z);
// 	return (0);
// }