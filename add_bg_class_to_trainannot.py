import os
import sys
from pathlib import Path

import json
import cv2
import numpy as np
from pycocotools.coco import COCO

import Polygon as plg
from main_linux_ocr import xyxytoxy4, get_union, get_intersection


def add_an_annot(
        imid,
        catid,
        bbox,
        train_coco):
    annid = np.unique(np.array(list(train_coco.anns.keys()))).size
    ann = {"id": annid,
           "image_id": imid,
           "category_id": catid,
           "iscrowd": 0,
           "bbox": bbox,
           "angle": -1,
           "segmentation": [],
           "keypoints": [],
           "text": ""}
    train_coco.anns[annid] = ann


data_root = Path('/media/shawnle/ff3f78c1-620f-47df-a6a6-8ee62c3f8c63/mpnet/2023/Jul/solomon-ai-kit/data/data_slmdptc/7SegmentDisplay/Char/')
detect_json = data_root / 'Models' / '1' / 'detection_annotation.json'
image_folder = data_root / 'Images'
train_json = image_folder / 'train.json'

det_coco = COCO(detect_json)
train_coco = COCO(train_json)

new_cat_id = 0
new_cat_name = "bg"
new_cat_supercategory = "background"
add_coco_cat = train_coco.cats[1].copy()
add_coco_cat["id"] = new_cat_id
add_coco_cat["name"] = new_cat_name
add_coco_cat["supercategory"] = new_cat_supercategory
train_coco.cats[new_cat_id] = add_coco_cat

thresholds = [0.5]
nd = len(det_coco.anns)
tp = np.zeros((nd, len(thresholds)))
fp = np.zeros((nd, len(thresholds)))
imid_gt_checked = dict()
for k in train_coco.imgs.keys():
    for v in train_coco.imgToAnns.values():
        if v[0]['image_id'] == k:
            ann_len = len(v)
            break
    imid_gt_checked[k] = np.zeros((ann_len, len(thresholds)))

for i, (pk, p) in enumerate(det_coco.anns.items()):
    imid = p['image_id']
    gt_checked = imid_gt_checked[imid]
    imid_gt = []
    for v in train_coco.imgToAnns.values():
        if v[0]['image_id'] == imid:
            imid_gt = v
            break

    x, y, w, h = p['bbox']
    x1, y1, x2, y2 = x, y, x + w, y + h
    pr_bb = plg.Polygon(np.array(xyxytoxy4(
        [x1, y1, x2, y2])).reshape(-1, 2))

    max_iou = 0
    max_iou_gti = 0
    for gti, gt in enumerate(imid_gt):
        x, y, w, h = gt['bbox']
        x1, y1, x2, y2 = x, y, x + w, y + h
        gt_bb = plg.Polygon(np.array(xyxytoxy4(
            [x1, y1, x2, y2])).reshape(-1, 2))

        union = get_union(pr_bb, gt_bb)
        inter = get_intersection(pr_bb, gt_bb)
        overlap = inter / (union + 1e-6)
        if overlap > max_iou:
            max_iou = overlap
            max_iou_gti = gti

    for t, thr in enumerate(thresholds):
        if max_iou > thr:
            if gt_checked[max_iou_gti, t] == 0:
                tp[i, t] = 1.
                gt_checked[max_iou_gti, t] = 1
            else:
                fp[i, t] = 1.
                add_an_annot(imid, new_cat_id, p['bbox'],
                             train_coco
                             )
        else:
            fp[i, t] = 1.
            add_an_annot(imid, new_cat_id, p['bbox'],
                         train_coco
                         )

# backup train.json
train_json_bak = image_folder / 'train.json.bak'
if not os.path.exists(train_json_bak):
    os.rename(train_json, train_json_bak)

# save new train.json
dump_coco = dict()
dump_coco['categories'] = list(train_coco.cats.values())
dump_coco['images'] = list(train_coco.imgs.values())
dump_coco['annotations'] = list(train_coco.anns.values())
with open(train_json, 'w') as f:
    json.dump(dump_coco, f)
print('Done.')
