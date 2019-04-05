if ( $?LD_LIBRARY_PATH == 0 ) then
  setenv LD_LIBRARY_PATH /users/divers/atlas/busato/home/stat/Limit/ExclusionPlot
else
  setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/users/divers/atlas/busato/home/stat/Limit/ExclusionPlot
endif
