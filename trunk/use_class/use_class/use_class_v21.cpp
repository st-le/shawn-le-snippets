// use_class.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"

#include "crectangle.h"
#include "dijsktra.h"

using namespace std;


//const int MAX_VTX = 100;

int adj_map[MAX_VTX][MAX_VTX] ={
	{-1,  5, -1, -1, -1,  3, -1, -1}, 
	{ 5, -1,  2, -1, -1, -1,  3, -1}, 
	{-1,  2, -1,  6, -1, -1, -1, 10}, 
	{-1, -1,  6, -1,  3, -1, -1, -1},
	{-1, -1, -1,  3, -1,  8, -1,  5}, 
	{ 3, -1, -1, -1,  8, -1,  7, -1}, 
	{-1,  3, -1, -1, -1,  7, -1,  2}, 
	{-1, -1, 10, -1,  5, -1,  2, -1} 
};

int vias_cnt = 0;
int vtx_cnt = 0;

int vias[MAX_VTX];


int _tmain(int argc, _TCHAR* argv[])
{
	CRectangle rect(3,4);
	CRectangle rectb;


	vias_cnt = 4;

	vias[0] = 0;
	vias[1] = 3;
	vias[2] = 6;
	vias[3] = 7;

	vtx_cnt = 8;


	dijsktra pathplanning(adj_map,vtx_cnt,vias,vias_cnt);

	pathplanning.Run();
	pathplanning.get_result();

	//printf("num of path = ",pathplanning.ret_path_cnt);
	getchar();
	
	//printf("num of path = ",pathplanning.get_result(vias));
	//printf("num of path = %d",rect.lalala);
	getchar();


	//cout << "area:" << rect.area() << endl;
	//cout << "areab:" << rectb.area() << endl;
	getchar();
	return 0;
}

