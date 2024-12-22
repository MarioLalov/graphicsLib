add_library(Managers "")

target_sources(Managers
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/DrawManager/DrawManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/RssManager/RssManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FactoryManager/FactoryManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SceneManager/SceneManager.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/DrawManager/DrawManager.h
    ${CMAKE_CURRENT_LIST_DIR}/RssManager/RssManager.h
    ${CMAKE_CURRENT_LIST_DIR}/FactoryManager/FactoryManager.h
    ${CMAKE_CURRENT_LIST_DIR}/SceneManager/SceneManager.h
  )
  
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(nlohmann_json 3.11.3 REQUIRED)

target_link_libraries(Managers
  PRIVATE
    sfml-graphics
    nlohmann_json::nlohmann_json
  )

target_include_directories(Managers
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
