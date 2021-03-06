#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <sstream>

using namespace std;

ros::Publisher velocity_publisher;
ros::Subscriber pose_subscriber;
turtlesim::Pose turtlesim_pose;

const double PI = 3.14159265359;

void move(double speed, double distance, bool isForward);
void rotate(double angular_speed, double angle, bool cloclwise);
void poseCallback(const turtlesim::Pose::ConstPtr & pose_message);
//void circle(double radius, double turn_angle, bool clockwise);

int main(int argc, char **argv)
{
// Initiate new ROS node named "robosys_turtle"
ros::init(argc, argv, "robosys_turtle");
ros::NodeHandle n;
double speed, angular_speed;
double distance, angle;
bool isForward, clockwise;


velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
pose_subscriber = n.subscribe("/turtle1/pose", 10, poseCallback);
ros::Rate loop_rate(0.5);

move(2,3,1);

for(int i=0; i<4; i++){
rotate(2,4/PI,0);
move(2,2,1);

}

rotate(2,4/PI,1);

move(2,3,1);

for(int i=0; i<4; i++){
rotate(2,4/PI,0);
move(2,2,1);

}
rotate(2,3/PI,1);

move(2,3,1);

for(int i=0; i<4; i++){
rotate(2,4/PI,0);
move(2,2,1);

}

ros::spin();

return 0;
}
void move(double speed, double distance, bool isForward)
{
geometry_msgs::Twist vel_msg;
//set a random linear velocity in the x-axis
if (isForward)
vel_msg.linear.x =abs(speed);
else
vel_msg.linear.x =-abs(speed);
vel_msg.linear.y =0;
vel_msg.linear.z =0;
//set a random angular velocity in the y-axis
vel_msg.angular.x = 0;
vel_msg.angular.y = 0;
vel_msg.angular.z =0;

double t0 = ros::Time::now().toSec();
double current_distance = 0.0;
ros::Rate loop_rate(100);
do{
velocity_publisher.publish(vel_msg);
double t1 = ros::Time::now().toSec();
current_distance = speed * (t1-t0);
ros::spinOnce();
loop_rate.sleep();

}while(current_distance<distance);

vel_msg.linear.x =0;
velocity_publisher.publish(vel_msg);
}

void rotate (double angular_speed, double relative_angle, bool clockwise)
{
geometry_msgs::Twist vel_msg;
//set a random linear velocity in the x-axis
vel_msg.linear.x =0;
vel_msg.linear.y =0;
vel_msg.linear.z =0;
//set a random angular velocity in the y-axis
vel_msg.angular.x = 0;
vel_msg.angular.y = 0;
if (clockwise)
vel_msg.angular.z =-abs(angular_speed);
else
vel_msg.angular.z =abs(angular_speed);

double t0 = ros::Time::now().toSec();
double current_angle = 0.0;
ros::Rate loop_rate(1000);
do{
velocity_publisher.publish(vel_msg);
double t1 = ros::Time::now().toSec();
current_angle = angular_speed * (t1-t0);
ros::spinOnce();
loop_rate.sleep();
//cout<<(t1-t0)<<", "<<current_angle <<", "<<relative_angle<<endl;
}while(current_angle<relative_angle);
vel_msg.angular.z =0;
velocity_publisher.publish(vel_msg);
}

void poseCallback(const turtlesim::Pose::ConstPtr & pose_message)
{
turtlesim_pose.x=pose_message->x;
turtlesim_pose.y=pose_message->y; turtlesim_pose.theta=pose_message->theta;
}
