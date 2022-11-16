<h1 id="title" align="center">C-QUIZ</h1>

<h3 align="center"> :black_heart:  Console Game in C language :black_large_square: </h3>

<p align="center">
  <a href="#title"><img src="https://forthebadge.com/images/badges/made-with-c.svg"></a>
  <a href="#title"><img src="https://forthebadge.com/images/badges/makes-people-smile.svg"></a>
</p>


<p align="center">
  <a href="#introduction">Introduction</a> •
  <a href="#demo">Demo</a> •
  <a href="#demo">Step</a> •
  <a href="#changingControls">Changing Controls</a>
</p>

<h1 id="introduction">Introduction</h1>
This is a game to play in  windows console (CMD), it comprise a track of rows and columns boxes where the players move to end the game. 
There are marked boxes that contain questions about C language and let them to overtake positions. 


<h1 id="demo">Demo</h1>
<p align="center">
  <img src="https://user-images.githubusercontent.com/99779642/202041387-160088bb-1175-400f-bc55-8988f6b4642c.gif" style="max-width:100%;width:auto;height:auto;">
</p>
<h1  align="center">Preview</h1>
<p align="center">
  <a href="/"><img src="https://forthebadge.com/images/badges/check-it-out.svg"></a>
</p>

<h1 id="controls">Controls</h1>

It is a Two-Player game.

<center>

| Player 1 Controls || Player 2 Controls |
|--|-|--|
|<table><tr><th>Key</th><th>Description</th></tr><tr align="center"><td>UpArrowKey</td><td>Move Up</td></tr><tr align="center"><td>DownArrowKey</td><td>Move Down</td></tr><tr align="center"><td>LeftArrowKey</td><td>Move Left</td></tr><tr align="center"><td>RightArrowKey</td><td>Move Right</td></tr><tr align="center"><td>SpaceBar</td><td>Place Bomb</td></tr> </table>|<span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>| <table> <tr><th>Key</th><th>Description</th></tr><tr align="center"><td>NumPad 8</td><td>Move Up</td></tr><tr align="center"><td>NumPad 5</td><td>Move Down</td></tr><tr align="center"><td>NumPad 4</td><td>Move Left</td></tr><tr align="center"><td>NumPad 6</td><td>Move Right</td></tr><tr align="center"><td>End Key</td><td>Place Bomb</td></tr> </table>|

</center>

<h1 id="changingControls">Changing Controls</h1>
You can change the controls by making changes in the following files present in <i>/Assets/Scripts</i> directory.

<h4>Player One</h4>

```javascript
○ Player One Movement | Player1.cs
○ Player One Bomb     | BombSpawner.cs
```
<h4>Player Two</h4>

```javascript
○ Player Two Movement | Player2Script.cs
○ Player Two Bomb     | Player2BombSpawner.cs
```

