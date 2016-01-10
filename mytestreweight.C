/*
The goal of this statistical exercise is to apply the re-weighting technique to a 2D problem.
The problem is the following:
- we have a 2D histogram that contain the correlation plot between the D meson pt (y-axis)
  and the pt of the B meson that decayed into the D meson. 
  The 2D is produced with Pythia and therefore it includes the proper kinematic of the B->D decay
  but it has a wrong absolute B spectrum. 
- the idea is to reweight the PYTHIA 2D-istogram according to the FONLL B meson pt.

What is a 2D histogram?
- the easiest way is to think at any histogram as a probability distribution function in one or more variable.
  The scatter 2D plot of Dpt vs Bpt is proportional (or equal if norm=1) to the probability of 

  p(i,j) is the probability of having ptD(i)<Dpt<ptD(i+1) && ptB(j)<Bpt<ptB(j+1).

 What is the probability of having ptD(i)<Dpt<ptD(i+1)? 
 
 p(j)=Sum_over_i p(i,j)

How do i do if i want to have p(j)=pFONLL(j)?

Very easy. I am imposing that the marginal PDF along j is the same.

p_reweighted(i,j)=Sum_over_i,y p(i,j) * p_FONLL(j)/p(j)


DEMOSTRATION.

Given:
- p_B,D(i,j)= joint probability unweighted
- p^w_B,D(i,j)= joint probability weighted
- p_B(i) marginal of p_B,D(i,j)
- p^Fonll_B(i) marginal of  FONLL

p^w_B,D(i,j)=p_B,D(i,j)*p^Fonll_B(i)/p_B(i) 

Indeed

p^w_B(i)= Sum_j  p_B,D(i,j)*p^Fonll_B(i)/p_B(i)  =  Fonll_B(i)/p_B(i) *p_B(i) =Fonll_B(i)

*/

void mytestreweight(){


  TFile*finput=new TFile("fworking.root");
  TH1D*hBPtFONLL=(TH1D*)finput->Get("hBPt");
  TH1D*hDPtFONLL=(TH1D*)finput->Get("hDPt");
  TH2D*hD=(TH2D*)finput->Get("hD");
  
   hD->SetXTitle("B p_{T} (GeV/c)");
   hD->SetYTitle("D^{0} p_{T} (GeV/c)");
   hBPtFONLL->SetXTitle("B p_{T} (GeV/c)");
   hDPtFONLL->SetXTitle("D p_{T} (GeV/c)");
  
  TH2D *hDreweight = (TH2D*)hD->Clone("hDreweight");
  TH1D *hBPtPythia = hD->ProjectionX("hBPtPythia");
  TH1D *hDPtPythia = hD->ProjectionY("hDPtPythia");

   for (int x=1;x<=hDreweight->GetNbinsX()+1;x++){  //loop over the B pt bins
      if (hBPtPythia->GetBinContent(x)==0) continue;
      double ratio = hBPtFONLL->GetBinContent(x)/hBPtPythia->GetBinContent(x);  // in each pt bin we calculate the ratio of pythiaB/FONLLB 
       
      for (int y=1;y<=hDreweight->GetNbinsY()+1;y++){   //loop over the D pt bins
         double ratio2 = ratio;                                              //copy the ratio for each B bin
         double val = hDreweight->GetBinContent(x,y)*ratio2;
         double valError = hDreweight->GetBinError(x,y)*ratio2;
	 hDreweight->SetBinContent(x,y,val);
	 hDreweight->SetBinError(x,y,valError);
      }   
   }

  TH1D *hBPtPythiaReweight = hDreweight->ProjectionX("hBPtPythiaReweight");
  TH1D *hDPtPythiaReweight = hDreweight->ProjectionY("hDPtPythiaReweight");
  
  hBPtPythiaReweight->Divide(hBPtFONLL);
   
  TCanvas*canvas=new TCanvas("canvas","canvas",1000,500);  
  canvas->SetLogy();
  canvas->Divide(3,1);
  canvas->cd(1);
  hBPtFONLL->Draw();
  canvas->cd(2);
  hBPtPythia->Draw();
  canvas->cd(3);
  hBPtPythiaReweight->Draw();

}