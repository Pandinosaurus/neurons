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
// Written and (C) by Aurelien Lucchi and Kevin Smith                  //
// Contact aurelien.lucchi (at) gmail.com or kevin.smith (at) epfl.ch  // 
// for comments & bug reports                                          //
/////////////////////////////////////////////////////////////////////////

#include "mex.h"
#include "integral.h"
#include <stdio.h>

// Caution : this number has to be chosen carefully to avoid any buffer
// overflow
#define MAX_WEAK_LEARNER_PARAM_LENGTH 500

/* Arguments : Cell containing image files,
   Cell containing parameters (ids for intensity features).
*/
void mexFunction(int nlhs,       mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    unsigned int *pIntegralImage;
    const mwSize *dim_array;
    mxArray *pCellParam;
    mxArray *pCellImage;
    mwSize nImages, nParams;
    char pParam[MAX_WEAK_LEARNER_PARAM_LENGTH]; // weak learner parameters
    int strLength;
    
    /* Check for proper number of input and output arguments */    
    if (nrhs != 2) {
	mexErrMsgTxt("2 input arguments required.");
    } 
    if (nlhs > 1){
	mexErrMsgTxt("Too many output arguments.");
    }
    
    /* Check data type of input argument */
    if (!mxIsCell(prhs[0])) {
      mexErrMsgTxt("Input array must be of type uint8 or cell.");
    }
    if (!mxIsCell(prhs[1])) {
      mexErrMsgTxt("Input array must be of type cell.");
    }
    
    /* Get the real data */
    /*pImage=(unsigned char *)mxGetPr(prhs[0]);*/
    nImages = mxGetNumberOfElements(prhs[0]);
    nParams = mxGetNumberOfElements(prhs[1]);

    mwSize number_of_dims = 2;
    const mwSize dims[]={nParams,nImages};

    /* Check type of the first image */
    pCellImage = mxGetCell(prhs[0],0);
    if(mxIsDouble(pCellImage))
      {
        double *pResult;
        plhs[0] = mxCreateNumericArray(number_of_dims,dims,mxDOUBLE_CLASS,mxREAL);
        pResult = (double*)mxGetData(plhs[0]);

        int iResult = 0;
        for(int iParam = 0;iParam<nParams;iParam++)
          {
            // retrieve cell content and transform it to a string
            pCellParam = mxGetCell(prhs[1],iParam);
            strLength = mxGetN(pCellParam)+1;
            mxGetString(pCellParam,pParam,strLength);

            for(int iImage = 0;iImage<nImages;iImage++)
              {
                /* retrieve the image */
                pCellImage = mxGetCell(prhs[0],iImage);
                dim_array = mxGetDimensions(pCellImage);        

                pResult[iResult] = getRectangleFeature((double*)mxGetData(pCellImage),dim_array[1],dim_array[0],pParam);
                iResult++;
              }
          }
      }
    else
      {
        int *pResult;
        plhs[0] = mxCreateNumericArray(number_of_dims,dims,mxINT32_CLASS,mxREAL);
        pResult = (int*)mxGetData(plhs[0]);

        int iResult = 0;
        for(int iParam = 0;iParam<nParams;iParam++)
          {
            // retrieve cell content and transform it to a string
            pCellParam = mxGetCell(prhs[1],iParam);
            strLength = mxGetN(pCellParam)+1;
            mxGetString(pCellParam,pParam,strLength);

            for(int iImage = 0;iImage<nImages;iImage++)
              {
                /* retrieve the image */
                pCellImage = mxGetCell(prhs[0],iImage);
                dim_array = mxGetDimensions(pCellImage);        

                pResult[iResult] = getRectangleFeature((unsigned int*)mxGetData(pCellImage),dim_array[1],dim_array[0],pParam);
                iResult++;
              }
          }
      }
}
