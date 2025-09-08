#include <ros/ros.h>
#include "turtlesim/Spawn.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "turtle_spawn");
    ros::NodeHandle nh;
    ros::service::waitForService("/spawn");
    ros::ServiceClient add_spawn_client;

    add_spawn_client = nh.serviceClient<turtlesim::Spawn>("/spawn");

    turtlesim::Spawn srv;
    srv.request.name = "machao";
    srv.request.x = 1;
    srv.request.y = 1;
    ROS_INFO("Call service to spawn turtle[x:%.2f, y:%.2f, name:%s]",srv.request.x, srv.request.y, srv.request.name.c_str());

    add_spawn_client.call(srv);// send and wait
    ROS_INFO("Spawn turtle [name:%s]",srv.response.name.c_str());
    return 0;
}
