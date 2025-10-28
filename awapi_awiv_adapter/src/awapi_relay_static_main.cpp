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
#include <topic_tools/relay_node.hpp>

#include <memory>
#include <vector>
#include <string>

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto exec = std::make_shared<rclcpp::executors::MultiThreadedExecutor>();
  std::vector<std::shared_ptr<rclcpp::Node>> nodes;

  auto create_relay = [&](const std::string & name) {
    rclcpp::NodeOptions opts;
    opts.arguments({
      "--ros-args",
      "-r", "__ns:=/awapi",
      "-r", "__node:=" + name
    });
    opts.use_intra_process_comms(true);

    auto node = std::make_shared<topic_tools::RelayNode>(opts);
    exec->add_node(node->get_node_base_interface());
    nodes.push_back(node);

    RCLCPP_INFO(
      rclcpp::get_logger("awapi_relay_static"),
      "Created relay node: %s", name.c_str()
    );
  };

  create_relay("route_relay");
  create_relay("predict_object_relay");
  create_relay("nearest_traffic_signal_relay");
  create_relay("ready_module_relay");
  create_relay("force_available_relay");
  create_relay("running_modules_relay");
  create_relay("autoware_engage_relay");
  create_relay("vehicle_engage_relay");
  create_relay("put_route_relay");
  create_relay("put_goal_relay");
  create_relay("lane_change_approval_relay");
  create_relay("force_lane_change_relay");
  create_relay("external_approval_relay");
  create_relay("force_approval_relay");
  create_relay("obstacle_avoid_approval_relay");
  create_relay("traffic_signal_relay");
  create_relay("overwrite_traffic_signals_relay");
  create_relay("speed_exceeded_relay");
  create_relay("crosswalk_status_relay");
  create_relay("intersection_status_relay");
  create_relay("expand_stop_range_relay");
  create_relay("pose_initialization_request_relay");

  exec->spin();

  rclcpp::shutdown();

  return 0;
}
