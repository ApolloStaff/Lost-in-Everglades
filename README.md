# Lost in Everglades

Lost in the Everglades in an RPG (Role-Playing-Game) between a player and the computer.

A group of tourists has been lost in the Everglades and a ranger must rescue them before time runs
out.

The Everglades are represented by a 5x5 matrix. The ranger (R) starts the rescue at the upper-left
corner of the park, the group of tourists (T) are lost at the lower-right corner. The ranger has 12
gongs of time to find and rescue the tourists before they perish.

During the journey, the ranger might find dangers (hungry alligator, swarm of giant mosquitoes,
venomous spider, or Python).

When the ranger finds a danger, they can choose to fight them or hide and wait for them to leave:

- If the Ranger hides & waits
    - Moves to the desired cell
    - Loses 5 gongs of time

- If the Ranger fights & wins
    - Moves to the desired cell
    - Loses 2 gongs of time

- If the Ranger fights & loses
    - Goes back to the initial cell
    - Loses 3 gongs of time
    - The Danger remains in the cell

## Notes:

- If the Ranger move to a cell with no dangers
    - Loses 1 gong of time
      
- The game ends when either:
    - The ranger rescues the group of tourists.
    - The time expires and the fate of the tourists is forever unknown.
