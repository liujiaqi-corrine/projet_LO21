QT += widgets
QT += core gui sql

SOURCES += \
    data/DataEngine.cpp \
    data/interfaces/InsideDataForUI.cpp \
    main.cpp \
    models/Automate.cpp \
    models/Cell.cpp \
    models/Cellulut.cpp \
    models/Grid.cpp \
    models/Library.cpp \
    models/Model.cpp \
    models/Rule.cpp \
    models/State.cpp \
    models/Surrounding.cpp \
    models/managers/DatabaseManager.cpp \
    models/managers/ModelsManager.cpp \
    models/managers/StatesManager.cpp \
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
    data/DataEngine.h \
    data/interfaces/InsideDataForUI.h \
    main.h \
    models/Automate.h \
    models/Cell.h \
    models/Cellulut.h \
    models/Grid.h \
    models/Library.h \
    models/Model.h \
    models/Rule.h \
    models/State.h \
    models/Surrounding.h \
    models/managers/DatabaseManager.h \
    models/managers/ModelsManager.h \
    models/managers/StatesManager.h \
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


