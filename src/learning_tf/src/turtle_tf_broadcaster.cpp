/* broadcaster */
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <turtlesim/Pose.h>

std::string turtle_name;

void posecallback(const turtlesim::PoseConstPtr& msg)
{
    static tf::TransformBroadcaster br;

    // 初始化tf数据
    tf::Transform transfrom;
    transfrom.setOrigin( tf::Vector3(msg->x, msg->y, 0.0) );
    tf::Quaternion q;
    q.setRPY(0, 0, msg->theta);// 接收三个角度
    transfrom.setRotation(q);

    // 广播world与海归坐标系之间的tf数据
    br.sendTransform(tf::StampedTransform(transfrom, ros::Time::now(), "world", turtle_name) );
}
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "my_tf_broadcaster");
    ros::NodeHandle nh;
    ros::Subscriber sub;

    /* 输入参数作为海龟名字 */
    if(argc != 2)
    {
        ROS_ERROR("need turtle name as argument");
        return -1;
    }
    turtle_name = argv[1];// 给全局变量赋值

    sub = nh.subscribe(turtle_name + "/pose", 10, posecallback);

    ros::spin();

    return 0;
}
