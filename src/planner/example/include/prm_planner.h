#ifndef _PRM
#define _PRM

#include<ros/ros.h>
#include<geometry_msgs/PoseStamped.h>
#include<geometry_msgs/Point.h>
#include <vector>
using std::vector;
//3D graph implementation
//edge definition in graph
struct Edge{
    int cost;
    int adjacentVexIndex1, adjacentVexIndex2;
    struct Edge *next;
    Edge(int b, int c, int a) : adjacentVexIndex1(b), adjacentVexIndex2(c), cost(a), next(nullptr){};
};

//vertice definition in graph
struct Vertice{
    int x,y,z;
    Edge * FirstAdjacentEdge;
    Vertice(int a, int b, int c) : x(a), y(b), z(c), FirstAdjacentEdge(nullptr){};
    bool operator==(const Vertice & v){
        return v.x==x && v.y==y && v.z==z;
    }
};

class Graph{
    public:
        void insertVex(Vertice vex1);
        void insertEdge(const Vertice & vex1, const Vertice & vex2, int cost);
    private:
        vector<Vertice> VexList;
        int numVex = 0, numEdge = 0;

};

//PRM based planner
class PRM{
    public:
        PRM();
        void callback(const geometry_msgs::PoseStamped::ConstPtr& msg);
        void planner_visualization();
        void node_visualization();
        void get_map_param();
    private:
        ros::NodeHandle nh_;
        //subscribe from topic /move_base_simple/goal to get the destination
        ros::Subscriber sub_;
        //publisher the visulization of the algorithm
        ros::Publisher pub_;
        ros::Publisher prm_pub_;
        //start and end point 
        geometry_msgs::Point start,goal;
        //map size
        double map_size_x,map_size_y,map_size_z;
        //sample number
        int n_sample;
};

#endif