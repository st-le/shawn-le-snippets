// 03/03/13 vx.x this approach is bad -> works already -> a programming error
// 03/03/13 v3.0 get color frameRGB & frame3D containing depth info

#include "BumbleBee2.h"

using namespace std;
using namespace cv;
//using namespace ;


void BumbleBee2::Triclops2Mat(const TriclopsImage TriImg, Mat& MatImg)
{

	//TriclopsImage myimage = edgeImage;

	//char* data1 = "asdfasdf";
	//cout << refImage.data << endl;
	MatImg = Mat::zeros(TriImg.nrows, TriImg.ncols, CV_8UC1);
	for (int i=0; i<TriImg.nrows; i++)
	{
		for (int j=0; j<TriImg.ncols; j++)
		{
			//cout << refImage.data[i*refImage.nrows + refImage.ncols] << " "; // << endl;
			MatImg.at<uchar>(i,j) = TriImg.data[i*TriImg.ncols + j];
		}
		//cout << endl;
	}
}

void BumbleBee2::TrClpGetDepthImg(const TriclopsImage16 depthImage16, Mat& depth_img)
{

	//depth_img = Mat::zeros(TriImg.nrows, TriImg.ncols, CV_16UC1);

	// Determine the number of pixels spacing per row
	int pixelinc = depthImage16.rowinc/2;
	int i,j,k;
	unsigned short*     row;
	unsigned short      disparity;
	float	       x, y, z;

	for ( i = 0, k = 0; i < depthImage16.nrows; i++ )
	{
		row     = depthImage16.data + i * pixelinc;
		for ( j = 0; j < depthImage16.ncols; j++, k++ )
		{
			disparity = row[j];

			// do not save invalid points
			//
			//if ( disparity < 0xFF00 )
			//{
			//	// convert the 16 bit disparity value to floating point x,y,z
			//	triclopsRCD16ToXYZ( triclops, i, j, disparity, &x, &y, &z );

			//	// look at points within a range
			//	if ( z < 5.0 )
			//	{
			//		if ( pixelFormat == FLYCAPTURE_RAW16 )
			//		{
			//			r = (int)colorImage.red[k];
			//			g = (int)colorImage.green[k];
			//			b = (int)colorImage.blue[k];		  
			//		}
			//		else
			//		{
			//			// For mono cameras, we just assign the same value to RGB
			//			r = (int)monoImage.data[k];
			//			g = (int)monoImage.data[k];
			//			b = (int)monoImage.data[k];
			//		}

			//		fprintf( pointFile, "%f %f %f %d %d %d %d %d\n", x, y, z, r, g, b, i, j );
			//		nPoints++;
			//	}
			//}
		}
	}
}


BumbleBee2::BumbleBee2()
{
	// Open the camera
	fe = flycaptureCreateContext( &flycapture );
	_HANDLE_FLYCAPTURE_ERROR( "flycaptureCreateContext()", fe );

	// Initialize the Flycapture context
	fe = flycaptureInitialize( flycapture, 0 );
	_HANDLE_FLYCAPTURE_ERROR( "flycaptureInitialize()", fe );

	// Save the camera's calibration file, and return the path 
	fe = flycaptureGetCalibrationFileFromCamera( flycapture, &szCalFile );
	_HANDLE_FLYCAPTURE_ERROR( "flycaptureGetCalibrationFileFromCamera()", fe );

	// Create a Triclops context from the cameras calibration file
	te = triclopsGetDefaultContextFromFile( &triclops, szCalFile );
	_HANDLE_TRICLOPS_ERROR( "triclopsGetDefaultContextFromFile()", te );

	// Get camera information
	fe = flycaptureGetCameraInfo( flycapture, &pInfo );
	_HANDLE_FLYCAPTURE_ERROR( "flycatpureGetCameraInfo()", fe );


	if (pInfo.CameraType == FLYCAPTURE_COLOR)
	{
		pixelFormat = FLYCAPTURE_RAW16;
	} 
	else 
	{
		pixelFormat = FLYCAPTURE_MONO16;
	}

	iMaxCols = 0;
	iMaxRows = 0;

	switch (pInfo.CameraModel)
	{
	case FLYCAPTURE_BUMBLEBEE2:
		{
			unsigned long ulValue;
			flycaptureGetCameraRegister( flycapture, 0x1F28, &ulValue );

			if ( ( ulValue & 0x2 ) == 0 )
			{
				// Hi-res BB2
				iMaxCols = 1024; 
				iMaxRows = 768;   
			}
			else
			{
				// Low-res BB2
				iMaxCols = 640;
				iMaxRows = 480;
			}
		}
		break;

	case FLYCAPTURE_BUMBLEBEEXB3:
		iMaxCols = 1280;
		iMaxRows = 960;
		break;

	default:
		te = TriclopsErrorInvalidCamera;
		_HANDLE_TRICLOPS_ERROR( "triclopsCheckCameraModel()", te );
		break;
	}

	// Start transferring images from the camera to the computer
	fe = flycaptureStartCustomImage( 
		flycapture, 3, 0, 0, iMaxCols, iMaxRows, 100, pixelFormat);
	_HANDLE_FLYCAPTURE_ERROR( "flycaptureStart()", fe );
}


