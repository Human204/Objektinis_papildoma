#include "lib.h"

void Skaitymas(map<string,zodziuinfo> &zodziai,std::stringstream &buf,vector<string> &saitai){
    string zodis,zodis2;
    int indeksas=0;
    while(!buf.eof()){
        buf>>zodis;
        
        // char raides[zodis.length()];
        vector<int> to_remove;
        if(zodis==" "&&zodis==""){
            zodis.clear();
            buf>>zodis;
        }
        if(urlcheck(zodis)){
            saitai.push_back(zodis);
            zodis.clear();
            buf>>zodis;
        }
        // zodis=tolower(zodis2);
        transform(zodis.begin(), zodis.end(), zodis.begin(), ::tolower);
        // cout<<zodis<<" || ";

        for(int i=0;i<zodis.length();i++){
            if((!isalnum(zodis[i])&&!isalnum(zodis[i+1]))||(!isalnum(zodis[i-1])&&!isalnum(zodis[i]))||(zodis[i]=='(')||(zodis[i]==')')){
                to_remove.push_back(i);
            }
        }
        int change=0;
        for(auto &i:to_remove){
            // cout<<i<<" // "<<zodis[i]<<" ";
            zodis.erase(i-change,1);
            change++;
        }
        if(zodziai.count(zodis)==0){
            zodziuinfo temp;
            temp.indeksai.push_back(indeksas);
            temp.pasikartojimai++;
            zodziai.insert(std::pair<string,zodziuinfo>(zodis,temp));
        }
        else{
            auto it=zodziai.find(zodis);
            it->second.pasikartojimai++;
            it->second.indeksai.push_back(indeksas);
        }
        zodis.clear();
        to_remove.clear();
        // cout<<'\n';
        indeksas++;
    }
}
void Rasymas(map<string,zodziuinfo> &zodziai,vector<string> &saitai){
    ofstream fout("o.txt");
    for(auto &it:zodziai){
        fout<<it.first<<" "<<it.second.pasikartojimai<<endl;
    }
    fout<<"\nSaitai: \n\n";
    for(auto &it:saitai){
        fout<<it<<endl;
    }
    ofstream fout2("table.txt");
    fout2<<"Zodziu indeksai: \n";
    for(auto &it:zodziai){
        if(it.second.indeksai.size()>1){
            // cout<<it.second.indeksai.size()<<"\n";
            fout2<<it.first<<": ";
            for(int i=0;i<it.second.indeksai.size();i++){
                fout2<<it.second.indeksai.at(i);
                if(i!=it.second.indeksai.size()-1)fout2<<" ";
                else fout2<<",";
            }
            fout2<<endl;
        }
    }
}

bool urlcheck(string zodis){
    if(zodis.compare(0,8,"https://")==0||zodis.compare(0,7,"http://")==0||zodis.compare(0,4,"www.")==0)return true;
    else return false;
}


int main(){
    // setlocale(LC_ALL,"Lithuanian");
    map<string,zodziuinfo> zodziai;
    vector<string> saitai;
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
    Skaitymas(zodziai,buf,saitai);
    Rasymas(zodziai,saitai);
    
    
}