NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -fPIE -fPIC

SRC_DIR := src
OBJ_DIR := obj
GNL_SRC_DIR := src/gnl_utils
GNL_OBJ_DIR := gnl_obj
PRINTF_SRC_DIR := src/printf_utils
PRINTF_OBJ_DIR := printf_obj


SOURCES = $(wildcard $(SRC_DIR)/*.c)
PRINTF_SOURCES = $(wildcard $(PRINTF_SRC_DIR)/*.c)
GNL_SOURCES = $(wildcard $(GNL_SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
PRINTF_OBJECTS = $(patsubst $(PRINTF_SRC_DIR)/%.c,$(PRINTF_OBJ_DIR)/%.o,$(PRINTF_SOURCES))
GNL_OBJECTS = $(patsubst $(GNL_SRC_DIR)/%.c,$(GNL_OBJ_DIR)/%.o,$(GNL_SOURCES))


all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(PRINTF_OBJ_DIR)/%.o: $(PRINTF_SRC_DIR)/%.c
	mkdir -p $(PRINTF_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(GNL_OBJ_DIR)/%.o: $(GNL_SRC_DIR)/%.c
	mkdir -p $(GNL_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(PRINTF_OBJECTS) $(GNL_OBJECTS)
	ar rcs $(NAME) $^

clean:
	rm -f $(OBJECTS) $(PRINTF_OBJECTS) $(GNL_OBJECTS)
	rm -rf $(OBJ_DIR)
	rm -rf $(PRINTF_OBJ_DIR)
	rm -rf $(GNL_OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re
