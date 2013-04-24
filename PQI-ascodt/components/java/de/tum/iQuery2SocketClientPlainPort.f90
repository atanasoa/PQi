module de_tum_iQuery2SocketClientPort 
use, intrinsic :: iso_c_binding
implicit none


type, public :: iQuery2SocketClientPort
     private
     integer(kind=c_long_long )::cPointer
     contains
     procedure,public::createPortInstance
     procedure,public::destroyPortInstance
     procedure,public::requestNumberOfParts
procedure,public::requestPartsInformation

end type iQuery2SocketClientPort
contains
subroutine createPortInstance(this)
    class(iQuery2SocketClientPort)::this
    call de_tum_iqueryc2socket_client_plain_port_create_instance(this%cPointer)
    

end subroutine createPortInstance

subroutine destroyPortInstance(this)
     class(iQuery2SocketClientPort)::this
     call de_tum_iqueryc2socket_client_plain_port_destroy_instance(this%cPointer)

end subroutine destroyPortInstance

subroutine requestPartsInformation(this,&
	offset,offset_len,&
	size,size_len,&
	dimensions,dimensions_len,&
	identifiers,identifiers_len)
     use, intrinsic :: iso_c_binding
     class(iQuery2SocketClientPort)::this
     	real(8),intent(inout),dimension(*)::offset
	integer,intent(in)::offset_len
	real(8),intent(inout),dimension(*)::size
	integer,intent(in)::size_len
	integer,intent(inout),dimension(*)::dimensions
	integer,intent(in)::dimensions_len
	integer,intent(inout),dimension(*)::identifiers
	integer,intent(in)::identifiers_len

     
     call de_tum_iqueryc2socket_client_plain_port_requestPartsInformation(this%cPointer,&
offset,offset_len,&
size,size_len,&
dimensions,dimensions_len,&
identifiers,identifiers_len)
end subroutine requestPartsInformation
subroutine requestNumberOfParts(this,&
	parts)
     use, intrinsic :: iso_c_binding
     class(iQuery2SocketClientPort)::this
     	integer,intent(inout)::parts

     
     call de_tum_iqueryc2socket_client_plain_port_requestNumberOfParts(this%cPointer,&
parts)
end subroutine requestNumberOfParts

end module  de_tum_iQuery2SocketClientPort
