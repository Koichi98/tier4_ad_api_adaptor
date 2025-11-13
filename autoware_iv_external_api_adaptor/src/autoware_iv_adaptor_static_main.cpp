// Copyright 2025 TIER IV, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <rclcpp/rclcpp.hpp>

#include "calibration_status.hpp"
#include "cpu_usage.hpp"
#include "diagnostics.hpp"
#include "door.hpp"
#include "emergency.hpp"
#include "fail_safe_state.hpp"
#include "initial_pose.hpp"
#include "localization_score.hpp"
#include "map.hpp"
#include "metadata_packages.hpp"
#include "operator.hpp"
#include "rosbag_logging_mode.hpp"
#include "route.hpp"
#include "service.hpp"
#include "start.hpp"
#include "system_monitor.hpp"
#include "vehicle_status.hpp"
#include "velocity.hpp"
#include "version.hpp"

#include <memory>
#include <vector>

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto exec = std::make_shared<rclcpp::executors::MultiThreadedExecutor>();
  std::vector<std::shared_ptr<rclcpp::Node>> nodes;

  // Create node options with namespace
  auto create_node_options = [](const std::string & node_name) {
    rclcpp::NodeOptions opts;
    opts.arguments({
      "--ros-args",
      "-r", "__ns:=/external",
      "-r", "__node:=" + node_name
    });
    opts.use_intra_process_comms(true);
    return opts;
  };

  // Create all 19 nodes
  auto calibration_status = std::make_shared<external_api::CalibrationStatus>(
    create_node_options("calibration_status"));
  nodes.push_back(calibration_status);

  auto cpu_usage = std::make_shared<external_api::CpuUsage>(
    create_node_options("cpu_usage"));
  nodes.push_back(cpu_usage);

  auto diagnostics = std::make_shared<external_api::Diagnostics>(
    create_node_options("diagnostics"));
  nodes.push_back(diagnostics);

  auto door = std::make_shared<external_api::Door>(
    create_node_options("door"));
  nodes.push_back(door);

  auto emergency = std::make_shared<external_api::Emergency>(
    create_node_options("emergency"));
  nodes.push_back(emergency);

  auto fail_safe_state = std::make_shared<external_api::FailSafeState>(
    create_node_options("fail_safe_state"));
  nodes.push_back(fail_safe_state);

  auto initial_pose = std::make_shared<external_api::InitialPose>(
    create_node_options("initial_pose"));
  nodes.push_back(initial_pose);

  auto localization_score = std::make_shared<external_api::LocalizationScore>(
    create_node_options("localization_score"));
  nodes.push_back(localization_score);

  auto map = std::make_shared<external_api::Map>(
    create_node_options("map"));
  nodes.push_back(map);

  auto operator_node = std::make_shared<external_api::Operator>(
    create_node_options("operator"));
  nodes.push_back(operator_node);

  auto rosbag_logging_mode = std::make_shared<external_api::RosbagLoggingMode>(
    create_node_options("rosbag_logging_mode"));
  nodes.push_back(rosbag_logging_mode);

  auto metadata_packages = std::make_shared<external_api::MetadataPackages>(
    create_node_options("metadata_packages"));
  nodes.push_back(metadata_packages);

  auto route = std::make_shared<external_api::Route>(
    create_node_options("route"));
  nodes.push_back(route);

  auto service = std::make_shared<external_api::Service>(
    create_node_options("service"));
  nodes.push_back(service);

  auto start = std::make_shared<external_api::Start>(
    create_node_options("start"));
  nodes.push_back(start);

  auto system_monitor = std::make_shared<external_api::SystemMonitor>(
    create_node_options("system_monitor"));
  nodes.push_back(system_monitor);

  auto vehicle_status = std::make_shared<external_api::VehicleStatus>(
    create_node_options("vehicle_status"));
  nodes.push_back(vehicle_status);

  auto velocity = std::make_shared<external_api::Velocity>(
    create_node_options("velocity"));
  nodes.push_back(velocity);

  auto version = std::make_shared<external_api::Version>(
    create_node_options("version"));
  nodes.push_back(version);

  // Add all nodes to executor
  for (auto & node : nodes) {
    exec->add_node(node->get_node_base_interface());
  }

  exec->spin();

  rclcpp::shutdown();

  return 0;
}
