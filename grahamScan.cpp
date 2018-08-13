#include <iostream>
#include <stack>
#include <stdlib.h>
#include <fstream>
#include<math.h>
using namespace std;





struct Point
{
	int x, y;
};

Point p0;

Point nextToTop(stack<Point> &S)
{
	Point p = S.top();
	S.pop();
	Point res = S.top();
	S.push(p);
	return res;
}

int swap(Point &p1, Point &p2)
{
	Point temp = p1;
	p1 = p2;
	p2 = temp;
}

int twoPointDist(Point p1, Point p2)
{
	return (p1.x - p2.x)*(p1.x - p2.x) +
		(p1.y - p2.y)*(p1.y - p2.y);
}

int orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0; // colinear
	return (val > 0)? 1: 2; // clock or counterclock wise
}

int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (twoPointDist(p0, *p2) >= twoPointDist(p0, *p1))? -1 : 1;

    return (o == 2)? -1: 1;
}

void convexHull(Point points[], int n)
{
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++)
    {
        int y = points[i].y;

        if ((y < ymin) || (ymin == y && points[i].x < points[min].x))
          {
             ymin = points[i].y,
             min = i;
          }
    }

    swap(points[0], points[min]);

    p0 = points[0];
    qsort(&points[1], n-1, sizeof(Point), compare);

    int m = 1;
    for (int i=1; i<n; i++)
    {
        while (i < n-1 && orientation(p0, points[i],points[i+1]) == 0)
        {
            i++;
        }
        points[m] = points[i];
        m++;
	}

    if (m < 3) return;

    int distance=0;
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);
    distance+=pow(twoPointDist(points[0],points[1]),0.5);
    //cout<<distance<<endl;
    distance+=pow(twoPointDist(points[1],points[2]),0.5);
    //cout<<distance<<endl;

    int i;
    for (i = 3; i < m; i++)
    {
        while (orientation(nextToTop(S), S.top(), points[i]) != 2)
            {
                S.pop();
            }
        S.push(points[i]);
        distance+=pow(twoPointDist(points[i-1],points[i]),0.5);
    }
    distance+=pow(twoPointDist(points[0],points[i]),0.5);
    cout<<distance<<"\n";
    Point solutionPoints[S.size()];
    int c=0;
    ofstream myfile;
    myfile.open ("output.txt");

    while (!S.empty())
    {
        Point p = S.top();
        solutionPoints[c]=p;
        c++;
        cout << p.x << ", " << p.y << endl;
        //myfile << p.x<<" "<<p.y<<endl;
        S.pop();
    }
    int s=sizeof(solutionPoints)/sizeof(solutionPoints[0]);
    solutionPoints[s]=solutionPoints[0];
    for(int i=0;i<s ;i++)
    {
        myfile<<solutionPoints[i].x<<" "<<solutionPoints[i].y<<" "<<solutionPoints[i+1].x<<" "<<solutionPoints[i+1].y<< endl;
    }

    myfile.close();
    //return solutionPoints;
}

int main()
{
    ifstream infile("input1.txt");
    int n;
	int a, b;
	if(infile>>a)
    {
        //cout<<a<<"\n";
        n=a;
    }
    Point points[n];


    int i=0;
    while (infile >> a >> b)
    {
        points[i]={a,b};
        i++;
        cout<<a<<","<<b<<"\n";
    }

    convexHull(points, n);

	return 0;
}
