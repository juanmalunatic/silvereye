# Tablas: ID de sensores, segmentos, angulos, axes, bones

Referencia "rápida" que podría estar mejor agrupada. Tanto joints como quats están se procesan en ISB en mainwindow.

|   | Real sensors (frame ID) | Raw sensors | Segments | Bone pointers (mBonePtrs) | Joints     | Axes Pointers  | Angles (Sagittal) |
|---|-------------------------|-------------|----------|---------------------------|------------|----------------|-------------------|
| 0 |                         | Hip         | Hip      | Hip                       | RightHip   | RightHip       | RightHip          |
| 1 | Hip                     | RThigh      | RThigh   | RThigh                    | RightKnee  | RightKnee      | RightKnee         |
| 2 | RThigh                  | RShin       | RShin    | RShin                     | RightAnkle | RightAnkle     | RightAnkle        |
| 3 | RShin                   | RFoot       | RFoot    | RFoot                     | LeftHip    | LeftHip        | LeftHip           |
| 4 | RFoot                   | LThigh      | LThigh   | LThigh                    | LeftKnee   | LeftKnee       | LeftKnee          |
| 5 | LThigh                  | LShin       | LShin    | LShin                     | LeftAnkle  | LeftAnkle      | LeftAnkle         |
| 6 | LShin                   | LFoot       | LFoot    | LFoot                     |            | personAxesNode |                   |
| 7 | LFoot                   |             |          |                           |            |                |                   |


## RAW SENSORS 

```
[0] : Hip 
[1] : RThigh 
[2] : RShin 
[3] : RFoot 
[4] : LThigh 
[5] : LShin 
[6]: LFoot
```

## JOINTS

```
[0] : right hip   (0 and 1) 
[1] : right knee  (1 and 2) 
[2] : right ankle (2 and 3) 
[3] : left hip    (0 and 4)  
[4] : left knee   (4 and 5)   
[5] : left ankle  (5 and 6)
```

## AXES POINTERS 
mAxesNodePtrs 

```
[0] = personAxesNode; 
[1] = rightHipAxesNode; 
[2] = rightKneeAxesNode; 
[3] = rightAnkleAxesNode; 
[4] = leftHipAxesNode; 
[5] = leftKneeAxesNode; 
[6] = leftAnkleAxesNode; 
```

# BONE POINTERS 
mBonePtrs 

```
[0] = hipsBone 
[1] = rThighBone 
[2] = rShinBone 
[3] = rFootBone 
[4] = lThighBone 
[5] = lShinBone 
[6] = lFootBone
```