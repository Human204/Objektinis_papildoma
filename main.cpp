#include "lib.h"

void Skaitymas(map<string,int> &zodziai,std::stringstream &buf){
    string zodis;
    while(!buf.eof()){
        buf>>zodis;
        
        // char raides[zodis.length()];
        vector<char> to_remove;
        cout<<zodis<<" || ";
        for(int i=0;i<zodis.length();i++){
            if(!isalnum(zodis[i])){
                // cout<<zodis[i]<<" ";
                to_remove.push_back(zodis[i]);
            }
        }
        
        for(auto &i:to_remove){
            cout<<i<<" // "<<zodis.find(i)<<" ";
            zodis.erase(zodis.find(i),zodis.find(i)+1);
        }
        // cout<<zodis<<endl;
        if(zodziai.count(zodis)==0)zodziai.insert(std::pair<string,int>(zodis,1));
        else{
            auto it=zodziai.find(zodis);
            it->second++;
        }
        zodis.clear();
        to_remove.clear();
        cout<<'\n';
    }
}
void Rasymas(map<string,int> &zodziai){
    ofstream fout("o.txt");
    for(auto &it:zodziai){
        fout<<it.first<<" "<<it.second<<endl;
    }
}


int main(){
    // setlocale(LC_ALL,"Lithuanian");
    map<string,int> zodziai;
    ifstream fin;
      try{
        fin.open("i.txt");
        if(!fin){
          throw std::runtime_error("Failo nera.");
        }
        cout<<"Failas atidarytas."<<endl;
      }
      catch(const std::exception &e){
        std::cerr<<e.what()<<endl;
        return 0;
      }
    std::stringstream buf;
    buf<<fin.rdbuf();
    fin.close();
    Skaitymas(zodziai,buf);
    Rasymas(zodziai);
    
    
}