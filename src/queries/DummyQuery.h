/*
 * DummyQuery.h
 *
 *  Created on: Jan 31, 2013
 *      Author: atanasoa
 */

#ifndef QUERIES_DUMMYQUERY_H_
#define QUERIES_DUMMYQUERY_H_

#include "queries/Query.h"
#include "tarch/la/Vector.h"

#include "queries/records/Answer.h"
#include "peano/utils/Globals.h"
#include <vector>
#include <unordered_map>
namespace queries{
class DummyQuery;
}

class queries::DummyQuery : public queries::Query{
private:
	tarch::la::Vector<DIMENSIONS,double> _offset;
	tarch::la::Vector<DIMENSIONS,double> _size;
	tarch::la::Vector<DIMENSIONS,int> _resolution;
	std::unordered_map<int,std::pair<double,double> > _data;

	int _time;
public:
	DummyQuery();

	DummyQuery(
			tarch::la::Vector<DIMENSIONS,double> offset,
			tarch::la::Vector<DIMENSIONS,double> size,
			tarch::la::Vector<DIMENSIONS,int> resolution,
			int scope,
			int time);

	virtual ~DummyQuery();
	bool isInVoxel(
			const tarch::la::Vector<2,double> &voxelOffset,
			const tarch::la::Vector<2,double> &voxelSize,
			double x,
			double y);
	bool isInVoxel(
			const tarch::la::Vector<3,double> &voxelOffset,
			const tarch::la::Vector<3,double> &voxelSize,
			double x,
			double y,
			double z);

	void release() ;
	void release(std::vector<queries::records::Answer>& answer) ;
	int getScope() ;
	void fillAnswers(std::vector<queries::records::Answer>& answers);
	bool intersectsWithQuery(const tarch::la::Vector<2,double> voxelOffset,const tarch::la::Vector<2,double> voxelSize) ;
	bool intersectsWithQuery(const tarch::la::Vector<3,double> voxelOffset,const tarch::la::Vector<3,double> voxelSize) ;
	bool intersectsWithVoxel(
			const tarch::la::Vector<3,double> voxelOffset1,
			const tarch::la::Vector<3,double> voxelSize1,
			const tarch::la::Vector<3,double> voxelOffset2,
			const tarch::la::Vector<3,double> voxelSize2
		);
	void setData(const tarch::la::Vector<2,double> &voxelOffset,const tarch::la::Vector<2,double> &voxelSize,double);
	void setData(const tarch::la::Vector<3,double> &voxelOffset,const tarch::la::Vector<3,double> &voxelSize,double);

};
#endif /* QUERIES_DUMMYQUERY_H_ */
