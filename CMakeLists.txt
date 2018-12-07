cmake_minimum_required(VERSION 3.10.2)

project(libwebsockets_demo C)

set(CMAKE_C_STANDARD 11)

# From FindLibWebSockets.cmake

find_path( LIBWEBSOCKETS_INCLUDE_DIR libwebsockets.h
        /usr/local/include
        /usr/include
        )

find_library( LIBWEBSOCKETS_LIBRARIES websockets
        /usr/local/lib
        /usr/lib
        )

get_filename_component(LIBWEBSOCKETS_LIBRARY_DIR ${LIBWEBSOCKETS_LIBRARIES} PATH )

SET ( LIBWEBSOCKETS_FOUND "NO" )
IF ( LIBWEBSOCKETS_INCLUDE_DIR )
    IF ( LIBWEBSOCKETS_LIBRARIES )
        SET ( LIBWEBSOCKETS_FOUND "YES" )
    ENDIF ( LIBWEBSOCKETS_LIBRARIES )
ENDIF ( LIBWEBSOCKETS_INCLUDE_DIR )


MARK_AS_ADVANCED(
        LIBWEBSOCKETS_LIBRARY_DIR
        LIBWEBSOCKETS_INCLUDE_DIR
        LIBWEBSOCKETS_LIBRARIES
)


include_directories(. ${LIBWEBSOCKETS_INCLUDE_DIR})

add_executable(libwebsockets_demo
        main.c
        simple-http.c
        simple-http.h
        websocket.c
        websocket.h
        service.c
        )

target_link_libraries(libwebsockets_demo ${LIBWEBSOCKETS_LIBRARIES} pthread)




