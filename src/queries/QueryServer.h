// Copyright (C) 2009 Technische Universitaet Muenchen
// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www5.in.tum.de/peano
#ifndef _PEANO_INTEGRATION_DATAQUERIES_QUERY_SERVER_H_
#define _PEANO_INTEGRATION_DATAQUERIES_QUERY_SERVER_H_

#include "tarch/services/Service.h"
#include "tarch/logging/Log.h"
#include "queries/records/HeapQuery.h"
#include "de/tum/QueryCxx2SocketPlainPort.h"

#include <vector>
#include <unordered_map>

namespace queries {
  class QueryServer;
    
}


/**
 * Query Server Service
 *
 * The query server service is the single point of contact to administer
 * queries. It implements the following functionality:
 *
 * - Administer the queries (only relevant for rank 0), i.e. you can fill it
 *   with the queries you receive and wish your code to answer.
 * - Dispatch the queries among the active nodes (hidden from user).
 * - Tell your algorithm whether there is a query to answer (only relevant on
 *   rank 0). If there is one, you should switch to a corresponding answering
 *   mapping that you have to implement as it is PDE-specific.
 * - Provide a unique contact point for your mapping to get the writer it
 *   shall use (relevant for mappings).
 * - Merge data from different nodes (hidden).
 *
 * The query server works with any regular grid writer.
 *
 * !!! Implementation Details
 *
 * The queries have an ascending number (id) to enable the root node to
 * distinguish them from each other. It could be, that the workers receive the
 * queries in a different order, or it might be that some mappings replying to
 * several queries answer to the queries in a different order. Anyway, the root
 * node has to sort the answers accordingly.
 *
 * !!! Data Queries
 *
 * A data query is represented by the following DaStGen datatype specification:
 * \code
     \include DataQuery.def
   \endcode
 * If you have to regenerate the datatype, change into the service's directory
 * and type in
 * \code
   java -jar ../../../../releases/tools/DaStGen.jar --plugin PeanoSnippetGenerator --naming PeanoNameTranslator DataQuery.def .
   \endcode
 *
 * !!! Data Format
 *
 * (int,doubles*)
 *
 * The first int is either the id of message or it is -2 to indicate that
 * this has been the last message from this node.
 *
 *
 * @author Atanas Atanasov, Tobias Weinzierl
 */
class queries::QueryServer: public tarch::services::Service {
  private:
      static tarch::logging::Log _log;
      	
      //struct Query {
      /**
       * Datafield describing the query.
       */
      //DataQuery _queryDescription;

      /**
       * Plotter associated to the query. Its lifecycle is managed by the
       * service, i.e. do not delete it.
       */
      //tarch::plotter::griddata::regular::CartesianGridWriter::VertexDataWriter* _vertexDataWriter;

      //Query( const DataQuery& queryDescription);

      /**
       * Delete all the objects stored in the two vectors.
       */
       //void closeAndDeleteDataWriter();
      //};

	/**
	 * Pending Queries
	 *
	 * A map of the individual queries that are yet to be answered.
	 */
	std::vector<queries::records::HeapQuery> _pendingQueries;
	std::vector<int> _heapIds;
	std::vector<std::unordered_map<int,std::pair<double,double> >*> _data;
	de::tum::QueryCxx2SocketPlainPort *_queryServer;
	int _dataTag;

	int _managementTag;

	int _bufferSize;

	int _finishedDataSendAcknowledgementsSinceLastReleaseCall;
	bool init;
	int _timestep;	
	/**
	 * Private Standard Constructor
	 *
	 * The constructor is private as this class is a singleton (service).
	 * Hence, it is executed exactly once throughout the application's
	 * lifetime. Then, it has to do the following things:
	 *
	 * - Reserve a tag for the query data exchange.
	 * - Initialise the DataQuery MPI datatype.
	 *
	 * !!! Implementation Details
	 *
	 * Do not use the logging within the constructor or singleton accessor. It
	 * might happen that the logging is not configured yet when the singleton
	 * is created. In this case, the application crashes.
	 */
	QueryServer();

	/**
	 * In the parallel mode, you sometimes only have the id at hand and you are
	 * searching for the corresponding complete query. That is exactly what this
	 * operation does.
	 *
	 * Precondition: A query with this id has to exist.
	 */
	int getIndexOfQuery( int id );

   // #ifdef Parallel
	/**
	 * Used by receiveDanglingMessages().
	 */
	void receiveIncomingQueryData();

