function(set_compile_options project_name compiler)
    set(MSVC_OPTIONS
        /Zc:preprocessor
    )

    set(CLANG_OPTIONS
        -Wno-gnu-zero-variadic-macro-arguments
    )

    set(GCC_OPTIONS
        # None
    )

    set(INTEL_OPTIONS
        # None
    )

    if(compiler STREQUAL "MSVC")
        set(OPTIONS ${MSVC_OPTIONS})
    elseif(compiler MATCHES ".*Clang")
        set(OPTIONS ${CLANG_OPTIONS})
    elseif(compiler STREQUAL "GCC")
        set(OPTIONS ${GCC_OPTIONS})
    elseif(compiler STREQUAL "Intel")
        set(OPTIONS ${INTEL_OPTIONS})
    else()
        message(AUTHOR_WARNING "No compile options set for '${compiler}'.")
        return()
    endif()

    target_compile_options(${project_name} INTERFACE ${OPTIONS})
endfunction()
