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

# launch
## node标签
- `pkg`:节点所在的功能包名称
- `type`：节点的可执行文件名
- `name`：节点运行时的名称，会覆盖节点内初始化时定义的节点名
- `output`：一般是screen
- `respawn`：
- `required`：
- `ns`：命名空间，
- `args`：

## param/rosparam
设置ros系统运行中的参数，存储在参数服务器
`<param name="output_frame" value="odom"/>`
- `name`：参数名
- `value`：参数值
如果需要加载一个参数文件里多个参数
`<rosparam file="params.yaml" command="load" ns="params"/>`

## arg
launch文件内部的局部变量
```
<arg name="arg-name" default="arg-value"/>
```
- `name`:参数名
- `value`：参数值

- 调用
`<param name="foo" value="$(arg arg-name)"/>`，`<node name="node" pkg="package" type="type" args="$(arg arg-name)"/>`

## 重映射
- remap
`<remap from="/turtlebot.cmd_vel" to="/cmd_vel"/>`
- `from`原命名
- `to`：映射之后的名字

## 嵌套
`<include file="$(dirname)/other.launch"/>`
- file：包含其他的launch文件

# 可视化工具
## rqt工具箱
- `rqt`:综合工具，所有下面的工具的集合，可以作为开发工具的上位机
- `rqt_console`:可以查看日志输出，并筛选对自己有用的警告与报错
- `rqt_plot`:查看变量的曲线变化
- `rqt_image_view`:图像rgb节点的输出
## Rviz
数据显示平台

## gazebo
物理仿真平台



