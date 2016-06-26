using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace ForestAdventure
{
    class Sword : Weapon
    {
        private int swordRadius = 40;
        private int maxDamage = 10;

        public override string Name { get { return "Sword"; } }

        public Sword(Game game, Point location)
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
                    default:
                        newDirection = value;
                        break;
                }
                #region other possible code - would this work too?
                /*   if (value == -1)
                   {
                       newDirection = 3;
                   }
                   if (value == 4)
                   {
                       newDirection = 0;
                   }
                   else
                       newDirection = value;
               */
                #endregion
            }
        }

        // Here, I reworked my old class so the sword stops swinging after one hit:
        /*public override void Attack(Direction direction, Random random)
        {
            int NewDirection = 0;
            if(!DamageEnemy(direction, swordRadius, maxDamage, random))
            { 
            NewDirection = (int)direction + 1;
            }
            if (!DamageEnemy((Direction)NewDirection, swordRadius, maxDamage, random))
            {
                NewDirection = (int)direction - 1;
            }
            DamageEnemy((Direction)NewDirection, swordRadius, maxDamage, random);
        }*/

        // Here is another version of Attack() method that doesn't use math operations:
        public override void Attack(Direction direction, Random random)
        {
            if (!DamageEnemy(direction, swordRadius, maxDamage, random))
            {
                direction = Clockwise(direction);
            }
            if (!DamageEnemy(direction, swordRadius, maxDamage, random))
            {
                direction = CounterClockwise(direction);
            }
            DamageEnemy(direction, swordRadius, maxDamage, random);
        }

        private Direction Clockwise(Direction oldDirection)
        {
            Direction newDirection = oldDirection;
            if (oldDirection == Direction.Up)
            { newDirection = Direction.Right; }
            if (oldDirection == Direction.Right)
            { newDirection = Direction.Down; }
            if (oldDirection == Direction.Down)
            { newDirection = Direction.Left; }
            if(oldDirection == Direction.Left)
            {newDirection = Direction.Up;}
            return newDirection;
        }

         private Direction CounterClockwise(Direction oldDirection)
        {
            Direction newDirection = oldDirection;
            if (oldDirection == Direction.Up)
            { newDirection = Direction.Down; }
            if (oldDirection == Direction.Right)
            { newDirection = Direction.Left; }
            if (oldDirection == Direction.Down)
            { newDirection = Direction.Up; }
            if(oldDirection == Direction.Left)
            {newDirection = Direction.Right;}
            return newDirection;
        }
    }
}