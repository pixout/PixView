
# Plugin sources
SET( SOURCES
  Receiver.cpp
  Painter.cpp
)

# Plugin headers used Qt
SET( MOC_HEADERS
  Receiver.hpp
  Painter.hpp
)

QT5_WRAP_CPP( SOURCES ${MOC_HEADERS})
ADD_LIBRARY(viewer_src OBJECT ${SOURCES} )
SET(COMMON_SOURCES ${COMMON_SOURCES} $<TARGET_OBJECTS:viewer_src> PARENT_SCOPE)
