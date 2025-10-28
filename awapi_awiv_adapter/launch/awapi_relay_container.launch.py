# Copyright 2025 TIER IV, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import launch
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    awapi_relay_static_node = Node(
        package="awapi_awiv_adapter",
        executable="awapi_relay_static",
        name="awapi_relay_static",
        namespace="awapi",
        output="screen",
        remappings=[
            ("route_relay/input_topic", LaunchConfiguration("input_route")),
            ("route_relay/output_topic", LaunchConfiguration("get_route")),
            ("predict_object_relay/input_topic", LaunchConfiguration("input_object")),
            ("predict_object_relay/output_topic", LaunchConfiguration("get_predicted_object")),
            ("nearest_traffic_signal_relay/input_topic", LaunchConfiguration("input_nearest_traffic_signal")),
            ("nearest_traffic_signal_relay/output_topic", LaunchConfiguration("get_nearest_traffic_signal")),
            ("ready_module_relay/input_topic", LaunchConfiguration("input_path_change_ready")),
            ("ready_module_relay/output_topic", LaunchConfiguration("get_path_change_ready")),
            ("force_available_relay/input_topic", LaunchConfiguration("input_path_change_force_available")),
            ("force_available_relay/output_topic", LaunchConfiguration("get_path_change_force_available")),
            ("running_modules_relay/input_topic", LaunchConfiguration("input_path_change_running")),
            ("running_modules_relay/output_topic", LaunchConfiguration("get_path_change_running")),
            ("autoware_engage_relay/input_topic", LaunchConfiguration("set_engage")),
            ("autoware_engage_relay/output_topic", LaunchConfiguration("output_autoware_engage")),
            ("vehicle_engage_relay/input_topic", LaunchConfiguration("set_engage")),
            ("vehicle_engage_relay/output_topic", LaunchConfiguration("output_vehicle_engage")),
            ("put_route_relay/input_topic", LaunchConfiguration("set_route")),
            ("put_route_relay/output_topic", LaunchConfiguration("output_route")),
            ("put_goal_relay/input_topic", LaunchConfiguration("set_goal")),
            ("put_goal_relay/output_topic", LaunchConfiguration("output_goal")),
            ("lane_change_approval_relay/input_topic", LaunchConfiguration("set_lane_change_approval")),
            ("lane_change_approval_relay/output_topic", LaunchConfiguration("output_lane_change_approval")),
            ("force_lane_change_relay/input_topic", LaunchConfiguration("set_force_lane_change")),
            ("force_lane_change_relay/output_topic", LaunchConfiguration("output_force_lane_change")),
            ("external_approval_relay/input_topic", LaunchConfiguration("set_path_change_approval")),
            ("external_approval_relay/output_topic", LaunchConfiguration("output_path_change_approval")),
            ("force_approval_relay/input_topic", LaunchConfiguration("set_path_change_force")),
            ("force_approval_relay/output_topic", LaunchConfiguration("output_path_change_force")),
            ("obstacle_avoid_approval_relay/input_topic", LaunchConfiguration("set_obstacle_avoid_approval")),
            ("obstacle_avoid_approval_relay/output_topic", LaunchConfiguration("output_obstacle_avoid_approval")),
            ("traffic_signal_relay/input_topic", LaunchConfiguration("input_traffic_signals")),
            ("traffic_signal_relay/output_topic", LaunchConfiguration("get_traffic_signals")),
            ("overwrite_traffic_signals_relay/input_topic", LaunchConfiguration("set_overwrite_traffic_signals")),
            ("overwrite_traffic_signals_relay/output_topic", LaunchConfiguration("output_overwrite_traffic_signals")),
            ("speed_exceeded_relay/input_topic", LaunchConfiguration("input_stop_speed_exceeded")),
            ("speed_exceeded_relay/output_topic", LaunchConfiguration("get_stop_speed_exceeded")),
            ("crosswalk_status_relay/input_topic", LaunchConfiguration("set_crosswalk_status")),
            ("crosswalk_status_relay/output_topic", LaunchConfiguration("input_external_crosswalk_status")),
            ("intersection_status_relay/input_topic", LaunchConfiguration("set_intersection_status")),
            ("intersection_status_relay/output_topic", LaunchConfiguration("input_external_intersection_status")),
            ("expand_stop_range_relay/input_topic", LaunchConfiguration("set_expand_stop_range")),
            ("expand_stop_range_relay/output_topic", LaunchConfiguration("input_expand_stop_range")),
            ("pose_initialization_request_relay/input_topic", LaunchConfiguration("set_pose_initialization_request")),
            ("pose_initialization_request_relay/output_topic", LaunchConfiguration("input_pose_initialization_request")),
        ],
    )

    return launch.LaunchDescription([awapi_relay_static_node])
