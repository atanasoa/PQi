module de_tum_Query2SocketPort 
use, intrinsic :: iso_c_binding
implicit none


type, public :: Query2SocketPort
     
     integer(kind=c_long_long )::reference
     contains
     procedure,public::create_port_client_instance
     procedure,public::create_port_client_instance_for_c
     procedure,public::destroyPortInstance
     procedure,public::getNumberOfParts
procedure,public::getQueryDescription
procedure,public::forwardAnswer

end type Query2SocketPort
contains

subroutine create_port_client_instance_for_c(this,host,port,buffer_size)
    class(Query2SocketPort)::this
    integer(kind=c_int)::port
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::buffer_size
    call de_tum_queryc2socket_plain_port_create_client_instance(this%reference,host,port,buffer_size)
    

end subroutine create_port_client_instance_for_c

subroutine create_port_client_instance(this,host,port,buffer_size)
    class(Query2SocketPort)::this
    integer::port
    character(*)::host
    integer::buffer_size
    call this%create_port_client_instance_for_c(host//c_null_char,port,buffer_size)
    

end subroutine create_port_client_instance



subroutine destroyPortInstance(this)
     class(Query2SocketPort)::this
     call de_tum_queryc2socket_plain_port_destroy_instance(this%reference)

end subroutine destroyPortInstance

subroutine forwardAnswer(this,&
	data,data_len,&
	rid)
     use, intrinsic :: iso_c_binding
     class(Query2SocketPort)::this
     	real(8),intent(in),dimension(*)::data
	integer,intent(in)::data_len
	integer,intent(in)::rid

     
     call de_tum_queryc2socket_plain_port_forwardAnswer(this%reference,&
data,data_len,&
rid)
end subroutine forwardAnswer
subroutine getQueryDescription(this,&
	offset,offset_len,&
	size,size_len,&
	resolution,resolution_len,&
	mids,mids_len)
     use, intrinsic :: iso_c_binding
     class(Query2SocketPort)::this
     	real(8),intent(inout),dimension(*)::offset
	integer,intent(in)::offset_len
	real(8),intent(inout),dimension(*)::size
	integer,intent(in)::size_len
	integer,intent(inout),dimension(*)::resolution
	integer,intent(in)::resolution_len
	integer,intent(inout),dimension(*)::mids
	integer,intent(in)::mids_len

     
     call de_tum_queryc2socket_plain_port_getQueryDescription(this%reference,&
offset,offset_len,&
size,size_len,&
resolution,resolution_len,&
mids,mids_len)
end subroutine getQueryDescription
subroutine getNumberOfParts(this,&
	parts)
     use, intrinsic :: iso_c_binding
     class(Query2SocketPort)::this
     	integer,intent(inout)::parts

     
     call de_tum_queryc2socket_plain_port_getNumberOfParts(this%reference,&
parts)
end subroutine getNumberOfParts

end module  de_tum_Query2SocketPort
