#include "ros/ros.h"
#include "calculate_determinant/CalcDet.h"
#include <iostream>
#include <string>
#include <vector>     
#include "std_msgs/Float32.h" 

ros::Publisher publisher;
ros::Subscriber subscriber;
std::string output_topic_name;
std::string input_topic_name;

void det_callback(const std_msgs::Float32::ConstPtr& msg){
    float number = msg->data;
    if (number ==0.f)
        ROS_INFO_STREAM("det = 0");
    else
    {
        if (number-int(number) == 0)
        {
            if (int(number) % 2 == 0)
                ROS_INFO_STREAM("even");
            else
                ROS_INFO_STREAM("odd");
        }
        else
            ROS_INFO_STREAM("odd");

    }


}

void check_number(std::string number)
{
    if (number.find_first_not_of( "-0123456789" ) != std::string::npos)
    {
        ROS_ERROR("Please enter matrix elements from 0 to 10...");
        ROS_BREAK();
    }
}

std::vector<int> split(std::string str, std::string delimiter)
{
    std::vector<int> matrix;
    int start = 0;
    int end = str.find(delimiter);
    std::string number;
    while (end != -1) {
        number = str.substr(start, end - start);
        check_number(number);
        matrix.push_back(std::stoi(number));
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }
    number = str.substr(start, end - start);
    check_number(number);
    matrix.push_back(std::stoi(number));
    return matrix;
}

bool calc_det(calculate_determinant::CalcDet::Request &req,
              calculate_determinant::CalcDet::Response &res)
{
    std::vector<int> matrix;
    matrix = split(req.matrix, " ");
    if (matrix.size() != 9)
    {
        ROS_ERROR("Number of matrix elements is not equal to 9!");
        ROS_BREAK();
    }
    else
    {
        res.det = matrix[0] * matrix[4] * matrix[8] +
                  matrix[3] * matrix[7] * matrix[2] +
                  matrix[1] * matrix[5] * matrix[6] -
                  matrix[2] * matrix[4] * matrix[6] -
                  matrix[0] * matrix[5] * matrix[7] -
                  matrix[1] * matrix[3] * matrix[8] ;

        ROS_INFO_STREAM("determinant of the matrix is:" << res.det);

    }

    std_msgs::Float32 det;
    det.data = float(res.det);
    publisher.publish(det);
    
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"calcelate_det_server");
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("calcelate_det",calc_det);

    publisher = n.advertise<std_msgs::Float32>("topic_det", 10);
    subscriber = n.subscribe("topic_det",10,det_callback);
    ROS_INFO_STREAM("READY");
    ros::spin();
    return 0;
}
