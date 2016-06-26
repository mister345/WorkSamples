using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Invaders.Model
{
    class Invader : Ship
    {
        public readonly static Size _invaderSize = new Size(25, 15);
        public InvaderType _invaderType;
        public int InvaderScore { get; private set; }
        public const double moveInterval = 5;

        public Invader(InvaderType invaderType, Point location):
            base(location, _invaderSize)
        {
            _invaderType = invaderType;
            _location = location;
            switch (invaderType)
            {
                case InvaderType.bug:
                    InvaderScore = 50;
                    break;
                case InvaderType.flyingsaucer:
                    InvaderScore = 30;
                    break;
                case InvaderType.satellite:
                    InvaderScore = 20;
                    break;
                case InvaderType.spaceship:
                    InvaderScore = 15;
                    break;
                case InvaderType.star:
                    InvaderScore = 5;
                    break;
                default:
                    break;
            }
        }

        public Point MoveLeft(double bugLocationX, double bugLocationY) 
        {
            double newX = bugLocationX - moveInterval;
            return new Point(newX, bugLocationY);
        }
        public Point MoveRight(double bugLocationX, double bugLocationY)
        {
            double newX = bugLocationX + moveInterval;
            return new Point(newX, bugLocationY);
        }
        public Point MoveDown(double bugLocationX, double bugLocationY) 
        {
            double newY = bugLocationY + moveInterval;
            return new Point(bugLocationX, newY);
        }
    }
}