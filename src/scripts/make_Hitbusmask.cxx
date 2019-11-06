#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <string>

int main(int argc,char *argv[]){
  bool debug=false;
  int i=0;
  int j=0;
  int mode=0;
  int ps;
  std::string Enable_half="            \"Enable\": [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]";
  std::string Hitbus_half="            \"Hitbus\": [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]";
  std::string Enablemask_all="            \"Enable\": [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]";
  std::string Hitbusmask_all="            \"Hitbus\": [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]";
  std::string Enable_all="            \"Enable\": [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]";
  std::string Hitbus_all="            \"Hitbus\": [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]";
  std::string str[5788];
  std::string buff;
  std::string input_filename=argv[1];
  std::ifstream ifs(input_filename.c_str());
  std::ofstream ofs("./configs/rd53a_test.json.mask");

  if(argc<3){
    std::cout<< "Usage : "<<argv[0]<<" config_file.json mask_mode"<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<"#######mask_mode########"<<std::endl;
    std::cout<<"#                      #"<<std::endl;
    std::cout<<"# 0 : one corecolumn   #"<<std::endl;
    std::cout<<"# 1 : diff bottom      #"<<std::endl;
    std::cout<<"# 2 : one column       #"<<std::endl;
    std::cout<<"# 3 : All OFF          #"<<std::endl;
    std::cout<<"# 4 : one column botto #"<<std::endl;
    std::cout<<"# 5 : all Hitbus OFF   #"<<std::endl;
    std::cout<<"# 6 : Hitbus upper OFF #"<<std::endl;
    std::cout<<"#                      #"<<std::endl;
    std::cout<<"########################"<<std::endl;

    return -1;
  }

  if(!ifs.is_open()){
    std::cerr << "Error! Cannnot open file " << std::endl;
    return -1;
  }
  
  while(std::getline(ifs,buff)){
    str[i]=buff;
    i++;
  }

  mode=atoi(argv[2]);
  if(mode<0 || mode>6){
    std::cerr<<"strange mode!"<<std::endl;
    return -1;
  }
  
  if(mode==0){
    for(j=181;j<i;j++){
      if (j<2534) {
	ps=str[j].find("Hitbus");
	if(ps != std::string::npos){
	  str[j]=str[j].replace(0,407,Hitbusmask_all);
	  if(debug){
	    std::cout<<str[j]<<std::endl;
	  }
	}
	ps=str[j].find("Enable");
	if(ps != std::string::npos){
	  str[j]=str[j].replace(0,407,Enablemask_all);
	  if(debug){
	    std::cout<<str[j]<<std::endl;
	  }
	}
      } else {
	ps=str[j].find("Hitbus");
	if(ps != std::string::npos){
	  str[j]=str[j].replace(0,407,Hitbus_all);
	  if(debug){
	    std::cout<<str[j]<<std::endl;
	  }
	}
	ps=str[j].find("Enable");
	if(ps != std::string::npos){
	  str[j]=str[j].replace(0,407,Enable_all);
	  if(debug){
	    std::cout<<str[j]<<std::endl;
	  }
	}
      }
    }
  }
  if(mode==1){  
    for(j=181;j<i;j++){
      if (j<1765) {
	ps=str[j].find("Hitbus");
	if(ps != std::string::npos){
	  str[j]=str[j].replace(0,407,Hitbusmask_all);
	  if(debug){
	    std::cout<<str[j]<<std::endl;
	  }
	}
	ps=str[j].find("Enable");
	if(ps != std::string::npos){
	  str[j]=str[j].replace(0,407,Enablemask_all);
	  if(debug){
	    std::cout<<str[j]<<std::endl;
	  }
	}
      } else {
	ps=str[j].find("Hitbus");
	if(ps != std::string::npos){
	  str[j]=str[j].replace(0,407,Hitbus_half);
	  if(debug){
	    std::cout<<str[j]<<std::endl;
	  }
	}
	ps=str[j].find("Enable");
	if(ps != std::string::npos){
	  str[j]=str[j].replace(0,407,Enable_half);
	  if(debug){
	    std::cout<<str[j]<<std::endl;
	  }
	}
      }
    }
  }
  if(mode==2){  
    for(j=181;j<i;j++){
      if (j<2576) {
	ps=str[j].find("Hitbus");
	if(ps != std::string::npos){
	  str[j]=str[j].replace(0,407,Hitbusmask_all);
	  if(debug){
	    std::cout<<str[j]<<std::endl;
	  }
	}
	ps=str[j].find("Enable");
	if(ps != std::string::npos){
	  str[j]=str[j].replace(0,407,Enablemask_all);
	  if(debug){
	    std::cout<<str[j]<<std::endl;
	  }
	}
      } else {
	ps=str[j].find("Hitbus");
	if(ps != std::string::npos){
	  str[j]=str[j].replace(0,407,Hitbus_all);
	  if(debug){
	    std::cout<<str[j]<<std::endl;
	  }
	}
	ps=str[j].find("Enable");
	if(ps != std::string::npos){
	  str[j]=str[j].replace(0,407,Enable_all);
	  if(debug){
	    std::cout<<str[j]<<std::endl;
	  }
	}
      }
    }
  }
  

  std::cout << "begin ofs" << std::endl;
  for(j=0;j<i;j++){
    ofs<<str[j];
    ofs<<"\n";
  }

  ofs.close();
  std::cout << "Done!" << std::endl;  
  return 0;
}
