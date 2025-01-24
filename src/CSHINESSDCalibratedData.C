#include "../include/CSHINESSDCalibratedData.h"
using namespace std;


//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
CSHINESSDCalibratedData::CSHINESSDCalibratedData()
{
  fL1SEChPedestals  = new Double_t [NUM_SSD*NUM_STRIP];
  fL2FEChPedestals  = new Double_t [NUM_SSD*NUM_STRIP];
  fL2BEChPedestals  = new Double_t [NUM_SSD*NUM_STRIP];

  fL1SEChCut        = new Double_t [NUM_SSD*NUM_STRIP];
  fL2FEChCut        = new Double_t [NUM_SSD*NUM_STRIP];
  fL2BEChCut        = new Double_t [NUM_SSD*NUM_STRIP];
  fCsIEChCut        = new Double_t [NUM_SSD*NUM_CSI];

  fL1SSlope         = new Double_t [NUM_SSD*NUM_STRIP];
  fL2FSlope         = new Double_t [NUM_SSD*NUM_STRIP];
  fL2BSlope         = new Double_t [NUM_SSD*NUM_STRIP];

  fL1SIntercept     = new Double_t [NUM_SSD*NUM_STRIP];
  fL2FIntercept     = new Double_t [NUM_SSD*NUM_STRIP];
  fL2BIntercept     = new Double_t [NUM_SSD*NUM_STRIP];

  fL1SEMeVCut       = new Double_t [NUM_SSD*NUM_STRIP];
  fL2FEMeVCut       = new Double_t [NUM_SSD*NUM_STRIP];
  fL2BEMeVCut       = new Double_t [NUM_SSD*NUM_STRIP];

  //cout<<"Enter Class CSHINESSDCalibratedData!"<<endl;
}

//______________________________________________________________________________
CSHINESSDCalibratedData::~CSHINESSDCalibratedData()
{
  delete [] fL1SEChPedestals;
  delete [] fL2FEChPedestals;
  delete [] fL2BEChPedestals;

  delete [] fL1SEChCut;
  delete [] fL2FEChCut;
  delete [] fL2BEChCut;
  delete [] fCsIEChCut;

  delete [] fL1SSlope;
  delete [] fL2FSlope;
  delete [] fL2BSlope;

  delete [] fL1SIntercept;
  delete [] fL2FIntercept;
  delete [] fL2BIntercept;

  delete [] fL1SEMeVCut;
  delete [] fL2FEMeVCut;
  delete [] fL2BEMeVCut;

  //cout<<"Exit Class CSHINESSDCalibratedData\n";
}
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo


//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//  提取 pedestals
Double_t* CSHINESSDCalibratedData::GetSiEChPedestals(const char* layertag)
{
  std::string pathDataInput(Form("%sSSD_%s_PulserCaliPedestals_Pedestal0000.dat", pathSiCaliParsFolder.c_str(), layertag));

  if (!readfile.IsFileExists(pathDataInput.c_str())) {
    cout<<Form("文件 %s 不存在!", pathDataInput.c_str())<<endl;
    return NULL;
  }

  Double_t* fSiEChPedestals;
  if (strcmp(layertag,"L1S")==0) {
    fSiEChPedestals = fL1SEChPedestals;
  } else if (strcmp(layertag,"L2F")==0) {
    fSiEChPedestals = fL2FEChPedestals;
  } else {
    fSiEChPedestals = fL2BEChPedestals;
  }

  Int_t numpar = 2; // pedestal mean, sigma
  Double_t*** pedestals = readfile.ReadData(pathDataInput.c_str(),NUM_SSD,NUM_STRIP,numpar);

  for (Int_t i=0; i<NUM_SSD; i++) {
    for (Int_t j=0; j<NUM_STRIP; j++) {
      fSiEChPedestals[i*NUM_STRIP+j] = pedestals[i][j][0];
    }
  }
  // delete, 释放内存
  readfile.DeleteData(pedestals,NUM_SSD,NUM_STRIP,numpar);
  return fSiEChPedestals;
}
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo


