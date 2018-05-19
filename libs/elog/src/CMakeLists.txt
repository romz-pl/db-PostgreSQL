
set( LIB_NAME ps-elog )

add_library( ${LIB_NAME} STATIC
    elog.c
)

target_include_directories( ${LIB_NAME} PRIVATE 
    ${PROJECT_SOURCE_DIR}/libs/global/include 
)

target_compile_options( ${LIB_NAME} PRIVATE ${ROMZ_CXX_FLAGS} )


