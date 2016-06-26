using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace ForestAdventure
{
    class PotionBlue: Weapon, IPotion
    {
        private const int healthRevival = 30;

        public bool Used {get; private set;}

        public override string Name { get { return "Blue Potion"; } }
        
                //Potion can only be used once; value set to unused in constructor.
        public PotionBlue(Game game, Point location)
            : base(game, location) 
            {
                Used = false;
            }

        //Overrides Attack method but increases player health instead.
        public override void Attack(Direction direction, Random random)
        {
            game.IncreasePlayerHealth(healthRevival, random);
            Used = true;
        }
    }
}
