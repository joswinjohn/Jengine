cmake -S $HOME/git/Jengine/ -B $HOME/git/Jengine/build/ &&
  make -f $HOME/git/Jengine/build/Makefile -C $HOME/git/Jengine/build &&
  exec $HOME/git/Jengine/build/Jengine
