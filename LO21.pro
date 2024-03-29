QT += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += xml

HEADERS += \
    UTProfiler.h \
    cursusGUI.h \
    uvGUI.h \
    cursus.h \
    visiteur.h \
    includes.h \
    dossier.h \
    dossierGUI2.h \
    visiteur2.h \
    menu.h \
    iterateur.h \
    exception.h \
    completion.h \
    completionGUI.h \
    visiteur_completion.h

SOURCES += \
    UTProfiler.cpp \
    cursusGUI.cpp \
    uvGUI.cpp \
    cursus.cpp \
    visiteur.cpp \
    dossier.cpp \
    dossierGUI2.cpp \
    visiteur2.cpp \
    main.cpp \
    menu.cpp \
    load_save_dossiers.cpp \
    completion.cpp \
    completionGUI.cpp \
    menuDossier.cpp \
    load_save_completion.cpp \
    visiteur_completion.cpp \
    algoCompletion.cpp


