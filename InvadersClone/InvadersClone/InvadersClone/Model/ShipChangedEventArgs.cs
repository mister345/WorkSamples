using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Invaders.Model
{
    class ShipChangedEventArgs : EventArgs
    {
        public Ship ShipUpdated { get; private set; }
        public bool Killed { get; private set; }
        public double X { get; private set; }
        public double Y { get; private set; }

        public ShipChangedEventArgs(Ship shipUpdated, double x, double y, bool killed)
        {
            ShipUpdated = shipUpdated;
            X = x;
            Y = y;
            Killed = killed;
        }
    }
}
