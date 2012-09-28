############################################################
#           Build Tests
############################################################

############################################################
#   Function to create an executable containing one test
############################################################
FUNCTION(register_test TEST_FILE)
    GET_FILENAME_COMPONENT(TEST_NAME ${TEST_FILE} NAME)
    MESSAGE(STATUS "Adding test " ${TEST_NAME})
    ADD_EXECUTABLE(${TEST_NAME} EXCLUDE_FROM_ALL ${TEST_FILE}.cpp main.cpp)
    TARGET_LINK_LIBRARIES(${TEST_NAME}
        ${LIBRARY_NAME}
        )
    SET(TESTS_SOURCES ${TESTS_SOURCES} ${TEST_FILE}.cpp PARENT_SCOPE)
    SET(TESTS_NAMES ${TESTS_NAMES} ${TEST_NAME} PARENT_SCOPE)
ENDFUNCTION()

register_test(addition_test)

############################################################
#  Create a tests executable that contain all registered 
#  tests
############################################################
ADD_EXECUTABLE(tests EXCLUDE_FROM_ALL ${TESTS_SOURCES} main.cpp)
TARGET_LINK_LIBRARIES(
    tests
    ${LIBRARY_NAME}
    )

