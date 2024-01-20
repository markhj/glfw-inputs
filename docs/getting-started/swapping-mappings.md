# Swapping mappings 🔄

Imagine this scenario:
You're building a game. In the game, arrow keys should move your character. But in the menu, you want the arrow keys
to navigate between buttons and options.

You _could_ add lots of conditional statements when the arrow keys are pressed.
Or you could completely separate what the keys do in-game and in the menu.

So you have one keyboard mapping which concerns itself with the in-game, and completely
separate mapping which details the menu navigation. And then you switch between them accordingly.

## How to swap ❎
Swapping is essentially quite simple. You just point a control's
mapping from one to another.

````c++
Keyboard keyboard;
KeyboardMapping inGameKeyboardMapping;
KeyboardMapping menuKeyboardMapping;

// Mapping is set to the "in-game" mode
keyboard.mapping = &inGameKeyboardMapping;

// Mapping is changed to the menu mode
keyboard.mapping = &menuKeyboardMapping;
````

## Example 🚀
A much simplified example on how the swapping would be done in practice:

````c++
Keyboard keyboard;
KeyboardMapping inGameKeyboardMapping;
KeyboardMapping menuKeyboardMapping;

function startGame()
{
    keyboard.mapping = &inGameKeyboardMapping;
}

function openPauseMenu()
{
    keyboard.mapping = &menuKeyboardMapping;
}

function closePauseMenu()
{
    keyboard.mapping = &inGameKeyboardMapping;
}
````
