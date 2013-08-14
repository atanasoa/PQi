#ifndef _QUERIES_QUERY_H_
#define _QUERIES_QUERY_H_

#include "tarch/la/Vector.h"
#include "peano/utils/Globals.h"

namespace queries{
  class Query;
}



/**
 * Query
 *
 * This interface is the connection point of an application to the whole query
 * thing. It represents a request for a particular piece of data.
 *
 * @author Atanas Atanasov, Tobias Weinzierl
 */
class queries::Query {
  public:
    virtual ~Query() {};

    /**
     * Release query
     *
     * This operation tells the query that the application has written all data
     * it knows about. Peano, e.g., invokes this function within endIteration(),
     * i.e. when the local traversal terminates.
     */
    virtual void release() = 0;

    /**
     * Get scope of query
     *
     * Typically, you have different scopes (variables) in your application.
     * CFD codes for example use three velocity components and pressure. That
     * implies that there are four scopes. To distinguish them, each query
     * comes along with an identifier. The mapping from identifiers to scopes
     * is up to the user, i.e. the semantics of the scope ids to unknowns.
     *
     * @return Scope tackled by this query.
     */
    virtual int getScope()=0;

    /**
     * Does Control Volume Intersect With Query
     *
     * With this operation, the application can check whether a domain (subpart)
     * intersects with the query. This operation has no real functionality - it
     * basically allows the application to tune the answering. If the subdomain,
     * e.g., does not intersect with the query, there is no need to answer it
     * at all.
     *
     * @param voxelOffset Bottom, left corner of the control volume.
     * @param voxelSize   Size of the contol volume.
     * @return If there is data in the control volume, the query would like to
     *         have these data.
     */
    virtual bool intersectsWithQuery(
		const int index,
    		const tarch::la::Vector<DIMENSIONS,double>&  voxelOffset,
    		const tarch::la::Vector<DIMENSIONS,double>&  voxelSize) = 0;

    /**
     * Write Data as Answer to Query
     *
     * With this operation, the application pipes data into the query trying to
     * answer it. The function should ask intersectsWithQuery() before (for
     * efficiency reasons) but this is not a must. Our query interface supports
     * both volume and point data. If an application writes point data,
     * voxelSize is zero.
     *
     * It is up to the concrete query implementation how to deal with data that
     * is not aligned with the query specification. Usually, d-dimensional
     * interpolation does the job, but there might be better alternatives
     * depending on the application.
     *
     * @param voxelOffset Either left bottom corner of control volume with a
     *        value or a point in the space.
     * @param voxelSize   Size of the control volume or zero (if it is point
     *        data rather than volume data)
     * @param value       Value belonging to the control voxel or point,
     *        respectively.
     */
    virtual void setData(
    		const tarch::la::Vector<DIMENSIONS,double>&  voxelOffset,
    		const tarch::la::Vector<DIMENSIONS,double>&  voxelSize, double value) = 0;

};

#endif
