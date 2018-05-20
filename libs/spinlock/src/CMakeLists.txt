
set( LIB_NAME ps-spinlock )

add_library( ${LIB_NAME} STATIC
    s_lock.c
    spin.c
)

target_include_directories( ${LIB_NAME} PRIVATE 
    ${PROJECT_SOURCE_DIR}/libs/global/include 
    ${PROJECT_SOURCE_DIR}/libs/elog/include
    ${PROJECT_SOURCE_DIR}/libs/rand/include
    ${PROJECT_SOURCE_DIR}/libs/sleep/include
)

target_compile_options( ${LIB_NAME} PRIVATE ${ROMZ_CXX_FLAGS} )


