cmake_minimum_required(VERSION 3.14)
project(awapi_awiv_adapter)

find_package(autoware_cmake REQUIRED)
autoware_package()

ament_auto_add_executable(awapi_awiv_adapter
  src/awapi_awiv_adapter_node.cpp
  src/awapi_awiv_adapter_core.cpp
  src/awapi_vehicle_state_publisher.cpp
  src/awapi_velocity_factor_converter.cpp
  src/awapi_autoware_state_publisher.cpp
  src/awapi_stop_reason_aggregator.cpp
  src/awapi_v2x_aggregator.cpp
  src/awapi_lane_change_state_publisher.cpp
  src/awapi_obstacle_avoidance_state_publisher.cpp
  src/awapi_max_velocity_publisher.cpp
  src/awapi_autoware_util.cpp
)

find_package(glog REQUIRED)
target_link_libraries(awapi_awiv_adapter glog::glog)

find_package(topic_tools REQUIRED)
find_package(rclcpp_components REQUIRED)

add_executable(awapi_relay_static
  src/awapi_relay_static_main.cpp
)

ament_target_dependencies(awapi_relay_static
  rclcpp
  topic_tools
  rclcpp_components
)

install(TARGETS awapi_relay_static
  DESTINATION lib/${PROJECT_NAME}
)

ament_auto_package(INSTALL_TO_SHARE launch)
