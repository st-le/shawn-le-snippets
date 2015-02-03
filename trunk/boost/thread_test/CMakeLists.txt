# CMakeList for DENSO PC
cmake_minimum_required(VERSION 2.8)
project( boost_test ) 

set( BOOST_ROOT "C:/boost_1_53_0/")
set( BOOST_INCLUDE_DIRS "C:/boost_1_53_0/")
set( Boost_LIBRARY_DIRS "C:/boost_1_53_0/stage/lib")


find_package( Boost REQUIRED )

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

message("${Boost_FOUND}")
message("${Boost_INCLUDE_DIRS}")

#set(OpenCV_DIR "D:/opencv/build")  
#set(OpenCV_DIR "D:/TEMP DRIVE/Softs/Mechatronics/OpenCV-2.4.2/OpenCV-2.4.2/opencv/build/")	 # win 8
#set(OpenCV_DIR "D:/Documents and Settings/SonLe/My Documents/SOFTs/OpenCV-2.4.2/opencv/build/")  # win XP

#find_package( OpenCV REQUIRED core highgui imgproc objdetect calib3d features2d ml flann nonfree video contrib gpu legacy photo ts stitching)

# check finding

add_executable( boost_test main.cpp)
target_link_libraries( boost_test ${Boost_LIBRARY_DIRS})

