LIBS += -lsfml-network -lsfml-system
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    Player.cpp
HEADERS += ../Actions.hpp \
    Player.hpp
