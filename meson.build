project('SoundyBoardy-Qt', 'cpp')
qt5_dep = dependency('qt5', modules: ['Core', 'Gui', 'Widgets', 'Multimedia', 'X11Extras'])

x11dep = dependency('x11')
sources = ['src/Filter.cpp', 'src/SoundUnit.cpp', 'src/main.cpp']

qt5 = import('qt5')
moc_inc = ['src/SoundUnit.hpp']
moc_files = qt5.preprocess(moc_headers : moc_inc,
                           dependencies: qt5_dep)

executable('soundyboardy', sources, moc_files, dependencies: [qt5_dep, x11dep])
