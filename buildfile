cxx.std = latest

using cxx

hxx{*}: extension = hpp
cxx{*}: extension = cpp

import libs = sfml-graphics%lib{sfml-graphics}

exe{waves}: {hxx cxx}{**} $libs