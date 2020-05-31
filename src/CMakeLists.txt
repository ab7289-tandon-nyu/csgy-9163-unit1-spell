set(LIB_SOURCES
    dictionary.c
)

set(MAIN_SOURCES
    main.c
)

set(HEADERS
    ${CONFIG_HEADERS}
    dictionary.h
)

add_library(dictionary STATIC ${LIB_SOURCES} ${HEADERS})

add_executable(main ${LIB_SOURCES} ${HEADERS})
target_link_libraries(main dictionary)

install(TARGETS dictionary
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/dictionary.h DESTINATION include)