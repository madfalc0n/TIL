# ROS tutorial Topic

ROS 프로그램에서 어떠한 로봇을 키보드를 이용하여 움직인다고 가정하자. 이 경우, 로봇과 키보드 사이에 통신경로가 존재하는 것으로 이 통신경로를 `토픽(Topic)`이라고 한다. 이 토픽을 통해 서로다른 노드간의 정보를 주고받는다. 로봇(노드1)과 키보드(노드2)사이 키보드로 부터 전달되는 정보를 토픽을 통해 로봇에게 전달되며 로봇은 그 정보를 토대로 행동을 수행하게 된다.

이 과정에서 정보를 주는자(publish)와 받는자(subscriber)로 구분된다.



## 0. 준비과정

해당과정을 실습하기 위해서는 ROS 패키지를 선행적으로 만들어야 함

1. cd ~/catkin_ws/src
2. catkin_create_pkg <패키지명> rospy std_msgs
3. cd ~/catkin_ws
4. catkin_make
5. source devel/setup.bash
6. rospack profile
7. roscd my_examples_pkg
8. mkdir scripts



## 1. Publisher

노드가 활성화 되어있다고 가정할 때 우리는 topic을 통해 주고받는 내용을 `rostopic`명령어를 이용하여 확인할 수 있다.

publisher에 대한 노드를 활성화하고 간단한 메시지를 전송하는 코드를 작성해보자(해당패키지/scripts 에 .py파일로 생성, 생성후 파일 수정 권한 추가해주어야 함).

```python
#! /usr/bin/env python

import rospy                               # ROS 라이브러리 호출
from std_msgs.msg import Int32             # 32bit 숫자형 메시지를 담기위한 패키지 import 

rospy.init_node('topic_publisher')         # 'topic_publisher'라는 이름의 노드를 init
pub = rospy.Publisher('/counter', Int32, queue_size=1)    
                                           # '/counter'라는 이름의 Publisher object 생성
                                           # messages of type Int32

rate = rospy.Rate(2)                       # publish rate of 2 Hz 주기로 설정
count = Int32()                            # Create a var of type Int32
count.data = 0                             # Initialize 'count' variable

while not rospy.is_shutdown():             # 프로그램 종료시 까지 무한루프
  pub.publish(count)                       # Publish the message within the 'count' variable
  count.data += 1                          # count 값 + 1
  rate.sleep()                             # Make sure the publish rate maintains at 2 Hz
```

완료 후 해당파일을 python 명령어 또는 rosrun 명령어를 통해 실행시켜보자(.py파일이 있는 경로에서 실행)

```bash
python <생성한파일.py> 또는 rosrun <패키지명> <생성한파일.py>
```

실행 후 쉘에서는 아무런 내용도 발생하지 않을 것이다. 실행을 끄지말고 새로운 쉘을 열어서 아래의 명령어들을 통해 확인해보자.

```bash
#rostopic list 명령어를 이용하여 현재 topic이 활성화된 리스트를 출력, grep 명령어를 이용하여 /counter 확인
user:~/catkin_ws/src/myoung_lab/scripts$ rostopic list | grep /counter
/counter


#rostopic info 명령어를 이용하여 해당 topic에 대한 세부정보 확인가능
user:~/catkin_ws/src/myoung_lab/scripts$ rostopic info /counter
Type: std_msgs/Int32

Publishers:
 * /topic_publisher (http://12_xterm:46727/)

Subscribers: None


#rostopic echo 명령어를 이용하여 주고받는 내용 확인 가능
user:~/catkin_ws/src/myoung_lab/scripts$ rostopic echo /counter
data: 203
---
data: 204
---
data: 205
---
data: 206
---
^C
user:~/catkin_ws/src/myoung_lab/scripts$

```

