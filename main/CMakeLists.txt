file(GLOB_RECURSE SOURCESCPP "*.cpp")
file(GLOB_RECURSE SOURCESC "*.c")

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()
HEADER_DIRECTORIES(HEADER_DIR_LIST)
    
idf_component_register(
    SRCS 
    ${SOURCESCPP}
    ${SOURCESC}
    INCLUDE_DIRS 
    ${HEADER_DIR_LIST}
)