void BumbleBee2::DeleteBuffer()
{
	// Delete the image buffer
	delete [] rowIntMono;
	redMono = NULL;
	greenMono = NULL;
	blueMono = NULL;

	// Delete the image buffer 16
	delete [] rowIntColor;
	redColor = NULL;
	greenColor = NULL;
	blueColor = NULL;
}


BumbleBee2::~BumbleBee2()
{

	// Close the camera
	fe = flycaptureStop( flycapture );
	_HANDLE_FLYCAPTURE_ERROR( "flycaptureStop()", fe );

	//// Delete the image buffer
	//delete [] rowIntMono;
	//redMono = NULL;
	//greenMono = NULL;
	//blueMono = NULL;

	//// Delete the image buffer 16
	//delete [] rowIntColor;
	//redColor = NULL;
	//greenColor = NULL;
	//blueColor = NULL;

	DeleteBuffer();

	fe = flycaptureDestroyContext( flycapture );
	_HANDLE_FLYCAPTURE_ERROR( "flycaptureDestroyContext()", fe );

	// Destroy the Triclops context
	te = triclopsDestroyContext( triclops ) ;
	_HANDLE_TRICLOPS_ERROR( "triclopsDestroyContext()", te );
}


//void BumbleBee2::getframe(Mat& frame)
void BumbleBee2::getframe(Mat& rawframe, Mat& recframe, Mat& dispframe)
{
	// Grab an image from the camera
	fe = flycaptureGrabImage2( flycapture, &flycaptureImage );
	_HANDLE_FLYCAPTURE_ERROR( "flycaptureGrabImage()", fe );

	// Extract information from the FlycaptureImage
	int imageCols = flycaptureImage.iCols;
	int imageRows = flycaptureImage.iRows;
	int imageRowInc = flycaptureImage.iRowInc;
	int iSideBySideImages = flycaptureImage.iNumImages;
	unsigned long timeStampSeconds = flycaptureImage.timeStamp.ulSeconds;
	unsigned long timeStampMicroSeconds = flycaptureImage.timeStamp.ulMicroSeconds;

	// Create buffers for holding the mono images
//	unsigned char* rowIntMono = 
//		new unsigned char[ imageCols * imageRows * iSideBySideImages ];
	rowIntMono = new unsigned char[ imageCols * imageRows * iSideBySideImages ];

	// Create a temporary FlyCaptureImage for preparing the stereo image
	FlyCaptureImage tempImage;
	tempImage.pData = rowIntMono;

	// Convert the pixel interleaved raw data to row interleaved format
	fe = flycapturePrepareStereoImage( flycapture, flycaptureImage, &tempImage, NULL);
	_HANDLE_FLYCAPTURE_ERROR( "flycapturePrepareStereoImage()", fe );

	// Pointers to positions in the mono buffer that correspond to the beginning
	// of the red, green and blue sections
	/*unsigned char* redMono = NULL;
	unsigned char* greenMono = NULL;
	unsigned char* blueMono = NULL;*/
	redMono = NULL;
	greenMono = NULL;
	blueMono = NULL;

	redMono = rowIntMono;
	if (flycaptureImage.iNumImages == 2)
	{
		greenMono = redMono + imageCols;
		blueMono = redMono + imageCols;
	}
	if (flycaptureImage.iNumImages == 3)
	{
		greenMono = redMono + imageCols;
		blueMono = redMono + ( 2 * imageCols );
	}

	// Use the row interleaved images to build up an RGB TriclopsInput.  
	// An RGB triclops input will contain the 3 raw images (1 from each camera).
	te = triclopsBuildRGBTriclopsInput(
		imageCols, 
		imageRows, 
		imageRowInc,  
		timeStampSeconds, 
		timeStampMicroSeconds, 
		redMono, 
		greenMono, 
		blueMono, 
		&triclopsInput);
	_HANDLE_TRICLOPS_ERROR( "triclopsBuildRGBTriclopsInput()", te );

	// Rectify the images
	te = triclopsRectify( triclops, &triclopsInput );
	_HANDLE_TRICLOPS_ERROR( "triclopsRectify()", te );

	// Do stereo processing
	te = triclopsStereo( triclops );
	_HANDLE_TRICLOPS_ERROR( "triclopsStereo()", te );

	// Retrieve the disparity image from the triclops context
	te = triclopsGetImage( triclops, TriImg_DISPARITY, TriCam_REFERENCE, &disparityImage );
	_HANDLE_TRICLOPS_ERROR( "triclopsGetImage()", te );

	// Retrieve the rectified image from the triclops context
	te = triclopsGetImage( triclops, TriImg_RECTIFIED, TriCam_REFERENCE, &refImage );
	_HANDLE_TRICLOPS_ERROR( "triclopsGetImage()", te );

	// Retrieve the raw image from the triclops context
	TriclopsImage rawImage;
	te = triclopsGetImage( triclops, TriImg_RAW, TriCam_REFERENCE, &rawImage );
	_HANDLE_TRICLOPS_ERROR( "triclopsGetImage()", te );

	// Retrieve the edge image from the triclops context
	TriclopsImage edgeImage;
	te = triclopsGetImage( triclops, TriImg_EDGE, TriCam_REFERENCE, &edgeImage );
	_HANDLE_TRICLOPS_ERROR( "triclopsGetImage()", te );

	// Retrieve the interpolated depth image from the context
	//TriclopsImage16 depthImage16;    // cannot get 16-depth image yet
	//te = triclopsGetImage16( triclops, TriImg16_DISPARITY, TriCam_REFERENCE, &depthImage16 );
	//_HANDLE_TRICLOPS_ERROR( "triclopsGetImage16()", te );

	// access some image data here => cannot work!!!!!
	/*unsigned char*	data = disparityImage.data;
	for (int i=0; i<50; i++)
	{
		cout << "number is=" << *data << endl;
		data++;
	}*/

	TriclopsImage myimage = rawImage;
	Mat ret_img;
	Triclops2Mat(myimage, ret_img);
	ret_img.copyTo(rawframe);

	myimage = refImage;
	Triclops2Mat(myimage, ret_img);
	ret_img.copyTo(recframe);

	myimage = disparityImage;
	Triclops2Mat(myimage, ret_img);
	ret_img.copyTo(dispframe);
	//Mat depth_img;

	//TrClpGetDepthImg(depthImage16, depth_img);

	//char* data1 = "asdfasdf";
	//cout << refImage.data << endl;
	//Mat ret_img = Mat::zeros(myimage.nrows, myimage.ncols, CV_8UC1);
	//for (int i=0; i<myimage.nrows; i++)
	//{
	//	for (int j=0; j<myimage.ncols; j++)
	//	{
	//		//cout << refImage.data[i*refImage.nrows + refImage.ncols] << " "; // << endl;
	//		ret_img.at<uchar>(i,j) = myimage.data[i*myimage.ncols + j];
	//	}
	//	cout << endl;
	//}

	//cout << "numrow = " << myimage.nrows << endl;
	//cout << "numcol = " << myimage.ncols << endl;

	//imshow("Reference Image", ret_img);
	//waitKey();

	//getchar();

	


	// Save the disparity and reference images
	/*te = triclopsSaveImage( &disparityImage, "disparity.pgm" );
	_HANDLE_TRICLOPS_ERROR( "triclopsSaveImage()", te );

	te = triclopsSaveImage( &refImage, "reference.pgm" );
	_HANDLE_TRICLOPS_ERROR( "triclopsSaveImage()", te );*/

	// Clear memory
	DeleteBuffer();
}


