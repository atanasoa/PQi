subroutine de_tum_query_f2c_nsd_create_client_instance(self,host,port,buffer_size) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     type(c_ptr)::host
     integer(kind=c_int)::port
     integer(kind=c_int)::buffer_size
end subroutine de_tum_query_f2c_nsd_create_client_instance


subroutine de_tum_query_f2c_nsd_destroy_instance(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
end subroutine de_tum_query_f2c_nsd_destroy_instance

subroutine  de_tum_query_f2c_nsd_getNumberOfParts(self,&
	parts) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	integer(kind=c_int),intent(inout)::parts

end subroutine de_tum_query_f2c_nsd_getNumberOfParts
subroutine  de_tum_query_f2c_nsd_getQueryDescription(self,&
	offset,offset_len,&
	size,size_len,&
	resolution,resolution_len,&
	mids,mids_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(inout),dimension(*)::offset
	integer(kind=c_int),intent(in)::offset_len
	real(kind=c_double),intent(inout),dimension(*)::size
	integer(kind=c_int),intent(in)::size_len
	integer(kind=c_int),intent(inout),dimension(*)::resolution
	integer(kind=c_int),intent(in)::resolution_len
	integer(kind=c_int),intent(inout),dimension(*)::mids
	integer(kind=c_int),intent(in)::mids_len

end subroutine de_tum_query_f2c_nsd_getQueryDescription
subroutine  de_tum_query_f2c_nsd_forwardAnswer(self,&
	data,data_len,&
	distance,distance_len,&
	indices,indices_len,&
	rid) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(in),dimension(*)::data
	integer(kind=c_int),intent(in)::data_len
	real(kind=c_double),intent(in),dimension(*)::distance
	integer(kind=c_int),intent(in)::distance_len
	integer(kind=c_int),intent(in),dimension(*)::indices
	integer(kind=c_int),intent(in)::indices_len
	integer(kind=c_int),intent(in)::rid

end subroutine de_tum_query_f2c_nsd_forwardAnswer
