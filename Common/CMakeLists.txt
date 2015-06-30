SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )

# Plugin sources
SET( SOURCES
  Fixture.cpp
  Logger.cpp
  PixelMapper.cpp
  Util.cpp
  PainterOutput.cpp
)

# Plugin headers used Qt
SET( MOC_HEADERS
  PixelMapper.hpp
  Logger.hpp
  PainterOutput.hpp
)

QT5_WRAP_CPP( SOURCES ${MOC_HEADERS})
ADD_LIBRARY(lib_src OBJECT ${SOURCES} )
SET(COMMON_SOURCES ${COMMON_SOURCES} $<TARGET_OBJECTS:lib_src> PARENT_SCOPE)
