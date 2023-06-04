#include"printtest.h"
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<printtest.h>
#include<iostream>
#include<sstream>
#include<ros/ros.h>
#include<std_msgs/String.h>
using namespace std;


class Printer_Node_Subscriber
{   
    private:

    int error ;
    ostringstream buf;
    ros::NodeHandle n_h;
    ros::Subscriber sub;
    ros::Rate lRate;
    char* com_port_;

    public:
    Printer_Node_Subscriber(ros::NodeHandle & nd, int _argc, char** _argv);
    ~Printer_Node_Subscriber();
    void loop();
    void list_Callback (const std_msgs::String::ConstPtr& msg);
    int bufftest();
    
};


Printer_Node_Subscriber::Printer_Node_Subscriber(ros::NodeHandle & nd, int _argc, char** _argv):buf(),error(0),n_h(nd),lRate(30)
{
    sub = n_h.subscribe("chatter", 1, &Printer_Node_Subscriber::list_Callback,this);

    ROS_INFO("[ROS_PRINTER] Init subscriber");

    com_port_ =(char*) malloc(30*sizeof(char));

    if(_argc>=2)
    {
        strcpy(com_port_,_argv[1]);
    }
    else
    {
        strcpy(com_port_,COM_PORT);
    }

    if (AbreConexaoImpressora(T_RS232, MODEL, com_port_, BAUD_R) == OPEN)
    {
        ROS_INFO("[ROS_PRINTER] Init printer");
        buf<<0<<0<<0;
        buf << ImpressaoTexto("Hello Printer\n", 0, 0, 1)
            //<<AvancaPapel(1)
            << Corte(2) << endl;
        ROS_INFO("[ROS_PRINTER] init stats: [%s]", (buf.str()).c_str());

        
        if(bufftest()==0){ROS_INFO("[ROS_PRINTER] SUCESS init printer");}
    }
    else
    {   
        error=-1;
        ROS_INFO("[ROS_PRINTER] Error opening communication with printer");
    }


}

Printer_Node_Subscriber::~Printer_Node_Subscriber()
{

}

void Printer_Node_Subscriber::loop()
{
    while (error==0&&ros::ok())
    {
        lRate.sleep();
        ros::spinOnce();
        ROS_INFO("SPIN_ONCE");
    }
    cout<<FechaConexaoImpressora()<<endl;
}
int Printer_Node_Subscriber::bufftest()
{
    std::string::iterator I = buf.str().begin();
    while (I!=buf.str().end()&&(error==0))
    {
        if(*(I)=='-')
        {
            ROS_INFO("[ROS_PRINTER] Printer error !!!");   
            error=-1;
        }
        I++;
    }
    buf.str().clear();
    return(error);
}

void Printer_Node_Subscriber::list_Callback (const std_msgs::String::ConstPtr& msg)
{   
    //(buf.str()).c_str();
    if(msg->data.size()>1)
    {
    ROS_INFO("[ROS_PRINTER] I heard: [%s]", msg->data.c_str());
    buf<<ImpressaoTexto(msg->data.c_str(),0,0,1)
    <<AvancaPapel(2)
    <<Corte(2);
    ROS_INFO("[ROS_PRINTER] callback stats: [%s]", (buf.str()).c_str());
    bufftest();
    }
}

int main(int argc, char **argv)
{
    ros::init (argc,argv,"printer_node");

    ros::NodeHandle n;

    Printer_Node_Subscriber sub(n,argc,argv);

    sub.loop();

    ROS_INFO("[ROS_PRINTER] subscriber noded ended");

    return 0;

}
