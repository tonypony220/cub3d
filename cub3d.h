#ifndef CUB3D_H
# define CUB3D_H

#define BEHAVE_HARD 1
#define LEAKS 0

#include "mlx/mlx.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"
#include <errno.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define RED 	"\033[1;31m"
#define GREEN  	"\033[0;32m"
#define RESET  	"\033[0;0m"
#define BOLD   	"\033[;1m"
#define REVERSE "\033[;7m"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 680
#define PI 3.1415926535
#define TEX_WIDTH 64
#define TEX_HEGHT 64

#define RESIZE 1

#define X 0
#define Y 1
#define SIZE 2
#define RAD 3
#define ROTATE 4

#define W_BUTTON 13
#define A_BUTTON 0
#define S_BUTTON 1
#define D_BUTTON 2
#define ESC_BUTTON 53
#define LEFT_BUTTON 124
#define RIGHT_BUTTON 123

#define LEN_VAR_ARRAY 3
#define NUMBER_LINE_MAP_FROM 0
#define COUNTER 1
#define CURRENT_LEN 2
#define EMPTY_CHR '.'

#define NO 0
#define SO 1
#define WE 2
#define EA 3
#define S  4
#define F  5
#define C  6
#define NUM_PARAMS 7
#define NUM_MAP_PATHS 5

typedef struct  s_sprite
{
	double		cord[2];
	int 		tex_num;
}               t_sprite;

typedef struct  s_spr
{
	double		cr[2];
	double		transform[2];
	int			screen[2];
	int 		height;
	int 		width;
	int			draw[2][2];

}               t_spr;

typedef struct  s_map
{
	int 		resolution_width;
	int 		resolution_hight;
	int 		respawn[2];
	int			path_provided;
	char		*texture_path[5];
	int			ceiling_color;
	int			floor_color;
	int			hight;
	int         width;
	int			sprite_counter;
	int			*sprites_order;
	float 		*sprites_dist;
	t_sprite	*sprites;
	double		*zbuf;
	char        *map;
	char		*visited;
	int			respawns;
	char		invalid;
}               t_map;

typedef struct  s_data
{
	void        *img;
	char        *addr;
	void		*buffer;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
	int			size[2];
}               t_data;


typedef struct  s_vars
{
	t_map		*map;
	void        *mlx;
	void        *win;
	t_data		*data;
	t_data		*texs[5];
	int			move;
	char		exit;
	char		save;
	double		player[5];
	char		btns[256];
	double 		win_k;
}               t_vars;

typedef struct  s_ray
{
	double		dir[2];
	int			move[2];
	double		plane[2];
	double 		on_map[2];
	double		ray_dir[2];
	double 		ray_len[2];
	double 		delta_len[2];
	double 		perpWallDist;
	double		on_wall;
	int			tex[2];
	int			wall_reached;
	int			side;
	int			cur_tex;
}               t_ray;

typedef struct  s_params
{
	int		height;
	int		width;
	int		bpp;

}               t_params;

void			put_player(t_vars *vars);
int     		render_next_frame(t_vars *vars);
t_map			*map_parser(char *filename);
int				create_trgb(int t, int r, int g, int b);
void        	pixel_put(t_vars *vars, int x, int y, int color);
void			fill_half_screen(t_vars *vars, int which_half, int color);

int 			load_texture(t_vars *vars, int num);
int				load_textures(t_vars *vars);
int				cub_exit(t_vars *vars, int exit_code);
void			find_x_texture_cord(t_ray *crds, t_vars *vars);
void			find_distanse_to_sprites(t_vars *vars);
void			selection_sorting_sprite(float arr_val[], int arr_pos[],
											int n);
void			project_sprites(t_vars *vars, t_ray *cd);
void			find_projection_size(t_vars *vars, t_spr *spr);
void			draw_sprite(t_vars *vars, t_spr *spr);
void 			combinate_all_moves(char *move);
void			dfs(t_map *map, char *mv, int x, int y);
void			create_bmp_file(char *img, char *file, int size[], int bpp);
void			*free_map(t_map *map);
int				strchrs(char *str, char c);
int				only_symbols(char *symbols, char *line);
void			find_ray_dir_and_initial_len(t_vars *vars, t_ray *cords);
void 			cast_ray(t_vars *vars, t_ray *cords);
void			init_player_screen(t_vars *vars, t_ray *cords);
void			init_ray(t_vars *vars, t_ray *cords, int x);
void			calculate_perp_dist(t_vars *vars, t_ray *cords);
int				get_pole_by_ray_dir(t_ray *cords);
void			put_textured_line(t_vars *vars, int line_len,
								  t_ray *cords, int x);
void			moving(t_vars *vars);
int             release_hook(int button, t_vars *vars);
int   			press_hook(int button, t_vars *vars);
int				mouse_hook(t_vars *vars);
int				parse_color(char* line, int i, t_map *map);
void			parse_line(char *line,  t_map *map);
void 			fill_map(t_map *map, char *line);
void			parse_map(char *filename, t_map *map, int *var);
void			wtf_it_must_be_done_that_way(char **tex_ids);

void			parse_resolution(char *p, t_map *map);
#define  keyPress         2
#define  keyRelease       3
#define  buttonPress      4
#define  buttonRelease    5
#define  motionNotify     6
#define  enterNotify      7
#define  leaveNotify      8
#define  focusIn          9
#define  focusOut         10
#define  keymapNotify     11
#define  expose           12
#define  graphicsExpose   13
#define  noExpose         14
#define  visibilityNotify 15
#define  createNotify     16
#define  destroyNotify    17
#define  unmapNotify      18
#define  mapNotify        19
#define  MapRequest       20
#define  ReparentNotify   21
#define  ConfigureNotify  22
#define  ConfigureRequest 23
#define  GravityNotify    24
#define  ResizeRequest    25
#define  CirculateNotify  26
#define  CirculateRequest 27
#define  PropertyNotify   28
#define  SelectionClear   29
#define  SelectionRequest 30
#define  SelectionNotify  31
#define  ColormapNotify   32
#define  ClientMessage    33
#define  MappingNotify    34
#define  GenericEvent     35
#define  LASTEvent        36

# define NoEventMask 0L
# define KeyPressMask (1L<<0)
# define KeyReleaseMask (1L<<1)
# define ButtonPressMask (1L<<2)
# define ButtonReleaseMask (1L<<3)
# define EnterWindowMask (1L<<4)
# define LeaveWindowMask (1L<<5)
# define PointerMotionMask (1L<<6)
# define PointerMotionHintMask (1L<<7)
# define Button1MotionMask (1L<<8)
# define Button2MotionMask (1L<<9)
# define Button3MotionMask (1L<<10)
# define Button4MotionMask (1L<<11)
# define Button5MotionMask (1L<<12)
# define ButtonMotionMask (1L<<13)
# define KeymapStateMask (1L<<14)
# define ExposureMask (1L<<15)
# define VisibilityChangeMask (1L<<16)
# define StructureNotifyMask (1L<<17)
# define ResizeRedirectMask (1L<<18)
# define SubstructureNotifyMask (1L<<19)
# define SubstructureRedirectMask (1L<<20)
# define FocusChangeMask (1L<<21)
# define PropertyChangeMask (1L<<22)
# define ColormapChangeMask (1L<<23)
# define OwnerGrabButtonMask (1L<<24)

#endif
