
set( LIB_NAME ps-rand )

add_library( ${LIB_NAME} STATIC
    random.c
    erand48.c
)

target_include_directories( ${LIB_NAME} PRIVATE 
    #    ${PROJECT_SOURCE_DIR}/libs/global/include 
#    ${PROJECT_SOURCE_DIR}/libs/elog/include
)

target_compile_options( ${LIB_NAME} PRIVATE ${ROMZ_CXX_FLAGS} )


