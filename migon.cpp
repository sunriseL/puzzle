#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>


using namespace std;
vector<vector<int> > mat; //รินฌสýื้ 
struct Point{
	int x,y;
	Point():x(1),y(1){
	}
	Point(int _x,int _y):x(_x),y(_y){
	}
}; 

map<Point,int> search;

bool operator<(const Point & a, const Point & b){
	if(a.x < b.x) return true;
	if(a.x > b.x) return false;
	return a.y < b.y;
}

struct Path{
	vector<Point> path;
	int len;
	Path(vector<Point>& s, int l):path(s),len(l){
	}
	Path():len(-1){
	}
};

bool operator==(const Point& a,const Point&b){
	return (a.x == b.x) && (a.y == b.y);
}

bool find(const Path& path,Point xy){
	int size = path.path.size();
	for(int i = 0;i < size;i++){
		if(path.path[i] == xy) return true;
	}
	return false;
}


Path shortest_path(Point xy,Path path){
	//cout << "start" << endl;
	//if(search[xy] == 1) return Path();
	//cout << xy.x << "  " << xy.y << "point searched" << endl;
	if(xy.x == mat.size()-2 && xy.y == mat[0].size()-2){
		path.path.push_back(xy);
		path.len++;
		return path;
	}
	if(xy.x == 0 || xy.y == 0 || xy.x == mat.size()-1 || xy.y == mat[0].size()-1) return Path();
	
	if(mat[xy.x][xy.y] == 1) return Path();
	//cout << 1 << endl;
	Path temp,short_path;
	path.path.push_back(xy);
	
	int min = 1000000;
	for(int i = -1;i < 2;i += 2){
		for(int j = -1;j < 2;j += 2){
			//cout << "point " << xy.x << " " << xy.y << " search " <<((i == -1)?xy.x+j:xy.x) << "  " << ((i==-1)?xy.y:xy.y+j) << endl;
			Point next = Point(((i == -1)?xy.x+j:xy.x),((i==-1)?xy.y:xy.y+j));
			if (find(path,next)) continue;
 			if(i == -1){
				temp = shortest_path(Point(xy.x+j,xy.y),path);
			}
			else{
				temp = shortest_path(Point(xy.x,xy.y + j),path);
			}
			//cout << ((i == -1)?xy.x+j:xy.x) << "  " << ((i==-1)?xy.y:xy.y+j) << "  "<<temp.len << endl;
			if(temp.len == -1) continue;
			if(temp.len < min){
				min = temp.len;
				short_path = temp;
				short_path.len++;
			}
		}
	}
	//cout << endl << endl;
	if(min == 1000000) return Path();
	return short_path;
}


int main(){
	ifstream fin("mg4.txt");
	int width,height;
	fin >> height >> width;
	for(int i = 0;i < height + 2;i++){
		mat.push_back(vector<int>(width+2));
	}
	for(int i = 0;i < height;i++){
		for(int j = 0;j < width;j++){
			fin >> mat[i+1][j+1];
		}
	}
	for(int i = 0;i < height;i++){
		for(int j = 0;j < width;j++){
			cout  << mat[i+1][j+1] << "\t";
		}
		cout << endl;
	}
	vector<Point> s;
	cout << mat.size() << "   " << mat[0].size() << endl;
	Path path = shortest_path(Point(1,1),Path(s,0));
	//cout << path.len << endl;
	Point temp;
	cout << path.len << endl;
	if(path.len == -1){
		cout << "no path to the end" << endl;
	}
	else{
		int size = path.path.size();
		for(int i = 0;i < size;i++){
			temp = path.path[i];
			mat[temp.x][temp.y] = 2;
	}
	for(int i = 0;i < height;i++){
		for(int j = 0;j < width;j++){
			cout  << mat[i+1][j+1] << "\t";
		}
		cout << endl;
	}
	}
}
