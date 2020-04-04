'''
    1. Do intrinsics calibration
    2. Estimate all the chessboard poses
'''
import numpy as np
import cv2
import glob
import os 
import json

# initialization
# ==============
DATA_DIR = r'some_path_to_data'
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
board_H, board_W, squareSz = 17, 24, 15


# prepare object points
# =====================
objpts_ = []
for i in range(board_H):
    for j in range(board_W):
        objpts_.append([[i*squareSz, j*squareSz,0]])        
objpts_ = np.array(objpts_, np.float32)
# print(objpts_, ' ', len(objpts_))
print('obj pts shape: ', objpts_.shape)


# read the images
# ===============
imgpts = []
objpts = []
for gl in glob.glob(os.path.join(DATA_DIR, '*.bmp')):
    im = cv2.imread(gl)

    gr = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)

    ret, corners = cv2.findChessboardCorners(gr, (board_H, board_W), None)
    # print('ret = ', ret)
    # print('corners = ', corners)

    if ret :
        objpts.append(objpts_)
        corners2 = cv2.cornerSubPix(gr, corners, (11,11), (-1,-1), criteria)
        imgpts.append(corners2)

        dsp = cv2.drawChessboardCorners(im, (board_H, board_W), corners2, ret )
        cv2.imshow('abc', dsp)
        cv2.waitKey(1)    


# calibration
# ===========
objpts = np.array(objpts)
print('obj pts shape: ', objpts.shape)
imgpts = np.array(imgpts)
print('img pts shape: ', imgpts.shape)
ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpts, imgpts, gr.shape[::-1], None, None)


# export results
# ==============
with open(os.path.join(DATA_DIR, "intrinsics.json"), "w") as f:
    d = {"K" : mtx.flatten().tolist(),
         "dist" : dist.flatten().tolist(), 
         "rvecs" : [rv.flatten().tolist() for rv in rvecs], 
         "tvecs" : [tv.flatten().tolist() for tv in tvecs]
         }
    json.dump(d, f)

print('Ends.')