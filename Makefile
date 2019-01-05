NAME = ft_ssl

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MFLAGS = -lft

INCLUDE_DIR = ./includes

DIR_OBJ = ./obj/

DIR_LIB = ./libft/

SRC_DIR = ./srcs/

MAIN =	main.c \
		md5.c \
		treat_data.c \
		get_stdin.c \
		display.c \
		sha256.c \
		fill_data.c \
		sha224.c \
		sha512.c \
		sha384.c \
		sha512_256.c \
		sha512_224.c \
		fill_data_64.c \
		utils.c

FILES = get_params.c

SRCS = $(addprefix $(SRC_DIR), $(FILES)) $(addprefix $(SRC_DIR), $(MAIN))

OBJS = $(patsubst %.c, $(DIR_OBJ)%.o, $(FILES)) $(patsubst %.c, $(DIR_OBJ)%.o, $(MAIN))

DEP_OBJ = src_msg \
		  $(OBJS)

RM = /bin/rm -rf

all: mkdirobj $(DEP_OBJ)
		@ make -C $(DIR_LIB)
		@ /bin/echo -n "Archiving object in $(NAME):"
		@ $(CC) -o $(NAME) $(OBJS) $(MFLAGS) -L $(DIR_LIB) #-fsanitize=address
		@ echo " \033[32mAll done!\033[0m"

$(DIR_OBJ)%.o: $(SRC_DIR)%.c
	@ /bin/echo -n "    $(notdir $@)"
	@ $(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE_DIR)
	@ echo " \033[32mOK\033[0m"

mkdirobj:
	@ mkdir -p $(DIR_OBJ)

clean:
	@ make clean -C $(DIR_LIB)
	@ /bin/echo -n "Removing object files:"
	@ $(RM) $(DIR_OBJ)
	@ echo " \033[32mdone\033[0m"

fclean: clean
	@ make fclean -C $(DIR_LIB)
	@ /bin/echo -n "Removing library:"
	@ $(RM) $(NAME)
	@ $(RM) $(NAME).dSYM
	@ echo " \033[32mdone\033[0m"

re: fclean all

src_msg:
	@ echo " src functions:"

debug: mkdirobj $(DEP_OBJ)
		@ make -C $(DIR_LIB)
		@ /bin/echo -n "Archiving object in $(NAME):"
		@ $(CC) $(CFLAGS) $(SRCS) -I$(INCLUDE_DIR) -o $(NAME) -L $(DIR_LIB) -l ft -g
		@ echo " \033[32mAll done!\033[0m"

.PHONY : all clean fclean re mkdirobj src_msg debug
