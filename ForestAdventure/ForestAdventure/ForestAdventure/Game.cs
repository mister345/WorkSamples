/***************************************************************************************
* File:           Game.cs                                                              *
*                                                                                      *
* Author:         Gregory Weiner                                                       *
* Version:        1.0 4.07.2012                                                        *
* Last Modified:  6.17.2012                                                            *
* License:        Free Software(GNU License Included)                                  *
* Purpose:        This is a bird's eye view adventure game demo, akin to the           *
*                 original Legend of Zelda for NES, written from scratch in C# for     *
*                 the Windows Forms platform. A turn-based 'dungeon' game, the player  *
*                 collects a new weapon each level and must kill all enemies in order  *
*                 to advance to the next level. Enemies may attack or flee based on    * 
*                 their attributes.                                                    *
*                                                                                      *
* Description:    The Game class and its subclasses contains the main business         *
*                 logic for the program. Display is handled through controls in        *
*                 the Forest.cs class.                                                 *
*                                                                                      *
* Input:          Click on arrows in HUD at bottom to move, inventory items to select  *
*                 them when they appear, and attack buttons to attack directionally.   *
*                                                                                      *
* Requirements:   Requires a functioning mouse for input. Runs in windowed mode.       *
*                                                                                      *
***************************************************************************************/
                                                                                        
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace ForestAdventure
{
    class Game
    {
        private Rectangle boundaries;
        private int level = 0;
        private Player player;

        public IEnumerable<Enemy> Enemies { get; private set;}
        public Weapon WeaponInRoom { get; private set; }

        public int Level { get { return level; } }
        public Point PlayerLocation { get { return player.Location; } }
        public int PlayerHitPoints { get { return player.HitPoints; } }
        public Rectangle Boundaries { get { return boundaries; } }

		public Game(Rectangle boundaries)
		{
			this.boundaries = boundaries;
			player = new Player(this, new Point(boundaries.Left + 50, boundaries.Top + 70));
		}

        public void Move(Direction direction, Random random)
        {
            player.Move(direction);

            foreach (Enemy enemy in Enemies)
            {
                    enemy.Move(random);
            }
        }

        public void Attack(Direction direction, Random random)
        {
            player.Attack(direction, random);
            foreach (Enemy enemy in Enemies)
                enemy.Move(random);
        }

        public void IncreasePlayerHealth(int health, Random random)
        {
            player.IncreaseHealth(health, random);
        }

        public void HitPlayer(int maxDamage, Random random)
        {
            player.Hit(maxDamage, random);
        }

        private Point GetRandomLocation(Random random)
        {
            return new Point(boundaries.Left +
            random.Next(boundaries.Right / 10 - boundaries.Left / 10) * 10,
            boundaries.Top +
            random.Next(boundaries.Bottom / 10 - boundaries.Top / 10) * 10);
        }

		public bool CheckPlayerInventory(string weaponName)
		{
			return player.Weapons.Contains(weaponName);
		}

        public void Equip(string weaponName)
        {
            player.Equip(weaponName);
        }

        public void NewLevel(Random random) {
            level++;
            switch (level)
            {
                case 1:
					Enemies = new List<Enemy>() {
					new Bat(this, GetRandomLocation(random)),
					};
                    WeaponInRoom = new Sword(this, GetRandomLocation(random));
                    break;

                case 2:
                    Enemies = new List<Enemy>() {
new Ghost(this, GetRandomLocation(random)),
new Ghost(this, GetRandomLocation(random)),
new Bat(this, GetRandomLocation(random)),
};
                    WeaponInRoom = new Bow(this, GetRandomLocation(random));
                    break;

                case 3:
                    Enemies = new List<Enemy>() {
new Bat(this, GetRandomLocation(random)),
new Ghost(this, GetRandomLocation(random)),
new Ghoul(this, GetRandomLocation(random)),
};
                    WeaponInRoom = new Mace(this, GetRandomLocation(random));
                    break;

                case 4:
                                        Enemies = new List<Enemy>() {
new Ghoul(this, GetRandomLocation(random)),
new Ghost(this, GetRandomLocation(random)),
new Ghoul(this, GetRandomLocation(random)),
};
                    WeaponInRoom = new PotionBlue(this, GetRandomLocation(random));
                    break;

                case 5:
                                        Enemies = new List<Enemy>() {
new Bat(this, GetRandomLocation(random)),
new Ghoul(this, GetRandomLocation(random)),
new Ghost(this, GetRandomLocation(random)),
new Ghoul(this, GetRandomLocation(random)),
};
                    WeaponInRoom = new PotionRed(this, GetRandomLocation(random));
                    break;

                case 6:
                Enemies = new List<Enemy>() {
new Ghoul(this, GetRandomLocation(random)),
new Bat(this, GetRandomLocation(random)),
new Ghoul(this, GetRandomLocation(random)),
new Ghost(this, GetRandomLocation(random)),
new Ghoul(this, GetRandomLocation(random)),
new Bat(this, GetRandomLocation(random)),
};
                    WeaponInRoom = new PotionRed(this, GetRandomLocation(random));
                    break;   
            }          
}
        }
    }