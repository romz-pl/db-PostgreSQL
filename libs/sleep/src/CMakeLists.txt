
set( LIB_NAME ps-sleep )

add_library( ${LIB_NAME} STATIC
    pgsleep.c
)

target_include_directories( ${LIB_NAME} PRIVATE 
    #    ${PROJECT_SOURCE_DIR}/libs/global/include 
    #    ${PROJECT_SOURCE_DIR}/libs/elog/include
    #    ${PROJECT_SOURCE_DIR}/libs/rand/include
)

target_compile_options( ${LIB_NAME} PRIVATE ${ROMZ_CXX_FLAGS} )


