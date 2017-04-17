if(WIN32)
  set(GETOPT ${CMAKE_SOURCE_DIR}/win32/wingetopt.c)
  include_directories(${CMAKE_SOURCE_DIR}/win32)
  if (${RDKAFKA_BUILD_TYPE} STREQUAL "STATIC")
    add_definitions(-DLIBRDKAFKA_STATICLIB)
  endif()
endif()

#add_executable(rdkafka_example rdkafka_example.c ${GETOPT})
#target_link_libraries(rdkafka_example PUBLIC rdkafka)

#add_executable(rdkafka_consumer_example rdkafka_consumer_example.c ${GETOPT})
#target_link_libraries(rdkafka_consumer_example PUBLIC rdkafka)

#add_executable(rdkafka_performance rdkafka_performance.c ${GETOPT})
#target_link_libraries(rdkafka_performance PUBLIC rdkafka)

add_executable(rdkafka_example_cpp rdkafka_example.cpp ${GETOPT})
set_target_properties(rdkafka_example_cpp PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(rdkafka_example_cpp PUBLIC rdkafka++ rdkafka)

#add_executable(kafkatest_verifiable_client kafkatest_verifiable_client.cpp ${GETOPT})
#set_target_properties(kafkatest_verifiable_client PROPERTIES LINKER_LANGUAGE CXX)
#target_link_libraries(kafkatest_verifiable_client PUBLIC rdkafka++ rdkafka)

add_executable(rdkafka_consumer_example_cpp rdkafka_consumer_example.cpp ${GETOPT})
set_target_properties(rdkafka_consumer_example_cpp PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(rdkafka_consumer_example_cpp PUBLIC rdkafka++ rdkafka)
