# Already installed? Do nothing.
if (TARGET ftxui::component)
  return()
endif()

# Try to find the package installed on the system.
#find_package(ftxui 4.0.0) 
if (ftxui_FOUND)
  return()
endif()

# Fetch the package from github.
include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v4.1.1
  )
FetchContent_MakeAvailable(ftxui)
