#ifndef CSHINESSDCalibratedData_H
#define CSHINESSDCalibratedData_H

#include "ReadFileModule.h"
#include "shared.h"


//______________________________________________________________________________
class CSHINESSDCalibratedData
{
public:
  CSHINESSDCalibratedData();
  virtual ~CSHINESSDCalibratedData();

  Double_t* GetSiEChPedestals    (const char* layertag);                  // [NUM_SSD*NUM_STRIP]
  Double_t* GetSiEChCut          (const char* layertag, Int_t numsigma);  // [NUM_SSD*NUM_STRIP]

  Double_t* GetSiCaliSlope       (const char* layertag);                  // [NUM_SSD*NUM_STRIP]
  Double_t* GetSiCaliIntercept   (const char* layertag);                  // [NUM_SSD*NUM_STRIP]
  Double_t* GetSiEMeVCut         (const char* layertag, Int_t numsigma);  // [NUM_SSD*NUM_STRIP]
  // Int_t ssdindex, const char* layertag, Int_t chindex, Double_t ech, Int_t numsigma
  Double_t GetSiEMeV   (Int_t, const char*, Int_t, Int_t, Int_t);

  Double_t* GetCsIEChCut(const char* layertag);   // [NUM_SSD*NUM_CSI]

private:
  Double_t* fL1SEChPedestals;   // [NUM_SSD*NUM_STRIP]
  Double_t* fL2FEChPedestals;   // [NUM_SSD*NUM_STRIP]
  Double_t* fL2BEChPedestals;   // [NUM_SSD*NUM_STRIP]

  Double_t* fL1SEChCut;         // [NUM_SSD*NUM_STRIP]
  Double_t* fL2FEChCut;         // [NUM_SSD*NUM_STRIP]
  Double_t* fL2BEChCut;         // [NUM_SSD*NUM_STRIP]
  Double_t* fCsIEChCut;         // [NUM_SSD*NUM_CSI]

  Double_t* fL1SSlope;          // [NUM_SSD*NUM_STRIP]
  Double_t* fL2FSlope;          // [NUM_SSD*NUM_STRIP]
  Double_t* fL2BSlope;          // [NUM_SSD*NUM_STRIP]

  Double_t* fL1SIntercept;      // [NUM_SSD*NUM_STRIP]
  Double_t* fL2FIntercept;      // [NUM_SSD*NUM_STRIP]
  Double_t* fL2BIntercept;      // [NUM_SSD*NUM_STRIP]

  Double_t* fL1SEMeVCut;        // [NUM_SSD*NUM_STRIP]
  Double_t* fL2FEMeVCut;        // [NUM_SSD*NUM_STRIP]
  Double_t* fL2BEMeVCut;        // [NUM_SSD*NUM_STRIP]
};

#endif