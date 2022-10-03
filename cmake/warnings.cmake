function(set_palace_warnings project_name)
    option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)

    set(MSVC_WARNINGS
            /W3
            /w14242
            /w14254
            /w14263
            /w14265
            /w14287
            /we4289
            /w14296
            /w14311
            /w14545
            /w14546
            /w14547
            /w14549
            /w14555
            /w14619
            /w14640
            /w14826
            /w14905
            /w14906
            /w14928
            /permissive-
    )

    set(CLANG_WARNINGS
            -Wall
            -Wextra
            -Wshadow
            -Wnon-virtual-dtor
            -Wold-style-cast
            -Wcast-align
            -Wunused
            -Woverloaded-virtual
            -Wpedantic
            -Wconversion
            -Wsign-conversion
            -Wnull-dereference
            -Wdouble-promotion
            -Wformat=2
    )

    set(GCC_WARNINGS
            ${CLANG_WARNINGS}
            -Wmisleading-indentation
            -Wduplicated-cond
            -Wduplicated-branches
            -Wlogical-op
            -Wuseless-cast
    )

    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(PROJECT_WARNINGS ${MSVC_WARNINGS})
        set(WARNINGS_AS_ERRORS_FLAGS "/WX")
    elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
        set(PROJECT_WARNINGS ${CLANG_WARNINGS})
        set(WARNINGS_AS_ERRORS_FLAGS "-Werror")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(PROJECT_WARNINGS ${GCC_WARNINGS})
        set(WARNINGS_AS_ERRORS_FLAGS "-Werror")
    else()
        message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
        return()
    endif()

    target_compile_options(${project_name} INTERFACE ${PROJECT_WARNINGS})

    if(WARNINGS_AS_ERRORS)
        target_compile_options(${project_name} INTERFACE ${WARNINGS_AS_ERRORS_FLAGS})
    endif()
endfunction()
