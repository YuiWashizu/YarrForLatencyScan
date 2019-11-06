#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <string>


std::string makeMask(int start, int goal) {
  std::string init="[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]";
  std::string s = "1";
  int len = s.length();
  int i = start;
  while (i<goal) { 
    int pos = init.find(s, i);
    if (pos != std::string::npos) {
    // std::cout << "i = " << i << std::endl;
    init.replace(pos, len, "0");
    }
    i = i+len;
  }
  return init;
}

  


int main(int argc,char *argv[]){
  bool debug=false;
  int i=0;
  int j=0;
  int ps;
  std::string str[5788];
  std::string buff;
  std::string input_filename=argv[1];
  std::ifstream ifs(input_filename.c_str());
  std::ofstream ofs("./configs/rd53a_test.json.dbg");
  std::string init="[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]";

  if(!ifs.is_open()){
    std::cerr << "Error! Cannnot open file " << std::endl;
    return -1;
  }
  
  while(std::getline(ifs,buff)){
    str[i]=buff;
    i++;
  }

  std::string mode=argv[2];
  // if(mode<0 || mode>6){
  //   std::cerr<<"strange mode!"<<std::endl;
  //   return -1;
  // }
  
  if(mode=="-c") {
    if (argc<5) {
      int column = atoi(argv[3]);
      std::string mask = makeMask(0, 192*2+1);
      for (j=183;j<i;j++) {
	if (j>=column*6+183 && j<(column+1)*6+183) {
	  ps=str[j].find("Enable");
	  if (ps != std::string::npos) {
	    str[j]=str[j].replace(0, 407, "            \"Enable\": "+init);
	  }
	  ps=str[j].find("Hitbus");
	  if (ps != std::string::npos) {
	    str[j]=str[j].replace(0, 407, "            \"Hitbus\": "+init);
	  }
	} else {
	  ps=str[j].find("Enable");
	  if (ps != std::string::npos) {
	    str[j]=str[j].replace(0, 407, "            \"Enable\": "+mask);
	  }
	  ps=str[j].find("Hitbus");
	  if (ps != std::string::npos) {
	    str[j]=str[j].replace(0, 407, "            \"Hitbus\": "+mask);
	  }
	}	  
      }  

    }
  }
  for(j=0;j<i;j++){
    ofs<<str[j];
    ofs<<"\n";
  }
  

  ofs.close();
  std::cout << "Done!" << std::endl;  
  return 0;

}
