function(create_filter filter folder)
    source_group("Header Files\\${filter}" REGULAR_EXPRESSION "include/${folder}/.*\.(hpp|h)")
    source_group("Source Files\\${filter}" REGULAR_EXPRESSION "src/${folder}/.*\.(cpp|cc)")
endfunction()
