const int MAX_VTX = 100;


class dijsktra
{
private:
	int rank;       
	int Dsz;
	int M[MAX_VTX][MAX_VTX];
	int	C[MAX_VTX][MAX_VTX];
	int D[MAX_VTX][MAX_VTX];
	int path_map[MAX_VTX][MAX_VTX];
	int trank;

	int inp_vias_cnt;
	

	int inp_vias[MAX_VTX];
	
		
public:
	int ret_path_cnt;
	int ret_path[MAX_VTX];

	void DijkstraSolving();
	void Run();
	void outPath(int a, int b, bool flg);
	void get_result();

	dijsktra(int (&inp_map)[MAX_VTX][MAX_VTX], int vtx_cnt, int vias[], int vias_cnt);
	~dijsktra(void);
};
