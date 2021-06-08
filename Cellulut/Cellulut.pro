QT += widgets
QT += core gui sql

SOURCES += \
    controllers/C_MainWindow.cpp \
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
    views/V_MainWindow.cpp \
    views/V_SimulationConfigurationWidget.cpp

HEADERS += \
    controllers/C_MainWindow.h \
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
    views/V_MainWindow.h \
    views/V_SimulationConfigurationWidget.h

FORMS += \
    views/v_mainwindow.ui \
    views/v_simulationconfigurationwidget.ui

