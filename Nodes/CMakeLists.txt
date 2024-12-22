add_library(Nodes "")

target_sources(Nodes
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Node/TransformationMatrix.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Node/Node.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Sprite/Sprite.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Node/TransformationMatrix.h
    ${CMAKE_CURRENT_LIST_DIR}/Node/Node.h
    ${CMAKE_CURRENT_LIST_DIR}/Sprite/Sprite.h
  )
  
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

target_link_libraries(Nodes
  PRIVATE
    sfml-graphics
  )

target_include_directories(Nodes
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
