/*
  LatencyAnalysis
*/
#undef fromHitTree_cxx

#include "fromHitTree.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

void LatencyAnalysis(std::string fname) {
  std::string str = fname.c_str();
  str.erase(fname.end()-4, fname.end());
  std::string foutname = str + "_latency.root";
  // std::string fpng_name = "./analysis/LatencyScane.png";
  TFile* f = TFile::Open(fname.c_str(), "READ");
  TTree* t = dynamic_cast<TTree*>(f->Get("HitTree"));
  fromHitTree event(t);
  int ievent;
  long long int nevents = t->GetEntries();
  int ihit;
  TFile* fout = TFile::Open(foutname.c_str(), "RECREATE");
  TH1* latency = new TH1F("latency", "HitTree;LatencyConfig;events", 510, 0, 510);
  
  for (ievent=0; ievent<nevents; ievent++) { 
    event.GetEntry(ievent);
    if (event.nhits!=0) {
      if (event.hit_l1id%16 == 7) {
	int lat_conf = 500-(ievent/1600);
	latency->Fill(lat_conf);
      }
    }
  }
  fout->Write();

  TCanvas* c1 = new TCanvas("c1", "c1", 700, 500);
  latency->Draw();
  // c1->SaveAs("LatencyScan.png");
}
