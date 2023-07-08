# eqxn
Equation writing and rendering, and maybe even some CAS

tex ref: A Gentle Introduction to TEX, by Michael Doob (google it)

you need tex and dvipng for the tex stuff
just install dvipng from apt (sudo apt-get install dvipng)
you also need gtk: apt-get -y install libgtk-3-dev

pipeline is 
tex somefile.tex
which produces
somefile.dvi
then
dvipng somefile.dvi
produces somefile[1,2,3].png - one for each page


## only do the below if you like building from source and things not
## working:
dvipng prereqs:
libgd:
wget https://bitbucket.org/libgd/gd-libgd/downloads/libgd-2.1.1.tar.gz
build with cmake

kpathsea:
https://ctan.org/pkg/kpathsea
source is an svn repo here: https://tug.org/svn/texlive/trunk/Build/source/texk/kpathsea/

get dvipng from 
https://ctan.org/tex-archive/dviware/dvipng
or
wget http://mirrors.ctan.org/dviware/dvipng.zip
unzip dvipng
