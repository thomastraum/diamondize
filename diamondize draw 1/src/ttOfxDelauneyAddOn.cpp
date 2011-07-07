//
//  ttOfxDelauneyAddOn.cpp
//  diamondize draw 1
//
//  Created by Thomas Eberwein on 04/07/2011.
//  Copyright 2011 --. All rights reserved.
//

#include "ttOfxDelauneyAddOn.h"


void ttOfxDelauneyAddOn::exportToEps()
{
    char reportStr[1024];
    sprintf( reportStr, "export/test-%i-%i-%i.ps", ofGetHours(), ofGetMinutes(), ofGetSeconds() );
    output.beginEPS( reportStr );
    
    for(int i = 0; i < ntri; i++){
		output.noFill();
		output.setColor(0x000000);
        output.triangle(p[v[i].p1].x, p[v[i].p1].y, p[v[i].p2].x, p[v[i].p2].y, p[v[i].p3].x, p[v[i].p3].y);
	}

    output.endEPS();
    
}