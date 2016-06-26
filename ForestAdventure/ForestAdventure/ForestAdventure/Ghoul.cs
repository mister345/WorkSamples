using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace ForestAdventure
{
    class Ghoul: Enemy
    {
        private const int maxDamage = 8;

		public Ghoul(Game game, Point location)
			: base(game, location, 12)
		{ }
		
		public override void Move(Random random)
		{
			if (random.Next(2) == 1)
				base.location = Move(FindPlayerDirection(game.PlayerLocation), game.Boundaries);
			else
			if (NearPlayer())
				game.HitPlayer(maxDamage, random);
		}
    }
}
