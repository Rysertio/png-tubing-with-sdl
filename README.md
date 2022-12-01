# PNG tubing with SDL
A very simple PNG tubing application written in c for linux. It uses the sdl library. Theres no WINDOWS support at the moment.
## Building from source  
1. You're gonna need the following packages     
`` gcc make libsdl2-dev libsdl2-image-dev libasound2-dev ``
2. If you're on a Debian based distro run     
 ``sudo apt-get install build-essential make git libsdl2-dev libsdl2-image-dev libasound2-dev ``
3. If you're on a Arch based distro run     
  ``sudo pacman -S base-devel make git sdl2_image ``
4. Clone this repo and run `make`     

```
git clone https://github.com/FPGA21/png-tubing-with-sdl/         
cd png-tubing-with-sdl && make
```

5. run the program within the directory using ``./game`` 
