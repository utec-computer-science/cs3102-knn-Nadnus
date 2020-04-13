#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include<math.h>
using namespace std;
template <typename T>
class CartesianCoord
{
public:
    typedef T value_t;
    value_t x;
    value_t y;
    value_t myDistance = 0;
    value_t distance(CartesianCoord & other){
        value_t toReturn = sqrt(pow(x - other.x,  2)+ pow(y - other.y, 2));
        other.myDistance = toReturn;
        return toReturn;
    }
    
    

public:
    CartesianCoord(value_t _x = 0, value_t _y = 0) : x(_x), y(_y) {}
    ~CartesianCoord(void) {}
    template <typename _T>
    friend ostream &operator  <<(ostream &out, const CartesianCoord<_T> c)
    {
        out << "(" << c.x << "," << c.y << ")";
        return out;
    }
};
template<typename T>
bool compare(CartesianCoord<T> my ,CartesianCoord<T> other){
        return (my.myDistance < other.myDistance)
    }

typedef CartesianCoord<int> coord_t;
vector<coord_t> knn(int k, vector<coord_t> &points,  coord_t &q)
{ 
    for(coord_t &myCoord:points){
        q.distance(myCoord);
    }
    std::sort(points.begin(),points.end(),compare<decltype(q.x)>);
    vector<coord_t> toReturn = vector<coord_t>(points.begin(),points.begin() + k);
    return toReturn;
}
int main()
{
    srand(time(NULL));
    vector<coord_t> points;
    for (int i = 0; i < 1000; i++)
        points.push_back(coord_t(rand() % 1000, rand() % 1000));
    vector<coord_t>::iterator it = points.begin();
    for (; it != points.end(); it++)
    {
        fflush(stdout);
        cout << "\r" << *it;
        usleep(2000);
    }
    cout << endl;
    vector<coord_t> knns;
    auto start = chrono::high_resolution_clock::now();
    auto buffer = coord_t(100, 200);
    knns = knn(3, points, buffer);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time: " << endl;
    cout << duration.count() << endl;
    cout << "knns" << endl;
}