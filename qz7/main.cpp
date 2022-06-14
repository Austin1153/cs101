#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class myString{
    
};

class ReadClass{
    private:
        string fname;
        string temp,outp;
        int count;
    public:
        ReadClass(){
            fname = "main.cpp";
            count = 0;
        }
        void showClass(){
            ifstream soursef;
            soursef.open(fname);
            while(getline(soursef, temp)){
                string pt="";
                int cki = temp.find("class ",0);
                if(cki!=-1){
                    for(char t:temp){
                        if(t!='{')
                            pt+=t;
                        else{
                            outp+=pt+"\n";
                            count++;
                        }
                            
                    }
                }
            }
            cout << count << " class in " << fname << endl << outp;
            soursef.close();
            
        }
};

int main(){
    ReadClass rfile;
    rfile.showClass();
    return 0;
}
