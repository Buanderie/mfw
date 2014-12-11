PROJECT(mfwedit)

FIND_PACKAGE(Qt4 REQUIRED)

SET(mfwedit_SOURCES main.cpp qneblock.cpp qneconnection.cpp qnemainwindow.cpp qneport.cpp qnodeseditor.cpp )
SET(mfwedit_HEADERS ui_qnemainwindow.h qnemainwindow.h qnodeseditor.h )
SET(mfwedit_FORMS qnemainwindow.ui)

QT4_WRAP_CPP(mfwedit_HEADERS_MOC ${mfwedit_HEADERS})
QT4_WRAP_UI(helloworld_FORMS_HEADERS ${mfwedit_FORMS})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )
include_directories( ${LIBMONADIC_SOURCE_DIR}/include )

ADD_EXECUTABLE(mfwedit ${mfwedit_SOURCES} ${mfwedit_HEADERS_MOC} ${mfw_FORMS_HEADERS}  )
TARGET_LINK_LIBRARIES(mfwedit ${QT_LIBRARIES} monadic )
