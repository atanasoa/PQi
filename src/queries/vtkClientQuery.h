/*
 * vtkClientQuery.h
 *
 *  Created on: Jan 31, 2013
 *      Author: atanasoa
 */

#ifndef QUERIES_VTKCLIENTQUERY_H_
#define QUERIES_VTKCLIENTQUERY_H_
#include "peano/utils/Globals.h"
#include "tarch/la/Vector.h"
#include "de/tum/iQueryCxx2SocketClientPlainPort.h"
namespace queries{
	class vtkClientQuery;
}

class queries::vtkClientQuery{
private:
	de::tum::iQueryCxx2SocketClientPlainPort _query;
public:
	vtkClientQuery();
	virtual ~vtkClientQuery();
	void synchronize();

};

#endif /* QUERIES_VTKCLIENTQUERY_H_ */
