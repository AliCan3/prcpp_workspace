include(prcpp_code)

prcpp_code(uebung_chat_client)
target_link_libraries(uebung_chat_client_app PRIVATE uebung_chat_core_lib)
