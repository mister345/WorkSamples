using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace ForestAdventure
{
	class Bat : Enemy
	{
		private const int maxDamage = 3;

		public Bat(Game game, Point location)
			: base(game, location, 6)
		{ }
		
		public override void Move(Random random)
		{
			if (random.Next(3) == 1)
				base.location = Move(FindPlayerDirection(game.PlayerLocation), game.Boundaries);
			else
				base.location = Move((Direction)random.Next(4), game.Boundaries);

			if (NearPlayer())
				game.HitPlayer(maxDamage, random);
		}
	}
}