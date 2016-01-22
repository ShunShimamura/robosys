#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
 
class turtleSim{
public:
    turtleSim();
    ~turtleSim();
    void poseCallback(const turtlesim::PoseConstPtr& pose);
    void setMoveVector(float linear_x);
    void setTurnVector(float angular_x);
    void timerCallback(const ros::TimerEvent&);
 
private:
    ros::Publisher twist_pub;
    ros::Subscriber pose_sub;
    ros::Timer timer;
    ros::NodeHandle nh;
};
 
turtleSim::turtleSim(){
    twist_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
    pose_sub = nh.subscribe<turtlesim::Pose>("turtle1/pose", 1, &turtleSim::poseCallback, this);
    timer = nh.createTimer(ros::Duration(0.1), &turtleSim::timerCallback, this);
 
    geometry_msgs::Twist twist;
    twist.linear.x = 0.0;
    twist.linear.y = 0.0;
    twist.linear.z = 0.0;
    twist.angular.x = 0.0;
    twist.angular.y = 0.0;
    twist.angular.z = 0.0;
    twist_pub.publish(twist);
}
 
turtleSim::~turtleSim(){
 
}
 
void turtleSim::poseCallback(const turtlesim::PoseConstPtr& pose){
    ROS_INFO("x:%f",pose->x);
}
 
void turtleSim::timerCallback(const ros::TimerEvent&){
    setMoveVector(1.0);
    setTurnVector(90*M_PI/180);
    setMoveVector(1.0);
    setTurnVector(90.0*M_PI/180);
    setMoveVector(1.0);
    setTurnVector(90.0*M_PI/180);
    setMoveVector(1.0);
    setTurnVector(90.0*M_PI/180);
    ROS_INFO("finishCallBack");
}
 
void turtleSim::setMoveVector(float linear_x){
    int i;
    geometry_msgs::Twist twist;
    ros::Rate loop_rate(10);
 
    for(i = 0;i < 50; i++){
        twist.linear.x = linear_x;
        twist_pub.publish(twist);
        loop_rate.sleep();
    }

}

void turtleSim::setTurnVector(float angular_z){
    int i;
    geometry_msgs::Twist twist;
    ros::Rate loop_rate(10);

    for(i = 0;i < 10; i++){
        twist.angular.z = angular_z;
        twist_pub.publish(twist);
        loop_rate.sleep();
    }
}
 
int main(int argc, char **argv){
    ros::init(argc, argv, "move_turtlesim");
 
    turtleSim turtlesim;
 
    ros::spin();
    return 0;
}

