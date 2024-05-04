# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/07 17:14:16 by lejimene          #+#    #+#              #
#    Updated: 2024/05/04 19:36:59 by lejimene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS 		= -g
CFILES 		= $(SRC)/main.c \
		$(SRC)/image.c \
	 	$(SRC)/doors.c \
		$(SRC)/sprites.c \
		$(SRC)/parse_cub_file.c \
		$(SRC)/parse_map.c \
	 	$(SRC)/utils_parse_map.c \
	 	$(SRC)/utils_parse_map_2.c \
	 	$(SRC)/parse_textures.c \
		$(SRC)/minimap.c \
		$(SRC)/cast_rays.c \
		$(SRC)/draw.c \
		$(SRC)/key_events.c \
		$(SRC)/utils_textures.c \
		$(SRC)/utils_minimap.c \
		$(SRC)/utils_colors.c \
	 	$(SRC)/sprites_utils.c \
	 	$(SRC)/player_move.c \
	 	$(SRC)/initialize_params.c \
	 	$(SRC)/draw_doors.c
OFILES 		= $(CFILES:.c=.o)
NAME 		= cub3d
SRC 		= ./srcs
LIB 		= cub3d.a
HPATH 		= includes
MLXFLAGS	= -I ./includes/ -I ./mlx -I./libft -L./libft -ldl -lglfw -pthread -lm
LINUXFLAGS 	= -lXext -lX11 -lm
MACFLAGS	= -Lmlx -lmlx -framework OpenGL -framework AppKit 
MLX_PATH	= MLX42/build/
MLX_NAME	= libmlx42.a
MLX		= $(MLX_PATH)$(MLX_NAME)
LIBFT		= ./libft/libft.a

all : $(NAME)

$(NAME) : $(OFILES)
	@${CC} $^ -o $@ $(LIBFT) $(MLX) ${MLXFLAGS} ${LINUXFLAGS}
	@ar -r $(LIB) $(OFILES)

$(MAC) : $(OFILES)
	@${CC} $^ -o $@ $(LIBFT) $(MLX) ${MLXFLAGS} ${MACFLAGS}
	@ar -r $(LIB) $(OFILES)


$(SRC)/%.o: $(SRC)/%.c $(HPATH)/%.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf ${OFILES}

fclean : clean
	@rm ${NAME} $(LIB)

re : fclean all

linux :
	git clone git@github.com:42Paris/minilibx-linux.git mlx
	make -C mlx && make -C libft
	$(NAME)

mac :
	git clone git@github.com:dannywillems/minilibx-mac-osx.git mlx
	make -C mlx && make -C libft
	$(MAC)