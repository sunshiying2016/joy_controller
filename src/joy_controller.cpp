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
  
  
  
  float lin_max_;
  
  float ang_max_;

  int num_;

  
  
public:

  geometry_msgs::Twist vel;

  ros::Publisher pub_; 
  
  joy_controller()
  {
    
  }
  ~joy_controller()
  {
    
  }

  void init()
  {
    sub_ = n_.subscribe("/joy", 10, &joy_controller::joyCallback, this);
    pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    lin_max_ = 0.5;
    ang_max_ = 0.5;
    num_ = 0;
  }
  
  void joyCallback(const sensor_msgs::Joy::ConstPtr& msg)
  {
//     std::cout<<"!!!!!!!!!!!!!!!!"<<std::endl;
    
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
      float ang_joy = msg->axes[0] * ang_max_;    //角速度
      float lin_joy = msg->axes[1] * lin_max_;
      std::cout<<"lin: "<<lin_joy<<"; ang: "<<ang_joy<<std::endl;
      //num_++;
      //std::cout<<num_<<std::endl;
      //if(num_==5000)
      //{num_=0;}
      
//       std::cout<<"ang: "<<ang_joy<<std::endl;
      vel.linear.x = lin_joy;
      vel.angular.z = ang_joy;
//      pub_.publish(vel);
    }
    
    
  }
  
};

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "joy_controller");

  joy_controller jc;
  jc.init();
  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    jc.pub_.publish(jc.vel);
    ros::spinOnce();
    loop_rate.sleep();
  }



  
 // ros::spin();

  return 0;
}
