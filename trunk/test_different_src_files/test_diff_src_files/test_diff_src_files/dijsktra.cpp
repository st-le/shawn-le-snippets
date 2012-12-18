   
#include "stdafx.h"
#include "dijsktra.h"


void dijsktra::DijkstraSolving()
	{
		int Int32Max = 65355;
		int minValue[MAX_VTX];
		int minNode[MAX_VTX]; 

		for (int i = 0; i < rank; i++)
		{
			minValue[i] = Int32Max;
			minNode[i] = 0;
		}

		for (int i = 0; i < rank; i++)
			for (int j = 0; j < rank; j++)
			{
				if (C[i][j] == -1)
					continue;
				if (D[i][j] > 0 && D[i][j] < minValue[i])
				{
					minValue[i] = D[i][j];
					minNode[i] = j;
				}
			}

			for (int i = 0; i < rank; i++)
			{
				C[i][minNode[i]] = -1;
				//printf("neg = %d\n",C[i][minNode[i]]);
				if (path_map[i][minNode[i]] < 0)  path_map[i][minNode[i]] = i;
			}

			for (int i = 0; i < rank; i++)
				for (int j = 0; j < rank; j++)
				{
					if (M[minNode[i]][j] < 0)
						continue;
					if (D[i][j] < 0)
					{
						D[i][j] = minValue[i] + M[minNode[i]][j];
						path_map[i][j] = minNode[i];
						continue;
					}
					if ((D[i][minNode[i]] + M[minNode[i]][j]) < D[i][j])
					{
						D[i][j] = minValue[i] + M[minNode[i]][j];
						path_map[i][j] = minNode[i];
					}
				}
	}


	void dijsktra::Run()
        {
            for (trank = 1; trank < rank; trank++)
            {
                DijkstraSolving();
               /* printf("iteration %d\n",trank);
                for (int i = 0; i < rank; i++)
				{
					for (int j = 0; j < rank; j++)
						printf("%d ",D[i][j]);
					printf("\n");						
				}
                printf("\n");
                for (int i = 0; i < rank; i++)
				{
					for (int j = 0; j < rank; j++)
						printf("%d ",C[i][j]);
					printf("\n");				
				}
                printf("\n");
				getchar();*/
            }
        }

		 
		  void dijsktra::outPath(int a, int b, bool flg)
		 {
			 if (a != b)
			 {
				 //printf("%d <- ",b);
				 ret_path_cnt++;
				 //	printf("ret_path_cnt = %d",ret_path_cnt);
				 ret_path[ret_path_cnt-1] = b;
				 outPath(a,path_map[a][b], flg);
			 }
			 else
			 {
				 if (flg)
				 {
					 ret_path_cnt++;
					 //	printf("ret_path_cnt = %d",ret_path_cnt);
					 ret_path[ret_path_cnt-1] = b;
					 //printf("%d\n",b);
				 }
			 }
		 }

		 void dijsktra::get_result()
		 {
			 ret_path_cnt = 0;
			 for (int i=inp_vias_cnt-1; i>0; i--)
			 {
				 //printf("get_result = %d ",i);
				 //printf("a=%d;b=%d ",inp_vias[i-1], inp_vias[i]);
				 if (i==1)
					 outPath(inp_vias[i-1], inp_vias[i], 1);
				 else
					 outPath(inp_vias[i-1], inp_vias[i], 0);
			 }
		 }


	 
    
		dijsktra::dijsktra(int (&inp_map)[MAX_VTX][MAX_VTX], int vtx_cnt, int vias[], int vias_cnt)
		{
				// passing parameters
			//printf("lalala\n");
			for (int i=0; i < vias_cnt; i++) 
			{
				inp_vias[i] = vias[i];
				// printf("%d ",vias[i]);
			}
			inp_vias_cnt = vias_cnt;
			rank = vtx_cnt;
			Dsz = rank;
			for (int i = 0; i < rank; i++)
			{
				for (int j = 0; j < rank; j++) 
				{
					M[i][j] = inp_map[i][j];
					C[i][j] = j;
					D[i][j] = M[i][j];
					//printf("neg = %d\n",D[i][j]);
					path_map[i][j] = -1;
				}

				C[i][i] = -1;
			}

		
            Run();

			get_result();

	/*		// Output result 	
			path_cnt = ret_path_cnt;
			for(int i=0; i<ret_path_cnt; i++)
				path[i] = ret_path[path_cnt - i -1]; */

		/*	printf("Path is\n");
			
			printf("ret_path_cnt=%d",ret_path_cnt);
			for(int i = 0; i<ret_path_cnt; i++)
				printf("%d -> ",path[i]);
		*/

            /*printf("Solution is\n");
            for(int i=0; i<Dsz; i++)
            {
				for (int j=0; j<Dsz; j++)
					printf("%d ",D[i][j]);
				printf("\n");
            }

			printf("Path is\n");
			outPath(0,7);
            printf("Press Enter for exit.");
            getchar();*/
		}

		dijsktra::~dijsktra(void)
		{
			
		}