	/**
	 * Used by receiveDanglingMessages().
	 */
	void receiveNewQueries();
   // #endif
  public:
	virtual ~QueryServer();

	/**
	 * Singleton
	 */
	static QueryServer& getInstance();

	/**
	 * Receive Dangling Messages
	 *
	 * If the current rank equals 0 (master process), this operation checks
	 * whether other nodes wanted to forward calls to a query. If the rank does
	 * not equal 0, i.e. if the method is executed on a worker, this operation
	 * just checks whether there are new queries triggered. If the latter is the
	 * case, the operation has to add the corresponding proxies to its internal
	 * list of query answering devices.
	 */
    virtual void receiveDanglingMessages();

    /**
     * Number of Pending Queries
     *
     * Returns the number of pending queries. If the executing rank equals 0,
     * this number is equal to the number of addQuery() calls since the last
     * eraseQueries() call. If the operation is invoked on a worker, the result
     * stems from the number of queries that have been received meanwhile.
     *
     * The getter is typically used by two different modules:
     * - The runner on the root node checks whether there are queries at all.
     *   If there are, it invokes the corresponding mappings answering the
     *   queries.
     * - The mappings (activated by the root node's runner due to the issue
     *   above, answer the queries. For this, they use
     *   getNumberOfPendingQueries() and getPendingQuery().
     */
    int getNumberOfPendingQueries() const;

    /**
     * @see getNumberOfPendingQueries()
     */
    queries::records::HeapQuery getPendingQueryDescription( int queryNumber ) const;
    //tarch::plotter::griddata::regular::CartesianGridWriter::VertexDataWriter& getPendingQueryDataWriter( int queryNumber );

    /**
     * Add a Query.
     *
     * May only be invoked on rank 0. The operation stores the query-plotter
     * pair in _pendingQueries and notifies all the other active nodes that
     * there's a new query around. As the runner later on typically at some
     * point checks whether there are queries pending, this operation
     * implicitly tells the runner to iterate with a query answering mapping.
     *
     * You pass the operation a plotter. You have to ensure that this plotter
     * remains alive till someone calls eraseQueries(). At the same time, you
     * are responsible to delete the writer at some point.
     *
     * You may not call this operation on a worker, i.e. only the global master
     * is allowed to do so.
     *
     * @param newQuery Query object that describes the query. Each query has
     *                 an internal query id. This id will be reset by the
     *                 addQuery() operation internally before a copy of the
     *                 object is inserted into the map.
     */
    void addQuery(
      queries::records::HeapQuery                              newQuery
    );

    /**
     * Set Query Data Buffer Size
     *
     * If the query server is running on a worker rank, it forwards all data
     * messages to the root node. This is however not done on a per message
     * basis, but several messages are packed into one message and then sent
     * en block. The default buffer size is 1.
     */
    void setBufferSize(int bufferSize);

    /**
     * Commit Queries
     *
     * This operation should be called by endIteration() of every mapping that
     * answers to queries. In the sequential mode, this operation just is nop,
     * but if you switch on the parallelisation, it does several things:
     *
     * - On rank 0: A non-blocking barrier, i.e. a barrier that still polls all
     *   the services.
     * - On rank 1: Empty all the buffers, i.e. send them back to root node.
     * - On rank 1: Send an acknowledgement to release the barrier. It is sent
     *   on the same tag as the messages. Consequently, it is the very last
     *   message that arrives on node 0.
     * - On rank 0: If all busy nodes have sent their acknowledgement, continue.
     *
     * Finally, all ranks delete the data writers that were used by the queries.
     */
    void commitQueries();
    
    bool intersectsWithQuery(int index, const tarch::la::Vector<2,double> voxelOffset,const tarch::la::Vector<2,double> voxelSize);
    bool holdsFullQuery(int index, const tarch::la::Vector<2,double> voxelOffset,const tarch::la::Vector<2,double> voxelSize);
    void setData(const int index,const tarch::la::Vector<2,double> &voxelOffset,const tarch::la::Vector<2,double> &voxelSize,const double x);	
    bool isInVoxel(const tarch::la::Vector<2,double> &voxelOffset,
		const tarch::la::Vector<2,double> &voxelSize,
		double x,
		double y);
    void swapBuffers(const int index);
    void sendData(const int index,const tarch::la::Vector<2,double> &voxelOffset,int level);
    void receiveData(const int index,const tarch::la::Vector<2,double> &voxelOffset,const int level,const int worker);
    void fireAnswers(const int index);
    /**
     * Synchronizes the pending query queues with through socket
     */
    void synchronize();	
};


#endif
