#include <fstream>
#include <iostream>
#include <string>
#include <vector>


class FileSearcher{

    static void generateLPS(const std::string &keyword, std::vector<int> &lps, const int &n){
        int pre=0,suf=1;

        while(suf<n){
            if(keyword[pre]==keyword[suf]){
                lps[suf]= pre+1;
                pre++,suf++;
            }
            else{
                if(pre==0) suf++;
                else{
                    pre= lps[pre-1];
                }
            }
        }
    }

    static bool contains(const std::string &line, const std::string &keyword){

        int n= line.length(), m= keyword.length();

        if(m>n) return false;
        
        std::vector<int> lps(m,0);
        generateLPS(keyword,lps,m);

        int first=0, second=0;

        while( first<n && second<m){
            if(line[first]==keyword[second]){
                first++,second++;
            }
            else{
                if(second==0) first++;
                else{
                    second= lps[second-1];
                }
            }
        }

        return second==m;

    }

    public:

    static bool containsKeyword(const std::string &path, const std::string &keyword){

        std::ifstream read(path, std::ios::in);
        if(!read){
            std::cerr<<"Could not open file "<<path<<"\n";
            return false;
        }

        std::string line;
        while(getline(read,line)){
            if(contains(line, keyword)){
                read.close();
                return true;
            }
        }

        read.close();
        return false;
    }
};