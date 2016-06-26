using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ForestAdventure
{
    // didn't add comments, here they are:
	//TODO: Move all Solution Items into Properties/Resources.resx. This is the place for all resources to be used in the project.
	// GW ANSWER: So I just highlighted everything, then dragged it into "Properties" in the solution explorer. is that correct?
	//Inventory items, Move controls and Attack controls should be placed on the "papirus", and not on the dangeon region.
	// GW ANSWER: the picturebox locations change when the game is executed. They look weird in the IDE, but move into place when running the game.
	public partial class Forest : Form
	{
		private Game game;
		private Random random = new Random();
        private bool isDoubleClick = false;
        private bool Attack = false;

        public Forest()
        {
            InitializeComponent();
        }      

        private void Forest_Load(object sender, EventArgs e)
        {
            game = new Game(new Rectangle(58, 50, 561, 219));
            game.NewLevel(random);
            UpdateCharacters();
        }

		public void UpdateCharacters()
		{
			Player.Location = game.PlayerLocation;
			playerHitPointsLabel.Text = game.PlayerHitPoints.ToString();
            batHitPointsLabel.Visible = false;
            batHUD.Visible = false;
            ghostHitPointsLabel.Visible = false;
            ghostHUD.Visible = false;
            ghoulHitPointsLabel.Visible = false;
            ghoulHUD.Visible = false;
            bool showBat = false;
			bool showGhost = false;
			bool showGhoul = false;
			int enemiesShown = 0;

			foreach (Enemy enemy in game.Enemies)
			{
				if (enemy is Bat)
				{
					bat.Location = enemy.Location;
                    batHitPointsLabel.Visible = true;
                    batHUD.Visible = true;
					batHitPointsLabel.Text = enemy.HitPoints.ToString();
					if (enemy.HitPoints > 0)
					{
						showBat = true;
						enemiesShown++;
					}
					if (enemy.Dead)
					{
						showBat = false;
						enemiesShown--;
					}
					bat.Visible = showBat;
				}

                if (enemy is Ghost)
                {
                    ghost.Location = enemy.Location;
                    ghostHitPointsLabel.Visible = true;
                    ghostHUD.Visible = true;
                    ghostHitPointsLabel.Text = enemy.HitPoints.ToString();
                    if (enemy.HitPoints > 0)
                    {
                        showGhost = true;
                        enemiesShown++;
                    }
                    if (enemy.Dead)
                    {
                        showGhost = false;
                        enemiesShown--;
                    }
                    ghost.Visible = showGhost;
                }

                if (enemy is Ghoul)
                {
                    ghoul.Location = enemy.Location;
                    ghoulHitPointsLabel.Visible = true;
                    ghoulHUD.Visible = true;
                    ghoulHitPointsLabel.Text = enemy.HitPoints.ToString();
                    if (enemy.HitPoints > 0)
                    {
                        showGhoul = true;
                        enemiesShown++;
                    }
                    if (enemy.Dead)
                    {
                        showGhoul = false;
                        enemiesShown--;
                    }
                    ghoul.Visible = showGhoul;
                }
			}

			sword.Visible = false;
			bow.Visible = false;
			potionRed.Visible = false;
			potionBlue.Visible = false;
			mace.Visible = false;
			Control weaponControl = null;
			switch (game.WeaponInRoom.Name)
			{
				case "Sword":
					weaponControl = sword; break;
				case "Bow":
					weaponControl = bow; break;
				case "Mace":
					weaponControl = mace; break;
                case "Blue Potion":
                    weaponControl = potionBlue; break;
                case "Red Potion":
                    weaponControl = potionRed; break;
				default: break;
			}
			weaponControl.Visible = true;

			swordInventory.Visible = game.CheckPlayerInventory("Sword");
			bowInventory.Visible = game.CheckPlayerInventory("Bow");
			maceInventory.Visible = game.CheckPlayerInventory("Mace");
			potionBlueInventory.Visible = game.CheckPlayerInventory("Blue Potion");
			potionRedInventory.Visible = game.CheckPlayerInventory("Red Potion");

			weaponControl.Location = game.WeaponInRoom.Location;
			if (game.WeaponInRoom.PickedUp)
				weaponControl.Visible = false;
			else
				weaponControl.Visible = true;
			if (game.PlayerHitPoints <= 0)
			{
				MessageBox.Show("You died");
				Application.Exit();
            }

                if (enemiesShown < 1)
                {
                    MessageBox.Show("You have defeated the enemies on this level");
                    game.NewLevel(random);
                    UpdateCharacters();
                }
		}

        #region Single Vs Double Click
        private void doubleClickTimer_Tick(object sender, EventArgs e)
        {
            doubleClickTimer.Stop();
            if (isDoubleClick)
            {
                Attack = true;
             //   MessageBox.Show("you just double clicked!");
                isDoubleClick = false;
            }
            else
            {
                Attack = false;
              //  MessageBox.Show("you just single clicked!");
            }
        }

        private void doubleClickTest_Click(object sender, EventArgs e)
        {
            doubleClickTimer.Start();
        }
        private void doubleClickTest_DoubleClick(object sender, EventArgs e)
        {
            isDoubleClick = true;
        }
        #endregion

		#region Move Button Input
        #region Old Dble vs Single Clk buttons
       /* private void moveDownButton_Click(object sender, EventArgs e)
		{
            doubleClickTimer.Start();
            if (!Attack)
            {
                game.Move(Direction.Down, random);
            }
            else
            return;
            UpdateCharacters();
		}

        private void moveDownButton_DoubleClick(object sender, EventArgs e)
        {
            isDoubleClick = true;
            if (Attack)
            {
                game.Attack(Direction.Down, random);
            }
            UpdateCharacters();
        }
        */
        #endregion

        private void moveDownButton_Click(object sender, EventArgs e)
        {
            if (!attackToggle)
            {
                game.Move(Direction.Down, random);
                UpdateCharacters();
            }
            else
            {
                game.Attack(Direction.Down, random);
                UpdateCharacters();
            }
            this.Focus();
        }

        private void moveUpButton_Click(object sender, EventArgs e)
		{
			game.Move(Direction.Up, random);
			UpdateCharacters();
            this.Focus();
		}

		private void moveLeftButton_Click(object sender, EventArgs e)
		{
			game.Move(Direction.Left, random);
			UpdateCharacters();
            this.Focus();
		}

		private void moveRightButton_Click(object sender, EventArgs e)
		{
			game.Move(Direction.Right, random);
			UpdateCharacters();
            this.Focus();
		} 
		#endregion

        #region Attack Buttons
        private void attackDownButton_Click(object sender, EventArgs e)
        {
            game.Attack(Direction.Down, random);
            UpdateCharacters();
            this.Focus();
        }

        private void attackLeftButton_Click(object sender, EventArgs e)
        {
            game.Attack(Direction.Left, random);
            UpdateCharacters();
            this.Focus();
        }

        private void attackUpButton_Click(object sender, EventArgs e)
        {
            game.Attack(Direction.Up, random);
            UpdateCharacters();
            this.Focus();
        }

        private void attackRightButton_Click(object sender, EventArgs e)
        {
            game.Attack(Direction.Right, random);
            UpdateCharacters();
            this.Focus();
        }
        #endregion   

		#region Inventory Section
        private void UpdateInventorySelection()
        {
            swordInventory.BorderStyle = BorderStyle.None;
            bowInventory.BorderStyle = BorderStyle.None;
            maceInventory.BorderStyle = BorderStyle.None;
            potionBlueInventory.BorderStyle = BorderStyle.None;
            potionRedInventory.BorderStyle = BorderStyle.None;
            this.Focus();
        }

        private void potionSelected()
        {
            attackUpButton.Text = " ? ";
            attackRightButton.Text = " ? ";
            attackLeftButton.Text = " ? ";
            attackDownButton.Text = " ? ";
            attackBox.Text = "Drink Potion";
            this.Focus();
        }

        private void resetHUD() 
        {
            attackUpButton.Text = "↑";
            attackRightButton.Text = "→";
            attackLeftButton.Text = "←";
            attackDownButton.Text = "↓";
            attackBox.Text = "Attack";
            this.Focus();
        }

		private void swordInventory_Click(object sender, EventArgs e)
		{
            resetHUD();
			game.Equip("Sword");
			UpdateInventorySelection();
			swordInventory.BorderStyle = BorderStyle.Fixed3D;
            this.Focus();
		}

		private void bowInventory_Click(object sender, EventArgs e)
		{
            resetHUD();
            game.Equip("Bow");
			UpdateInventorySelection();
			bowInventory.BorderStyle = BorderStyle.Fixed3D;
            this.Focus();
		}

		private void maceInventory_Click(object sender, EventArgs e)
		{
            game.Equip("Mace");
            resetHUD();
			UpdateInventorySelection();
			maceInventory.BorderStyle = BorderStyle.Fixed3D;
            this.Focus();
		}

		private void potionBlueInventory_Click(object sender, EventArgs e)
		{
			UpdateInventorySelection();
            potionSelected();
            game.Equip("Blue Potion");
			potionBlueInventory.BorderStyle = BorderStyle.Fixed3D;
            this.Focus();
		}

		private void potionRedInventory_Click(object sender, EventArgs e)
		{
			UpdateInventorySelection();
            potionSelected();
            game.Equip("Red Potion");
			potionRedInventory.BorderStyle = BorderStyle.Fixed3D;
            this.Focus();
		} 
		#endregion

        private bool attackToggle = false;

        private void attackToggleButton_KeyDown(object sender, KeyEventArgs e)
        {
            e.Handled = true;
            if (!attackToggle)
            {
                if (e.KeyCode == Keys.Control)
                    attackToggle = true;
            }
            else
            {
                if (e.KeyCode == Keys.Control)
                    attackToggle = false;
            }
            this.Focus();
        }

        private void Dungeon_KeyDown(object sender, KeyEventArgs e)
        {
            if (!attackToggle)
            {
                if (e.KeyCode == Keys.Control)
                    attackToggle = true;
            }
            else
            {
                if (e.KeyCode == Keys.Control)
                    attackToggle = false;
            }
        }

        //private void Dungeon_KeyPress(object sender, KeyPressEventArgs e)
        //{
        //    char pressedKey = e.KeyChar;
        //    if (!AttackToggle)
        //    {
        //        if (pressedKey is (char)Keys.ControlKey)
        //            AttackToggle = true;
        //    }
        //    else
        //    {
        //        if (pressedKey == Keys.ControlKey)
        //            AttackToggle = false;
        //    }
        //}
        }
}