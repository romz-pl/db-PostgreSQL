
set( LIB_NAME ps-port-atomics )

add_library( ${LIB_NAME} STATIC
    atomics.c
)

target_include_directories( ${LIB_NAME} PRIVATE 
    ${PROJECT_SOURCE_DIR}/libs/global/include )

target_compile_options( ${LIB_NAME} PRIVATE ${ROMZ_CXX_FLAGS} )


