
# Ref : https://automaticaddison.com/how-to-simulate-a-robot-using-gazebo-and-ros-2/


import os
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import ThisLaunchFileDir,LaunchConfiguration
from launch_ros.actions import Node
from launch.actions import ExecuteProcess
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time', default='True')
    world_file_name = 'tinyroom.world'

    pkg_dir = get_package_share_directory('uwbcart_ros')
    os.environ["GAZEBO_MODEL_PATH"] = os.path.join(pkg_dir, 'models')

    world = os.path.join(pkg_dir, 'worlds', world_file_name)
    launch_file_dir = os.path.join(pkg_dir, 'launch')

    gazebo = ExecuteProcess(
            cmd=['gazebo', '--verbose', world, '-s', 'libgazebo_ros_init.so', 
            '-s', 'libgazebo_ros_factory.so'],
            output='screen')

    #GAZEBO_MODEL_PATH has to be correctly set for Gazebo to be able to find the model
    #spawn_entity = Node(package='gazebo_ros', node_executable='spawn_entity.py',
    #                    arguments=['-entity', 'demo', 'x', 'y', 'z'],
    #                    output='screen')
    
    #spawn_entity = Node(package='warehouse_robot_spawner_pkg', executable='spawn_demo',
    #                    arguments=['WarehouseBot', 'demo', '-1.5', '-4.0', '0.0'],
    #                    output='screen')


    #---- spawn robot cart ------
    urdf_file_name = 'urdf/cubeBot.gazebo.xacro'
    print("urdf_file_name : {}".format(urdf_file_name))
    urdf = os.path.join(
      get_package_share_directory('uwbcart_ros'),
      urdf_file_name)

    cart = Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            output='screen',
            parameters=[{'use_sim_time': use_sim_time}],
            arguments=[urdf])

    return LaunchDescription([
        gazebo,
        cart
     #   spawn_entity,
    ])
