module de_tum_SimFNativeSocketDispatcher
use, intrinsic :: iso_c_binding
implicit none


type, public :: SimNativeSocketDispatcher
     integer(kind=c_long_long )::reference
     contains
     procedure,public::createClientDispatcherInstanceForC
     procedure,public::createClientDispatcherInstance
     procedure,public::destroyDispatcherInstance
     
     
     	procedure,public::sim
	procedure,private::sim_internal

end type SimNativeSocketDispatcher
contains
subroutine createClientDispatcherInstanceForC(this,host,port,buffer_size)
    class(SimNativeSocketDispatcher)::this
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::port
    integer(kind=c_int)::buffer_size
    this%reference=0
    call de_tum_sim_f2c_nsd_create_client_instance(this%reference,host,port,buffer_size)
    
    

end subroutine createClientDispatcherInstanceForC

subroutine createClientDispatcherInstance(this,host,port,buffer_size)
    class(SimNativeSocketDispatcher)::this
    character(*)::host
    integer::port
    integer::buffer_size
    call this%createClientDispatcherInstanceForC(host//c_null_char,port,buffer_size)
    
    

end subroutine createClientDispatcherInstance

subroutine destroyDispatcherInstance(this)
     class(SimNativeSocketDispatcher)::this
     call de_tum_sim_f2c_nsd_destroy_instance(this%reference)

end subroutine destroyDispatcherInstance

subroutine sim_internal(this)
     use, intrinsic :: iso_c_binding
     class(SimNativeSocketDispatcher)::this
     
     call de_tum_sim_f2c_nsd_sim(this%reference)
end subroutine sim_internal

subroutine sim(this)
     use, intrinsic :: iso_c_binding
     class(SimNativeSocketDispatcher)::this
     
     call this%sim_internal()
end subroutine sim

end module  de_tum_SimFNativeSocketDispatcher
