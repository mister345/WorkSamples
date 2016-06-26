using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace ForestAdventure
{
    class Bow : Weapon
    {
        private const int bowRadius = 600;
        private const int maxDamage = 5;

        public override string Name { get { return "Bow"; } }

        public Bow(Game game, Point location)
            : base(game, location) { }

        public override void Attack(Direction direction, Random random)
        {
            DamageEnemy(direction, bowRadius, maxDamage, random);
        }
    }
}
