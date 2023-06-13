#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<ctime>
#include<vector>
#include<algorithm>
#include<cctype>
using namespace std;
string subStringer(const string& str,char delim,int position){
   size_t start=0;
   size_t end=str.find(delim);
   vector<string>tokens;
   //HELLO WORLD WE ARE THERE;
   while(end!=string::npos){
    tokens.push_back(str.substr(start,end-start));
    start=end+1;
    end=str.find(delim,start);
   };
   tokens.push_back(str.substr(start));
   return tokens[position];
}
void addLocation(const string& fileName,const string& location){
    ofstream outputFile(fileName.c_str(),ios::app);
    cout<<location<<endl;
    if (outputFile.is_open()) {
        outputFile << location<<endl;
        outputFile.close();
        cout << "location recorded successfully." << endl;
    } else {
        cout << "Failed to open the file." << endl;
    }
}
bool searchLocation(const string& fileName,const string& location){
    ifstream inFile(fileName.c_str());
    if(!inFile){
        return false;
    }
    string line;
    while(getline(inFile,line)){
        if(line==location){
            return true;
        }
    }
    return false;
}
void deleteLocation(const string& fileName,const string& location){
    ofstream temp("C:\\Users\\abc\\Documents\\codes\\NE\\DSA\\Book\\NE\\temp.txt");
    ifstream original(fileName.c_str());
    if(!original){
        cout<<"can not open the file"<<endl;
        return;
    }
    else{
        string line;
        while(getline(original,line)){
            if(line==location){
                continue;
            }
            else{
                temp<<line<<endl;
            }
        }
        temp.close();
        original.close();
        ofstream outFile(fileName.c_str());
        ifstream tempFile("C:\\Users\\abc\\Documents\\codes\\NE\\DSA\\Book\\NE\\temp.txt");
        outFile<<tempFile.rdbuf();
        remove("C:\\Users\\abc\\Documents\\codes\\NE\\DSA\\Book\\NE\\temp.txt");
        cout<<"location deleted successfully"<<endl;
    }
}
void listContents(const string& fileName,const string& key){
    ifstream inFile(fileName.c_str());
    inFile.seekg(0,ios::end);
    if(inFile.tellg()==0){
    	cout<<"No "+key+" found"<<endl;
    	return;
	}
    if (!inFile.is_open()) {
        cout << "Failed to open the file." << endl;
        return;
    }
    inFile.seekg(0,ios::beg);
    string line;
    while (getline(inFile, line)) {
        	cout << line << endl;
    }

    inFile.close();
}
void recordDisease(const string& fileName,const string& location,const string& disease,const string& cases){
    if(!searchLocation("C:\\Users\\abc\\Documents\\codes\\NE\\DSA\\Book\\NE\\locations.txt",location)){
        cout<<"This location does not exist"<<endl;
        return;
    }
    ofstream outFile(fileName.c_str(),ios::app);
    if(!outFile){
        cout<<"can not open file"<<endl;
        return;
    }
    
    outFile<<location+" "+disease+" "+cases<<endl;
    cout<<"disease and its location recorded"<<endl;
    outFile.close();
}
void readDiseases(const string& fileName){
    ifstream inFile(fileName.c_str());
    if(!inFile){
        cout<<"can not open the file";
        return;
    }
    inFile.seekg(0,ios::end);
    if(inFile.tellg()==0){
        cout<<"no disease found"<<endl;
        return;
    }
    inFile.seekg(0,ios::beg);
    string line;
    while(getline(inFile,line)){
        cout<<subStringer(line,' ',1)<<endl;
    }
    inFile.close();
}
void findLocationDisease(const string& fileName,string disease){
    ifstream inFile(fileName.c_str());
    if(!inFile){
        cout<<"can not open the file"<<endl;
        return;
    }
    string line;
    vector<string> results;
    while(getline(inFile,line)){
        if(subStringer(line,' ',1)==disease){
            results.push_back(subStringer(line,' ',0));
        }
    }
    for(string location:results){
        cout<<location<<endl;
    }
}
void findCases(const string& fileName,string disease){
    ifstream inFile(fileName.c_str());
    if(!inFile){
        cout<<"can not open the file"<<endl;
        return;
    }
    inFile.seekg(0,ios::end);
    if(inFile.tellg()==0){
        cout<<"no disease found"<<endl;
        return;
    }
    inFile.seekg(0,ios::beg);
    vector<string> diseases;
    string line;
    while(getline(inFile,line)){
        if(subStringer(line,' ',1)==disease){
            diseases.push_back(line);
        }
    }
    int cases=0;
    for(string disease:diseases){
        cases=cases+stoi(subStringer(disease,' ',2));
    }
    cout<<cases<<endl;
}
void showHelp(){
    cout<<"==============================================================="<<endl;
    cout<<"*                                HELP MENU"<<endl;
    cout<<"==============================================================="<<endl;
    cout<<"add <location>                         :add new Location"<<endl;
    cout<<"delete <location>                      :delete new Location"<<endl;
    cout<<"record <location> <disease> <cases>    :record a disease and its cases"<<endl;
    cout<<"add <location>                         :add new Location"<<endl;
    cout<<"list locations                         :list all existing locations"<<endl;
    cout<<"list diseases                          :list all existing diseases"<<endl;
    cout<<"where <disease>                        :Find where disease exists"<<endl;
    cout<<"cases <location> <disease>             :find cases of disease in a Location"<<endl;
    cout<<"cases <disease>                        :find total cases of a given disease"<<endl;
    cout<<"help                                   :prints user manual"<<endl;
    cout<<"Exit                                   :Exit the program"<<endl;
}
int main(){
    time_t currentTime=time(nullptr);
    string timeString=ctime(&currentTime);
    cout<<"================================================"<<endl;
    cout<<"*  Welcome to Disease Cases Reporting System"<<endl;
    cout<<"*"<<endl;
    cout<<"* it is developed by Kayitare Audax as practical*"<<endl;
    cout<<"* evaluation for the end of Year 3"<<endl;
    cout<<"================================================"<<endl;
    cout<<timeString<<endl;
    cout<<"Need a help? type \'help\' then press Enter"<<endl;
    showHelp();
    string option;
    // cout<<subStringer("Hello world",' ',1)<<endl;
    do{
        while(option!="Exit"){
        cout<<"console> ";
        getline(cin,option);
        if(option=="Help"){
            showHelp();
        }
        else if(subStringer(option,' ',0)=="add"){
            string location=subStringer(option,' ',1);
            addLocation("C:\\Users\\abc\\Documents\\codes\\NE\\DSA\\Book\\NE\\locations.txt",location);
        }
        else if(subStringer(option,' ',0)=="delete"){
            string location=subStringer(option,' ',1);
            deleteLocation("C:\\Users\\abc\\Documents\\codes\\NE\\DSA\\Book\\NE\\locations.txt",location);
        }
        else if(option=="list locations"){
            listContents("C:\\Users\\abc\\Documents\\codes\\NE\\DSA\\Book\\NE\\locations.txt","location");
        }
        else if(option=="list diseases"){
            readDiseases("C:\\Users\\abc\\Documents\\codes\\NE\\DSA\\Book\\NE\\diseases.txt");
        }
        else if(subStringer(option,' ',0)=="record"){
            string location=subStringer(option,' ',1);
            string disease=subStringer(option,' ',2);
            string cases=subStringer(option,' ',3);
            recordDisease("C:\\Users\\abc\\Documents\\codes\\NE\\DSA\\Book\\NE\\diseases.txt",location,disease,cases);
        }
        else if(subStringer(option,' ',0)=="where"){
            string disease=subStringer(option,' ',1);
            findLocationDisease("C:\\Users\\abc\\Documents\\codes\\NE\\DSA\\Book\\NE\\diseases.txt",disease);
        }
        else if(subStringer(option,' ',0)=="cases"){
            string disease=subStringer(option,' ',1);
            findCases("C:\\Users\\abc\\Documents\\codes\\NE\\DSA\\Book\\NE\\diseases.txt",disease);
        }
        else{
            cout<<"this Command does not exist"<<endl;
        }
        }
    }
    while(option!="Exit");
}