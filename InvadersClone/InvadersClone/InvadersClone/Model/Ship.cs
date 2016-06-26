using System;
using System.Windows;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Invaders.Model
{
    abstract class Ship
    {
        protected Point _location;
        public Point Location
        {
            get { return _location; }
            set { _location = value; }
        }        
        public Size Size { get; protected set; }
        public Rect Area
        {
            get { return new Rect(Location, Size); }
        }

        public Ship() { }

        public Ship(Point location, Size size)
        {
            Location = location;
            Size = size;
        }

        public void Move(Direction direction) {
            MessageBox.Show(direction.ToString());
        }
    }
}
