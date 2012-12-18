#include "StdAfx.h"
#include "mapper.h"



bool mapper::LineX(Point2f o1, Point2f p1, Point2f o2, Point2f p2, Point2f &r)
{
	Point2f x = o2 - o1;
	Point2f d1 = p1 - o1;
	Point2f d2 = p2 - o2;

	float cross = d1.x*d2.y - d1.y*d2.x;
	if (abs(cross) < /*EPS*/1e-8)
		return false;

	double t1 = (x.x * d2.y - x.y * d2.x)/cross;
	r = o1 + d1 * t1;
	return true;
}


bool mapper::PinRect(CvPoint P, CvRect rect)
{
	bool ans = false;

	if ((P.x >= rect.x )&&(P.y >= rect.y)
		&& (P.x <= rect.x + rect.width) && ( P.y <= rect.y + rect.height))
	{
		ans = true;
	}

	return ans;
}



bool mapper::LineXRect(Point2f A, Point2f B, CvRect rect)  // not yet thouroughly checked
{
	bool ans = false;

	Point2f uplft(rect.x, rect.y);
	Point2f uprgt(rect.x + rect.width, rect.y);
	Point2f lwlft(rect.x, rect.y + rect.height);
	Point2f lwrgt(rect.x + rect.width, rect.y + rect.height);
	Point2f cr;

	/*if((LineX(A,B,uplft,uprgt,cr)||LineX(A,B,uprgt,lwrgt,cr)
		||LineX(A,B,lwrgt,lwlft,cr)||LineX(A,B,lwlft,uplft,cr))&&
		())
	{
		ans = true;
	}*/
	
	if(LineX(A,B,uplft,uprgt,cr)&& PinRect(cr,rect))
	{
		ans = true;
	}

	if(LineX(A,B,uprgt,lwrgt,cr)&& PinRect(cr,rect))
	{
		ans = true;
	}

	if(LineX(A,B,lwrgt,lwlft,cr)&& PinRect(cr,rect))
	{
		ans = true;
	}

	if(LineX(A,B,lwlft,uplft,cr)&& PinRect(cr,rect))
	{
		ans = true;
	}

	return ans;
}


void mapper::get_open_vertex()
{
	// Get all open vertex
	
	bool flg0,flg1,flg2,flg3;
	CvRect rect,rect1;	

	for(int i = 0; i<inp_obs_cnt; i++)
	{
		rect = inp_obs_arr[i];

		Point2f uplft(rect.x, rect.y);
		Point2f uprgt(rect.x + rect.width, rect.y);
		Point2f lwlft(rect.x, rect.y + rect.height);
		Point2f lwrgt(rect.x + rect.width, rect.y + rect.height);

		flg0 = false;
		flg1 = false;
		flg2 = false;
		flg3 = false;
		for(int j = 0; j<inp_obs_cnt; j++)
			if(i!=j)
			{
				rect1 = inp_obs_arr[j];
				if (!flg0) flg0 = PinRect(uplft,rect1);
				if (!flg1) flg1 = PinRect(uprgt,rect1);
				if (!flg2) flg2 = PinRect(lwrgt,rect1);
				if (!flg3) flg3 = PinRect(lwlft,rect1);								
			}

			if(!flg0)
			{
				vtx_cnt++;
				vtx_arr[vtx_cnt-1] = uplft;
			}

			if(!flg1)
			{
				vtx_cnt++;
				vtx_arr[vtx_cnt-1] = uprgt;
			}

			if(!flg2)
			{
				vtx_cnt++;
				vtx_arr[vtx_cnt-1] = lwrgt;
			}				

			if(!flg3)
			{
				vtx_cnt++;
				vtx_arr[vtx_cnt-1] = lwlft;
			}
	}

	// OUTPUT test
	//printf("number of vertex = %d\n",vtx_cnt);

}


void mapper::make_map()
{
	bool X;
	double d;

	for (int i = 0; i < vtx_cnt-1; i++)
	{
		ret_adj_map[i][i] = 0;

		for (int j = i+1; j < vtx_cnt; j++)
		{
			X = false;	

			for (int k = 0; k < inp_obs_cnt; k++)
				if(LineXRect(vtx_arr[i], vtx_arr[j],inp_obs_arr[k]))
				{
					X = true;
					break;
				}
			
			if(X)
			{
				ret_adj_map[i][j] = -1;
				ret_adj_map[j][i] = -1;
			} 
			else
			{
				//d = 0;
				//d = sqrt(4);
				//d = sqrt(pow(vtx_arr[i].x - vtx_arr[j].x, 2) + pow(vtx_arr[i].y - vtx_arr[j].y, 2));
				//d = sqrt(pow(2- 3) + pow(5 - [j].y));
				d = (vtx_arr[i].x - vtx_arr[j].x, 2)*(vtx_arr[i].x - vtx_arr[j].x, 2) + (vtx_arr[i].y - vtx_arr[j].y, 2)*(vtx_arr[i].y - vtx_arr[j].y, 2);
				ret_adj_map[i][j] = floor(d);
				ret_adj_map[j][i] = floor(d);
			}
		}
	}			
}


//mapper(CvRect obs_arr[], int obs_cnt, CvRect vias[], int &vias_cnt, int (&inp_map)[MAX_VTX][MAX_VTX], int &vtx_cnt)
mapper::mapper(CvRect obs_arr[], int obs_cnt, CvPoint vias[], int &vias_cnt)
{
	// Passing data
	inp_obs_cnt = obs_cnt;
	for (int i = 0; i < obs_cnt; i++) inp_obs_arr[i] = obs_arr[i];
	
	inp_vias_cnt = vias_cnt;
	for (int i = 0; i < vias_cnt; i++) inp_vias[i] = vias[i];

	// Initialize Vertex array
	vtx_cnt = vias_cnt;
	for (int i = 0; i < vias_cnt; i++) vtx_arr[i] = vias[i];

	get_open_vertex();

	make_map();
}


mapper::mapper(void)
{
}

mapper::~mapper(void)
{
}
