add_library(
    rdkafka++
    ${RDKAFKA_BUILD_TYPE}
    ConfImpl.cpp
    ConsumerImpl.cpp
    HandleImpl.cpp
    KafkaConsumerImpl.cpp
    MessageImpl.cpp
    MetadataImpl.cpp
    ProducerImpl.cpp
    QueueImpl.cpp
    RdKafka.cpp
    TopicImpl.cpp
    TopicPartitionImpl.cpp
)

if(WIN32)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  if (${RDKAFKA_BUILD_TYPE} STREQUAL "STATIC")
    add_definitions(-DLIBRDKAFKA_STATICLIB)
  else()
    add_definitions(-DLIBRDKAFKACPP_EXPORTS)
  endif()
endif()

target_link_libraries(rdkafka++ PUBLIC rdkafka)

# Support '#include <rdkafcpp.h>'
target_include_directories(rdkafka++ PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>")

install(
    TARGETS rdkafka++
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
    FILES "rdkafkacpp.h"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/librdkafka"
)
