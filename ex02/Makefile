NAME = PmergeMe
CPP = c++
CPPFLAGS = -Wall -Werror -Wextra -MMD -std=c++20 -g

BUILD_DIR = build
SRC =	main.cpp \
		PmergeMe.cpp

OBJ = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC))
DEP = ${OBJ:.o=.d}

all: $(NAME)
	@printf "Compilation done👍\n"

$(NAME): $(OBJ) Makefile
	@printf "Compiling executable: $(NAME)\n"
	@$(CPP) $(CPPFLAGS) $(OBJ) -o $@

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	@printf "Compiling $@ \n"
	@$(CPP) $(CPPFLAGS) -c $< -o $@ -MF $(basename $@).d

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) --no-print-directory

$(BUILD_DIR):
	mkdir -p $@

-include $(DEP)

.PHONY:	clean fclean re all