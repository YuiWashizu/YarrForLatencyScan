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
#include "TGraph.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

void bcidVSnhits(std::string fname) {
  
  TFile* f = TFile::Open(fname.c_str(), "READ");
  TTree* t = dynamic_cast<TTree*>(f->Get("HitTree"));
  fromHitTree event(t);
  int nevent = t->GetEntries();
  int nhits[nevent/16+1];
  int bcid[nevent/16+1];

  for (int ievent=0; ievent<nevent; ievent++) {
    event.GetEntry(ievent);
    if (event.hit_l1id%16 == 7) {
      nhits[(ievent-7)/16] = event.nhits;
      bcid[(ievent-7)/16] = event.hit_bcid;
      // if (nhits[ievent]<0) {
      std::cout << "nhits[" << (ievent-7)/16 << "] : " << nhits[(ievent-7)/16] << std::endl;
      std::cout << "bcid[" << (ievent-7)/16 << "]  : " << bcid[(ievent-7)/16] << std::endl;
      // }
    }
  }
  
  TGraph *g = new TGraph(nevent/16, bcid, nhits);
  g->SetMarkerStyle(4);
  g->Draw("AP");
}

