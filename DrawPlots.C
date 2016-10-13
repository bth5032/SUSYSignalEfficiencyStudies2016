#include "TString.h"
#include <vector>
#include "getBaselineNums.C"

double err_binomial(double A, double B, double errA, double errB) {
	double c = B-A;
	double d = sqrt(errB*errB - errA*errA);
	return (1/pow(A+c,2)) * sqrt(pow(c*errA,2) + pow(A*d,2));
}

void ProcessSample(TString sample){
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

	TH1D * lowVert_light = (TH1D*) ((TH1D*) files[0]->Get("SUSYLight_type1MET_widebin_lowPU"))->Clone("lowVert_light");
	TH1D * highVert_light = (TH1D*) ((TH1D*) files[0]->Get("SUSYLight_type1MET_widebin_highPU"))->Clone("highVert_light");

//cout<<__LINE__<<endl;

	TH1D * lowVert_heavy = (TH1D*) ((TH1D*) files[1]->Get("SUSYHeavy_type1MET_widebin_lowPU"))->Clone("lowVert_heavy");
	TH1D * highVert_heavy = (TH1D*) ((TH1D*) files[1]->Get("SUSYHeavy_type1MET_widebin_highPU"))->Clone("highVert_heavy");

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

vector<pair<double, double>> baseline_stats = getBaselineNums();


double hmlv_count = baseline_stats[0].first;
double hmlv_err = baseline_stats[0].second;

double hmhv_count = baseline_stats[1].first;
double hmhv_err = baseline_stats[1].second;

double lmlv_count = baseline_stats[2].first;
double lmlv_err = baseline_stats[2].second;

double lmhv_count = baseline_stats[3].first;
double lmhv_err = baseline_stats[3].second;


double lowVert_light_count = lowVert_light->GetBinContent(lowVert_light->FindBin(300));
double lowVert_light_error = lowVert_light->GetBinError(lowVert_light->FindBin(300));
double lowVert_light_eff = lowVert_light_count/lmlv_count;
double lowVert_light_eff_err = err_binomial(lowVert_light_count, lmlv_count, lowVert_light_error, lmlv_err);

double highVert_light_count = highVert_light->GetBinContent(highVert_light->FindBin(300));
double highVert_light_error = highVert_light->GetBinError(highVert_light->FindBin(300));
double highVert_light_eff = highVert_light_count/lmhv_count;
double highVert_light_eff_err = err_binomial(highVert_light_count, lmhv_count, highVert_light_eff_err, lmhv_err);

double lowVert_heavy_count = lowVert_heavy->GetBinContent(lowVert_heavy->FindBin(300));
double lowVert_heavy_error = lowVert_heavy->GetBinError(lowVert_heavy->FindBin(300));
double lowVert_heavy_eff = lowVert_heavy_count/hmlv_count;
double lowVert_heavy_eff_err = err_binomial(lowVert_heavy_count, hmlv_count, lowVert_heavy_eff_err, hmlv_err);

double highVert_heavy_count = highVert_heavy->GetBinContent(highVert_heavy->FindBin(300));
double highVert_heavy_error = highVert_heavy->GetBinError(highVert_heavy->FindBin(300));
double highVert_heavy_eff = highVert_heavy_count/hmhv_count;
double highVert_heavy_eff_err = err_binomial(highVert_heavy_count, hmhv_count, highVert_heavy_eff_err, hmhv_err);


cout<<"SR "+sample+": SUSY Light low vertex count 300+ MET count "<<lowVert_light_count<<"+/-"<<lowVert_light_error<<" Efficiency: "<<lowVert_light_eff<<"+/-"<<lowVert_light_eff_err<<endl;
cout<<"SR "+sample+": SUSY Light high vertex count 300+ MET count "<<highVert_light_count<<"+/-"<<highVert_light_error<<" Efficiency: "<<highVert_light_eff<<"+/-"<<highVert_light_eff_err<<endl;
cout<<"SR "+sample+": SUSY Heavy low vertex count 300+ MET count "<<lowVert_heavy_count<<"+/-"<<lowVert_heavy_error<<" Efficiency: "<<lowVert_heavy_eff<<"+/-"<<lowVert_heavy_eff_err<<endl;
cout<<"SR "+sample+": SUSY Heavy high vertex count 300+ MET count "<<highVert_heavy_count<<"+/-"<<highVert_heavy_error<<" Efficiency: "<<highVert_heavy_eff<<"+/-"<<highVert_heavy_eff_err<<endl;
}

void DrawPlots(TString sample=""){
	if (sample != ""){
		ProcessSample(sample);
	}
	else{
		cout<<"================================================"<<endl;
		cout<<"Edge"<<endl;
		ProcessSample("edge");
		cout<<"////////////////////////////////////"<<endl;
		cout<<"/A/Btag/"<<endl;
		ProcessSample("A_Btag");
		cout<<"/A/Bveto/"<<endl;
		ProcessSample("A_Bveto");	
		cout<<"////////////////////////////////////"<<endl;
		cout<<"/B/Btag/"<<endl;
		ProcessSample("B_Btag");
		cout<<"/B/Bveto/"<<endl;
		ProcessSample("B_Bveto");
		cout<<"////////////////////////////////////"<<endl;
		cout<<"ATLAS"<<endl;
		ProcessSample("ATLAS");
		cout<<"================================================"<<endl;
	}
	
}