//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// 计算 ECh_Cut = pedestal + num * sigma
Double_t* CSHINESSDCalibratedData::GetSiEChCut(const char* layertag)
{
  std::string pathDataInput(Form("%sSSD_%s_PulserCaliPedestals_Pedestal0000.dat", pathSiCaliParsFolder.c_str(), layertag));

  if (!readfile.IsFileExists(pathDataInput.c_str())) {
    cout<<Form("文件 %s 不存在!", pathDataInput.c_str())<<endl;
    return NULL;
  }

  Double_t* fSiEChCut;
  Double_t  fSiNumSigma[NUM_SSD];
  if (strcmp(layertag,"L1S")==0) {
    fSiEChCut = fL1SEChCut;
    for (Int_t i=0; i<NUM_SSD; i++) {
      fSiNumSigma[i] = NUM_SIGMA_L1S[i];
    }
  } else if (strcmp(layertag,"L2F")==0) {
    fSiEChCut = fL2FEChCut;
    for (Int_t i=0; i<NUM_SSD; i++) {
      fSiNumSigma[i] = NUM_SIGMA_L2F[i];
    }
  } else {
    fSiEChCut = fL2BEChCut;
    for (Int_t i=0; i<NUM_SSD; i++) {
      fSiNumSigma[i] = NUM_SIGMA_L2B[i];
    }
  }

  Int_t numpar = 2; // pedestal mean, sigma
  Double_t*** pedestals = readfile.ReadData(pathDataInput.c_str(),NUM_SSD,NUM_STRIP,numpar);

  for (Int_t i=0; i<NUM_SSD; i++) {
    for (Int_t j=0; j<NUM_STRIP; j++) {
      fSiEChCut[i*NUM_STRIP+j] = pedestals[i][j][0] + fSiNumSigma[i]*pedestals[i][j][1];
    }
  }
  // delete, 释放内存
  readfile.DeleteData(pedestals,NUM_SSD,NUM_STRIP,numpar);
  return fSiEChCut;
}
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo


//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// 计算 ECh_Cut = pedestal + num * sigma
Double_t* CSHINESSDCalibratedData::GetSiEChCut(const char* layertag, Double_t numsigma)
{
  std::string pathDataInput(Form("%sSSD_%s_PulserCaliPedestals_Pedestal0000.dat", pathSiCaliParsFolder.c_str(), layertag));

  if (!readfile.IsFileExists(pathDataInput.c_str())) {
    cout<<Form("文件 %s 不存在!", pathDataInput.c_str())<<endl;
    return NULL;
  }

  Double_t* fSiEChCut;
  if (strcmp(layertag,"L1S")==0) {
    fSiEChCut = fL1SEChCut;
  } else if (strcmp(layertag,"L2F")==0) {
    fSiEChCut = fL2FEChCut;
  } else {
    fSiEChCut = fL2BEChCut;
  }

  Int_t numpar = 2; // pedestal mean, sigma
  Double_t*** pedestals = readfile.ReadData(pathDataInput.c_str(),NUM_SSD,NUM_STRIP,numpar);

  for (Int_t i=0; i<NUM_SSD; i++) {
    for (Int_t j=0; j<NUM_STRIP; j++) {
      fSiEChCut[i*NUM_STRIP+j] = pedestals[i][j][0] + numsigma*pedestals[i][j][1];
    }
  }
  // delete, 释放内存
  readfile.DeleteData(pedestals,NUM_SSD,NUM_STRIP,numpar);
  return fSiEChCut;
}
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo


//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//  提取硅条的能量曲线的斜率, 参数为 <peak1 + peak2> 的情况
Double_t* CSHINESSDCalibratedData::GetSiCaliSlope(const char* layertag)
{
  std::string pathDataInput(Form("%sSSD_%s_SiEnergyCaliParameters.dat", pathSiCaliParsFolder.c_str(), layertag));

  if (!readfile.IsFileExists(pathDataInput.c_str())) {
    cout<<Form("文件 %s 不存在!", pathDataInput.c_str())<<endl;
    return NULL;
  }

  Double_t* fSiCaliSlope;
  if (strcmp(layertag,"L1S")==0) {
    fSiCaliSlope = fL1SSlope;
  } else if (strcmp(layertag,"L2F")==0) {
    fSiCaliSlope = fL2FSlope;
  } else {
    fSiCaliSlope = fL2BSlope;
  }

  Int_t numpar = 4; // k_ave, h_ave, k_deadlayer, h_deadlayer
  Double_t*** pedestals = readfile.ReadData(pathDataInput.c_str(),NUM_SSD,NUM_STRIP,numpar);

  for (Int_t i=0; i<NUM_SSD; i++) {
    for (Int_t j=0; j<NUM_STRIP; j++) {
      fSiCaliSlope[i*NUM_STRIP+j] = pedestals[i][j][0]; // k_ave
    }
  }
  // delete, 释放内存
  readfile.DeleteData(pedestals,NUM_SSD,NUM_STRIP,numpar);
  return fSiCaliSlope;
}
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo


//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//  提取硅条的能量曲线的截距, 参数为 <peak1 + peak2> 的情况
Double_t* CSHINESSDCalibratedData::GetSiCaliIntercept(const char* layertag)
{
  std::string pathDataInput(Form("%sSSD_%s_SiEnergyCaliParameters.dat", pathSiCaliParsFolder.c_str(), layertag));

  if (!readfile.IsFileExists(pathDataInput.c_str())) {
    cout<<Form("文件 %s 不存在!", pathDataInput.c_str())<<endl;
    return NULL;
  }

  Double_t* fSiCaliIntercept;
  if (strcmp(layertag,"L1S")==0) {
    fSiCaliIntercept = fL1SIntercept;
  } else if (strcmp(layertag,"L2F")==0) {
    fSiCaliIntercept = fL2FIntercept;
  } else {
    fSiCaliIntercept = fL2BIntercept;
  }

  Int_t numpar = 4; // k_ave, h_ave, k_deadlayer, h_deadlayer
  Double_t*** pedestals = readfile.ReadData(pathDataInput.c_str(),NUM_SSD,NUM_STRIP,numpar);

  for (Int_t i=0; i<NUM_SSD; i++) {
    for (Int_t j=0; j<NUM_STRIP; j++) {
      fSiCaliIntercept[i*NUM_STRIP+j] = pedestals[i][j][1]; //h_ave
    }
  }
  // delete, 释放内存
  readfile.DeleteData(pedestals,NUM_SSD,NUM_STRIP,numpar);
  return fSiCaliIntercept;
}
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo


