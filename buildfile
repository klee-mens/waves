cxx.std = latest

using cxx

hxx{*}: extension = hpp
cxx{*}: extension = cpp

import libs = sfml-graphics%lib{sfml-graphics}

./: exe{waves}: cxx{main} $libs
./: exe{heat}: cxx{heat} $libs