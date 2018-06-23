#-------------------------------------------------
#
# Project created by QtCreator 2018-06-02T20:55:03
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Editor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    editor.cpp \
    editorview.cpp \
    editorscene.cpp \
    stagedata.cpp \
    stageelement.cpp \
    stageelementworm.cpp \
    stageelemlonggirder.cpp \
    stageelemshortgirder.cpp \
    qgraphicsitemlayer.cpp \
    ../../../libs/yaml-cpp/src/contrib/graphbuilder.cpp \
    ../../../libs/yaml-cpp/src/contrib/graphbuilderadapter.cpp \
    ../../../libs/yaml-cpp/src/binary.cpp \
    ../../../libs/yaml-cpp/src/convert.cpp \
    ../../../libs/yaml-cpp/src/directives.cpp \
    ../../../libs/yaml-cpp/src/emit.cpp \
    ../../../libs/yaml-cpp/src/emitfromevents.cpp \
    ../../../libs/yaml-cpp/src/emitter.cpp \
    ../../../libs/yaml-cpp/src/emitterstate.cpp \
    ../../../libs/yaml-cpp/src/emitterutils.cpp \
    ../../../libs/yaml-cpp/src/exceptions.cpp \
    ../../../libs/yaml-cpp/src/exp.cpp \
    ../../../libs/yaml-cpp/src/memory.cpp \
    ../../../libs/yaml-cpp/src/node.cpp \
    ../../../libs/yaml-cpp/src/node_data.cpp \
    ../../../libs/yaml-cpp/src/nodebuilder.cpp \
    ../../../libs/yaml-cpp/src/nodeevents.cpp \
    ../../../libs/yaml-cpp/src/null.cpp \
    ../../../libs/yaml-cpp/src/ostream_wrapper.cpp \
    ../../../libs/yaml-cpp/src/parse.cpp \
    ../../../libs/yaml-cpp/src/parser.cpp \
    ../../../libs/yaml-cpp/src/regex_yaml.cpp \
    ../../../libs/yaml-cpp/src/scanner.cpp \
    ../../../libs/yaml-cpp/src/scanscalar.cpp \
    ../../../libs/yaml-cpp/src/scantag.cpp \
    ../../../libs/yaml-cpp/src/scantoken.cpp \
    ../../../libs/yaml-cpp/src/simplekey.cpp \
    ../../../libs/yaml-cpp/src/singledocparser.cpp \
    ../../../libs/yaml-cpp/src/stream.cpp \
    ../../../libs/yaml-cpp/src/tag.cpp

HEADERS  += mainwindow.h \
    editor.h \
    editorview.h \
    editorscene.h \
    stagedata.h \
    stageelement.h \
    stageelementworm.h \
    stageelemlonggirder.h \
    stageelemshortgirder.h \
    qgraphicsitemlayer.h \
    ../../../libs/yaml-cpp/src/contrib/graphbuilderadapter.h \
    ../../../libs/yaml-cpp/src/collectionstack.h \
    ../../../libs/yaml-cpp/src/directives.h \
    ../../../libs/yaml-cpp/src/emitterstate.h \
    ../../../libs/yaml-cpp/src/emitterutils.h \
    ../../../libs/yaml-cpp/src/exp.h \
    ../../../libs/yaml-cpp/src/indentation.h \
    ../../../libs/yaml-cpp/src/nodebuilder.h \
    ../../../libs/yaml-cpp/src/nodeevents.h \
    ../../../libs/yaml-cpp/src/ptr_vector.h \
    ../../../libs/yaml-cpp/src/regex_yaml.h \
    ../../../libs/yaml-cpp/src/regeximpl.h \
    ../../../libs/yaml-cpp/src/scanner.h \
    ../../../libs/yaml-cpp/src/scanscalar.h \
    ../../../libs/yaml-cpp/src/scantag.h \
    ../../../libs/yaml-cpp/src/setting.h \
    ../../../libs/yaml-cpp/src/singledocparser.h \
    ../../../libs/yaml-cpp/src/stream.h \
    ../../../libs/yaml-cpp/src/streamcharsource.h \
    ../../../libs/yaml-cpp/src/stringsource.h \
    ../../../libs/yaml-cpp/src/tag.h \
    ../../../libs/yaml-cpp/src/token.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

INCLUDEPATH += ../../../libs/yaml-cpp/include
