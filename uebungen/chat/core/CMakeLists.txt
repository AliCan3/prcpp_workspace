include(prcpp_code)

prcpp_code(uebung_chat_core)

target_link_libraries(uebung_chat_core_lib
        PUBLIC pthread)

target_compile_definitions(uebung_chat_core_lib
        PUBLIC "-DASIO_STANDALONE")
