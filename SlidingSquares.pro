  TEMPLATE = subdirs
 
  SUBDIRS = \
            src/SlidingSquaresQt \
            src/SlidingSquaresLib

  # where to find the sub projects - give the folders
  lib.subdir = src/SlidingSquaresLib
  app.subdir  = src/SlidingSquaresQt
 
  # what subproject depends on others
  app.depends = lib
 