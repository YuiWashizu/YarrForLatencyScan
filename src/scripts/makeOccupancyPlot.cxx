#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <TCanvas.h>
#include <TH2D.h>
#include <TPaveStats.h>
#include <TFile.h>
#include <TStyle.h>
#include <TF1.h>
#include <TLegend.h>
TStyle*gStyle;

const int ncol = 400;
const int nrow = 192;
bool debug=false;
TH2D*getHist(std::string filename, int maximum=110){
  std::ifstream ifs(filename);


  double occ[ncol][nrow];
  std::string tmpchar;
  double tmpdouble=0;
  ifs >> tmpchar;
  ifs >> tmpchar;
  ifs >> tmpchar;
  ifs >> tmpchar;
  if(maximum==16 || maximum==-1)ifs >> tmpchar >> tmpchar >> tmpchar;
  else ifs >> tmpchar;
  ifs >> tmpdouble >> tmpdouble >> tmpdouble;
  ifs >> tmpdouble >> tmpdouble >> tmpdouble;
  ifs >> tmpdouble >> tmpdouble ;
//  for(int ii=0;ii<8;ii++){
//    ifs.getline(tmpchar,1);
//    std::cout << tmpchar << std::endl;
//  }
  for (int row=0; row<nrow; row++) {
    for (int col=0; col<ncol; col++) {
      ifs >> occ[col][row];
      if(debug)std::cout << occ[col][row] << " " ;
    }
    if(debug)std::cout << std::endl;
  }
  TH2D* h2 = new TH2D(filename.c_str(),filename.c_str(),ncol,-0.5,ncol-0.5,nrow,-0.5,nrow-0.5);
  h2->Sumw2();
  for (int row=0; row<nrow; row++) {
    for (int col=0; col<ncol; col++) {
      h2->Fill(col, row, occ[col][row]);

    }
  }
  //  h2->GetXaxis()->SetRangeUser(50,100);
  //  h2->GetYaxis()->SetRangeUser(50,100);
  h2->SetMinimum(0);
  if(maximum!=-1) h2->SetMaximum(maximum);

  return h2;
}
int main(int argc, char* argv[]) {
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);

  
  if (argc < 3) {
    std::cout << "Provide input file!" << std::endl;
    return -1;
  }

  TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
  gPad->SetLogz(1);
  std::cout << argv[1] << std::endl;
  TH2D *h1= new TH2D(*(TH2D*)getHist(argv[1],atoi(argv[2]))->Clone());
  //  h1->SetMinimum(0);
  //  h1->SetMaximum(120);
  h1->Draw("COLZ");
  c1->Update();
  std::stringstream ss; ss.str("");
  ss << argv[1] << ".png";
  c1->Print(ss.str().c_str());
  std::stringstream ss2; ss2.str("");
  ss2 << argv[1] << ".root";
  TFile *fp = new TFile(ss2.str().c_str(),"RECREATE");
  h1->Write();
  fp->Write();
  fp->Close();
}
