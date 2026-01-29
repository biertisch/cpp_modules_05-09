NAME		=	convert

SRC_FILES	=	main ScalarConverter

SRC_DIR		=	src/
OBJ_DIR		=	obj/
INC_DIR		=	include/

SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEP			=	$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

CXX			=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -g -std=c++98 -MMD -MP -I$(INC_DIR)
VAL			=	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=yes
RM			=	rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking executable..."
	@$(CXX) $^ -o $@
	@echo "$(NAME) built!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp | $(OBJ_DIR)
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

run: all
	./$(NAME)

val: all
	$(VAL) ./$(NAME)

clean:
	@echo "Removing object files..."
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "Removing executable and shrubbery..."
	@$(RM) $(NAME) *_shrubbery

re: fclean all

.PHONY: all run val clean fclean re

-include $(DEP)