//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// 计算参数为 <peak1 + peak2> 的情况下, ECh_Cut 对应的能量 EMeV_Cut
Double_t* CSHINESSDCalibratedData::GetSiEMeVCut(const char* layertag)
{
  Double_t* fSiEMeVCut;
  if (strcmp(layertag,"L1S")==0) {
    fSiEMeVCut = fL1SEMeVCut;
  } else if (strcmp(layertag,"L2F")==0) {
    fSiEMeVCut = fL2FEMeVCut;
  } else {
    fSiEMeVCut = fL2BEMeVCut;
  }

  Double_t* slope     = GetSiCaliSlope    (layertag);
  Double_t* intercept = GetSiCaliIntercept(layertag);
  Double_t* echcut    = GetSiEChCut       (layertag);

  for (Int_t i=0; i<NUM_SSD; i++) {
    for (Int_t j=0; j<NUM_STRIP; j++) {
      fSiEMeVCut[i*NUM_STRIP+j] = slope[i*NUM_STRIP+j]*echcut[i*NUM_STRIP+j] + intercept[i*NUM_STRIP+j];
    }
  }
  return fSiEMeVCut;
}
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo


//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// 对于每个 SSD 的 每个 Ch, 给定 ECh 时, 计算对应的能量 EMeV
Double_t CSHINESSDCalibratedData::GetSiEMeV(Int_t ssdindex, const char* layertag, Int_t chindex, Int_t ech)
{
  Double_t* slope     = GetSiCaliSlope    (layertag);
  Double_t* intercept = GetSiCaliIntercept(layertag);
  Double_t* echcut    = GetSiEChCut       (layertag);
  if (ech < echcut[ssdindex*NUM_STRIP+chindex]) return -9999; // 忽略 ech<cut 的事件
  return  slope[ssdindex*NUM_STRIP+chindex]*ech + intercept[ssdindex*NUM_STRIP+chindex];
}
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo


//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
Double_t* CSHINESSDCalibratedData::GetCsIEChCut(const char* layertag)
{
  std::string pathDataInput(Form("%sSSD_%s_PulserCaliPedestals_Pedestal0000.dat", pathSiCaliParsFolder.c_str(), layertag));

  if (!readfile.IsFileExists(pathDataInput.c_str())) {
    cout<<Form("文件 %s 不存在!", pathDataInput.c_str())<<endl;
    return NULL;
  }

  Double_t fCsINumSigma[NUM_SSD];
  for (Int_t i=0; i<NUM_SSD; i++) {
    fCsINumSigma[i] = NUM_SIGMA_L3A[i];
  }

  Int_t numpar = 2;
  Double_t*** echcut = readfile.ReadData(pathDataInput.c_str(),NUM_SSD,NUM_CSI,numpar);

  for (Int_t i=0; i<NUM_SSD; i++) {
    for (Int_t j=0; j<NUM_CSI; j++) {
      fCsIEChCut[i*NUM_CSI+j] = echcut[i][j][0] + fCsINumSigma[i] * echcut[i][j][1];
    }
  }
  // delete, 释放内存
  readfile.DeleteData(echcut,NUM_SSD,NUM_CSI,numpar);
  return fCsIEChCut;
}
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo


//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
Double_t* CSHINESSDCalibratedData::GetCsIEChCut(const char* layertag, Double_t numsigma)
{
  std::string pathDataInput(Form("%sSSD_%s_PulserCaliPedestals_Pedestal0000.dat", pathSiCaliParsFolder.c_str(), layertag));

  if (!readfile.IsFileExists(pathDataInput.c_str())) {
    cout<<Form("文件 %s 不存在!", pathDataInput.c_str())<<endl;
    return NULL;
  }

  Int_t numpar = 2;
  Double_t*** echcut = readfile.ReadData(pathDataInput.c_str(),NUM_SSD,NUM_CSI,numpar);

  for (Int_t i=0; i<NUM_SSD; i++) {
    for (Int_t j=0; j<NUM_CSI; j++) {
      fCsIEChCut[i*NUM_CSI+j] = echcut[i][j][0] + numsigma * echcut[i][j][1];
    }
  }
  // delete, 释放内存
  readfile.DeleteData(echcut,NUM_SSD,NUM_CSI,numpar);
  return fCsIEChCut;
}
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
