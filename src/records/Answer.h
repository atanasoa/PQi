#ifndef _QUERIES_RECORDS_ANSWER_H
#define _QUERIES_RECORDS_ANSWER_H

#include "peano/utils/Globals.h"
#include "tarch/compiler/CompilerSpecificSettings.h"
#include "peano/utils/PeanoOptimisations.h"
#ifdef Parallel
	#include "tarch/parallel/Node.h"
#endif
#ifdef Parallel
	#include <mpi.h>
#endif
#include "tarch/logging/Log.h"
#include "tarch/la/Vector.h"
#include <bitset>
#include <complex>
#include <string>
#include <iostream>

namespace queries {
   namespace records {
      class Answer;
      class AnswerPacked;
   }
}

/**
 * @author This class is generated by DaStGen
 * 		   DataStructureGenerator (DaStGen)
 * 		   2007-2009 Wolfgang Eckhardt
 * 		   2012      Tobias Weinzierl
 *
 * 		   build date: 29-11-2012 08:46
 *
 * @date   02/04/2013 11:43
 */
class queries::records::Answer { 
   
   public:
      
      typedef queries::records::AnswerPacked Packed;
      
      struct PersistentRecords {
         double _data;
         int _dataIndex;
         double _position;
         /**
          * Generated
          */
         PersistentRecords();
         
         /**
          * Generated
          */
         PersistentRecords(const double& data, const int& dataIndex, const double& position);
         
         /**
          * Generated
          */
          double getData() const ;
         
         /**
          * Generated
          */
          void setData(const double& data) ;
         
         /**
          * Generated
          */
          int getDataIndex() const ;
         
         /**
          * Generated
          */
          void setDataIndex(const int& dataIndex) ;
         
         /**
          * Generated
          */
          double getPosition() const ;
         
         /**
          * Generated
          */
          void setPosition(const double& position) ;
         
         
      };
      
   private: 
      PersistentRecords _persistentRecords;
      
   public:
      /**
       * Generated
       */
      Answer();
      
      /**
       * Generated
       */
      Answer(const PersistentRecords& persistentRecords);
      
      /**
       * Generated
       */
      Answer(const double& data, const int& dataIndex, const double& position);
      
      /**
       * Generated
       */
      virtual ~Answer();
      
      /**
       * Generated
       */
       double getData() const ;
      
      /**
       * Generated
       */
       void setData(const double& data) ;
      
      /**
       * Generated
       */
       int getDataIndex() const ;
      
      /**
       * Generated
       */
       void setDataIndex(const int& dataIndex) ;
      
      /**
       * Generated
       */
       double getPosition() const ;
      
      /**
       * Generated
       */
       void setPosition(const double& position) ;
      
      /**
       * Generated
       */
      std::string toString() const;
      
      /**
       * Generated
       */
      void toString(std::ostream& out) const;
      
      
      PersistentRecords getPersistentRecords() const;
      /**
       * Generated
       */
      AnswerPacked convert() const;
      
      
   #ifdef Parallel
      protected:
         static tarch::logging::Log _log;
         
         int _senderRank;
         
      public:
         
         /**
          * Global that represents the mpi datatype.
          * There are two variants: Datatype identifies only those attributes marked with
          * parallelise. FullDatatype instead identifies the whole record with all fields.
          */
         static MPI_Datatype Datatype;
         static MPI_Datatype FullDatatype;
         
         /**
          * Initializes the data type for the mpi operations. Has to be called
          * before the very first send or receive operation is called.
          */
         static void initDatatype();
         
         static void shutdownDatatype();
         
         void send(int destination, int tag, bool exchangeOnlyAttributesMarkedWithParallelise);
         
         void receive(int source, int tag, bool exchangeOnlyAttributesMarkedWithParallelise);
         
         static bool isMessageInQueue(int tag, bool exchangeOnlyAttributesMarkedWithParallelise);
         
         int getSenderRank() const;
         
   #endif
      
   };
   
   /**
    * @author This class is generated by DaStGen
    * 		   DataStructureGenerator (DaStGen)
    * 		   2007-2009 Wolfgang Eckhardt
    * 		   2012      Tobias Weinzierl
    *
    * 		   build date: 29-11-2012 08:46
    *
    * @date   02/04/2013 11:43
    */
   class queries::records::AnswerPacked { 
      
      public:
         
         struct PersistentRecords {
            double _data;
            int _dataIndex;
            double _position;
            /**
             * Generated
             */
            PersistentRecords();
            
            /**
             * Generated
             */
            PersistentRecords(const double& data, const int& dataIndex, const double& position);
            
            /**
             * Generated
             */
             double getData() const ;
            
            /**
             * Generated
             */
             void setData(const double& data) ;
            
            /**
             * Generated
             */
             int getDataIndex() const ;
            
            /**
             * Generated
             */
             void setDataIndex(const int& dataIndex) ;
            
            /**
             * Generated
             */
             double getPosition() const ;
            
            /**
             * Generated
             */
             void setPosition(const double& position) ;
            
            
         };
         
      private: 
         PersistentRecords _persistentRecords;
         
      public:
         /**
          * Generated
          */
         AnswerPacked();
         
         /**
          * Generated
          */
         AnswerPacked(const PersistentRecords& persistentRecords);
         
         /**
          * Generated
          */
         AnswerPacked(const double& data, const int& dataIndex, const double& position);
         
         /**
          * Generated
          */
         virtual ~AnswerPacked();
         
         /**
          * Generated
          */
          double getData() const ;
         
         /**
          * Generated
          */
          void setData(const double& data) ;
         
         /**
          * Generated
          */
          int getDataIndex() const ;
         
         /**
          * Generated
          */
          void setDataIndex(const int& dataIndex) ;
         
         /**
          * Generated
          */
          double getPosition() const ;
         
         /**
          * Generated
          */
          void setPosition(const double& position) ;
         
         /**
          * Generated
          */
         std::string toString() const;
         
         /**
          * Generated
          */
         void toString(std::ostream& out) const;
         
         
         PersistentRecords getPersistentRecords() const;
         /**
          * Generated
          */
         Answer convert() const;
         
         
      #ifdef Parallel
         protected:
            static tarch::logging::Log _log;
            
            int _senderRank;
            
         public:
            
            /**
             * Global that represents the mpi datatype.
             * There are two variants: Datatype identifies only those attributes marked with
             * parallelise. FullDatatype instead identifies the whole record with all fields.
             */
            static MPI_Datatype Datatype;
            static MPI_Datatype FullDatatype;
            
            /**
             * Initializes the data type for the mpi operations. Has to be called
             * before the very first send or receive operation is called.
             */
            static void initDatatype();
            
            static void shutdownDatatype();
            
            void send(int destination, int tag, bool exchangeOnlyAttributesMarkedWithParallelise);
            
            void receive(int source, int tag, bool exchangeOnlyAttributesMarkedWithParallelise);
            
            static bool isMessageInQueue(int tag, bool exchangeOnlyAttributesMarkedWithParallelise);
            
            int getSenderRank() const;
            
      #endif
         
      };
      
      #endif
      
