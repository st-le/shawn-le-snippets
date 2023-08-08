import os
import sys
from pathlib import Path

import json
import cv2
import numpy as np
from pycocotools.coco import COCO

from slmutils.annotator import Annotator

data_root = Path('/media/shawnle/ff3f78c1-620f-47df-a6a6-8ee62c3f8c63/mpnet/2023/Jul/solomon-ai-kit/data/data_slmdptc/7SegmentDisplay/Char/')
detect_json = data_root / 'Models' / '1' / 'detection_annotation.json'
image_folder = data_root / 'Images'
result_folder = image_folder / 'result'
img_exts = ["png", "jpg"]

coco_api = COCO(detect_json)

drawer = Annotator(show_bboxes=True,
                   show_masks=False,
                   show_kpts=False,
                   show_scores=False,
                   show_label=False,
                   class_names=[""],
                   )

for iid, img_info in coco_api.imgs.items():
    assert iid == img_info['id']

    img_path = img_info['file_name']
    img_name = os.path.basename(img_path)
    if os.path.exists(img_path):
        img = cv2.imread(img_path)

    img_anns = coco_api.imgToAnns[iid]
    result = {"rois": [], "class_ids": [], "word": []}
    for ann in img_anns:
        bbox = ann['bbox']
        x1, y1, w, h = bbox
        x2, y2 = x1 + w, y1 + h

        result["rois"].append([x1, y1, x2, y2])
        result["class_ids"].append(0)

    result['rois'] = np.array(result['rois'])
    img_res = drawer(img.copy(), results=result)
    cv2.imwrite(
        os.path.join(result_folder, img_name),
        img_res,
    )
