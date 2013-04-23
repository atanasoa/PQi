/*
 * vtkClientQuery.h
 *
 *  Created on: Jan 31, 2013
 *      Author: atanasoa
 */

#ifndef QUERIES_VTKCLIENTQUERY_H_
#define QUERIES_VTKCLIENTQUERY_H_
#include "peano/utils/Globals.h"
#include "queries/Query.h"
#include "tarch/la/Vector.h"
#include "queries/QueryCxx2SocketClientPlainPort.h"
namespace queries{
	class vtkClientQuery;
}

class queries::vtkClientQuery : public queries::Query{
private:
	queries::QueryCxx2SocketClientPlainPort _query_client;
public:
	vtkClientQuery();
	virtual ~vtkClientQuery();
	void release();
	int getScope();
	bool intersectsWithQuery(const tarch::la::Vector<DIMENSIONS,double> voxelOffset,const tarch::la::Vector<DIMENSIONS,double> voxelSize) ;
	void setData(const tarch::la::Vector<DIMENSIONS,double> voxelOffset,const tarch::la::Vector<DIMENSIONS,double> voxelSize,double);
};

#endif /* QUERIES_VTKCLIENTQUERY_H_ */
