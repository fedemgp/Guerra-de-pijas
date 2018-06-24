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
    ../../../libs/yaml-cpp/contrib/graphbuilder.cpp \
    ../../../libs/yaml-cpp/contrib/graphbuilderadapter.cpp \
    ../../../libs/yaml-cpp/binary.cpp \
    ../../../libs/yaml-cpp/convert.cpp \
    ../../../libs/yaml-cpp/directives.cpp \
    ../../../libs/yaml-cpp/emit.cpp \
    ../../../libs/yaml-cpp/emitfromevents.cpp \
    ../../../libs/yaml-cpp/emitter.cpp \
    ../../../libs/yaml-cpp/emitterstate.cpp \
    ../../../libs/yaml-cpp/emitterutils.cpp \
    ../../../libs/yaml-cpp/exceptions.cpp \
    ../../../libs/yaml-cpp/exp.cpp \
    ../../../libs/yaml-cpp/memory.cpp \
    ../../../libs/yaml-cpp/node.cpp \
    ../../../libs/yaml-cpp/node_data.cpp \
    ../../../libs/yaml-cpp/nodebuilder.cpp \
    ../../../libs/yaml-cpp/nodeevents.cpp \
    ../../../libs/yaml-cpp/null.cpp \
    ../../../libs/yaml-cpp/ostream_wrapper.cpp \
    ../../../libs/yaml-cpp/parse.cpp \
    ../../../libs/yaml-cpp/parser.cpp \
    ../../../libs/yaml-cpp/regex_yaml.cpp \
    ../../../libs/yaml-cpp/scanner.cpp \
    ../../../libs/yaml-cpp/scanscalar.cpp \
    ../../../libs/yaml-cpp/scantag.cpp \
    ../../../libs/yaml-cpp/scantoken.cpp \
    ../../../libs/yaml-cpp/simplekey.cpp \
    ../../../libs/yaml-cpp/singledocparser.cpp \
    ../../../libs/yaml-cpp/stream.cpp \
    ../../../libs/yaml-cpp/tag.cpp

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
    ../../../libs/yaml-cpp/contrib/anchordict.h \
    ../../../libs/yaml-cpp/contrib/graphbuilder.h \
    ../../../libs/yaml-cpp/contrib/graphbuilderadapter.h \
    ../../../libs/yaml-cpp/node/detail/bool_type.h \
    ../../../libs/yaml-cpp/node/detail/impl.h \
    ../../../libs/yaml-cpp/node/detail/iterator.h \
    ../../../libs/yaml-cpp/node/detail/iterator_fwd.h \
    ../../../libs/yaml-cpp/node/detail/memory.h \
    ../../../libs/yaml-cpp/node/detail/node.h \
    ../../../libs/yaml-cpp/node/detail/node_data.h \
    ../../../libs/yaml-cpp/node/detail/node_iterator.h \
    ../../../libs/yaml-cpp/node/detail/node_ref.h \
    ../../../libs/yaml-cpp/node/convert.h \
    ../../../libs/yaml-cpp/node/emit.h \
    ../../../libs/yaml-cpp/node/impl.h \
    ../../../libs/yaml-cpp/node/iterator.h \
    ../../../libs/yaml-cpp/node/node.h \
    ../../../libs/yaml-cpp/node/parse.h \
    ../../../libs/yaml-cpp/node/ptr.h \
    ../../../libs/yaml-cpp/node/type.h \
    ../../../libs/yaml-cpp/anchor.h \
    ../../../libs/yaml-cpp/binary.h \
    ../../../libs/yaml-cpp/collectionstack.h \
    ../../../libs/yaml-cpp/directives.h \
    ../../../libs/yaml-cpp/dll.h \
    ../../../libs/yaml-cpp/emitfromevents.h \
    ../../../libs/yaml-cpp/emitter.h \
    ../../../libs/yaml-cpp/emitterdef.h \
    ../../../libs/yaml-cpp/emittermanip.h \
    ../../../libs/yaml-cpp/emitterstate.h \
    ../../../libs/yaml-cpp/emitterstyle.h \
    ../../../libs/yaml-cpp/emitterutils.h \
    ../../../libs/yaml-cpp/eventhandler.h \
    ../../../libs/yaml-cpp/exceptions.h \
    ../../../libs/yaml-cpp/exp.h \
    ../../../libs/yaml-cpp/indentation.h \
    ../../../libs/yaml-cpp/mark.h \
    ../../../libs/yaml-cpp/nodebuilder.h \
    ../../../libs/yaml-cpp/nodeevents.h \
    ../../../libs/yaml-cpp/noncopyable.h \
    ../../../libs/yaml-cpp/null.h \
    ../../../libs/yaml-cpp/ostream_wrapper.h \
    ../../../libs/yaml-cpp/parser.h \
    ../../../libs/yaml-cpp/ptr_vector.h \
    ../../../libs/yaml-cpp/regex_yaml.h \
    ../../../libs/yaml-cpp/regeximpl.h \
    ../../../libs/yaml-cpp/scanner.h \
    ../../../libs/yaml-cpp/scanscalar.h \
    ../../../libs/yaml-cpp/scantag.h \
    ../../../libs/yaml-cpp/setting.h \
    ../../../libs/yaml-cpp/singledocparser.h \
    ../../../libs/yaml-cpp/stlemitter.h \
    ../../../libs/yaml-cpp/stream.h \
    ../../../libs/yaml-cpp/streamcharsource.h \
    ../../../libs/yaml-cpp/stringsource.h \
    ../../../libs/yaml-cpp/tag.h \
    ../../../libs/yaml-cpp/token.h \
    ../../../libs/yaml-cpp/traits.h \
    ../../../libs/yaml-cpp/yaml.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

INCLUDEPATH += ../../../libs
