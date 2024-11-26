# Project Proposal

## Description

Traditional street fighter-like fighting game. Perform combos on the opponent with normal and special moves to knock them out and win the round. Best of three wins the game.

## Terms

| Term         | Definition                                                                                                                                                                                 |
| ------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Whiff        | A missed attack                                                                                                                                                                            |
| Punish       | Attacking an opponent when they are unable to block. Whiff punishing is a type of punish where your opponent is in the recovery animation of his missed attack and cannot block your move. |
| Turn         | Doesn't mean turn based in the traditional sense, instead meaning that one of the players is on the offensive and the other is forced to block his attacks.                                |
| Normal       | A basic attack usually performed from a single button input.                                                                                                                               |
| Special      | A move that typically required a motion and an attack button to execute.                                                                                                                   |
| Motion Input | A special input type where the player has to press a certain sequence of directions to get the attack to come out.                                                                         |
| Chip Damage  | Damage dealt while blocking, usually a portion of the total damage of the move.                                                                                                            |
| Throw Tech   | In this game, pressing and attack button in a small window before the throw actually goes into effect that pushes your opponent away to prevent them from continuing their offense.        |
| Cancel       | Removing the recovery of an attack, usually so that you can transition immediately into another move.                                                                                      |

## Gameplay

Two players select their characters, then there is a small countdown until the fight starts. The players start in a neutral state where neither of them have the advantage and they must use their normal and special moves to go on the offensive. Whiffing could result in you being whiff punished and letting your opponent take their turn.

Upon successfully hitting your enemy or making them block your attack you can take your turn and attempt to hit your opponent and start your combo to chunk their health. Normal moves do not deal chip damage while special moves do to prevent blocking indefinitely and running down the clock.

There are a few ways for the round to end, the first one being running out of time, where the player with the highest health remaining will win the round, the second being a double K.O. where both players hit eachother with an attack that reduces both their health to 0, where no one takes the round, and the third being when only one player reaches 0 health where the other player takes the round. The first to reach 2 rounds won takes the game.

## Requirements

1.  The player can change their control scheme to allow them to use controls they are more comfortable with.
2.  The game must save the player's chosen control scheme and load it on the startup of the game.
3.  The players must be able to chose a character after selecting the play option.
4.  The player can move left and right.
5.  The player can jump.
6.  The player can use one of 3 buttons to attack (Light, Medium, and Heavy).
7.  The player can attack on the ground or in the air.
8.  The player can block by holding the direction opposite their opponent.
9.  The player can block low and mid attacks by crouch blocking and can block mid and high attacks by stand blocking.
10. The player can throw their opponent by holding a movement direction and pressing the Heavy attack button while near their opponent.
11. The player can tech their opponent's throw.
12. The player can perform special moves by using motion inputs.
13. Special moves must deal chip damage against blocking enemies.
14. The player's attacks must be able to hit the opponent (hitbox collision).
15. The player must be able to cancel some moves into other moves to allow combo flexibility.
16. The game's timer must count down to 0 to prevent rounds from lasting forever.
17. The players' health values must be able to be reduced so the game doesn't last forever.
18. When a player's health reaches 0 the round must end and grant the other player a point.
19. When a player reaches 2 points the game must end and prompt the players with an option to keep playing or return to the main menu.

## References

### Motion Inputs and Input System

Input system and parser based on the MUGEN [deep buffering](https://mugen-net.work/wiki/index.php?title=Deep_Buffering#Algorithm) implementation.

### Graphics Library and Input Polling

Built using the [raylib](https://www.raylib.com) graphics library to handle rendering and input polling.

### Fighting Game Terms and Definitions

[Figthing Game Glossary](https://glossary.infil.net/)

## Ignore, not part of the proposal

### Before Submitting:

- Change Starting State in StateMachine constructor to main menu state

### TODO

- Rewrite Makefile to reduce compilation time
- Work on player class
- Create Fight class to hold 2 players and add it to PlayState as a member
- Command parser
  - Add Command abstract class
  - Has command sequence field
  - Has check for input method

### Files with TODOs

- Player.h
- Fight.h & Fight.cpp

## Play State

### TODO

- Fields
  - Player1 (Player)
  - Player2 (Player)
  - UserInterface (UserInterface)
- Methods
  - Update
  - Render

## States Relationship

![States Relationship Diagram](./src/assets/game_states_relationship.png)
