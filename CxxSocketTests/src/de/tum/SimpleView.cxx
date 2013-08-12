/*
 * Copyright 2007 Sandia Corporation.
 * Under the terms of Contract DE-AC04-94AL85000, there is a non-exclusive
 * license for use of this work by or on behalf of the
 * U.S. Government. Redistribution and use in source and binary forms, with
 * or without modification, are permitted provided that this Notice and any
 * statement of authorship are reproduced on all copies.
 */


#include "ui_SimpleView.h"
#include "SimpleView.h"

#include <vtkDataObjectToTable.h>
#include <vtkElevationFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkQtTableView.h>
#include <vtkRenderWindow.h>
#include <vtkVectorText.h>
#include <vtkRenderer.h>
#define VTK_CREATE(type, name) \
  vtkSmartPointer<type> name = vtkSmartPointer<type>::New()
#define VTK_CREATE_PRIVATE(type, name) \
  name = vtkSmartPointer<type>::New()

// Constructor
SimpleView::SimpleView() 
{
  this->ui = new Ui_SimpleView;
  this->ui->setupUi(this);

  // Qt Table View
  this->TableView = vtkSmartPointer<vtkQtTableView>::New();

  // Place the table view in the designer form
  this->ui->tableFrame->layout()->addWidget(this->TableView->GetWidget());
  
  // Geometry
  VTK_CREATE_PRIVATE(vtkMyImageData, data);
  data->SetOffset(0.0,0.0,0.0);
  data->SetDimensions(3,3,3);
  data->SetBoundingBox(4.0,4.0,4.0);
  // Mapper
  VTK_CREATE(vtkDataSetMapper, mapper);
  mapper->ImmediateModeRenderingOn();
  mapper->SetInputConnection(data->GetOutputPort());

  // Actor in scene
  VTK_CREATE(vtkActor, actor);
  actor->SetMapper(mapper);

  // VTK Renderer
  VTK_CREATE(vtkRenderer, ren);

  // Add Actor to renderer
  ren->AddActor(actor);

  // VTK/Qt wedded
  this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(ren);
  renWin=this->ui->qvtkWidget->GetRenderWindow();
  // Just a bit of Qt interest: Culling off the
  // point data and handing it to a vtkQtTableView
  // Set up action signals and slots
  connect(this->ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(slotOpenFile()));
  connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));

};

SimpleView::~SimpleView()
{
  // The smart pointers should clean up for up

}

// Action to be taken upon file open 
void SimpleView::slotOpenFile()
{

}

void SimpleView::slotExit() {
  qApp->exit();
}
