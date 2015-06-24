##
## Makefile for  in /home/dumont_p/rendu/cpp_bomberman
##
## Made by _p dumont
## Login   <dumont_p@epitech.net>
##
## Started on  Tue Apr 14 13:33:57 2015 _p dumont
## Last update Sun Jun 14 15:46:34 2015 Delmaere Antoine
##

MAKE		+= --no-print-directory

CXX		= g++

CXXFLAGS	= -W -Wall -I./includes -I./includes/gdl -D_GNU_SOURCE
export CXXFLAGS

OUT_FORMAT	= @printf "\e[0;36m$(CXX)\e[0m -c -o \e[0;34m%-45s\e[0m \e[0;35m%s\e[0m\n" "$@" "$^"
export OUT_FORMAT

LDFLAGS		= -Llibs/ -lgdl_gl -lGL -lGLEW -lGLU -ldl -lrt -lfbxsdk -lSDL2 -lpthread -lm -lsfmlaudio -lsfmlsystem

SRC		=	src/main.cpp
SRC		+=	src/Game.cpp
SRC		+=	src/GameState.cpp
SRC		+=	src/GameIntro.cpp
SRC		+=	src/Time.cpp
SRC		+=	src/Timer.cpp
SRC		+=	src/AEventListener.cpp
SRC		+=	src/EventListener.cpp
SRC		+=	src/JoysticListener.cpp
SRC		+=	src/KeyboardListener.cpp
SRC		+=	src/ADrawable.cpp
SRC		+=	src/Text.cpp
SRC		+=	src/GameMenu.cpp
SRC		+=	src/Button.cpp
SRC		+=	src/ResourceManager.cpp
SRC		+=	src/GameConfig.cpp
SRC		+=	src/GamePlay.cpp
SRC		+=	src/GameCmd.cpp
SRC		+=	src/KeyConf.cpp
SRC		+=	src/Player.cpp
SRC		+=	src/Bomb.cpp
SRC		+=	src/Bombermap.cpp
SRC		+=	src/IEntity.cpp
SRC		+=	src/ATimeEntity.cpp
SRC		+=	src/Cube.cpp
SRC		+=	src/Explosion.cpp
SRC		+=	src/Save.cpp
SRC		+=	src/ABonus.cpp
SRC		+=	src/bonusBomb.cpp
SRC		+=	src/bonusSpeed.cpp
SRC		+=	src/bonusRange.cpp
SRC		+=	src/GamePlaySetting.cpp
SRC		+=	src/ISelectGUI.cpp
SRC		+=	src/InputNumber.cpp
SRC		+=	src/IMapEntity.cpp
SRC		+=	src/IA.cpp
SRC		+=	src/BattleWindow.cpp
SRC		+=	src/MyContext.cpp
SRC		+=	src/Load.cpp
SRC		+=	src/GameScore.cpp
SRC		+=	src/GamePause.cpp
SRC		+=	src/bonusGPS.cpp

OBJ		= $(SRC:.cpp=.o)

NAME		= bomberman

RM		= rm -vf

%.o: 		%.cpp
	@$(CXX) -c $(CXXFLAGS)            -o $@ $^
	$(OUT_FORMAT)

$(NAME):	$(OBJ)
	@$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo -e "\e[0;32m$(notdir $(NAME)) linked successfully !\e[0m"

all:		$(NAME)

clean:
	@$(RM) $(OBJ)

fclean:		clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
