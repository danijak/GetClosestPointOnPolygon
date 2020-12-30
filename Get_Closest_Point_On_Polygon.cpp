#include<iostream>
#include <vector> 
#include<math.h>
#include <climits>
using namespace std; 

// Using Struct to define point
struct Point{
    double x;
    double y;
};

// Using Jordan curve theorem -For point inside the polygon
bool isPointInside(vector<Point> polygon, Point point){
	bool c=false; // true if point is inside the polygon else false
	int i,j;
	int n=polygon.size(); //Number of edges in polygon
	for(i=0,j=n-1; i<n;j=i++){
		if(((polygon[i].y>point.y) != (polygon[j].y>point.y)) && (point.x < (polygon[j].x-polygon[i].x) * (point.y-polygon[i].y) / (polygon[j].y-polygon[i].y) + polygon[i].x) )
			c=!c;
	}
	return c;
}

// For point on Polygon(on edge) 
bool isPointOnEdge(vector<Point> polygon, Point point){
    int n=polygon.size(); //Number of edges in polygon
    double distance1,distance2,distance3; //distance1 represents AP, distance2 represents PB and distance3 represents AB
    bool result=false; //if point is on the edge or not
    int i,j;
    for(i=0,j=n-1; i<n;j=i++){       
        distance1=sqrt(pow((polygon[i].x-point.x),2)+pow((polygon[i].y-point.y),2)); // Euclidean distance
        distance2=sqrt(pow((polygon[j].x-point.x),2)+pow((polygon[j].y-point.y),2));
        distance3=sqrt(pow((polygon[i].x-polygon[j].x),2)+pow((polygon[i].y-polygon[j].y),2));
        if(distance1+distance2==distance3)
        {
            result=true;
            break;
        }               
    }
    return result;
}

// For point outside the Polygon
struct Point findMinimunPerpendicularDistance(vector<Point> polygon, Point point){	
	struct Point p,min_pt;
	double a,b,c,d,dot,len_sq,cos_theta=-1, min_dist=100000, dist;
	int i,j;
	int n=polygon.size();
	for(i=0,j=n-1; i<n;j=i++){		
		a=point.x-polygon[i].x;
		b=point.y-polygon[i].y;
		c=polygon[j].x-polygon[i].x;
		d=polygon[j].y-polygon[i].y;
		dot=a*c+b*d;
		len_sq=c*c+d*d;
		cos_theta=dot/len_sq;
		if(cos_theta<0){
			p.x=polygon[i].x;
			p.y=polygon[i].y;
		}
		else if(cos_theta>1){
			p.x=polygon[j].x;
			p.y=polygon[j].y;
		}
		else{
			p.x=polygon[i].x+cos_theta*c;
			p.y=polygon[i].y+cos_theta*d;
		}
		double dx=point.x-p.x;
		double dy=point.y-p.y;
		dist=sqrt(dx*dx+dy*dy);
		if(dist<min_dist){
			min_pt.x=p.x;
			min_pt.y=p.y;
			min_dist=dist;
		}
	}
	return min_pt;
}

// called in main function
Point getClosestPointInsidePolygon(vector<Point> polygon, Point point){

    struct Point p;
   // Case 1: Check if point is inside the polygon
    if(isPointInside(polygon,point))
        return point;
   //Case 2: If point is on the edge
   if(isPointOnEdge(polygon,point))
        return point;
   //Case 3: When point is outside find the perpendicular projection 
    p = findMinimunPerpendicularDistance(polygon,point);
  return p;

}

// main function with input and output return closest point on polygon 
int main(){

    vector<Point> polygon;
    struct Point p;
    int n;
    cout<<"Enter the sides of polygon";
    cin>>n;
    struct Point temp;
    for(int i=0;i<n;i++){
		cout<<"Enter the (x"<<i+1<<","<<"y"<<i+1<<")"<<endl;
        cin>>temp.x>>temp.y;
        polygon.push_back(temp);

    }    
    cout<<"Enter the coordinates(x,y) of the point";
    cin>>p.x>>p.y;
    struct Point output;
    output = getClosestPointInsidePolygon(polygon,p);
    cout<<"("<<output.x<<" , "<<output.y<<")"<<endl;
    return 0;
}
