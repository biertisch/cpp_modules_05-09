NAME		=	bureaucrat

SRC			=	main.cpp Bureaucrat.cpp

OBJ_DIR		=	obj/
OBJ			=	$(patsubst %.cpp, $(OBJ_DIR)%.o, $(SRC))
DEP			=	$(patsubst %.cpp, $(OBJ_DIR)%.d, $(SRC))

CXX			=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -g -std=c++98 -MMD -MP
VAL			=	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s
RM			=	rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking executable..."
	@$(CXX) $^ -o $@
	@echo "$(NAME) built!"

$(OBJ_DIR)%.o: %.cpp | $(OBJ_DIR)
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
	@echo "Removing executable..."
	@$(RM) $(NAME)

re: fclean all

.PHONY: all run val clean fclean re

-include $(DEP)