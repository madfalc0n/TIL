# ROS mange

ROS를 관리하는 방법





## 1. ROS install in my local computer

로컬에 ROS를 설치해보자! 자세한 내용은 [위키](http://wiki.ros.org/noetic/Installation)를 참조

ROS 버전: Noetic

Ubuntu 버전: 20.04 Focal



## 2. workspace 관리

During the whole Course, you have been working within a directory called **catkin_ws**. As you may already know, this directory is known as the **catkin workspace** or **ROS workspace**, and it is basically the place where you will have to place all the new ROS packages that you create. But... How do you create one of these workspaces? Is it possible to have more than one workspace?

During the Course, this workspace was already provided to you, so you just had to worry about putting all your packages inside there. But now, let's try to answer some of these interesting questions during the following Notebook.

### A.2.1  Create a ROS workspace 

For this example, you can use the same Robot Ignite Academy environment you've been working during the whole Course. You will just add a new workspace to it.

First of all, let's create the folder where we will create our ROS workspace.

  **Execute in Local Shell #1**

In [ ]:

```
mkdir -p ~/mynew_ws/src
```

Now, you will need to compile it by running the **catkin_make** command.

  **Execute in Local Shell #1**

In [ ]:

```
cd ~/mynew_ws/
```

In [ ]:

```
catkin_make
```

You already know about **catkin_make** command, don't you? You've used it along the course in order to compile your packages. The **catkin_make** command is a convenience tool for working with catkin workspaces. Running it the first time in your workspace, it will create the **CMakeLists.txt** file in your **src** folder. Also, if you look in your current directory you should now have a **build** and **devel** folder. Inside the **devel** folder you can see that there are now several *setup.\*sh* files. Sourcing any of these files will overlay this workspace on top of your environment.

  **Execute in Local Shell #1**

In [ ]:

```
source devel/setup.bash
```

To make sure your workspace is properly overlayed by the setup script, you can check the **ROS_PACKAGE_PATH** environment variable with the following command.

  **Execute in Local Shell #1**

In [ ]:

```
echo $ROS_PACKAGE_PATH
```

If everything goes fine, you should get the following:

In [ ]:

```
user:~/mynew_ws$ echo $ROS_PACKAGE_PATH
/home/user/mynew_ws/src:/home/user/catkin_ws/src:/home/simulations/public_sim_ws/src:/opt/ros/noetic/share
```

As you can see, your new workspace, named **mynew_ws**, is now on top of the **catkin_ws** you've been using during the whole course.

**NOTE**: Bear in mind that the IDE is configured to work only with 1 workspace, which is the **catkin_ws**, so you won't be able to visualize this new workspace within the IDE.

\- Exercise A.1 -

a) Now, repeat the whole process with your local computer. Create a new workspace in your local ROS installation, which you completed in **Appendix 1**.

After you setup your workspace in your local ROS installation, you'll be able to start creating new ROS packages there, or even download and place there the ones you created during the Course!

\- End of Exercise A.1 -

**Congratulations!** You are now able to download and use all the packages you created during the Course into your local machine. Enjoy it! And... keep pushing your ROS learning!