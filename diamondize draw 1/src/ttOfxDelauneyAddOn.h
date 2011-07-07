//
//  ttOfxDelauneyAddOn.h
//  diamondize draw 1
//
//  Created by Thomas Eberwein on 04/07/2011.
//  Copyright 2011 --. All rights reserved.
//

#pragma once
#include "ofxDelaunay.h"
#include "ofxVectorGraphics.h"

class ttOfxDelauneyAddOn : public ofxDelaunay {
    
public:
    
    void exportToEps();
    
    ofxVectorGraphics output;
    
};