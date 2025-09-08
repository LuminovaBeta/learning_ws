# 自定义话题信息

1. 定义msg文件
2. 在package.xml添加功能包依赖
```
<build_depend>message_generation</build_depend>
<exec_depend>message_runtime</exec_depend>
```
3. 在CMakeLists.txt添加编译选项
-  find_package(... message_generation)
-  add_message_files( FILES MyStatus.msg)
-  generate_messages(DEPENDENCIES std_msgs)
-  catkin_package(... message_runtime)
-  **注意！这里一定要注意顺序**
4. 编译生成语言相关文件

- `depend`：依赖
- `message_generation`：generation(产生)，顾名思义，这个依赖的作用是，编译期需要它来生成 *.h（C++）/ *.py（Python）等代码。
- `message_runtime`：runtime(运行时)，运行期需要它来提供已生成消息给你和依赖你的其他包使用。

# 配置代码编译规则
复制源代码的这三行，将
```
add_executable(${PROJECT_NAME}_node src/learning_topic_node.cpp)
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})
add_dependencies(${PROJECT_NAME}_node
                 ${${PROJECT_NAME}_EXPORTED_TARGETS}
                 ${catkin_EXPORTED_TARGETS})
```

