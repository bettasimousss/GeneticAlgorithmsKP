QT += widgets

HEADERS     = \
    mainwin.h \
    KnackSack.h \
    dialog.h \
    fen_ag.h \
    objet.h \
    strategies.h \
    data_structures.h \
    wintabou.h \
    fichier_pas.h \
    exact_choices.h \
    result_tabou.h \
    mainwindow_sample.h \
    result_ag.h \
    traitement.h
SOURCES     = \
              main.cpp \
    mainwin.cpp \
    KnackSack.cpp \
    dialog.cpp \
    a_faire.cpp \
    fen_ag.cpp \
    objet.cpp \
    strategies.cpp \
    wintabou.cpp \
    fichier_pas.cpp \
    exact_choices.cpp \
    result_tabou.cpp \
    mainwindow_sample.cpp \
    result_ag.cpp \
    traitement.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/layouts/basiclayouts
INSTALLS += target

simulator: warning(This example might not fully work on Simulator platform)

FORMS += \
    dialog.ui \
    fen_ag.ui \
    wintabou.ui \
    fichier_pas.ui \
    exact_choices.ui \
    result_tabou.ui \
    mainwindow_sample.ui \
    result_ag.ui
