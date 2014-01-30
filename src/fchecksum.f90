function fchecksum(data_, bytes)
  use ISO_C_BINDING
  implicit none
  type(C_PTR) :: data_
  integer(C_SIZE_T) :: bytes
  character(kind=C_CHAR, len=1), dimension(9) :: cstr
  character*8 :: fchecksum
  integer :: i
  interface
    subroutine checksum(data_, bytes, result_) bind(C)
      use ISO_C_BINDING
      type(C_PTR), value :: data_
      integer(C_SIZE_T), value :: bytes
      character(kind=C_CHAR, len=1), dimension(*) :: result_
    end subroutine checksum
  end interface

  call checksum(data_, bytes, cstr)
  do i = 1, 8
    fchecksum(i:i) = cstr(i)
  end do
end function fchecksum
