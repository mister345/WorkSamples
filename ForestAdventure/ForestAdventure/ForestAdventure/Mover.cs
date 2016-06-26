using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace ForestAdventure
{
	/// <summary>
	/// Abstract, base class for all characters in the game.
	/// </summary>
    abstract class Mover
    {
		#region Constants
		protected const int MoveInterval = 30;
		#endregion

		#region Fields
		protected Point location;
        protected Game game;
		#endregion

		#region Constructors
		public Mover(Game game, Point location)
		{
			this.game = game;
			this.location = location;
		}
		#endregion

		#region Properties
		public Point Location { get { return location; } }      
		#endregion

		#region Methods
		public bool Nearby(Point locationToCheck, int distance)
        {
            if (Math.Abs(location.X - locationToCheck.X) < distance &&
            (Math.Abs(location.Y - locationToCheck.Y) < distance))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public Point Move(Direction direction, Rectangle boundaries)
        {
            Point newLocation = location;
            switch (direction)
            {
                case Direction.Up:
                    if (newLocation.Y - MoveInterval >= boundaries.Top)
                        newLocation.Y -= MoveInterval;
                    break;

                case Direction.Down:
                    if (newLocation.Y + MoveInterval <= boundaries.Bottom)
                        newLocation.Y += MoveInterval;
                    break;

                case Direction.Left:
                    if (newLocation.X - MoveInterval >= boundaries.Left)
                        newLocation.X -= MoveInterval;
                    break;

                case Direction.Right:
                    if (newLocation.X + MoveInterval <= boundaries.Right)
                        newLocation.X += MoveInterval;
                    break;
                default: break;
            }
            return newLocation;
		}
		#endregion
	}
}
