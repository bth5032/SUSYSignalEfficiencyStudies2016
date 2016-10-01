#include "TString.h"
#include <vector>

void DrawPlots(TString sample){
	TString dir_loc = "/nfs-7/userdata/bobak/SUSYSignalEfficiency2016/";

	vector<TFile*> files;
	if (sample == "edge"){
		files.push_back(TFile::Open(dir_loc+TString("SUSYLightEdgeZ.root"), "READ"));
		files.push_back(TFile::Open(dir_loc+TString("SUSYHeavyEdgeZ.root"), "READ"));
	}
	else if (sample=="A_Btag"){
		files.push_back(TFile::Open(dir_loc+TString("SUSYLightA_btag.root"), "READ"));
		files.push_back(TFile::Open(dir_loc+TString("SUSYHeavyA_btag.root"), "READ"));
	}
	else if (sample=="A_Bveto"){
		files.push_back(TFile::Open(dir_loc+TString("SUSYLightA_bveto.root"), "READ"));
		files.push_back(TFile::Open(dir_loc+TString("SUSYHeavyA_bveto.root"), "READ"));
	}
	else if (sample=="B_Btag"){
		files.push_back(TFile::Open(dir_loc+TString("SUSYLightB_btag.root"), "READ"));
		files.push_back(TFile::Open(dir_loc+TString("SUSYHeavyB_btag.root"), "READ"));
	}
	else if (sample=="B_Bveto"){
		files.push_back(TFile::Open(dir_loc+TString("SUSYLightB_bveto.root"), "READ"));
		files.push_back(TFile::Open(dir_loc+TString("SUSYHeavyB_bveto.root"), "READ"));
	}
	else if (sample=="ATLAS"){
		files.push_back(TFile::Open(dir_loc+TString("SUSYLightATLAS.root"), "READ"));
		files.push_back(TFile::Open(dir_loc+TString("SUSYHeavyATLAS.root"), "READ"));
	}
	else{
		cout<<"Unrecognized sample: "<<sample<<endl;
		exit(1);
	}

//cout<<__LINE__<<endl;

	TH1D * lowVert_light = (TH1D*) ((TH1D*) files[0]->Get("SUSY_type1MET_widebin_lowVert"))->Clone("lowVert_light");
	TH1D * highVert_light = (TH1D*) ((TH1D*) files[0]->Get("SUSY_type1MET_widebin_highVert"))->Clone("highVert_light");

	TH1D * lowVert_heavy = (TH1D*) ((TH1D*) files[0]->Get("SUSY_type1MET_widebin_lowVert"))->Clone("lowVert_heavy");
	TH1D * highVert_heavy = (TH1D*) ((TH1D*) files[0]->Get("SUSY_type1MET_widebin_highVert"))->Clone("highVert_heavy");

//cout<<__LINE__<<endl;

	lowVert_light->SetLineColor(kRed);
	highVert_light->SetLineColor(kBlue);
	lowVert_heavy->SetLineColor(kRed);
	highVert_heavy->SetLineColor(kBlue);

//cout<<__LINE__<<endl;

//===============================
//Draw Plots
//===============================

	TCanvas *c1 = new TCanvas("MET_Light_canvas", "", 2000, 2000);
	c1->cd();

//cout<<__LINE__<<endl;

	gPad->SetLogy(1);
	gStyle->SetOptStat(kFALSE);

	lowVert_light->SetTitle("E^{miss}_{T} by pileup SUSY signals (mLSP=200, mGluino=1300)");
	lowVert_light->Draw("HIST");
	highVert_light->Draw("HIST SAME");

//cout<<__LINE__<<endl;
	
	TLegend *l1;
	l1 = new TLegend(0.73, 0.73, 0.88, 0.88);
	  
	l1->SetLineColor(kWhite);  
	l1->SetShadowColor(kWhite);
	l1->SetFillColor(kWhite);
	l1->AddEntry(lowVert_light, "Less than 20 verticies", "f");
	l1->AddEntry(highVert_light, "20 or more verticies", "f");
	  
	l1->Draw("same");

//cout<<__LINE__<<endl;

	c1->SaveAs("plots/"+sample+"_MET_light.png");

	TCanvas *c2 = new TCanvas("MET_Heavy_canvas", "", 2000, 2000);
	c2->cd();

//cout<<__LINE__<<endl;

	gPad->SetLogy(1);
	gStyle->SetOptStat(kFALSE);

	lowVert_heavy->SetTitle("E^{miss}_{T} by pileup SUSY signals (mLSP=1000, mGluino=1400)");
	lowVert_heavy->Draw("HIST");
	highVert_heavy->Draw("HIST SAME");

//cout<<__LINE__<<endl;
	
	TLegend *l2;
	l2 = new TLegend(0.73, 0.73, 0.88, 0.88);
	  
	l2->SetLineColor(kWhite);  
	l2->SetShadowColor(kWhite);
	l2->SetFillColor(kWhite);
	l2->AddEntry(lowVert_heavy, "Less than 20 verticies", "f");
	l2->AddEntry(highVert_heavy, "20 or more verticies", "f");
	  
	l2->Draw("same");

//cout<<__LINE__<<endl;

	c2->SaveAs("plots/"+sample+"_MET_heavy.png");


cout<<"SUSY Light low vertex count MET in bin 300+"<<lowVert_light->GetBinContent(lowVert_light->FindBin(300))<<endl;
cout<<"SUSY Light high vertex count MET in bin 300+"<<highVert_light->GetBinContent(highVert_light->FindBin(300))<<endl;
cout<<"SUSY Heavy low vertex count MET in bin 300+"<<lowVert_heavy->GetBinContent(lowVert_heavy->FindBin(300))<<endl;
cout<<"SUSY Heavy high vertex count MET in bin 300+"<<highVert_heavy->GetBinContent(highVert_heavy->FindBin(300))<<endl;
}