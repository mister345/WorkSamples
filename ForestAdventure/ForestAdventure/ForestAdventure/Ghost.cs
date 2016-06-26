using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace ForestAdventure
{
    class Ghost: Enemy
    {
        private const int maxDamage = 5;

		public Ghost(Game game, Point location)
			: base(game, location, 8)
		{ }
		
		public override void Move(Random random)
		{
			if (random.Next(3) == 1)
				base.location = Move(FindPlayerDirection(game.PlayerLocation), game.Boundaries);
			else
			if (NearPlayer())
				game.HitPlayer(maxDamage, random);
		}
    }
}
