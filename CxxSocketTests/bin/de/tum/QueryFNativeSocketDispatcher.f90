module de_tum_QueryFNativeSocketDispatcher
use, intrinsic :: iso_c_binding
implicit none


type, public :: QueryNativeSocketDispatcher
     integer(kind=c_long_long )::reference
     contains
     procedure,public::createClientDispatcherInstanceForC
     procedure,public::createClientDispatcherInstance
     procedure,public::destroyDispatcherInstance
     
     
     	procedure,public::getNumberOfParts
	procedure,private::getNumberOfParts_internal
	procedure,public::getQueryDescription
	procedure,private::getQueryDescription_internal
	procedure,public::forwardAnswer
	procedure,private::forwardAnswer_internal

end type QueryNativeSocketDispatcher
contains
subroutine createClientDispatcherInstanceForC(this,host,port,buffer_size)
    class(QueryNativeSocketDispatcher)::this
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::port
    integer(kind=c_int)::buffer_size
    this%reference=0
    call de_tum_query_f2c_nsd_create_client_instance(this%reference,host,port,buffer_size)
    
    

end subroutine createClientDispatcherInstanceForC

subroutine createClientDispatcherInstance(this,host,port,buffer_size)
    class(QueryNativeSocketDispatcher)::this
    character(*)::host
    integer::port
    integer::buffer_size
    call this%createClientDispatcherInstanceForC(host//c_null_char,port,buffer_size)
    
    

end subroutine createClientDispatcherInstance

subroutine destroyDispatcherInstance(this)
     class(QueryNativeSocketDispatcher)::this
     call de_tum_query_f2c_nsd_destroy_instance(this%reference)

end subroutine destroyDispatcherInstance

subroutine forwardAnswer_internal(this,&
	data,data_len,&
	distance,distance_len,&
	indices,indices_len,&
	rid)
     use, intrinsic :: iso_c_binding
     class(QueryNativeSocketDispatcher)::this
     	real(kind=c_double),intent(in),dimension(*)::data
	integer(kind=c_int),intent(in)::data_len
	real(kind=c_double),intent(in),dimension(*)::distance
	integer(kind=c_int),intent(in)::distance_len
	integer(kind=c_int),intent(in),dimension(*)::indices
	integer(kind=c_int),intent(in)::indices_len
	integer(kind=c_int),intent(in)::rid

     call de_tum_query_f2c_nsd_forwardAnswer(this%reference,&
data,data_len,&
distance,distance_len,&
indices,indices_len,&
rid)
end subroutine forwardAnswer_internal

subroutine forwardAnswer(this,&
	data,data_len,&
	distance,distance_len,&
	indices,indices_len,&
	rid)
     use, intrinsic :: iso_c_binding
     class(QueryNativeSocketDispatcher)::this
     	real(8),intent(in),dimension(*)::data
	integer,intent(in)::data_len
	real(8),intent(in),dimension(*)::distance
	integer,intent(in)::distance_len
	integer,intent(in),dimension(*)::indices
	integer,intent(in)::indices_len
	integer,intent(in)::rid

     call this%forwardAnswer_internal(&
data,data_len,&
distance,distance_len,&
indices,indices_len,&
rid)
end subroutine forwardAnswer
subroutine getQueryDescription_internal(this,&
	offset,offset_len,&
	size,size_len,&
	resolution,resolution_len,&
	mids,mids_len)
     use, intrinsic :: iso_c_binding
     class(QueryNativeSocketDispatcher)::this
     	real(kind=c_double),intent(inout),dimension(*)::offset
	integer(kind=c_int),intent(in)::offset_len
	real(kind=c_double),intent(inout),dimension(*)::size
	integer(kind=c_int),intent(in)::size_len
	integer(kind=c_int),intent(inout),dimension(*)::resolution
	integer(kind=c_int),intent(in)::resolution_len
	integer(kind=c_int),intent(inout),dimension(*)::mids
	integer(kind=c_int),intent(in)::mids_len

     call de_tum_query_f2c_nsd_getQueryDescription(this%reference,&
offset,offset_len,&
size,size_len,&
resolution,resolution_len,&
mids,mids_len)
end subroutine getQueryDescription_internal

subroutine getQueryDescription(this,&
	offset,offset_len,&
	size,size_len,&
	resolution,resolution_len,&
	mids,mids_len)
     use, intrinsic :: iso_c_binding
     class(QueryNativeSocketDispatcher)::this
     	real(8),intent(inout),dimension(*)::offset
	integer,intent(in)::offset_len
	real(8),intent(inout),dimension(*)::size
	integer,intent(in)::size_len
	integer,intent(inout),dimension(*)::resolution
	integer,intent(in)::resolution_len
	integer,intent(inout),dimension(*)::mids
	integer,intent(in)::mids_len

     call this%getQueryDescription_internal(&
offset,offset_len,&
size,size_len,&
resolution,resolution_len,&
mids,mids_len)
end subroutine getQueryDescription
subroutine getNumberOfParts_internal(this,&
	parts)
     use, intrinsic :: iso_c_binding
     class(QueryNativeSocketDispatcher)::this
     	integer(kind=c_int),intent(inout)::parts

     call de_tum_query_f2c_nsd_getNumberOfParts(this%reference,&
parts)
end subroutine getNumberOfParts_internal

subroutine getNumberOfParts(this,&
	parts)
     use, intrinsic :: iso_c_binding
     class(QueryNativeSocketDispatcher)::this
     	integer,intent(inout)::parts

     call this%getNumberOfParts_internal(&
parts)
end subroutine getNumberOfParts

end module  de_tum_QueryFNativeSocketDispatcher
