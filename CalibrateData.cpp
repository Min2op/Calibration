#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include <numeric>


using namespace std;

struct calibratedData{
    string roomNo;
    vector<pair<string, int>> macID_meanSignalStrength;

};

struct macID_signalStrength{
    string macAddresses;
    vector<int> signalStrengths;

};

void CalibrateData(filesystem::path path){
    macID_signalStrength x;
    ifstream iFile;
    string holder, newMacAddress;
    int newSignalStrength;  
    vector<macID_signalStrength> dataArr;


    iFile.open(path, ios::in);
        
        while(iFile >> holder){
                
                
                if(holder == "Address:"){
                    iFile >> newMacAddress;
                }
                else if (holder == "Signal")
                {
                    iFile >> holder;
                    holder = holder.substr(6,3);
                    newSignalStrength = stoi(holder);
                    
                    if(dataArr.empty()){
                   
                        x.macAddresses = newMacAddress;
                        x.signalStrengths.push_back(newSignalStrength);
                        dataArr.push_back(x);
                    }
                    else if (!dataArr.empty())
                    {
                        for(int i = 0; i < dataArr.size(); i++ ){
                            if(newMacAddress == dataArr[i].macAddresses){
                                x.signalStrengths.clear();
                                dataArr[i].signalStrengths.push_back(newSignalStrength);
                                break;
                            }
                            else if(i == dataArr.size() -1){
                                x.signalStrengths.clear();
                                x.macAddresses = newMacAddress;
                                x.signalStrengths.push_back(newSignalStrength);
                                dataArr.push_back(x);
                                }

                        }
                    }                
                }
                if(iFile.eof()){
                    iFile.close();
                }
            }
               
                
            for(int p = 0; p < dataArr.size(); p++){
                    cout << dataArr[p].macAddresses << endl;
                    for(int k = 0; k < dataArr[p].signalStrengths.size(); k++){
                        cout << dataArr[p].signalStrengths[k] << endl;
                    }
                    


            }
            

}

int main(){
    int choice = 0;
    vector<filesystem::path> filepaths;
    cout << " Welcome to the Calibration programme " << endl;
    cout << "Please select the file you want to calibrate from " << endl;

    auto fileReader = filesystem::directory_iterator("/home/alex/Documents/RoomData/CalibrationData/");
    int i = 1;
    
    for(auto& entry : fileReader){
        
        filesystem::path F = entry;
        cout << i << ": " << F.filename() << endl;
        filepaths.push_back(F);
        i++;
    
    }
    cin >> choice;
    CalibrateData(filepaths[choice - 1]);
    


    return 0;
}