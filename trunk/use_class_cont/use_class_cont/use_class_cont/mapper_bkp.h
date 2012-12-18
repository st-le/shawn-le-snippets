//#pragma once

//#include "global.h"


//#include "stdafx.h"

//#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <math.h>


const int MAX_VTX = 100;
const int MAX_OBS = 50;


class mapper
{
//private:
	/*
	int inp_obs_cnt;// = 0;
	int inp_vias_cnt;// = 0;
	int vtx_cnt_lc;// = 0;

	int ret_adj_map[MAX_VTX][MAX_VTX];

	CvRect inp_obs_arr[MAX_OBS];
	CvRect inp_vias[MAX_VTX];
	CvPoint vtx_arr_lc[MAX_VTX];*/

public:

	/*bool LineX(Point2f o1, Point2f p1, Point2f o2, Point2f p2, Point2f &r);
	//void LineX(Point2f o1, Point2f p1, Point2f o2, Point2f p2, Point2f &r);

	bool PinRect(CvPoint P, CvRect rect);

	bool LineXRect(Point2f A, Point2f B, CvRect rect);

	void get_open_vertex(void);

	mapper(CvRect obs_arr[], int obs_cnt, CvRect vias[], int &vias_cnt, int (&inp_map)[MAX_VTX][MAX_VTX], int &vtx_cnt); */

	mapper(void);
	
//	~mapper(void);

}
