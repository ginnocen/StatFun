/*
very simple exercise of bayesian interference (Example 3.20, Pag.180)
A binary signal is transmitted.
P(S=1)=p
P(S=-1)=1-p
The received signal is Y=N+S, where Noise is modelled as a gaussian centered in 0 with sigma=1.
Measuring Y=y, what is the probability that S=1?
*/

void BayesInterference(double p=1/2.){


TF1*fS1=new TF1("fS1","1/sqrt(2*3.14)*exp(-(x-1)^2/2)",-10,10);
fS1->SetLineColor(1);
TF1*fSm1=new TF1("fSm1","1/sqrt(2*3.14)*exp(-(x+1)^2/2)",-10,10);
fSm1->SetLineColor(2);

//probabilty di S=1 give Y con P(S=1)=1/2 P(S=-1)=1/2

TF1*probS1giveny=new TF1("probS1giveny","[0]*exp(x)/([0]*exp(x)+(1-[0])*exp(-x))",-10.,10.);
probS1giveny->SetParameter(0,p);
probS1giveny->SetLineColor(4);
probS1giveny->Draw();

TCanvas *canvas=new TCanvas("canvas","canvas",1000,500);
canvas->Divide(2,1);
canvas->cd(1);
fS1->Draw();
fSm1->Draw("same");
canvas->cd(2);
probS1giveny->Draw();

}