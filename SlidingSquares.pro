TEMPLATE = subdirs

SUBDIRS = \
    src/SlidingSquaresConsole \
    src/SlidingSquaresQt \
    src/SlidingSquaresLib

# where to find the sub projects - give the folders
lib.subdir = src/SlidingSquaresLib
app.subdir = src/SlidingSquaresQt
console.subdir = src/SlidingSquaresConsole

# what subproject depends on others
app.depends = lib
console.depends = lib
