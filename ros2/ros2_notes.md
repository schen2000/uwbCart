

# Gazebo Spawn
## use spawn_entity service
* https://zmk5.github.io/general/demo/ros2-spawning-entity/
* https://discourse.ros.org/t/spawning-a-robot-entity-using-a-node-with-gazebo-and-ros-2/9985
* https://automaticaddison.com/how-to-simulate-a-robot-using-gazebo-and-ros-2/

## use cmd
* https://github.com/ros-simulation/gazebo_ros_pkgs/issues/1236
 ( ros2 run gazebo_ros spawn_entity.py -file $HOME/dev_ws/src/urdf_tutorial/urdf/05-visual.urdf -entity 05 )

## use robot_state_publish
* https://github.com/atinfinity/megarover_samples_ros2/blob/foxy/launch/robot_state_publisher.launch.py
* https://answers.ros.org/question/314607/spawn-model-with-ros2-gazebo/