void BumbleBee2::getframe16(Mat& recframe, Mat& frameRGB, Mat& frame3D)   // be aware of triclops 16bit & triclops 8bit co-exist!!!!!!!!!!
{
	//colorImage = {0};
	//monoImage  = {0};
	//TriclopsColorImage  colorImage = {0};
	//TriclopsImage       monoImage = {0};

	// Set up some stereo parameters:
	// Set to 320x240 output images
	te = triclopsSetResolution( triclops, 240, 320 );
	_HANDLE_TRICLOPS_ERROR( "triclopsSetResolution()", te );

	// Set disparity range
	te = triclopsSetDisparity( triclops, 0, 240 );
	_HANDLE_TRICLOPS_ERROR( "triclopsSetDisparity()", te );   

	// Lets turn off all validation except subpixel and surface
	// This works quite well
	te = triclopsSetTextureValidation( triclops, 0 );
	_HANDLE_TRICLOPS_ERROR( "triclopsSetTextureValidation()", te );
	te = triclopsSetUniquenessValidation( triclops, 0 );
	_HANDLE_TRICLOPS_ERROR( "triclopsSetUniquenessValidation()", te );

	// Turn on sub-pixel interpolation
	te = triclopsSetSubpixelInterpolation( triclops, 1 );
	_HANDLE_TRICLOPS_ERROR( "triclopsSetSubpixelInterpolation()", te );

	// Grab an image from the camera
	fe = flycaptureGrabImage2( flycapture, &flycaptureImage );
	_HANDLE_FLYCAPTURE_ERROR( "flycaptureGrabImage()", fe );

	// Extract information from the FlycaptureImage
	int imageCols = flycaptureImage.iCols;
	int imageRows = flycaptureImage.iRows;
	int imageRowInc = flycaptureImage.iRowInc;
	int iSideBySideImages = flycaptureImage.iNumImages;
	unsigned long timeStampSeconds = flycaptureImage.timeStamp.ulSeconds;
	unsigned long timeStampMicroSeconds = flycaptureImage.timeStamp.ulMicroSeconds;

	// Create buffers for holding the color and mono images
	rowIntColor = new unsigned char[ imageCols * imageRows * iSideBySideImages * 4 ];
	rowIntMono = new unsigned char[ imageCols * imageRows * iSideBySideImages ];

	// Create a temporary FlyCaptureImage for preparing the stereo image
	FlyCaptureImage tempColorImage;
	FlyCaptureImage tempMonoImage;

	tempColorImage.pData = rowIntColor;
	tempMonoImage.pData = rowIntMono;

	// Convert the pixel interleaved raw data to row interleaved format
	fe = flycapturePrepareStereoImage( flycapture, flycaptureImage, &tempMonoImage, &tempColorImage );
	_HANDLE_FLYCAPTURE_ERROR( "flycapturePrepareStereoImage()", fe );

	// Pointers to positions in the color buffer that correspond to the beginning
	// of the red, green and blue sections
	redColor = NULL;
	greenColor = NULL;
	blueColor = NULL; 

	redColor = rowIntColor;
	if (flycaptureImage.iNumImages == 2)
	{
		greenColor = redColor + ( 4 * imageCols );
		blueColor = redColor + ( 4 * imageCols );
	}

	if (flycaptureImage.iNumImages == 3)
	{
		greenColor = redColor + ( 4 * imageCols );
		blueColor = redColor + ( 2 * 4 * imageCols );
	}

	// Pointers to positions in the mono buffer that correspond to the beginning
	// of the red, green and blue sections
	redMono = NULL;
	greenMono = NULL;
	blueMono = NULL; 

	redMono = rowIntMono;
	if (flycaptureImage.iNumImages == 2)
	{
		greenMono = redMono + imageCols;
		blueMono = redMono + imageCols;
	}

	if (flycaptureImage.iNumImages == 3)
	{
		greenMono = redMono + imageCols;
		blueMono = redMono + ( 2 * imageCols );
	}

	// Use the row interleaved images to build up a packed TriclopsInput.
	// A packed triclops input will contain a single image with 32 bpp.
	te = triclopsBuildPackedTriclopsInput(
		imageCols,
		imageRows,
		imageRowInc * 4,
		timeStampSeconds,
		timeStampMicroSeconds,
		redColor,
		&colorData );
	_HANDLE_TRICLOPS_ERROR( "triclopsBuildPackedTriclopsInput()", te );

	// Use the row interleaved images to build up an RGB TriclopsInput.  
	// An RGB triclops input will contain the 3 raw images (1 from each camera).
	te = triclopsBuildRGBTriclopsInput(
		imageCols, 
		imageRows, 
		imageRowInc,  
		timeStampSeconds, 
		timeStampMicroSeconds, 
		redMono, 
		greenMono, 
		blueMono, 
		&stereoData);
	_HANDLE_TRICLOPS_ERROR( "triclopsBuildRGBTriclopsInput()", te );

	// Preprocessing the images
	te = triclopsRectify( triclops, &stereoData );
	_HANDLE_TRICLOPS_ERROR( "triclopsRectify()", te );

	// Stereo processing
	te = triclopsStereo( triclops ) ;
	_HANDLE_TRICLOPS_ERROR( "triclopsStereo()", te );


	//******************************
	// Retrieve the 8bit rectified image from the triclops context
	te = triclopsGetImage( triclops, TriImg_RECTIFIED, TriCam_REFERENCE, &refImage );
	_HANDLE_TRICLOPS_ERROR( "triclopsGetImage()", te );

	// Retrieve the interpolated depth image from the context
	te = triclopsGetImage16( triclops, TriImg16_DISPARITY, TriCam_REFERENCE, &depthImage16 );
	_HANDLE_TRICLOPS_ERROR( "triclopsGetImage16()", te );

	// Rectify the color image if applicable
	if ( pixelFormat == FLYCAPTURE_RAW16 )
	{
		te = triclopsRectifyColorImage( triclops, 
			TriCam_REFERENCE, 
			&colorData, 
			&colorImage );
		_HANDLE_TRICLOPS_ERROR( "triclopsRectifyColorImage()", te );
	}
	else
	{
		te = triclopsGetImage( triclops,
			TriImg_RECTIFIED,
			TriCam_REFERENCE,
			&monoImage );
		_HANDLE_TRICLOPS_ERROR( "triclopsGetImage()", te );
	}


	// Determine the number of pixels spacing per row
	int pixelinc = depthImage16.rowinc/2;
	int i,j,k;
	//unsigned short*     row;
	unsigned short      disparity;
	float	       x, y, z;
	//int		       r, g, b;
	uchar		   r, g, b;
	pixelinc = depthImage16.rowinc/2;
	int		       nPoints = 0;

	frameRGB = Mat::zeros(colorImage.nrows, colorImage.ncols, CV_8UC3);  // make a if statement to init size for frames!!!!!!!!!!!!
	frame3D = Mat::zeros(colorImage.nrows, colorImage.ncols, CV_32FC3);

	for ( i = 0, k = 0; i < depthImage16.nrows; i++ )
	{
		row     = depthImage16.data + i * pixelinc;
		for ( j = 0; j < depthImage16.ncols; j++, k++ )
		{
			disparity = row[j];

			// do not save invalid points
			if ( disparity < 0xFF00 )
			{
				// convert the 16 bit disparity value to floating point x,y,z
				triclopsRCD16ToXYZ( triclops, i, j, disparity, &x, &y, &z );

				// look at points within a range
				//if ( z < 5.0 )
				{
					if ( pixelFormat == FLYCAPTURE_RAW16 )
					{
						/*r = (int)colorImage.red[k];
						g = (int)colorImage.green[k];
						b = (int)colorImage.blue[k];		  */
						r = colorImage.red[k];
						g = colorImage.green[k];
						b = colorImage.blue[k];		  
					}
					else
					{
						// For mono cameras, we just assign the same value to RGB
						/*r = (int)monoImage.data[k];
						g = (int)monoImage.data[k];
						b = (int)monoImage.data[k];*/
						r = monoImage.data[k];
						g = monoImage.data[k];
						b = monoImage.data[k];
					}

					//fprintf( pointFile, "%f %f %f %d %d %d %d %d\n", x, y, z, r, g, b, i, j );
					//printf( "%f %f %f %d %d %d %d %d\n", x, y, z, r, g, b, i, j );
					// pass the data to output
					frameRGB.at<Vec3b>(i,j)[0] = b;
					frameRGB.at<Vec3b>(i,j)[1] = g;
					frameRGB.at<Vec3b>(i,j)[2] = r;

					frame3D.at<Vec3f>(i,j)[0] = x;
					frame3D.at<Vec3f>(i,j)[1] = y;
					frame3D.at<Vec3f>(i,j)[2] = z;
					
					nPoints++;
				}
			}
		}
	}

	// return grey rectified 8bit image
	TriclopsImage myimage = refImage;
	Triclops2Mat(myimage, recframe);
	//ret_img.copyTo(recframe);


	// Clear memory
	DeleteBuffer();
}