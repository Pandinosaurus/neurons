/////////////////////////////////////////////////////////////////////////
// This program is free software; you can redistribute it and/or       //
// modify it under the terms of the GNU General Public License         //
// version 2 as published by the Free Software Foundation.             //
//                                                                     //
// This program is distributed in the hope that it will be useful, but //
// WITHOUT ANY WARRANTY; without even the implied warranty of          //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   //
// General Public License for more details.                            //
//                                                                     //
// Written and (C) by German Gonzalez                                  //
// Contact <ggonzale@atenea> for comments & bug reports                //
/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "CubeFactory.h"
#include "Cloud.h"
#include "Cloud_P.h"
#include "Point3D.h"
#include "Point2D.h"

using namespace std;



int main(int argc, char **argv) {

  Cloud<Point3D>* cd = new Cloud<Point3D>();
  cd->v_saveVisibleAttributes = true;
  cd->loadFromFile("data/cloud.cl");
  printf("Cloud loaded\n");
  cd->saveToFile("data/cloud_copy.cl");
  printf("Check manually that the files data/cloud.cl and data/cloud_copy.cl represent the same cloud\n");

  Cloud<Point3D>* clone = new Cloud<Point3D>(*cd);
  clone->saveToFile("data/cloned.cl");
  printf("Check manually that the files data/cloud.cl and data/cloned.cl represent the same cloud\n");

  Cloud_P* cl1; Cloud_P* cl2;
  clone->split(cl1, cl2);
  cl1->saveToFile("data/split1.cl");
  cl2->saveToFile("data/split2.cl");

}
