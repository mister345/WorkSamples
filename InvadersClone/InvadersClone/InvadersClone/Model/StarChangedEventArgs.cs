using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Invaders.Model
{
    class StarChangedEventArgs: EventArgs {
        public Point StarThatChanged { get; set; }
        public bool Removed { get; private set; }
        
        public StarChangedEventArgs(Point starThatChanged, bool removed)
        {
            StarThatChanged = starThatChanged;
            Removed = removed;
        }
    }
}
