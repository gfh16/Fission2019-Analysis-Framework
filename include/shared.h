#ifndef SHARED_H
#define SHARED_H

#include "TMath.h"

//______________________________________________________________________________
extern const double RadToDeg;
extern const double DegToRad;

//______________________________________________________________________________
extern const int NUM_SSD;
extern const int NUM_STRIP;
extern const int NUM_CSI;
extern const int NUM_MAX_PARTICLES_PER_TEL;

//______________________________________________________________________________
// 定义轻粒子的原子序数(Z)与质量数(A)
extern const int    NUM_LCPs;
extern const int    Z_A_LCPs[16][2];

//______________________________________________________________________________
// 定义每一套硅条望远镜、每一层硅的厚度
extern const double SIL1THICKNESS[4]; //mm
extern const double SIL2THICKNESS[4]; //mm
extern const double CSITHICKNESS;     //mm

//______________________________________________________________________________
// 定义每一层的 Cut 值所使用的 pedestal sigma number
extern const double NUM_SIGMA_L1S[4];
extern const double NUM_SIGMA_L2F[4];
extern const double NUM_SIGMA_L2B[4];
extern const double NUM_SIGMA_L3A[4];

//______________________________________________________________________________
// 定义每一层的 Muliplicity Cut
extern const double MULTICUT_L1S;
extern const double MULTICUT_L2F;
extern const double MULTICUT_L2B;
extern const double MULTICUT_L3A;

//______________________________________________________________________________
// 定义 L2B_L2F Energy Cut
extern const double L2BL2F_ENERGYBOUNDARY[4];
extern const double L2BL2F_LOWENERGYNEGATIVECUT [4];
extern const double L2BL2F_LOWENERGYPOSITIVECUT [4];
extern const double L2BL2F_HIGHENERGYNEGATIVECUT[4];
extern const double L2BL2F_HIGHENERGYPOSITIVECUT[4];

//______________________________________________________________________________
// 对于能穿透 L2 的粒子, 通过 LISE 计算给出 L1, L2 的能损比例, 作为新的约束条件
extern const double L1L2_ENERGYLOWCUT [4];
extern const double L1L2_ENERGYHIGHCUT[4];

//______________________________________________________________________________
extern const char* PATHDATAFOLDER;        // data 数据文件夹绝对路径
extern const char* PATHFIGURESFOLDER;     // figures 输出文件夹绝对路径
extern const char* PATHROOTFILESFOLDER;   // root 文件所在文件夹绝对路径
extern const char* PATHHOMEFOLDER;        // home 目录所在绝对路径 (在不同机器上使用时需要修改)

extern const char* NAMERAWFILELIST;       //原始文件 list的文件名, 用于 Rawdata->RawRoot
extern const char* NAMERAWROOTFILELIST;   //RawRoot文件 list 的文件名,用于 RawRoot->MapRoot
extern const char* NAMEMAPROOTFILELIST;   //MapRoot文件 list 的文件名,用于 QualityCheck

#endif
