//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May 24 17:52:06 2019 by ROOT version 6.14/04
// from TTree HitTree/Hit Tree
// found on file: rootfile.root
//////////////////////////////////////////////////////////

#ifndef fromLatencyScan_h
#define fromLatencyScan_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class fromLatencyScan {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           nhits;
   Int_t           hit_bcid;
   Int_t           hit_l1id;
   Int_t           hit_col[3];   //[nhits]
   Int_t           hit_row[3];   //[nhits]
   Int_t           hit_tot[3];   //[nhits]
   Int_t           pixel_cluster_id[3];   //[nhits]
   Int_t           nclusters;
   Int_t           cluster_tot[1];   //[nclusters]
   Int_t           cluster_id[1];   //[nclusters]
   Int_t           cluster_size[1];   //[nclusters]
   Int_t           cluster_ncol[1];   //[nclusters]
   Int_t           cluster_nrow[1];   //[nclusters]

   // List of branches
   TBranch        *b_nhits;   //!
   TBranch        *b_hit_bcid;   //!
   TBranch        *b_hit_l1id;   //!
   TBranch        *b_hit_col;   //!
   TBranch        *b_hit_row;   //!
   TBranch        *b_hit_tot;   //!
   TBranch        *b_pixel_cluster_id;   //!
   TBranch        *b_nclusters;   //!
   TBranch        *b_cluster_tot;   //!
   TBranch        *b_cluster_id;   //!
   TBranch        *b_cluster_size;   //!
   TBranch        *b_cluster_ncol;   //!
   TBranch        *b_cluster_nrow;   //!

   fromLatencyScan(TTree *tree=0);
   virtual ~fromLatencyScan();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef fromLatencyScan_cxx
fromLatencyScan::fromLatencyScan(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("rootfile.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("rootfile.root");
      }
      f->GetObject("HitTree",tree);

   }
   Init(tree);
}

fromLatencyScan::~fromLatencyScan()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t fromLatencyScan::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t fromLatencyScan::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void fromLatencyScan::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nhits", &nhits, &b_nhits);
   fChain->SetBranchAddress("hit_bcid", &hit_bcid, &b_hit_bcid);
   fChain->SetBranchAddress("hit_l1id", &hit_l1id, &b_hit_l1id);
   fChain->SetBranchAddress("hit_col", hit_col, &b_hit_col);
   fChain->SetBranchAddress("hit_row", hit_row, &b_hit_row);
   fChain->SetBranchAddress("hit_tot", hit_tot, &b_hit_tot);
   fChain->SetBranchAddress("pixel_cluster_id", pixel_cluster_id, &b_pixel_cluster_id);
   fChain->SetBranchAddress("nclusters", &nclusters, &b_nclusters);
   fChain->SetBranchAddress("cluster_tot", cluster_tot, &b_cluster_tot);
   fChain->SetBranchAddress("cluster_id", cluster_id, &b_cluster_id);
   fChain->SetBranchAddress("cluster_size", cluster_size, &b_cluster_size);
   fChain->SetBranchAddress("cluster_ncol", cluster_ncol, &b_cluster_ncol);
   fChain->SetBranchAddress("cluster_nrow", cluster_nrow, &b_cluster_nrow);
   Notify();
}

Bool_t fromLatencyScan::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void fromLatencyScan::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t fromLatencyScan::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef fromLatencyScan_cxx
