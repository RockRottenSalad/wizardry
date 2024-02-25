
#define COMPILER "clang"

#define DEBUG_FLAGS "-g", "-Wall", "-Wextra", "-I ./src/"

#define MAIN_SRC "./test.c"
#define OUTPUT "./bin/test"

#include<wiz_build.h>

int main(int argc, char** argv)
{
    WIZ_BUILD_INIT(argc, argv);
    command_t compile = MAKE_CMD(BIN(COMPILER), DEBUG_FLAGS, "-o", OUTPUT);

    size_t files =
        FOR_FILE_IN_DIR("./src/data_structures/", WHERE( FILE_FORMAT("c") ),
            CMD_APPEND(&compile, FILE_PATH); 
            LOG("Adding " BLUE("%s") " to build", FILE_NAME);
            );

    ASSERT(files > 0);
    FOR_FILE_IN_DIR("./src/utils/", WHERE( FILE_FORMAT("c") ),
            CMD_APPEND(&compile, FILE_PATH); 
            LOG("Adding " BLUE("%s") " to build", FILE_NAME);
            );


    CMD_APPEND(&compile, MAIN_SRC);

    SET_COMPILE_TARGET(OUTPUT);
    EXEC_CMD(compile);
    CHECK_COMPILE_STATUS();

    if(argc > 1 && STRCMP(argv[1], "gdb"))
        CMD(BIN("gdb"), OUTPUT);
    else if(argc > 1 && STRCMP(argv[1], "val"))
        CMD(BIN("valgrind"), OUTPUT);
    else if(argc > 1 && STRCMP(argv[1], "run"))
        CMD(OUTPUT);
    
    WIZ_BUILD_DEINIT();
    return 0;
}


