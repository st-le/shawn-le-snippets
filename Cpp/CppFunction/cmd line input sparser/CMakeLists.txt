cmake_minimum_required(VERSION 2.8)
project( vid_cam_calib ) 


set(OpenCV_DIR "D:/opencv/build")

find_package( OpenCV REQUIRED core highgui imgproc objdetect calib3d features2d ml flann nonfree video contrib gpu legacy photo ts stitching) # 


# check finding
IF (OpenCV_FOUND)
message("OpenCV is found\n")
ELSE (OpenCV_FOUND)
message("OpenCV is NOT found\n")
ENDIF (OpenCV_FOUND)


include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})


message("OpenCV_LIB_DIR = ${OpenCV_LIB_DIR}")
message("OpenCV_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")
message("OpenCV_DIR = ${OpenCV_DIR}")
message("OpenCV_LIBS = ${OpenCV_LIBS}")

add_executable( vid_cam_calib main.cpp)

target_link_libraries( vid_cam_calib ${OpenCV_LIBS} )

