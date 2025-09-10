# broadcaster
# 前提
## 安装tf
```
sudo apt-get install ros-noetic-turtle-tf
```
## tf的一些可视化工具
`rosrun tf view_frames`可以输出一个pdf查看tf树关系，其中world是世界的坐标原点
`rosrun tf tf_echo turtle1 turtle2`:可以查看两个的坐标关系
## rviz
三维可视化平台

# 坐标公式
T-turtle1_turtle2 = T-turtle1_world * T-turtle2_world

# 编程实现
首先创建tf的广播器，这个广播器创建了坐标变换值，发布坐标变换，
然后通过另一个节点创建一个监听器，通过这个监听器

## 代码解释
```
// 获取tf数据
listener.lookupTransform("/turtle2", "/turtle1", ros::Time(0), transform);
```
- `lookupTransform(target_frame, source_frame, time, transform)`：查询target_framei相对source_frame的坐标转换，也就是turtle2相对turtle1的位置关系，最后将查询到的数据保存到transfrom

```
// 角速度控制
vel_msg.angular.z = 4.0 * atan2(transform.getOrigin().y(), transform.getOrigin().x());
```
- `transform.getOrigin().x()`、`.y()` 就是 turtle1 在 turtle2 坐标系中的坐标。
- 用 `atan2(y, x)` 算夹角 → turtle2 应该转向 turtle1 的方向。

```
// 线速度控制
vel_msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(), 2) + pow(transform.getOrigin().y(), 2));
```
- `sqrt(x²+y²)` = 两只乌龟之间的距离

## 运行
```
roscore
rosrun turtlesim turtlesim_node
rosrun learning_tf turtle_tf_broadcaster __name:=turtle1_tf_broadcaster /turtle1
rosrun learning_tf turtle_tf_broadcaster __name:=turtle2_tf_broadcaster /turtle2
rosrun learning_tf turtle_tf_listener
```