using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace ForestAdventure
{
	abstract class Weapon : Mover
	{
		public bool PickedUp { get; private set; }

        public abstract string Name { get; }

		public Weapon(Game game, Point location) :
			base(game, location)
		{
			PickedUp = false;
		}

		public void PickUpWeapon()
		{
			PickedUp = true;
		}

		public abstract void Attack(Direction direction, Random random);

        /// <summary>
        /// Test two conditions, 1. is the enemy behind the player? 2. is it within range? to determine
        /// if nearby or not in this method. I have it search along a given axis, with a width of 20 + 20 = 40
        /// (otherwise, the enemy would have to have the exact same cross coordinate as the player to return a hit, 
        /// which hardly ever happens.
        /// </summary>
        /// <param name="enemyLocation"></param>
        /// <param name="target"></param>
        /// <param name="testRadius"></param>
        /// <param name="direction"></param>
        /// <returns></returns>
        public bool Nearby(Point enemyLocation, Point target, int testRadius, Direction direction)
        {
            if (direction == Direction.Left || direction == Direction.Right)
            {
                    if ((Math.Abs(enemyLocation.X - target.X) < testRadius
                               &&
                           Math.Abs(game.PlayerLocation.X - enemyLocation.X) < testRadius
                               &&
                           Math.Abs(game.PlayerLocation.Y - enemyLocation.Y) < 20))
                        {
                            return true;
                        }
                        else
                    {
                            return false;
                    }}

            if(direction == Direction.Up || direction == Direction.Down)
            {
                    if ((Math.Abs(enemyLocation.Y - target.Y) < testRadius
                   &&
               Math.Abs(game.PlayerLocation.Y - enemyLocation.Y) < testRadius
                   &&
               Math.Abs(game.PlayerLocation.X - enemyLocation.X) < 30))
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
            }
            else
                return false;
            }

        protected bool DamageEnemy(Direction direction, int radius, int damage, Random random)
        {
            Point target = game.PlayerLocation;
            target = Move(direction, radius, game.Boundaries);
                foreach (Enemy enemy in game.Enemies)
                    {
                    if (Nearby(enemy.Location, target, radius, direction))
                    {
                        enemy.Hit(damage, random);
                        return true;
                    }
                }
            return false;
        }

        public Point Move(Direction direction, int radius, Rectangle boundaries)
		{
            Point newLocation = game.PlayerLocation;
            switch (direction)
            {
                case Direction.Up:
                    newLocation.Y -= radius;
                    break;
                
                case Direction.Down:
                    newLocation.Y += radius;
                    break;
                
                case Direction.Left:
                    newLocation.X -= radius;
                    break;

                case Direction.Right:
                    newLocation.X += radius;
                    break;
                default: break;
            }

            return newLocation;
		}
	}
}