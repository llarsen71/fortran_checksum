program chksum
  implicit none
  integer*8, allocatable :: a(:)
  integer :: i, j

  j = 3
  allocate(a(j))
  do i = 1, j
    a(i) = i
  end do
  call testi(a,j*sizeof(a(1)))

contains

  subroutine testi(a, bytes)
    use iso_c_binding
    implicit none
    integer*8, target :: a(1)
    integer(c_size_t) :: bytes
    character*8 :: fchecksum
    character*8 :: chk

    chk = fchecksum(c_loc(a), bytes)
    write(*,*) chk
  end subroutine
end program

