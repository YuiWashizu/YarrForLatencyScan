/*
  EventperPixelDist

  =========================
  can use this at src
  % root
  root[0] .L ./analysis/fromHitTree.C+()
  root[1] .x EventperPixelDist.C+("filename")
  =========================
*/
#include "fromHitTree.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TF1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "math.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>


void EventperPixelDist (const std::string& fname) {
  std::string rootfileout = fname + "_out.root";
  std::string outimage = fname + "_EventperPixelDist.png";

  TFile* f = TFile::Open(fname.c_str(), "READ");
  TTree* t = dynamic_cast<TTree*>(f->Get("HitTree"));
  
  fromHitTree event(t);
  int ievent;
  int nevents = t->GetEntries();
  int ihits;
  
  
  TFile* fout = TFile::Open(rootfileout.c_str(), "RECREATE");
  TH2* h_hitmap = new TH2F("h_hitmap", fname.c_str(), 140, 260, 400, 100, 0, 100);
  TH1* z_dist = new TH1F("z_dist", fname.c_str(), 15, 0, 15);

  for (ievent=0; ievent<nevents; ievent++) {
    event.GetEntry(ievent);
    if (event.nhits!=0) {
      for (ihits=0; ihits<event.nhits; ++ihits) {
	h_hitmap->Fill(event.hit_col[ihits], event.hit_row[ihits]);
      }
    }
  }

  for (int row=246; row<400; row++) {
    for (int col=2; col<97; col++) {
      int z = h_hitmap->GetBinContent(h_hitmap->GetBin(row, col));
      if (z==0) {
	std::cout << "row, col = " << row << ", " << col << std::endl;
      }
      // std::cout << "z = " << z << std::endl;
      z_dist->Fill(z);
    }
  }

  
  fout->Write();
  
  TF1 *fit1 = new TF1("fit1", "[0]*TMath::Poisson(x, [1])");
  fit1->SetParameter(0, 2);
  fit1->SetParameter(1, 4);
  // fit1->Draw();
  TCanvas* c1 = new TCanvas("c1", "c1", 700, 500);
  z_dist->Fit("fit1", "", "", 1, 12);
  z_dist->Draw("e");
  c1->SaveAs(outimage.c_str());
}

