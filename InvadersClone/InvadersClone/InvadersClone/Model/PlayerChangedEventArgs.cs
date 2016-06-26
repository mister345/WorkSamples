using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Invaders.Model
{
    class PlayerChangedEventArgs: EventArgs
    {
        public bool Killed { get; private set; }
        public double LocationX { get; private set; }
        public double LocationY { get; private set; }

        public PlayerChangedEventArgs(bool killed, double locationX, double locationY) 
        {
            Killed = killed;
            LocationX = locationX;
            LocationY = locationY;
        }
    }
}
