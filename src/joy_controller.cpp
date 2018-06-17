#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <iostream>

// using namesapce std;




class joy_controller
{
  ros::NodeHandle n_;

  ros::Subscriber sub_; 
  
  ros::Publisher pub_; 
  
  float lin_max_;
  
  float ang_max_;
  
public:
  
  joy_controller()
  {
    
  }
  ~joy_controller()
  {
    
  }

  void init()
  {
    sub_ = n_.subscribe("/joy", 1000, &joy_controller::joyCallback, this);
    pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
    lin_max_ = 0.3;
    ang_max_ = 0.3;
  }
  
  void joyCallback(const sensor_msgs::Joy::ConstPtr& msg)
  {
//     std::cout<<"!!!!!!!!!!!!!!!!"<<std::endl;
    geometry_msgs::Twist vel;
//     vel.linear.x = 0;
//     vel.angular.z = 0;
    if(msg->buttons[1]==1)
    {
      vel.linear.x = 0;
      vel.angular.z = 0;
      pub_.publish(vel);
    }
    
    if(msg->buttons[0]==1)
    {
      vel.linear.x = 1;
      vel.angular.z = 1;
      float ang_joy = msg->axes[0] * ang_max_;    //角速度
      float lin_joy = msg->axes[1] * lin_max_;
      std::cout<<"lin: "<<lin_joy<<"; ang: "<<ang_joy<<std::endl;
//       std::cout<<"ang: "<<ang_joy<<std::endl;
      pub_.publish(vel);
    }
    
    
  }
  
};

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "joy_controller");

  joy_controller jc;
  jc.init();
  

  
  ros::spin();

  return 0;
}
