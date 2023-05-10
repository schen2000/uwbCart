
# Ref : https://automaticaddison.com/how-to-simulate-a-robot-using-gazebo-and-ros-2/


import os
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription,DeclareLaunchArgument
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import ThisLaunchFileDir,LaunchConfiguration, Command
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


  
    #---- load urdf 1
    urdf_file_name = 'urdf/cart.urdf.xacro'
    print("urdf_file_name : {}".format(urdf_file_name))
    urdf = os.path.join(pkg_dir, urdf_file_name)
#    with open(urdf, 'r') as infp:
#        robot_desc = infp.read()

    #---- load urdf 2
    xacro_path = LaunchConfiguration('xacro_path', default=urdf)

    #----- robot state
        # ref : https://answers.ros.org/question/361623/ros2-robot_state_publisher-xacro-python-launch/
    robot_state_node = Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            output='screen',
        #    parameters=[{'use_sim_time': use_sim_time, 'robot_description': robot_desc}],
        #        arguments=[urdf])
            parameters=[{'robot_description': Command(['xacro ',  xacro_path])}]            
            )
    #----
    #---- spawn robot cart ------
    spawn_cart = Node(package='gazebo_ros', executable='spawn_entity.py',
                        arguments=['-entity', 'cart', '-topic', '/robot_description'],
                        output='screen')

    #----- final return ----
    return LaunchDescription([
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='false',
            description='Use simulation (Gazebo) clock if true'),
        gazebo,
        robot_state_node,
        spawn_cart
    ])
