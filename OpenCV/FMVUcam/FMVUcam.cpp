#include "FMVUcam.h"

using namespace std;
using namespace cv;


FMVUcam::FMVUcam()
{
	uiSize = _MAX_CAMS;

	//
	// This function enumerates all the cameras found on the machine, across
	// all 1394 buses and cards. It fills an array of FlyCaptureInfoEx 
	// structures with all of the pertinent information from the attached
	// cameras. The index of a given FlyCaptureInfoEx structure in the array 
	// parInfo is the device number.
	//
	error = flycaptureBusEnumerateCamerasEx( arInfo, &uiSize );
	_HANDLE_ERROR( error, "flycaptureBusEnumerateCameras()" );

	for( unsigned int uiBusIndex = 0; uiBusIndex < uiSize; uiBusIndex++ )
	{
		FlyCaptureInfoEx* pinfo = &arInfo[ uiBusIndex ];
		printf( 
			"Index %u: %s (%u)\n",
			uiBusIndex,
			pinfo->pszModelName,
			pinfo->SerialNumber );
	}

	//
	// Create the context. This call must be made before any other calls to
	// to the context are made, as a valid context is needed for all
	// camera-specific FlyCapture library calls. This call sets the context
	// to the default settings, but flycaptureInitialize() must be called
	// below to fully initialize the camera for use.
	//
	error = flycaptureCreateContext( &context );
	_HANDLE_ERROR( error, "flycaptureCreateContext()" );

	//
	// Initialize the camera. This call initializes one of the cameras on the
	// bus with the FlyCaptureContext that is passed in. This should generally
	// be called right after creating the context but before doing anything 
	// else.
	//
	// This call performs several functions. It sets the camera to communicate 
	// at the proper bus speed, turns on color processing (if available) and 
	// sets the Bayer orientation to the correct setting. Finally, it also 
	// initializes the white balance tables for cameras that support that 
	// function.
	//
	printf( "Initializing camera %u.\n", _CAMERA_INDEX );
	error = flycaptureInitialize( context, _CAMERA_INDEX );
	_HANDLE_ERROR( error, "flycaptureInitialize()" );

	//
	// Reset the camera to default factory settings by asserting bit 0
	//
	error = flycaptureSetCameraRegister( context, INITIALIZE, 0x80000000 );
	_HANDLE_ERROR( error, "flycaptureSetCameraRegister()" );

	//
	// Power-up the camera (for cameras that support this feature)
	//
	error = flycaptureSetCameraRegister( context, CAMERA_POWER, 0x80000000 );
	_HANDLE_ERROR( error, "flycaptureSetCameraRegister()" );

	//
	// Retrieve information about the camera.
	//
	error = flycaptureGetCameraInfo( context, &info );
	_HANDLE_ERROR( error, "flycaptureGetCameraInfo()" );

	printf( "Camera info:\n" );
	reportCameraInfo( &info );

	//
	// Start grabbing images in the current videomode and framerate. Driver
	// level image buffer allocation is performed at this point. After this
	// point, images will be constantly grabbed by the camera and stored
	// in the buffers on the PC.
	//
	printf( "Starting camera.\n\n" );
	error = flycaptureStart( 
		context, 
		FLYCAPTURE_VIDEOMODE_640x480Y8,   // 60fps goes with 640x480 Y8 mode (gray)
		FLYCAPTURE_FRAMERATE_60 );			// ANY goes with ANY gives an RGB frame
	_HANDLE_ERROR( error, "flycaptureStart()" );


	//
	// Record the time taken to grab _IMAGES_TO_GRAB images.
	//
	memset( &image, 0x0, sizeof( FlyCaptureImage ) );
	
}

FMVUcam::~FMVUcam()
{
	//
	// Stop the camera. This does not destroy the context. This simply stops
	// the grabbing of images from the camera. This should always be called 
	// prior to calling flycaptureDestroyContext().
	//
	error = flycaptureStop( context );
	_HANDLE_ERROR( error, "flycaptureStop()" );

	//
	// Destroy the context. This should always be called before exiting
	// the application to prevent memory leaks.
	//
	error = flycaptureDestroyContext( context );
	_HANDLE_ERROR( error, "flycaptureDestroyContext()" );

	//delete [] imageConverted.pData; //-> moved to function DeleteBuffer()
	DeleteBuffer();	

	printf( "Done!  (hit enter)" );
}

void FMVUcam::DeleteBuffer()
{
	delete [] imageConverted.pData;
}

