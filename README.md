# imgd4000-boids
Agent-based simulation assignment for IMGD 4000

Gameplay video: [https://drive.google.com/file/d/1J4oQwK8fzj-tdMmbQcvUGNeyYuR6A9K2/view?usp=sharing](https://drive.google.com/file/d/1J4oQwK8fzj-tdMmbQcvUGNeyYuR6A9K2/view?usp=sharing)

For the most part I followed the in-class [flocking tutorial](https://github.com/charlieroberts/imgd4000-2024/blob/main/day_4_flocking.md), with the initial boid locations randomly generated, and implemented the [psuedocode by Conrad Parker](http://www.kfish.org/boids/pseudocode.html) with some slight changes to constants for the rules.

For the tweaks, I limited the speed and had the boids tend towards a particular place that's randomly picked at the start. When a boid reaches the target area, a new target is chosen randomly. I also bounded the position, though this isn't really apparent after adding the target place since the target will always be within bounds.
