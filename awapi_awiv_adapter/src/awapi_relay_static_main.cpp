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

  {
    auto param_node = std::make_shared<rclcpp::Node>(
      "param_reader",
      rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true)
    );

    auto create_relay = [&](const std::string & name) {
      std::string input_topic_param = name + ".input_topic";
      std::string output_topic_param = name + ".output_topic";

      std::string input_topic = "";
      std::string output_topic = "";

      if (param_node->has_parameter(input_topic_param)) {
        input_topic = param_node->get_parameter(input_topic_param).as_string();
      } else {
        RCLCPP_ERROR(
          rclcpp::get_logger("awapi_relay_static"),
          "Missing required parameter: %s", input_topic_param.c_str()
        );
        throw std::runtime_error("Missing parameter: " + input_topic_param);
      }

      if (param_node->has_parameter(output_topic_param)) {
        output_topic = param_node->get_parameter(output_topic_param).as_string();
      } else {
        RCLCPP_ERROR(
          rclcpp::get_logger("awapi_relay_static"),
          "Missing required parameter: %s", output_topic_param.c_str()
        );
        throw std::runtime_error("Missing parameter: " + output_topic_param);
      }

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
  }

  exec->spin();

  rclcpp::shutdown();

  return 0;
}
