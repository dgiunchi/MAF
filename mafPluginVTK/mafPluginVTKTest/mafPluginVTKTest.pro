# -------------------------------------------------
# Project created by QtCreator 2010-03-01T14:14:10
# -------------------------------------------------
QT += xml
CONFIG += qtestlib
CONFIG += link_prl
SOURCES += main.cpp \
    mafVisualPipeVTKSurfaceTest.cpp \
    mafViewVTKTest.cpp \
    mafDataPipeImageThresholdTest.cpp \
    mafExternalDataCodecVTKTest.cpp \
    mafSerializationVTKTest.cpp \
    mafSerializationExtDataTest.cpp \
    mafSerializationRawBinaryExtDataTest.cpp \
    mafSerializationRawASCIIExtDataTest.cpp \
    mafVTKWidgetTest.cpp \
    mafVisualPipeSelectionTest.cpp \
    mafDataBoundaryAlgorithmVTKTest.cpp

include(../../mafInstallTest.pri)
include(../../mafImportVXL.pri)
include(../../mafImportVTK.pri)
include(../../mafImportQXMLRPC.pri)
include(../../mafImportQtSoap.pri)
INCLUDEPATH += ../../mafResources \
                        ../../mafEventBus \
                        ../../mafCore

LIBS += -L$$DESTDIR \
    -lmafResources$$LIB_EXT -lmafEventBus$$LIB_EXT -lmafCore$$LIB_EXT -lmafPluginVTK$${LIB_EXT}
