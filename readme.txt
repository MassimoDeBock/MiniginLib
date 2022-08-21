=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-
Engine choices:

Resources:
	Textures and SpriteGroups when initialised have a pointer to them stored to stop duplicates:
		first load of texture a: 	load and save a weak_ptr to a.
		second load of texture a:	return a shared_ptr to a without loading again.

Input:
	Keyboard input is considered like a controller
		when making a game you just have to setup which you want to use for which user
			(2 users on 1 keyboard is supported)
		after initializing the input (controller or keyboard) you can just consider them both as controllers
	Works with switch joycons when using: BetterJoy (https://github.com/Davidobot/BetterJoy/tree/master/BetterJoyForCemu)
		(I have a recording on my phone to show if needed)
	
Components:
	Components also are stored with a string as key which allows for easier grabbing.
	This key also makes Thinks get drawn in a set order (lower ascii value for first char means drawn first, if equal go to the next char,..)
		Using '-' before object name gives it priority over Regular leters, '_' makes it get drawn after, you can use multiple to sort even better

=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-
Game choices:
	I mainly focussed on showing the engine works properly

	map:
		the map is drawn as a grid
		road tiles check which are connected and which aren't this way getting a correct tile
		wall tiles check diagonally in a similar way (with extra checks to avoid edge cases)
		
		benefits: changing the map will automatically update it visually, only 0's and 1's needed
	
	movement:
		check the displayedtile value (not an extra value, the value used for displaying the correct tile)


=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-

https://github.com/SmollBunny/MiniginLib.git
(some intermediat ones before splitting library and game) 
https://github.com/SmollBunny/FirstEngine.git
https://github.com/SmollBunny/Minigin.git