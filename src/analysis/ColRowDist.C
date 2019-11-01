/*
  ColRowDist
*/
#include "fromHitTree.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>


void ColRowDist(const std::string& fname) {
  TFile *f = TFile::Open(fname.c_str(), "READ");
  TTree *t = dynamic_cast<TTree*>(f->Get("HitTree"));

  fromHitTree event(t);
  int ievent;
  int nevents = t->GetEntries();
  int ihit;

  TFile *fout = TFile::Open("./analysis/ColRow.root", "RECREATE");
  TH1 *col_dist = new TH1F("col_dist", "HitDist;col;events", 136, 264, 400);
  TH1 *row_dist = new TH1F("row_dist", "HitDist;row;events", 100, 0, 100);
  TH2 *hitmap = new TH2F("hitmap", "HitMap;col;row", 136, 264, 400, 100, 0 ,100);
  int countNonZero = 0;

  for (ievent=0; ievent<nevents; ievent++) {
    event.GetEntry(ievent);
    if (event.nhits!=0) {
      countNonZero++;
      for (ihit=0; ihit<event.nhits; ihit++) {
	col_dist->Fill(event.hit_col[ihit]);
	row_dist->Fill(event.hit_row[ihit]);
	hitmap->Fill(event.hit_col[ihit], event.hit_row[ihit]);
      }
    }
  }
  std::cout << "AllEvents          = " << nevents << std::endl;
  std::cout << "countNonZeroEvents = " << countNonZero << std::endl;
  row_dist->Fit("gaus");
  fout->Write();
  

}
      

    
