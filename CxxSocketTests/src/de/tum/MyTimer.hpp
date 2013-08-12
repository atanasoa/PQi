#ifndef MYTIMER_HPP
#define MYTIMER_HPP
#include <iostream>
#include <QObject>
#include <vtkSmartPointer.h>
#include "de/tum/vtkMyImageData.h"
#include <vtkExecutive.h>
#include <vtkThreadedStreamingPipeline.h>
#include <vtkRenderWindow.h>
#include "de/tum/SocketTestAImplementation.h"
class MyTimer: public QObject{
Q_OBJECT
	private:
		vtkSmartPointer<vtkMyImageData> _data;
		vtkSmartPointer<vtkRenderWindow> _renderer;
		de::tum::SocketTestAImplementation* _dataSource;
		int _counter;	
	public:
                MyTimer(){
			_counter=2;		
		}
		void setRenderer(vtkSmartPointer<vtkRenderWindow> renderer){
			_renderer=renderer;
		}
		void setData(vtkSmartPointer<vtkMyImageData> data){
			_data=data;
                        
		}
		void setDataSource(de::tum::SocketTestAImplementation* dataSource){
			_dataSource=dataSource;
		}
	public slots:
		void update(){
			_dataSource->cloneData(_data->_data);
			_data->Modified();
       		((vtkThreadedStreamingPipeline*)(_data->GetExecutive()))->Push();
			_renderer->Render();
 		}

};
#endif
