add_executable(bmpfilter
    main.c
    fileIO.c
    memory.c
    image.c
)
target_link_libraries(bmpfilter m)
