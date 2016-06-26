using System.Windows.Forms;

namespace ForestAdventure
{
    partial class Forest
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Forest));
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.label1 = new System.Windows.Forms.Label();
            this.batHUD = new System.Windows.Forms.Label();
            this.ghostHUD = new System.Windows.Forms.Label();
            this.ghoulHUD = new System.Windows.Forms.Label();
            this.playerHitPointsLabel = new System.Windows.Forms.Label();
            this.batHitPointsLabel = new System.Windows.Forms.Label();
            this.ghostHitPointsLabel = new System.Windows.Forms.Label();
            this.ghoulHitPointsLabel = new System.Windows.Forms.Label();
            this.moveBox = new System.Windows.Forms.GroupBox();
            this.moveUpButton = new System.Windows.Forms.Button();
            this.moveLeftButton = new System.Windows.Forms.Button();
            this.moveRightButton = new System.Windows.Forms.Button();
            this.moveDownButton = new System.Windows.Forms.Button();
            this.attackBox = new System.Windows.Forms.GroupBox();
            this.attackUpButton = new System.Windows.Forms.Button();
            this.attackDownButton = new System.Windows.Forms.Button();
            this.attackLeftButton = new System.Windows.Forms.Button();
            this.attackRightButton = new System.Windows.Forms.Button();
            this.Player = new System.Windows.Forms.PictureBox();
            this.bat = new System.Windows.Forms.PictureBox();
            this.ghost = new System.Windows.Forms.PictureBox();
            this.ghoul = new System.Windows.Forms.PictureBox();
            this.potionRed = new System.Windows.Forms.PictureBox();
            this.potionBlue = new System.Windows.Forms.PictureBox();
            this.sword = new System.Windows.Forms.PictureBox();
            this.bow = new System.Windows.Forms.PictureBox();
            this.mace = new System.Windows.Forms.PictureBox();
            this.maceInventory = new System.Windows.Forms.PictureBox();
            this.bowInventory = new System.Windows.Forms.PictureBox();
            this.swordInventory = new System.Windows.Forms.PictureBox();
            this.potionBlueInventory = new System.Windows.Forms.PictureBox();
            this.potionRedInventory = new System.Windows.Forms.PictureBox();
            this.doubleClickTimer = new System.Windows.Forms.Timer(this.components);
            this.attackToggleButton = new ForestAdventure.InputButton();
            this.tableLayoutPanel1.SuspendLayout();
            this.moveBox.SuspendLayout();
            this.attackBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Player)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bat)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ghost)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ghoul)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.potionRed)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.potionBlue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.sword)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bow)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mace)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.maceInventory)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bowInventory)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.swordInventory)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.potionBlueInventory)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.potionRedInventory)).BeginInit();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.AutoSize = true;
            this.tableLayoutPanel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tableLayoutPanel1.BackColor = System.Drawing.Color.Transparent;
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25.30612F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 74.69388F));
            this.tableLayoutPanel1.Controls.Add(this.label1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.batHUD, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.ghostHUD, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.ghoulHUD, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.playerHitPointsLabel, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.batHitPointsLabel, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.ghostHitPointsLabel, 1, 2);
            this.tableLayoutPanel1.Controls.Add(this.ghoulHitPointsLabel, 1, 3);
            this.tableLayoutPanel1.ForeColor = System.Drawing.Color.Coral;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(716, 424);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 4;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 18F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(261, 80);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Lavender;
            this.label1.Location = new System.Drawing.Point(4, 0);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(58, 20);
            this.label1.TabIndex = 0;
            this.label1.Text = "Player";
            // 
            // batHUD
            // 
            this.batHUD.AutoSize = true;
            this.batHUD.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.batHUD.ForeColor = System.Drawing.Color.Lavender;
            this.batHUD.Location = new System.Drawing.Point(4, 20);
            this.batHUD.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.batHUD.Name = "batHUD";
            this.batHUD.Size = new System.Drawing.Size(37, 20);
            this.batHUD.TabIndex = 1;
            this.batHUD.Text = "Bat";
            // 
            // ghostHUD
            // 
            this.ghostHUD.AutoSize = true;
            this.ghostHUD.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ghostHUD.ForeColor = System.Drawing.Color.Lavender;
            this.ghostHUD.Location = new System.Drawing.Point(4, 40);
            this.ghostHUD.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.ghostHUD.Name = "ghostHUD";
            this.ghostHUD.Size = new System.Drawing.Size(58, 20);
            this.ghostHUD.TabIndex = 2;
            this.ghostHUD.Text = "Ghost";
            // 
            // ghoulHUD
            // 
            this.ghoulHUD.AutoSize = true;
            this.ghoulHUD.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ghoulHUD.ForeColor = System.Drawing.Color.Lavender;
            this.ghoulHUD.Location = new System.Drawing.Point(4, 60);
            this.ghoulHUD.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.ghoulHUD.Name = "ghoulHUD";
            this.ghoulHUD.Size = new System.Drawing.Size(57, 20);
            this.ghoulHUD.TabIndex = 3;
            this.ghoulHUD.Text = "Ghoul";
            // 
            // playerHitPointsLabel
            // 
            this.playerHitPointsLabel.AutoSize = true;
            this.playerHitPointsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.playerHitPointsLabel.ForeColor = System.Drawing.Color.Lavender;
            this.playerHitPointsLabel.Location = new System.Drawing.Point(70, 0);
            this.playerHitPointsLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.playerHitPointsLabel.Name = "playerHitPointsLabel";
            this.playerHitPointsLabel.Size = new System.Drawing.Size(130, 20);
            this.playerHitPointsLabel.TabIndex = 4;
            this.playerHitPointsLabel.Text = "playerHitPoints";
            // 
            // batHitPointsLabel
            // 
            this.batHitPointsLabel.AutoSize = true;
            this.batHitPointsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.batHitPointsLabel.ForeColor = System.Drawing.Color.Lavender;
            this.batHitPointsLabel.Location = new System.Drawing.Point(70, 20);
            this.batHitPointsLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.batHitPointsLabel.Name = "batHitPointsLabel";
            this.batHitPointsLabel.Size = new System.Drawing.Size(108, 20);
            this.batHitPointsLabel.TabIndex = 5;
            this.batHitPointsLabel.Text = "batHitPoints";
            // 
            // ghostHitPointsLabel
            // 
            this.ghostHitPointsLabel.AutoSize = true;
            this.ghostHitPointsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ghostHitPointsLabel.ForeColor = System.Drawing.Color.Lavender;
            this.ghostHitPointsLabel.Location = new System.Drawing.Point(70, 40);
            this.ghostHitPointsLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.ghostHitPointsLabel.Name = "ghostHitPointsLabel";
            this.ghostHitPointsLabel.Size = new System.Drawing.Size(127, 20);
            this.ghostHitPointsLabel.TabIndex = 6;
            this.ghostHitPointsLabel.Text = "ghostHitPoints";
            // 
            // ghoulHitPointsLabel
            // 
            this.ghoulHitPointsLabel.AutoSize = true;
            this.ghoulHitPointsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ghoulHitPointsLabel.ForeColor = System.Drawing.Color.Lavender;
            this.ghoulHitPointsLabel.Location = new System.Drawing.Point(70, 60);
            this.ghoulHitPointsLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.ghoulHitPointsLabel.Name = "ghoulHitPointsLabel";
            this.ghoulHitPointsLabel.Size = new System.Drawing.Size(126, 20);
            this.ghoulHitPointsLabel.TabIndex = 7;
            this.ghoulHitPointsLabel.Text = "ghoulHitPoints";
            // 
            // moveBox
            // 
            this.moveBox.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.moveBox.BackColor = System.Drawing.Color.Transparent;
            this.moveBox.Controls.Add(this.moveUpButton);
            this.moveBox.Controls.Add(this.moveLeftButton);
            this.moveBox.Controls.Add(this.moveRightButton);
            this.moveBox.Controls.Add(this.moveDownButton);
            this.moveBox.Location = new System.Drawing.Point(604, 552);
            this.moveBox.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.moveBox.Name = "moveBox";
            this.moveBox.Padding = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.moveBox.Size = new System.Drawing.Size(148, 88);
            this.moveBox.TabIndex = 1;
            this.moveBox.TabStop = false;
            this.moveBox.Text = "Move";
            // 
            // moveUpButton
            // 
            this.moveUpButton.AutoSize = true;
            this.moveUpButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.moveUpButton.Location = new System.Drawing.Point(52, 21);
            this.moveUpButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.moveUpButton.Name = "moveUpButton";
            this.moveUpButton.Size = new System.Drawing.Size(36, 28);
            this.moveUpButton.TabIndex = 3;
            this.moveUpButton.Text = "↑";
            this.moveUpButton.UseVisualStyleBackColor = true;
            this.moveUpButton.Click += new System.EventHandler(this.moveUpButton_Click);
            // 
            // moveLeftButton
            // 
            this.moveLeftButton.AutoSize = true;
            this.moveLeftButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.moveLeftButton.Location = new System.Drawing.Point(8, 38);
            this.moveLeftButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.moveLeftButton.Name = "moveLeftButton";
            this.moveLeftButton.Size = new System.Drawing.Size(36, 28);
            this.moveLeftButton.TabIndex = 4;
            this.moveLeftButton.Text = "←";
            this.moveLeftButton.UseVisualStyleBackColor = true;
            this.moveLeftButton.Click += new System.EventHandler(this.moveLeftButton_Click);
            // 
            // moveRightButton
            // 
            this.moveRightButton.AutoSize = true;
            this.moveRightButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.moveRightButton.Location = new System.Drawing.Point(100, 38);
            this.moveRightButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.moveRightButton.Name = "moveRightButton";
            this.moveRightButton.Size = new System.Drawing.Size(36, 28);
            this.moveRightButton.TabIndex = 5;
            this.moveRightButton.Text = "→";
            this.moveRightButton.UseVisualStyleBackColor = true;
            this.moveRightButton.Click += new System.EventHandler(this.moveRightButton_Click);
            // 
            // moveDownButton
            // 
            this.moveDownButton.AutoSize = true;
            this.moveDownButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.moveDownButton.Location = new System.Drawing.Point(52, 58);
            this.moveDownButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.moveDownButton.Name = "moveDownButton";
            this.moveDownButton.Size = new System.Drawing.Size(36, 28);
            this.moveDownButton.TabIndex = 6;
            this.moveDownButton.Text = "↓";
            this.moveDownButton.UseVisualStyleBackColor = true;
            this.moveDownButton.Click += new System.EventHandler(this.moveDownButton_Click);
            // 
            // attackBox
            // 
            this.attackBox.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.attackBox.BackColor = System.Drawing.Color.Transparent;
            this.attackBox.Controls.Add(this.attackUpButton);
            this.attackBox.Controls.Add(this.attackDownButton);
            this.attackBox.Controls.Add(this.attackLeftButton);
            this.attackBox.Controls.Add(this.attackRightButton);
            this.attackBox.Location = new System.Drawing.Point(748, 550);
            this.attackBox.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.attackBox.Name = "attackBox";
            this.attackBox.Padding = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.attackBox.Size = new System.Drawing.Size(146, 88);
            this.attackBox.TabIndex = 2;
            this.attackBox.TabStop = false;
            this.attackBox.Text = "Attack";
            // 
            // attackUpButton
            // 
            this.attackUpButton.AutoSize = true;
            this.attackUpButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.attackUpButton.Location = new System.Drawing.Point(52, 21);
            this.attackUpButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.attackUpButton.Name = "attackUpButton";
            this.attackUpButton.Size = new System.Drawing.Size(36, 28);
            this.attackUpButton.TabIndex = 7;
            this.attackUpButton.Text = "↑";
            this.attackUpButton.UseVisualStyleBackColor = true;
            this.attackUpButton.Click += new System.EventHandler(this.attackUpButton_Click);
            // 
            // attackDownButton
            // 
            this.attackDownButton.AutoSize = true;
            this.attackDownButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.attackDownButton.Location = new System.Drawing.Point(52, 58);
            this.attackDownButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.attackDownButton.Name = "attackDownButton";
            this.attackDownButton.Size = new System.Drawing.Size(36, 28);
            this.attackDownButton.TabIndex = 10;
            this.attackDownButton.Text = "↓";
            this.attackDownButton.UseVisualStyleBackColor = true;
            this.attackDownButton.Click += new System.EventHandler(this.attackDownButton_Click);
            // 
            // attackLeftButton
            // 
            this.attackLeftButton.AutoSize = true;
            this.attackLeftButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.attackLeftButton.Location = new System.Drawing.Point(8, 38);
            this.attackLeftButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.attackLeftButton.Name = "attackLeftButton";
            this.attackLeftButton.Size = new System.Drawing.Size(36, 28);
            this.attackLeftButton.TabIndex = 8;
            this.attackLeftButton.Text = "←";
            this.attackLeftButton.UseVisualStyleBackColor = true;
            this.attackLeftButton.Click += new System.EventHandler(this.attackLeftButton_Click);
            // 
            // attackRightButton
            // 
            this.attackRightButton.AutoSize = true;
            this.attackRightButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.attackRightButton.Location = new System.Drawing.Point(98, 38);
            this.attackRightButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.attackRightButton.Name = "attackRightButton";
            this.attackRightButton.Size = new System.Drawing.Size(36, 28);
            this.attackRightButton.TabIndex = 9;
            this.attackRightButton.Text = "→";
            this.attackRightButton.UseVisualStyleBackColor = true;
            this.attackRightButton.Click += new System.EventHandler(this.attackRightButton_Click);
            // 
            // Player
            // 
            this.Player.BackColor = System.Drawing.Color.Transparent;
            this.Player.Image = ((System.Drawing.Image)(resources.GetObject("Player.Image")));
            this.Player.Location = new System.Drawing.Point(216, 190);
            this.Player.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.Player.Name = "Player";
            this.Player.Size = new System.Drawing.Size(38, 34);
            this.Player.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.Player.TabIndex = 3;
            this.Player.TabStop = false;
            // 
            // bat
            // 
            this.bat.BackColor = System.Drawing.Color.Transparent;
            this.bat.Image = ((System.Drawing.Image)(resources.GetObject("bat.Image")));
            this.bat.Location = new System.Drawing.Point(265, 190);
            this.bat.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.bat.Name = "bat";
            this.bat.Size = new System.Drawing.Size(38, 34);
            this.bat.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.bat.TabIndex = 4;
            this.bat.TabStop = false;
            this.bat.Visible = false;
            // 
            // ghost
            // 
            this.ghost.BackColor = System.Drawing.Color.Transparent;
            this.ghost.Image = ((System.Drawing.Image)(resources.GetObject("ghost.Image")));
            this.ghost.Location = new System.Drawing.Point(310, 190);
            this.ghost.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.ghost.Name = "ghost";
            this.ghost.Size = new System.Drawing.Size(38, 34);
            this.ghost.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.ghost.TabIndex = 5;
            this.ghost.TabStop = false;
            this.ghost.Visible = false;
            // 
            // ghoul
            // 
            this.ghoul.BackColor = System.Drawing.Color.Transparent;
            this.ghoul.Image = ((System.Drawing.Image)(resources.GetObject("ghoul.Image")));
            this.ghoul.Location = new System.Drawing.Point(360, 190);
            this.ghoul.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.ghoul.Name = "ghoul";
            this.ghoul.Size = new System.Drawing.Size(38, 34);
            this.ghoul.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.ghoul.TabIndex = 6;
            this.ghoul.TabStop = false;
            this.ghoul.Visible = false;
            // 
            // potionRed
            // 
            this.potionRed.BackColor = System.Drawing.Color.Transparent;
            this.potionRed.Image = ((System.Drawing.Image)(resources.GetObject("potionRed.Image")));
            this.potionRed.Location = new System.Drawing.Point(592, 190);
            this.potionRed.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.potionRed.Name = "potionRed";
            this.potionRed.Size = new System.Drawing.Size(38, 34);
            this.potionRed.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.potionRed.TabIndex = 7;
            this.potionRed.TabStop = false;
            this.potionRed.Visible = false;
            // 
            // potionBlue
            // 
            this.potionBlue.BackColor = System.Drawing.Color.Transparent;
            this.potionBlue.Image = ((System.Drawing.Image)(resources.GetObject("potionBlue.Image")));
            this.potionBlue.Location = new System.Drawing.Point(548, 190);
            this.potionBlue.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.potionBlue.Name = "potionBlue";
            this.potionBlue.Size = new System.Drawing.Size(38, 34);
            this.potionBlue.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.potionBlue.TabIndex = 8;
            this.potionBlue.TabStop = false;
            this.potionBlue.Visible = false;
            // 
            // sword
            // 
            this.sword.BackColor = System.Drawing.Color.Transparent;
            this.sword.Image = ((System.Drawing.Image)(resources.GetObject("sword.Image")));
            this.sword.Location = new System.Drawing.Point(405, 190);
            this.sword.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.sword.Name = "sword";
            this.sword.Size = new System.Drawing.Size(38, 34);
            this.sword.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.sword.TabIndex = 9;
            this.sword.TabStop = false;
            // 
            // bow
            // 
            this.bow.BackColor = System.Drawing.Color.Transparent;
            this.bow.Image = ((System.Drawing.Image)(resources.GetObject("bow.Image")));
            this.bow.Location = new System.Drawing.Point(450, 190);
            this.bow.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.bow.Name = "bow";
            this.bow.Size = new System.Drawing.Size(38, 34);
            this.bow.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.bow.TabIndex = 10;
            this.bow.TabStop = false;
            this.bow.Visible = false;
            // 
            // mace
            // 
            this.mace.BackColor = System.Drawing.Color.Transparent;
            this.mace.Image = ((System.Drawing.Image)(resources.GetObject("mace.Image")));
            this.mace.Location = new System.Drawing.Point(495, 190);
            this.mace.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.mace.Name = "mace";
            this.mace.Size = new System.Drawing.Size(38, 34);
            this.mace.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.mace.TabIndex = 11;
            this.mace.TabStop = false;
            this.mace.Visible = false;
            // 
            // maceInventory
            // 
            this.maceInventory.BackColor = System.Drawing.Color.Transparent;
            this.maceInventory.Image = ((System.Drawing.Image)(resources.GetObject("maceInventory.Image")));
            this.maceInventory.Location = new System.Drawing.Point(387, 568);
            this.maceInventory.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.maceInventory.Name = "maceInventory";
            this.maceInventory.Size = new System.Drawing.Size(62, 56);
            this.maceInventory.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.maceInventory.TabIndex = 16;
            this.maceInventory.TabStop = false;
            this.maceInventory.Visible = false;
            this.maceInventory.Click += new System.EventHandler(this.maceInventory_Click);
            // 
            // bowInventory
            // 
            this.bowInventory.BackColor = System.Drawing.Color.Transparent;
            this.bowInventory.Image = ((System.Drawing.Image)(resources.GetObject("bowInventory.Image")));
            this.bowInventory.Location = new System.Drawing.Point(317, 568);
            this.bowInventory.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.bowInventory.Name = "bowInventory";
            this.bowInventory.Size = new System.Drawing.Size(62, 56);
            this.bowInventory.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.bowInventory.TabIndex = 15;
            this.bowInventory.TabStop = false;
            this.bowInventory.Visible = false;
            this.bowInventory.Click += new System.EventHandler(this.bowInventory_Click);
            // 
            // swordInventory
            // 
            this.swordInventory.BackColor = System.Drawing.Color.Transparent;
            this.swordInventory.Image = ((System.Drawing.Image)(resources.GetObject("swordInventory.Image")));
            this.swordInventory.Location = new System.Drawing.Point(247, 568);
            this.swordInventory.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.swordInventory.Name = "swordInventory";
            this.swordInventory.Size = new System.Drawing.Size(62, 56);
            this.swordInventory.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.swordInventory.TabIndex = 14;
            this.swordInventory.TabStop = false;
            this.swordInventory.Visible = false;
            this.swordInventory.Click += new System.EventHandler(this.swordInventory_Click);
            // 
            // potionBlueInventory
            // 
            this.potionBlueInventory.BackColor = System.Drawing.Color.Transparent;
            this.potionBlueInventory.Image = ((System.Drawing.Image)(resources.GetObject("potionBlueInventory.Image")));
            this.potionBlueInventory.Location = new System.Drawing.Point(457, 568);
            this.potionBlueInventory.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.potionBlueInventory.Name = "potionBlueInventory";
            this.potionBlueInventory.Size = new System.Drawing.Size(62, 56);
            this.potionBlueInventory.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.potionBlueInventory.TabIndex = 13;
            this.potionBlueInventory.TabStop = false;
            this.potionBlueInventory.Visible = false;
            this.potionBlueInventory.Click += new System.EventHandler(this.potionBlueInventory_Click);
            // 
            // potionRedInventory
            // 
            this.potionRedInventory.BackColor = System.Drawing.Color.Transparent;
            this.potionRedInventory.Image = ((System.Drawing.Image)(resources.GetObject("potionRedInventory.Image")));
            this.potionRedInventory.Location = new System.Drawing.Point(527, 568);
            this.potionRedInventory.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.potionRedInventory.Name = "potionRedInventory";
            this.potionRedInventory.Size = new System.Drawing.Size(62, 56);
            this.potionRedInventory.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.potionRedInventory.TabIndex = 12;
            this.potionRedInventory.TabStop = false;
            this.potionRedInventory.Visible = false;
            this.potionRedInventory.Click += new System.EventHandler(this.potionRedInventory_Click);
            // 
            // doubleClickTimer
            // 
            this.doubleClickTimer.Interval = 500;
            this.doubleClickTimer.Tick += new System.EventHandler(this.doubleClickTimer_Tick);
            // 
            // attackToggleButton
            // 
            this.attackToggleButton.Location = new System.Drawing.Point(0, 0);
            this.attackToggleButton.Name = "attackToggleButton";
            this.attackToggleButton.Size = new System.Drawing.Size(75, 23);
            this.attackToggleButton.TabIndex = 0;
            this.attackToggleButton.Click += new System.EventHandler(this.moveLeftButton_Click);
            this.attackToggleButton.KeyDown += new System.Windows.Forms.KeyEventHandler(this.attackToggleButton_KeyDown);
            // 
            // Dungeon
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(1175, 681);
            this.Controls.Add(this.Player);
            this.Controls.Add(this.maceInventory);
            this.Controls.Add(this.bowInventory);
            this.Controls.Add(this.swordInventory);
            this.Controls.Add(this.potionBlueInventory);
            this.Controls.Add(this.potionRedInventory);
            this.Controls.Add(this.ghoul);
            this.Controls.Add(this.ghost);
            this.Controls.Add(this.bat);
            this.Controls.Add(this.attackBox);
            this.Controls.Add(this.moveBox);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.mace);
            this.Controls.Add(this.bow);
            this.Controls.Add(this.sword);
            this.Controls.Add(this.potionBlue);
            this.Controls.Add(this.potionRed);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.MaximizeBox = false;
            this.Name = "Dungeon";
            this.Text = "Forest Adventure";
            this.Load += new System.EventHandler(this.Forest_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Dungeon_KeyDown);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.moveBox.ResumeLayout(false);
            this.moveBox.PerformLayout();
            this.attackBox.ResumeLayout(false);
            this.attackBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Player)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bat)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ghost)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ghoul)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.potionRed)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.potionBlue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.sword)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bow)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mace)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.maceInventory)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bowInventory)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.swordInventory)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.potionBlueInventory)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.potionRedInventory)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label batHUD;
        private System.Windows.Forms.Label ghostHUD;
        private System.Windows.Forms.Label ghoulHUD;
        private System.Windows.Forms.Label playerHitPointsLabel;
        private System.Windows.Forms.Label batHitPointsLabel;
        private System.Windows.Forms.Label ghostHitPointsLabel;
        private System.Windows.Forms.Label ghoulHitPointsLabel;
        private System.Windows.Forms.GroupBox moveBox;
        private System.Windows.Forms.GroupBox attackBox;

        //TESTING OUT DOUBLECLICK BUTTON HERE!
        //private DoubleClickButton doubleClickTest;
        //TESTING OUT DOUBLECLICK BUTTON HERE!

        private InputButton attackToggleButton;

        private System.Windows.Forms.Button moveUpButton;
        private System.Windows.Forms.Button moveLeftButton;
        private System.Windows.Forms.Button moveRightButton;
        private System.Windows.Forms.Button moveDownButton;
        private System.Windows.Forms.Button attackUpButton;
        private System.Windows.Forms.Button attackDownButton;
        private System.Windows.Forms.Button attackLeftButton;
        private System.Windows.Forms.Button attackRightButton;
        private System.Windows.Forms.PictureBox Player;
        private System.Windows.Forms.PictureBox bat;
        private System.Windows.Forms.PictureBox ghost;
        private System.Windows.Forms.PictureBox ghoul;
        private System.Windows.Forms.PictureBox potionRed;
        private System.Windows.Forms.PictureBox potionBlue;
        private System.Windows.Forms.PictureBox sword;
        private System.Windows.Forms.PictureBox bow;
        private System.Windows.Forms.PictureBox mace;
        private System.Windows.Forms.PictureBox maceInventory;
        private System.Windows.Forms.PictureBox bowInventory;
        private System.Windows.Forms.PictureBox swordInventory;
        private System.Windows.Forms.PictureBox potionBlueInventory;
        private System.Windows.Forms.PictureBox potionRedInventory;
        private System.Windows.Forms.Timer doubleClickTimer;
    }
}

