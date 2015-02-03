cmake_minimum_required(VERSION 2.8)
project( testmatrix ) 


#set(OpenCV_DIR "D:/opencv/build")
#set(OpenCV_DIR "D:/TEMP DRIVE/Softs/Mechatronics/OpenCV-2.4.2/OpenCV-2.4.2/opencv/build/")
#set(Eigen_INCLUDE_DIRS "D:/Users/lab/Google Drive/USB (1)/Projects/Cpp_libs/eigen")
set(Eigen_INCLUDE_DIRS "C:/eigen-3.2.4")

#find_package( OpenCV REQUIRED core highgui imgproc objdetect calib3d features2d ml flann nonfree video contrib gpu legacy photo ts stitching) # 


# check finding
#IF (OpenCV_FOUND)
#message("OpenCV is found\n")
#ELSE (OpenCV_FOUND)
#message("OpenCV is NOT found\n")
#ENDIF (OpenCV_FOUND)

include_directories(${Eigen_INCLUDE_DIRS})
#include_directories(${OpenCV_INCLUDE_DIRS} ${Eigen_INCLUDE_DIRS})
#link_directories(${OpenCV_LIB_DIR})

#message("OpenCV_LIB_DIR = ${OpenCV_LIB_DIR}")
#message("OpenCV_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")
#message("OpenCV_DIR = ${OpenCV_DIR}")
#message("OpenCV_LIBS = ${OpenCV_LIBS}")

add_executable( testmatrix main_test.cpp )

#target_link_libraries( testEigen ${OpenCV_LIBS} )

