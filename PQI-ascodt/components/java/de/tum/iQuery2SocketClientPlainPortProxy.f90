subroutine  de_tum_iqueryc2socket_client_plain_port_create_instance(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
end subroutine de_tum_iqueryc2socket_client_plain_port_create_instance

subroutine  de_tum_iqueryc2socket_client_plain_port_destroy_instance(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
end subroutine de_tum_iqueryc2socket_client_plain_port_destroy_instance

subroutine  de_tum_iqueryc2socket_client_plain_port_requestNumberOfParts(self,&
	parts) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	integer(kind=c_int),intent(inout)::parts

end subroutine de_tum_iqueryc2socket_client_plain_port_requestNumberOfParts
subroutine  de_tum_iqueryc2socket_client_plain_port_requestPartsInformation(self,&
	offset,offset_len,&
	size,size_len,&
	dimensions,dimensions_len,&
	identifiers,identifiers_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(inout),dimension(*)::offset
	integer(kind=c_int),intent(in)::offset_len
	real(kind=c_double),intent(inout),dimension(*)::size
	integer(kind=c_int),intent(in)::size_len
	integer(kind=c_int),intent(inout),dimension(*)::dimensions
	integer(kind=c_int),intent(in)::dimensions_len
	integer(kind=c_int),intent(inout),dimension(*)::identifiers
	integer(kind=c_int),intent(in)::identifiers_len

end subroutine de_tum_iqueryc2socket_client_plain_port_requestPartsInformation
