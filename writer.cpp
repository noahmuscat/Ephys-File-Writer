//
//  writer.cpp
//  Ephys TXT File Writer
//
//  Created by Noah Muscat on 1/28/23.
//

#include "writer.h"
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>


void ephysWriter(int channels, std::string version, std::string name, std::string type, int width, int height) {
    //assuming collinear for now (not considering any channel mapping)
    
    int pitch = 0;
    int spacing = 0;
    
    // gathers pitch
    if (type == "shank") {
        std::cout << "Enter pitch (in micrometers): ";
        std::cin >> pitch;
    }
    else if (type == "tetrode") {
        std::cout << "Enter distance between centers of electrodes (in micrometers): ";
        std::cin >> pitch;
        
        std::cout << "Enter spacing between tetrodes (in micrometers): ";
        std::cin >> spacing;
    }
    else {
        pitch = 1;
    }
    
    
    // creates vector of channelNum size initialized to 0, used for the group #
    int groupArr [channels];
    for (int i = 0; i < channels; i++) {
        groupArr[i] = 0;
    }
    
    // creates vector of channelNum size used for channel numbers
    int chanArr [channels];
    int channelNum = 0;
    for (int i = 0; i < channels; i++) {
        chanArr[i] = channelNum;
        channelNum++;
    }
    
    int xArr [channels];
    int yArr [channels];
    
    if (type == "tetrode") {
        // creates vector of channelNum size used for the x coordinate
        int xincrement = 1;
        int xCoord = 0;
        for (int i = 0; i < channels; i++) {
            xArr[i] = xCoord;
            if (xincrement % 2 == 0) {
                xCoord += pitch;
            }
            if (xincrement % 4 == 0) {
                xCoord += spacing - 10;
            }
            xincrement++;
        }
        
        // creates vector of channelNum size used for the y coordinate
        int yincrement = 1;
        for (int i = 0; i < channels; i++) {
            if (yincrement % 2 != 0) {
                yArr[i] = 0;
            }
            else {
                yArr[i] = pitch;
            }
            yincrement++;
        }
        
    }
        
    else {
        // creates vector of channelNum size used for the x coordinate
        int xCoord = 0;
        for (int i = 0; i < channels; i++) {
            // increments by pitch
            xArr[i] = xCoord;
            xCoord = xCoord + pitch;
        }
        
        // creates vector of channelNum size used for the y coordinate
        int yCoord = 0;
        for (int i = 0; i < channels; i++) {
            // increments by pitch
            yArr[i] = yCoord;
            yCoord = yCoord + pitch;
        }
    }
    
    
    /*
-------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------
     */
    
    
    std::ofstream output("test.txt");
    
    output << "{";
    
    //writes format_version
    output << "\"format_version\":[" << "\"" << version << "\"" << "],";
    
    //writes probe_name
    output << "\"probe_name\":[" << "\"" << name << "\"" << "],";
    
    //writes probe_type
    output << "\"probe_type\":[" << "\"" << type << "\"" << "],";
    
    //writes channel sequence
    output << "\"channel\":" << std::endl << "[";
    for(int i = 0; i < channels; i ++){
        if (i == channels - 1) {
            output << chanArr[i];
        }
        else {
            output << chanArr[i] << ", " ;
        }
    }
    output << "],";
    
    //writes x coords
    output << "\"x\":" << std::endl << "[";
    for(int i = 0; i < channels; i ++){
        if (i == channels - 1) {
            output << xArr[i];
        }
        else {
            output << xArr[i] << ", " ;
        }
    }
    output << "],";
    
    //writes y coords
    output << "\"y\":" << std::endl << "[";
    for(int i = 0; i < channels; i ++){
        if (i == channels - 1) {
            output << yArr[i];
        }
        else {
            output << yArr[i] << ", " ;
        }
    }
    output << "],";
    
    //writes group
    output << "\"group\":" << std::endl << "[";
    for(int i = 0; i < channels; i ++){
        if (i == channels - 1) {
            output << groupArr[i];
        }
        else {
            output << groupArr[i] << ", " ;
        }
    }
    output << "],";
    
    // writes site width and height
    output << "\"site_width\":[" << width << "],";
    output << "\"site_height\":[" << height << "]";
    
    output << "}";
}


