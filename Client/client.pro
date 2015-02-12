LIBS += -lsfml-network -lsfml-system -lsfml-window -lsfml-graphics
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    main.cpp \
    InputManager.cpp
HEADERS += \
    ../Utility/Actions.hpp \
    InputManager.hpp
