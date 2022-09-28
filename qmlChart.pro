QT += quick

SOURCES += \
    src/main.cpp \
    src/model/pointslistmodel.cpp \
    src/quickChart.cpp

resources.prefix = /$${TARGET}
RESOURCES += ./res/chart.qrc

CONFIG += qmltypes

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_NAME = QuickChart
QML_IMPORT_MAJOR_VERSION = 1
QML_IMPORT_PATH = ./src

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

DISTFILES +=

HEADERS += \
    src/model/pointslistmodel.h \
    src/quickChart.h

INCLUDEPATH  += ./src
