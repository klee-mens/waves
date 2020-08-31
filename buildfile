cxx.std = latest

using cxx

hxx{*}: extension = hpp
cxx{*}: extension = cpp

exe{waves}: {hxx cxx}{**}