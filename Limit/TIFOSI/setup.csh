if ( $?LD_LIBRARY_PATH == 0 ) then
  setenv LD_LIBRARY_PATH /AtlasDisk/home/busato/stat/Limit/TIFOSI
else
  setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/AtlasDisk/home/busato/stat/Limit/TIFOSI
endif
