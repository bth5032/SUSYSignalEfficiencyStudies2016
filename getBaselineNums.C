#include "TH1.h"
#include "TChain.h"

using namespace std;

vector<pair<double,double>> getBaselineNums(){
/* Returns pairs of value/error in the order: highmass_lowvertex, highmass_highvertex, lowmass_lowvertex, lowmass_highvertex */

TH1D * lmhv = new TH1D("lmhv", "low mass, high vertex", 100, 0, 100);
TH1D * hmhv = new TH1D("hmhv", "high mass, high vertex", 100, 0, 100);
TH1D * hmlv = new TH1D("hmlv", "high mass, low vertex", 100, 0, 100);
TH1D * lmlv = new TH1D("lmlv", "low mass, low vertex", 100, 0, 100);


TChain *ch = new TChain("t");
ch->Add("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-11-05_ichep/t5zz_80x_v2*.root");

ch->Draw("dilmass>>hmlv", "evt_scale1fb*(mass_gluino == 1400 && mass_LSP == 1000 && nVert < 20)");
ch->Draw("dilmass>>hmhv", "evt_scale1fb*(mass_gluino == 1400 && mass_LSP == 1000 && nVert >= 20)");
ch->Draw("dilmass>>lmlv", "evt_scale1fb*(mass_gluino == 1300 && mass_LSP == 200 && nVert < 20)");
ch->Draw("dilmass>>lmhv", "evt_scale1fb*(mass_gluino == 1300 && mass_LSP == 200 && nVert >= 20)");


double lmlv_err, lmhv_err, hmhv_err, hmlv_err;
double lmlv_count, lmhv_count, hmhv_count, hmlv_count;

lmlv_count = lmlv->IntegralAndError(-1,101, lmlv_err);
hmlv_count = hmlv->Integral(-1,101, hmlv_err);
lmhv_count = lmhv->IntegralAndError(-1,101, lmhv_err);
hmhv_count = hmhv->Integral(-1,101, hmhv_err);

vector<pair<double, double>> ret;

ret.push_back(make_pair(hmlv_count, hmlv_err));
ret.push_back(make_pair(hmhv_count, hmhv_err));
ret.push_back(make_pair(lmlv_count, lmlv_err));
ret.push_back(make_pair(lmhv_count, lmhv_err));

cout<<"high mass, low vertex"<<ret[0].first<<"+/-"<<ret[0].second<<endl;
cout<<"high mass, high vertex"<<ret[1].first<<"+/-"<<ret[1].second<<endl;
cout<<"low mass, low vertex"<<ret[2].first<<"+/-"<<ret[2].second<<endl;
cout<<"low mass, high vertex"<<ret[3].first<<"+/-"<<ret[3].second<<endl;

return ret;
}