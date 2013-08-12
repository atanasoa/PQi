/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkMyElevationFilter.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkMyImageData.h"
#include "vtkObjectFactory.h"
#include "vtkDoubleArray.h"
#include "vtkPoints.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkDataObject.h"
#include "vtkImageData.h"
#include "vtkThreadedStreamingPipeline.h"
#include "vtkPointData.h"
#include "vtkMutexLock.h"
#include "vtkInformationExecutivePortKey.h"
#include "vtkCellData.h"

vtkStandardNewMacro(vtkMyImageData);
//vtkCxxSetObjectMacro(vtkMyStructuredGridSource, Controller, vtkMultiProcessController);
//----------------------------------------------------------------------------
vtkMyImageData::vtkMyImageData()
{
	SetNumberOfInputPorts(0);

}

//----------------------------------------------------------------------------
vtkMyImageData::~vtkMyImageData()
{
}


//----------------------------------------------------------------------------
int vtkMyImageData::RequestData( vtkInformation *vtkNotUsed(request),
		vtkInformationVector **vtkNotUsed(inputVector),
		vtkInformationVector* outputVector)
{

	// get the info object
	vtkInformation *outInfo = outputVector->GetInformationObject(0);
	int subext[6];
	vtkImageData *output = vtkImageData::SafeDownCast(
			outInfo->Get(vtkDataObject::DATA_OBJECT()));
	output->GetUpdateExtent(subext);

	double globalSpacing[3];
	int dimPiece[3];
	globalSpacing[0]=BoundingBox[0]/(double)(Dimensions[0]-1);
	globalSpacing[1]=BoundingBox[1]/(double)(Dimensions[1]-1);
	globalSpacing[2]=(Dimensions[2]==1)?0.0:BoundingBox[2]/(double)(Dimensions[2]-1);\
	dimPiece[0]=subext[1]-subext[0]+1;
	dimPiece[1]=subext[3]-subext[2]+1;
	dimPiece[2]=subext[5]-subext[4]+1;
	
	//offsetPiece[0]=Offset[0]+((double)subext[0])*globalSpacing[0];
	//offsetPiece[1]=Offset[1]+((double)subext[2])*globalSpacing[1];
	//offsetPiece[2]=Offset[2]+((double)subext[4])*globalSpacing[2];
	
	output->SetExtent(subext);

	output->SetSpacing(globalSpacing);
	output->SetOrigin(Offset);
	int dims=dimPiece[0]*dimPiece[1]*dimPiece[2];

		vtkDoubleArray* vs=vtkDoubleArray::New();



		vs->SetNumberOfComponents(1);
		vs->SetNumberOfTuples(dims);
		vs->SetName("test");
		for(unsigned int i=0;i<dims;i++){
			vs->SetTuple1(i,_data[i]);

		}
		vs->Squeeze();
		output->GetPointData()->SetScalars(vs);
		vs->Delete();
	


	return 1;
}
int vtkMyImageData::RequestInformation(
		vtkInformation *vtkNotUsed(request),
		vtkInformationVector **vtkNotUsed(inputVector),
		vtkInformationVector *outputVector)
{
	vtkInformation *outInfo = outputVector->GetInformationObject(0);
	int ext[6];
	ext[0]=0;
	ext[1]=Dimensions[0]-1;
	ext[2]=0;
	ext[3]=Dimensions[1]-1;
	ext[4]=0;
	ext[5]=Dimensions[2]-1;
	//ext{0,Dimensions[0]-1,0,Dimensions[1]-1,0,Dimensions[2]-1};        
	outInfo->Set(vtkThreadedStreamingPipeline::WHOLE_EXTENT(),
			ext, 6);
	outInfo->Set(vtkThreadedStreamingPipeline::UPDATE_EXTENT(),
			ext, 6);
	outInfo->Set(vtkThreadedStreamingPipeline::WHOLE_BOUNDING_BOX(),
			Offset[0],
			Offset[0]+BoundingBox[0],
			Offset[1],
			Offset[1]+BoundingBox[1],
			Offset[2],
			Offset[2]+BoundingBox[2]);

	return 1;
}

//----------------------------------------------------------------------------
void vtkMyImageData::PrintSelf(ostream& os, vtkIndent indent)
{

}

