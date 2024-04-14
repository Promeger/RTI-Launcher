# CMakeList.txt : CMake project for RTI, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (RTI "RTI.cpp" "RTI.h" "Helpers/GlobalState.h" "Helpers/MenuButton.h" "Helpers/MenuButton.cpp" "Helpers/GlobalFont.h" "Helpers/GlobalFont.cpp" "Helpers/Application.h" "Helpers/Application.cpp" "Helpers/CurrentApp.h" "Helpers/CurrentApp.cpp" "Helpers/Slider.h" "Helpers/Slider.cpp" "Helpers/ToggleButton.h" "Helpers/ToggleButton.cpp"
"Helpers/CommunicationManager.h" "Helpers/CommunicationManager.cpp"
"StatusBar/StatusBar.h" "StatusBar/StatusBar.cpp" 
"MainMenu/MainMenu.h" "MainMenu/MainMenu.cpp" 
"Settings/Settings.h" "Settings/Settings.cpp"
"Player/Player.h" "Player/Player.cpp" "Player/Playlist.h" "Player/Playlist.cpp" "Player/MyStream.h" "Player/MyStream.cpp") 

target_include_directories(RTI PRIVATE "/usr/include")
target_include_directories(RTI PRIVATE "/usr/include/x86_64-linux-gnu")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RTI PROPERTY CXX_STANDARD 20)
endif()



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)


target_link_libraries(RTI PRIVATE sfml-window)
target_link_libraries(RTI PRIVATE sfml-graphics)
target_link_libraries(RTI PRIVATE sfml-system)
target_link_libraries(RTI PRIVATE sfml-audio)
target_link_libraries(RTI PRIVATE tag)
target_link_libraries(RTI PRIVATE sndfile)


install(TARGETS RTI)
# TODO: Add tests and install targets if needed.
