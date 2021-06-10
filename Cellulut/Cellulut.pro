QT += widgets
QT += core gui sql

SOURCES += \
    main.cpp \
    models/Automate.cpp \
    models/Cell.cpp \
    models/Grid.cpp \
    models/Library.cpp \
    models/Model.cpp \
    models/Rule.cpp \
    models/State.cpp \
    models/Surrounding.cpp \
    ui/UIEngine.cpp \
    ui/interfaces/InsideUIForData.cpp \
    ui/views/MainMenuView.cpp \
    ui/views/MainWindow.cpp \
    ui/views/SimulationView.cpp \
    ui/views/SimulationViewV2.cpp \
    ui/views/grid/SimulationBoard.cpp \
    ui/views/templates/CreateTemplateView.cpp \
    ui/views/templates/LoadTemplateView.cpp

HEADERS += \
    main.h \
    models/Automate.h \
    models/Cell.h \
    models/Grid.h \
    models/Library.h \
    models/Model.h \
    models/Rule.h \
    models/State.h \
    models/Surrounding.h \
    ui/UIEngine.h \
    ui/interfaces/InsideUIForData.h \
    ui/views/MainMenuView.h \
    ui/views/MainWindow.h \
    ui/views/SimulationView.h \
    ui/views/SimulationViewV2.h \
    ui/views/grid/SimulationBoard.h \
    ui/views/templates/CreateTemplateView.h \
    ui/views/templates/LoadTemplateView.h

FORMS += \
    ui/views/MainMenuView.ui \
    ui/views/MainWindow.ui \
    ui/views/SimulationView.ui \
    ui/views/templates/CreateTemplateView.ui \
    ui/views/templates/LoadTemplateView.ui


