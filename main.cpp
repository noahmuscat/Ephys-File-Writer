//
//  main.cpp
//  Ephys TXT File Writer
//
//  Created by Noah Muscat on 1/28/23.
//

#include <stdio.h>
#include <string>
#include <locale>
#include <iostream>
#include "writer.h"

using namespace std;

int main() {
    int channels = 0;
    string type = "";
    string type2 = "";
    string version = "";
    string name = "";
    int width = 0;
    int height = 0;
    int spacing = 0;
    
    cout << ".json File Automated Writer" << endl << endl;
    
    cout << "Enter the number of channels: ";
    cin >> channels;
    
    cout << "Enter the version of device: ";
    cin >> version;
    
    cout << "Enter the name of device: ";
    cin >> name;
    
    cout << "Enter the type of device: ";
    cin >> type2;
    
    // accounts for differing capitalization inputs
    for (int i = 0; i < type2.length(); i++) {
        type.push_back(tolower(type2.at(i)));
    }
    
    cout << "Enter the site's width (in micrometers): ";
    cin >> width;
    
    cout << "Enter the site's height (in micrometers): ";
    cin >> height;
    
    ephysWriter(channels, version, name, type, width, height);
    return 0;
}
