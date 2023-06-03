#include<ros/ros.h>
#include<std_msgs/String.h>
#include<iostream>
#include<stdlib.h>


class ros_ru_interface
{
private:
    ros::NodeHandle* nh;
    ros::Subscriber ru_sub;
    ros::Publisher ru_pub;
    std_msgs::StringPtr str_msg;
public:
    ros_ru_interface(ros::NodeHandle* pNh = NULL);
    ~ros_ru_interface();
    void ru_sub_callback(const std_msgs::String::ConstPtr& msg);
};

ros_ru_interface::ros_ru_interface(ros::NodeHandle* pNh ):
nh(pNh),
ru_sub((nh->subscribe("RU_dbg_topic",1000,&ros_ru_interface::ru_sub_callback,this))),
// ru_pub(/*(nh->advertise<std_msgs::String>("chatter",1000))*/ ),
// ru_pub(),
str_msg(new std_msgs::String)
{
   ru_pub= ((*nh).advertise<std_msgs::String>("chatter",1000));
}

ros_ru_interface::~ros_ru_interface()
{
    nh = NULL;
}

void ros_ru_interface::ru_sub_callback(const std_msgs::String::ConstPtr& msg)
{
    for(int i = 0; i < msg->data.size()  ; i++)
    {
        char* name = (char*) malloc(20*sizeof(char));
        int n = (int)((msg->data.data())[i] - '0');
        ROS_INFO(" [ROS_RU_NODE] n == %d",n);
        switch (n)
        {
        case 1:
            strcpy(name , "Almoco");
            break;
        
        case 2:
            //name = "Jantar";
            strcpy(name , "Jantar");
            break;
        
        case 3:
            //name = "Pao de Queijo";
            strcpy(name , "Pao de Queijo");
            break;
        default:
            // name = "Empty";
            strcpy(name , "Empty");
            break;
        }
        str_msg->data=name;  // copy the name content //
        ru_pub.publish(str_msg);
        str_msg->data.clear();
        free(name);
        name =NULL;
    }

}


int main(int argc, char **argv)
{
    ros::init(argc,argv,"ru_interface");

    ros::NodeHandle nh ;

    ros_ru_interface ru_intf (&nh);

    while(ros::ok()){ros::spinOnce();}

}
