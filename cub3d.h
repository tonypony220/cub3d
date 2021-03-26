/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:37:13 by mehtel            #+#    #+#             */
/*   Updated: 2021/03/23 21:39:24 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define BEHAVE_HARD 1
# define LEAKS 0

# include "mlx/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <errno.h>

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# define RED 	"\033[1;31m"
# define GREEN  	"\033[0;32m"
# define RESET  	"\033[0;0m"
# define BOLD   	"\033[;1m"
# define REVERSE "\033[;7m"

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 680
# define PI 3.1415926535
# define TEX_WIDTH 64
# define TEX_HEGHT 64

# define RESIZE 1

# define COM 3

# define X 0
# define Y 1
# define SIZE 2
# define RAD 3
# define ROTATE 4
# define W_BUTTON 13

# define A_BUTTON 0
# define S_BUTTON 1
# define D_BUTTON 2
# define ESC_BUTTON 53
# define LEFT_BUTTON 124
# define RIGHT_BUTTON 123

# define LEN_VAR_ARRAY 3
# define NUMBER_LINE_MAP_FROM 0
# define COUNTER 1
# define CURRENT_LEN 2
# define EMPTY_CHR '.'

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define S  4
# define F  5
# define C  6
# define R  7
# define NUM_PARAMS 8
# define NUM_MAP_PATHS 5

# define ERR_COLOR  (1 <<  0)
# define ERR_DBL    (1 << 1)
# define ERR_PARAM  (1 << 2)
# define ERR_FILE   (1 << 3)
# define ERR_NONE   (1 << 4)
# define ERR_PATH   (1 << 5)
# define ERR_RES    (1 << 6)
# define ERR_MALLOC (1 << 7)
# define ERR_RSPWN	(1 << 8)
# define ERR_MAP	(1 << 9)
# define ERR_TEX	(1 << 10)

typedef struct	s_sprite
{
	double		cord[2];
	int			tex_num;
}				t_sprite;

typedef struct	s_spr
{
	double		cr[2];
	double		transform[2];
	int			screen[2];
	int			height;
	int			width;
	int			draw[2][2];

}				t_spr;

typedef struct	s_map
{
	int			resolution_width;
	int			resolution_hight;
	int			respawn[2];
	int			path_provided;
	char		*texture_path[5];
	int			ceiling_color;
	int			floor_color;
	int			hight;
	int			width;
	int			sprite_counter;
	int			*sprites_order;
	float		*sprites_dist;
	t_sprite	*sprites;
	double		*zbuf;
	char		*map;
	char		*visited;
	char		respawns;
	int			invalid;
}				t_map;

typedef struct	s_data
{
	void		*img;
	char		*addr;
	void		*buffer;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			size[2];
}				t_data;

typedef struct	s_vars
{
	t_map		*map;
	void		*mlx;
	void		*win;
	t_data		*data;
	t_data		*texs[5];
	int			move;
	char		exit;
	char		save;
	double		player[5];
	char		btns[256];
	double		win_k;
}				t_vars;

typedef struct	s_ray
{
	double		dir[2];
	int			move[2];
	double		plane[2];
	double		on_map[2];
	double		ray_dir[2];
	double		ray_len[2];
	double		delta_len[2];
	double		perp;
	double		on_wall;
	int			tex[2];
	int			wall_reached;
	int			side;
	int			cur_tex;
}				t_ray;

typedef struct	s_params
{
	int			height;
	int			width;
	int			bpp;
}				t_params;

void			put_player(t_vars *vars);
int				render_next_frame(t_vars *vars);
t_map			*map_parser(char *filename, t_vars *vars);
int				create_trgb(int t, int r, int g, int b);
void			pixel_put(t_vars *vars, int x, int y, int color);
void			fill_half_screen(t_vars *vars, int which_half, int color);
int				load_texture(t_vars *vars, int num);
int				load_textures(t_vars *vars);
int				cub_exit(t_vars *vars, int exit_code);
void			find_x_texture_cord(t_ray *crds, t_vars *vars);
void			find_distanse_to_sprites(t_vars *vars);
void			selection_sorting_sprite(float arr_val[], int arr_pos[],
											int n);
void			project_sprites(t_vars *vars, t_ray *cd);
void			find_projection_size(t_vars *vars, t_spr *spr);
void			draw_sprite(t_vars *vars, t_spr *spr);
void			combinate_all_moves(char *move);
void			dfs(t_map *map, char *mv, int x, int y);
void			create_bmp_file(char *img, char *file, int size[], int bpp);
void			*free_map(t_map *map);
int				strchrs(char *str, char c);
int				only_symbols(char *symbols, char *line);
void			find_ray_dir_and_initial_len(t_vars *vars, t_ray *cords);
void			cast_ray(t_vars *vars, t_ray *cords);
void			init_player_screen(t_vars *vars, t_ray *cords);
void			init_ray(t_vars *vars, t_ray *cords, int x);
void			calculate_perp_dist(t_vars *vars, t_ray *cords);
int				get_pole_by_ray_dir(t_ray *cords);
void			put_textured_line(t_vars *vars, int line_len,
							t_ray *cords, int x);
void			moving(t_vars *vars);
int				release_hook(int button, t_vars *vars);
int				press_hook(int button, t_vars *vars);
int				mouse_hook(t_vars *vars);
int				parse_color(char *line, int i, t_map *map);
void			parse_line(char *line, t_map *map);
void			fill_map(t_map *map, char *line);
void			parse_map(char *filename, t_map *map, int *var);
void			wtf_it_must_be_done_that_way(char **tex_ids);
int				check_respawn(t_map *map);

# define KEYPRESS         2
# define KEYRELEASE       3
# define BUTTONPRESS      4
# define BUTTONRELEASE    5
# define MOTIONNOTIFY     6
# define ENTERNOTIFY      7
# define LEAVENOTIFY      8
# define FOCUSIN          9
# define FOCUSOUT         10
# define KEYMAPNOTIFY     11
# define EXPOSE           12
# define GRAPHICSEXPOSE   13
# define NOEXPOSE         14
# define VISIBILITYNOTIFY 15
# define CREATENOTIFY     16
# define DESTROY_NOTIF    17
# define UNMAPNOTIFY      18
# define MAPNOTIFY        19
# define MAPREQUEST       20
# define REPARENTNOTIFY   21
# define CONFIGURENOTIFY  22
# define CONFIGUREREQUEST 23
# define GRAVITYNOTIFY    24
# define RESIZEREQUEST    25
# define CIRCULATENOTIFY  26
# define CIRCULATEREQUEST 27
# define PROPERTYNOTIFY   28
# define SELECTIONCLEAR   29
# define SELECTIONREQUEST 30
# define SELECTIONNOTIFY  31
# define COLORMAPNOTIFY   32
# define CLIENTMESSAGE    33
# define MAPPINGNOTIFY    34
# define GENERICEVENT     35
# define LASTEVENT        36

# define NOEVENTMASK 0L
# define KEYPRESSMASK (1L<<0)
# define KEYRELEASEMASK (1L<<1)
# define BUTTONPRESSMASK (1L<<2)
# define BUTTONRELEASEMASK (1L<<3)
# define ENTERWINDOWMASK (1L<<4)
# define LEAVEWINDOWMASK (1L<<5)
# define POINTERMOTIONMASK (1L<<6)
# define POINTERMOTIONHINTMASK (1L<<7)
# define BUTTON1MOTIONMASK (1L<<8)
# define BUTTON2MOTIONMASK (1L<<9)
# define BUTTON3MOTIONMASK (1L<<10)
# define BUTTON4MOTIONMASK (1L<<11)
# define BUTTON5MOTIONMASK (1L<<12)
# define BUTTONMOTIONMASK (1L<<13)
# define KEYMAPSTATEMASK (1L<<14)
# define EXPOSUREMASK (1L<<15)
# define VISIBILITYCHANGEMASK (1L<<16)
# define STRUCTURENOTIFYMASK (1L<<17)
# define RESIZEREDIRECTMASK (1L<<18)
# define SUBSTRUCTURENOTIFYMASK (1L<<19)
# define SUBSTRUCTUREREDIRECTMASK (1L<<20)
# define FOCUSCHANGEMASK (1L<<21)
# define PROPERTYCHANGEMASK (1L<<22)
# define COLORMAPCHANGEMASK (1L<<23)
# define OWNERGRABBUTTONMASK (1L<<24)
#endif
