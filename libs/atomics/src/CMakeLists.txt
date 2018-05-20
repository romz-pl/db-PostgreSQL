
set( LIB_NAME ps-atomics )

add_library( ${LIB_NAME} STATIC
    atomics.c
)

target_include_directories( ${LIB_NAME} PRIVATE 
    ${PROJECT_SOURCE_DIR}/libs/global/include 
    ${PROJECT_SOURCE_DIR}/libs/spinlock/include
)

target_compile_options( ${LIB_NAME} PRIVATE ${ROMZ_CXX_FLAGS} )


