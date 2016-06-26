using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Invaders.Model
{
    class Shot
    {
        private double ShotPixelsPerSecond = 100;
        public bool IsBomb { get; private set; }
        public Point Location { get; private set; }
        public static Size ShotSize = new Size(2, 10);
        private Direction _direction;
        public Direction Direction 
        { 
            get
            {
                return _direction;
            }
        }
        private DateTime _lastMoved;
        public Shot(Point location, Direction direction, bool isBomb)
        {
            Location = location;
            _direction = direction;
            _lastMoved = DateTime.Now;
            IsBomb = isBomb;

            if (isBomb)
                ShotPixelsPerSecond = 80;
        }
        public void Move()
        {
            TimeSpan timeSinceLastMoved = DateTime.Now - _lastMoved;
            double distance = timeSinceLastMoved.Milliseconds * ShotPixelsPerSecond / 1000;

            if (Direction == Direction.Down) distance *= -1;
            Location = new Point(Location.X, Location.Y - (int)distance);
            _lastMoved = DateTime.Now;
        }
    }
}