void FMVUcam::getframe(Mat& rawframe)
{

	//printf( "Grabbing images" );
	/*for ( int iImage = 0; iImage < _IMAGES_TO_GRAB; iImage++ )
	{*/
		//
		// Grab an image. This obtains an pointer to the latest full
		// image captured by the camera and saved in the image buffer.
		//
		// flycaptureGrabImage2 is used instead of flycaptureGrabImage because
		// it returns a FlyCaptureImage structure, which is generally easier to 
		// work with.
		//
		error = flycaptureGrabImage2( context, &image );
		_HANDLE_ERROR( error, "flycaptureGrabImage2()" );

	//	printf( "." );
	//}

	//printf( "\n" );


	//
	// Convert the last image that was grabbed.
	//
	// First, allocate memory space for the converted image. The size needed is
	// multiplied by 4 because we are converting to FLYCAPTURE_BGRU, which
	// contains 4 bytes (32 bits) of data per pixel. If converting to a 
	// FLYCAPTURE_BGR image, then the size only needs to be multiplied by 3 as
	// each converted pixel will only contain 3 bytes (24 bits) of data.
	// The pixelFormat field should also be set appropriately either to
	// FLYCAPTURE_BGRU or FLYCAPTURE_BGR.
	//
	// for me, I convert to FLYCAPTURE_BGR to use 3-byte pixel
	//imageConverted.pData = new unsigned char[ image.iCols * image.iRows * 4 ];
	//imageConverted.pixelFormat = FLYCAPTURE_BGRU;
	imageConverted.pData = new unsigned char[ image.iCols * image.iRows * 3 ];
	imageConverted.pixelFormat = FLYCAPTURE_BGR;
	
	//
	// Now that the converted image's data structure is filled in correctly and
	// sufficient memory space has been allocated, proceed with converting the 
	// raw image into a BGR image.
	//
	printf( "Converting last image.\n" );
	error = flycaptureConvertImage( context, &image, &imageConverted );
	_HANDLE_ERROR( error, "flycaptureConvertImage()" );


	//
	// Save the converted image to disk.
	//
	printf( "Saving converted image.\n\n" );
	error = flycaptureSaveImage(
		context,
		&imageConverted,
		FILENAME_CONVERTED,
		SAVE_FORMAT );
	_HANDLE_ERROR( error, "flycaptureSaveImage()" );


	// return MatImg
	FlyCap2Mat(imageConverted, rawframe);

	// Clear memory
	DeleteBuffer();
}


void FMVUcam::FlyCap2Mat(const FlyCaptureImage FCImg, Mat& MatImg)
{
	// this is a 3-bytes (channel) image
	//TriclopsImage myimage = edgeImage;w

	//char* data1 = "asdfasdf";
	//cout << refImage.data << endl;

	//MatImg = Mat::zeros(FCImg.iRows, FCImg.iCols, CV_8UC1);
	MatImg = Mat::zeros(FCImg.iRows, FCImg.iCols, CV_8UC3);
	for (int i=0; i<FCImg.iRows; i++)
	{
		for (int j=0; j<FCImg.iCols; j++)
		{
			//cout << refImage.data[i*refImage.nrows + refImage.ncols] << " "; // << endl;   // this applies for 1 channel image

			// this assumed format is not correct
			/*MatImg.at<Vec3b>(i,j)[0] = FCImg.pData[i*FCImg.iCols + j*3 + 0];
			MatImg.at<Vec3b>(i,j)[1] = FCImg.pData[i*FCImg.iCols + j*3 + 1];
			MatImg.at<Vec3b>(i,j)[2] = FCImg.pData[i*FCImg.iCols + j*3 + 2];*/

			MatImg.at<Vec3b>(i,j)[0] = FCImg.pData[i*3*FCImg.iCols + j*3 + 0];
			MatImg.at<Vec3b>(i,j)[1] = FCImg.pData[i*3*FCImg.iCols + j*3 + 1];
			MatImg.at<Vec3b>(i,j)[2] = FCImg.pData[i*3*FCImg.iCols + j*3 + 2];
		}
		//cout << endl;
	}
}

void FMVUcam::reportCameraInfo( const FlyCaptureInfoEx* pinfo )
{
	//
	// Print out camera information. This can be obtained by calling
	// flycaptureGetCameraInfo() anytime after the camera has been initialized.
	//
	printf( "Serial number: %d\n", pinfo->SerialNumber );
	printf( "Camera model: %s\n", pinfo->pszModelName );
	printf( "Camera vendor: %s\n", pinfo->pszVendorName );
	printf( "Sensor: %s\n", pinfo->pszSensorInfo );
	printf( "DCAM compliance: %1.2f\n", (float)pinfo->iDCAMVer / 100.0 );
	printf( "Bus position: (%d,%d).\n", pinfo->iBusNum, pinfo->iNodeNum );
}

