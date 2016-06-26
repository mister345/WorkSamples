using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Invaders.Model
{
    class ShotMovedEventArgs : EventArgs
    {
            public Shot Shot { get; private set; }
            public bool Removed { get; private set; }
            public bool IsBomb { get; private set; }
            public ShotMovedEventArgs(Shot shot, bool removed, bool isBomb)
            {
                Shot = shot;
                Removed = removed;
                IsBomb = isBomb;
            }
        }
    }