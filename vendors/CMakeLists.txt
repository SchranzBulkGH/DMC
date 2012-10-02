CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

INCLUDE(ExternalProject)

ExternalProject_Add(Igloo
    GIT_REPOSITORY git://github.com/joakimkarlsson/igloo.git
    GIT_TAG igloo.0.9
    INSTALL_DIR ${CMAKE_SOURCE_DIR}/vendors/
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND cp -rf <SOURCE_DIR>/igloo <INSTALL_DIR>/include/igloo
    )

