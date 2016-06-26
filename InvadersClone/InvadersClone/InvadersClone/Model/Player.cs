using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.ComponentModel;

namespace Invaders.Model
{
    class Player : Ship
    {
        const double Speed = 10;

        public bool Dead { get; private set; }

        public readonly static Size _playerSize = new Size(25, 15);

        public Player(Size playAreaSize)
            : base(new Point(playAreaSize.Width / 2, playAreaSize.Height - _playerSize.Height * 2), _playerSize)
        {
        }

        public double PlayerX
        {   get { return Location.X; }
            set {
                Point newLocation = new Point(value, Location.Y);
                Location = newLocation;}}

        public double PlayerY
        {   get { return Location.Y; }
            set
            {   Point newLocation = new Point(Location.X, value);
                Location = newLocation;}}

        private string _testInput = "TEST COMPLETE";
        public string TestInput
        {   get { return _testInput; }
            set { _testInput = value; }}

        public void MovePlayer(Direction direction, Size playAreaSize)
        {
            #region old code
            //if (e.Key == Key.Left || e.Key == Key.Right)
            //{
            //    if (e.Key == Key.Left)
            //        return position - Speed;
            //    else
            //        return position + Speed;
            //}

            //else
            //{
            //    if (e.Key == Key.Up)
            //        return position - Speed;
            //    else
            //        return position + Speed;
            //}
            #endregion

            Point newLocation = Location;
            switch(direction){
                case Direction.Left:
                    if (newLocation.X - Speed > -10)
                    {
                        newLocation.X -= Speed;
                        Location = newLocation;
                    }
                    break;

                case Direction.Right:
                    if (newLocation.X + Speed < playAreaSize.Width - 15)
                    {
                        newLocation.X += Speed;
                        Location = newLocation;
                    }
                    break;
            }
        }

        public void Die() { Dead = true; }
    }
}