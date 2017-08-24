Thanks for taking your time playing and grading this project.

I would like to call this "game" Reversed Snake. The goal of this game is to collect 5 paddles using the character. Character is controlled by WASD keys. By default this character would move right with a speed of 0.5, if you hold A button it will move left with speed 0.5.Same things for W and S button, but you will also move right as moving up and down doesn't counter the effect of moving right.

Whenever you collect 1 paddle, your speed (for all directions) will be reduced by 0.1, which means that after collecting 5 paddles, your speed will decrease to 0. That's how you win the game. The game will exit automatically after speed reaches 0. Or you can manually quit the game by pressing Q button on your keyboard.

P.S.: You may want to load all symbols for this project to let it work correctly. To do this, click Debug on Visual Studio, choose Options. Then on the pop-up window expand Debugging section and select Symbols. Check "Microsoft Symbol Servers", choose a location to store all symbols and press OK. Failed to do this will potentially cause the entire computer to halt without receving any information. The only way to recover the controll is to force restart the computer (by pressing and holding power key on your computer).

As far as shining point of my Engine, I would say that BlockAllocator, BitArray and FSA from semester 1 are fully functional. Matrix4X4, Vector3D, Vector4D and CollisionDetection (isColliding function in CollisionChecker) from semester 2 are also fully functional and works fine.