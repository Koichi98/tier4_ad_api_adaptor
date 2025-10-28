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

  auto create_relay = [&](const std::string & name,
                          const std::string & input_topic,
                          const std::string & output_topic) {
    rclcpp::NodeOptions opts;
    opts.arguments({
      "--ros-args",
      "-r", "__ns:=/awapi",
      "-r", "__node:=" + name
    });
    opts.append_parameter_override("input_topic", input_topic);
    opts.append_parameter_override("output_topic", output_topic);
    opts.use_intra_process_comms(true);

    auto node = std::make_shared<topic_tools::RelayNode>(opts);
    exec->add_node(node->get_node_base_interface());
    nodes.push_back(node);

    RCLCPP_INFO(
      rclcpp::get_logger("awapi_relay_static"),
      "Created relay node: %s (%s -> %s)",
      name.c_str(), input_topic.c_str(), output_topic.c_str()
    );
  };

  create_relay("route_relay",
               "/planning/mission_planning/route", "autoware/get/route");
  create_relay("predict_object_relay",
               "/perception/object_recognition/objects", "prediction/get/objects");
  create_relay("nearest_traffic_signal_relay",
               "/planning/scenario_planning/lane_driving/behavior_planning/debug/traffic_signal",
               "traffic_light/get/nearest_traffic_signal");
  create_relay("ready_module_relay",
               "/planning/scenario_planning/lane_driving/behavior_planning/behavior_path_planner/ready_module",
               "path_change/get/ready_module");
  create_relay("force_available_relay",
               "/planning/scenario_planning/lane_driving/behavior_planning/behavior_path_planner/force_available",
               "path_change/get/force_available");
  create_relay("running_modules_relay",
               "/planning/scenario_planning/lane_driving/behavior_planning/behavior_path_planner/running_modules",
               "path_change/get/running_modules");
  create_relay("autoware_engage_relay",
               "autoware/put/engage", "/autoware/engage");
  create_relay("vehicle_engage_relay",
               "autoware/put/engage", "/vehicle/engage");
  create_relay("put_route_relay",
               "autoware/put/route", "/planning/mission_planning/route");
  create_relay("put_goal_relay",
               "autoware/put/goal", "/planning/mission_planning/goal");
  create_relay("lane_change_approval_relay",
               "lane_change/put/approval",
               "/planning/scenario_planning/lane_driving/lane_change_approval");
  create_relay("force_lane_change_relay",
               "lane_change/put/force",
               "/planning/scenario_planning/lane_driving/force_lane_change");
  create_relay("external_approval_relay",
               "path_change/put/approval",
               "/planning/scenario_planning/lane_driving/behavior_planning/behavior_path_planner/path_change_approval");
  create_relay("force_approval_relay",
               "path_change/put/force",
               "/planning/scenario_planning/lane_driving/behavior_planning/behavior_path_planner/path_change_force");
  create_relay("obstacle_avoid_approval_relay",
               "object_avoidance/put/approval",
               "/planning/scenario_planning/lane_driving/obstacle_avoidance_approval");
  create_relay("traffic_signal_relay",
               "/perception/traffic_light_recognition/traffic_signals",
               "traffic_light/get/traffic_signals");
  create_relay("overwrite_traffic_signals_relay",
               "traffic_light/put/traffic_signals",
               "/external/traffic_light_recognition/traffic_signals");
  create_relay("speed_exceeded_relay",
               "/planning/scenario_planning/velocity_smoother/stop_speed_exceeded",
               "autoware/get/stop_speed_exceeded");
  create_relay("crosswalk_status_relay",
               "autoware/put/crosswalk_states",
               "/planning/scenario_planning/lane_driving/behavior_planning/behavior_velocity_planner/input/external_crosswalk_states");
  create_relay("intersection_status_relay",
               "autoware/put/intersection_states",
               "/planning/scenario_planning/lane_driving/behavior_planning/behavior_velocity_planner/input/external_intersection_states");
  create_relay("expand_stop_range_relay",
               "autoware/put/expand_stop_range",
               "/planning/scenario_planning/lane_driving/motion_planning/obstacle_stop_planner/input/expand_stop_range");
  create_relay("pose_initialization_request_relay",
               "autoware/put/pose_initialization_request",
               "/localization/util/pose_initialization_request");

  exec->spin();

  rclcpp::shutdown();

  return 0;
}
