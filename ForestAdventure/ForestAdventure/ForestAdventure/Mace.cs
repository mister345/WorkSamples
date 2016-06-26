using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace ForestAdventure
{
    class Mace: Weapon
    {
        private const int maceRadius = 30;
        private const int maxDamage = 60;

        public override string Name { get { return "Mace"; } }
        
        public Mace(Game game, Point location)
            : base(game, location) { }

        private int newDirection;
        public int NewDirection
        {

            get
            {
                return newDirection;
            }
            set
            {
                switch (value)
                {
                    case -1:
                        newDirection = 3;
                        break;
                    case 4:
                        newDirection = 0;
                        break;
                    case 5:
                        newDirection = 1;
                        break;

                    default:
                        newDirection = value;
                        break;
                }
            }
        }

        public override void Attack(Direction direction, Random random)
        {
            NewDirection = (int)direction;
            DamageEnemy(direction, maceRadius, maxDamage, random);
            NewDirection = (int)direction + 1;
            DamageEnemy((Direction)NewDirection, maceRadius, maxDamage, random);
            NewDirection = (int)direction - 1;
            DamageEnemy((Direction)NewDirection, maceRadius, maxDamage, random);
            NewDirection = (int)direction +2;
            DamageEnemy((Direction)NewDirection, maceRadius, maxDamage, random);

        }    }
}
