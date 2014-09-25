// 24/05/12: this func is not safe yet
// int MATmtxdisp(Mat mtx)
// {	float ele;   // if type is double -> error

	// for(int i = 0; i < mtx.rows; i++)
	// {
		// for(int j = 0; j < mtx.cols; j++)
		// {
			Vec3b ele = mtx.at<Vec3b>(i,j);
			// ele = mtx.at<float>(i,j);   // if type is double -> error
						printf("ele (%d,%d) has chan1=%d, chan2=%d, chan3=%d\n",i,j, ele[0],ele[1],ele[2]);
			// printf("%8.2f",ele);
		// }
		// printf("\n");
	// }

		// return 0;
// }

// 24/05/12 
// v1.2: this template function is safe. Usage:  double num=0; MATmtxdisp(tvec,num);  Note: tested with Double and float!   
template<class _num> 
	int MATmtxdisp(const Mat& mtx, _num usedtype)
	{	//float ele;
		_num ele;

		for(int i = 0; i < mtx.rows; i++)
		{
			for(int j = 0; j < mtx.cols; j++)
			{
				//Vec3b ele = mtx.at<Vec3b>(i,j);
				ele = mtx.at<_num>(i,j);
				//			printf("ele (%d,%d) has chan1=%d, chan2=%d, chan3=%d\n",i,j, ele[0],ele[1],ele[2]);
				printf("%8.2f",ele);
			}
			printf("\n");
		}

		return 0;
	};