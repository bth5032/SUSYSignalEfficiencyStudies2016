#include "TString.h"
#include "ScanChain.C"
#include "DefineDatasets.C"
#include "ConfigParser.C"

void runScanChain(ConfigParser* conf){
  cout<<"Using config:"<<endl;
  conf->print();

  ScanChain(getSUSYChain(conf->get("data_set")), conf->get("Name"), conf);   

}

void doAll ( TString config_name, TString config_file="configs/run_modes.conf" ) {

  ConfigParser *conf = new ConfigParser(config_file.Data());

  if (config_name == "all") {
    while ( conf->loadNextConfig() )
    {
      runScanChain(conf);
    }
  }

  else if ( conf->loadConfig(config_name.Data()) ){
    runScanChain(conf);
  }

  else{
    cout<<"Configuration "<<config_name<<" could not be loaded, please check the name and config file, "<<config_file<<"and try again."<<endl;
    exit(1);
  }
}
