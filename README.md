### Piconfig:

This is just a simple project using Ncurses as a frontend for configuring picom.
If you somehow find this repo and want to use it, you'll have to edit file.c and change
the path to your picom.conf. Also it won't work unless you use the included picom.conf file.

This was just a project to get a better grasp on C. I wasn't very consistant with the code as
I was experimenting.

### Install:

```
git clone https://github.com/jas3333/piconfig
cd piconfig
make

```

You'll then want to copy the picom.conf file to `~/.config/picom/` and put piconfig wherever.
