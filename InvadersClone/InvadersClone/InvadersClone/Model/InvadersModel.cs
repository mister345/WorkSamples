/******************************************************************************************
* File:           InvadersModel.cs                                                        *
*                                                                                         *
* Author:         Gregory Weiner                                                          *
* Version:        1.0 8.01.2012                                                           *
* Last Modified:  2.02.2013                                                               *
* License:        Free Software(GNU License Included)                                     *
* Purpose:        This is a clone of the classic space shooter game 'Invaders,'           *
*                 written from scratch in C# for the WPF platform. A real-time            *
*                 shooter game, the player scores points by destroying incoming           *
*                 alien invaders, and loses if the invaders collide with the player       *
*                 or reach the bottom of the screen.                                      *
*                                                                                         *
*                 This Application follows the model-view-viewmodel design pattern,       *
*                 in which the game logic occurs in the model layer(written in C#),       *
*                 the display and binding logic happens in the view layer (written in     *
*                 xaml), and the viewmodel is the pipeline that provides communication    *
*                 between the two aforementioned layers.This allows for better            *
*                 portability of the business logic, and better compartmentalization of   *
*                 code overall.                                                           *
*                                                                                         *
* Description:    This is the Model Layer of the Program, written in C#,                  *
*                 where the main business logic happens.                                  *
*                                                                                         *
* Input:          Arrow keys for movement, Space key to shoot, P to pause                 *
*                                                                                         *
* Requirements:   Requires a functioning keyboard for input.                              *
*                 Runs in windowed mode.                                                  *
*                                                                                         *
*******************************************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Threading;

namespace Invaders.Model
{
    class InvadersModel
    {
        public readonly static Size PlayAreaSize = new Size(400, 300);
        public const int MaximumPlayerShots = 5;
        public const int InitialStarCount = 50;
        public const int MaximumInvadersInWave = 60;
        public const double moveInterval = 30;

        private readonly Random _random = new Random();

        private int score;
        public string Score
        {
            get
            {
                return "SCORE: " + score;
            }
        }
        public int Wave { get; private set; }
        public int Lives { get; private set; }

        Random random = new Random();

        public bool GameOver { get; private set; }

        private DateTime? _playerDied = null;
        public bool PlayerDying
        {
            get { return _playerDied.HasValue; }
        }

        public bool GamePaused = false;

        private Player _player;

        private readonly List<Shot> _playerShots = new List<Shot>();
        private readonly List<Shot> _invaderShots = new List<Shot>();
        public readonly List<Point> _stars = new List<Point>();
        public readonly List<Invader> _invaders = new List<Invader>();

        private Direction _invaderDirection = Direction.Right;
        private bool _justMovedDown = false;

        private DateTime _lastUpdated = DateTime.MinValue;
        // this has to be set to SOME value (minimum), 
        // otherwise Update field will never get executed

        public InvadersModel()
        {
            EndGame();
            StartGame();
        }
        public void EndGame()
        {
            GameOver = true;
        }

        public void StartGame()
        {
            GameOver = false;

            Lives = 5;
            _playerDied = null;

            _invaders.Clear();
            _playerShots.Clear();

            _invaderShots.Clear();

            foreach (Shot shot in _invaderShots)
            {
                OnShotMoved(shot, false, false);
            }

            foreach (Point star in _stars)
            {
                OnStarChanged(star, false);
            }
            _stars.Clear();

            CreateStars();

            Wave = 0;
            NextWave();
        }

        internal void Update()
        {
            if (!GameOver)
            {
                if (!PlayerDying)
                {
                    if (_invaders.Count != 0)
                    {
                        if (_player == null) // Quick fix for getting player to show up before input
                        {
                            _player = new Player(PlayAreaSize);
                            OnShipChanged(_player, _player.Location.X, _player.Location.Y, false);
                        }

                        BulkMoveInvaders();
                        InvadersFire();
                        MoveShots();
                        CheckForCollisions();
                    }
                    else
                        NextWave();
                }
                else
                {
                    if (DateTime.Now - _playerDied > TimeSpan.FromMilliseconds(2500))
                    {
                        _playerDied = null;

                        if (Lives > 0)
                        { Lives--; }
                        else
                        { EndGame(); }
                    }
                }
            }
        }

        public void CheckForCollisions()
        {           
            CheckForInvaderCollisions();
            CheckForPlayerShot();
            CheckForPlayerCollisions();
        }

        // Checks if any invader shots hit player
        public void CheckForPlayerShot()
        {
            List<Shot> invaderShotsToRemove = new List<Shot>();
            foreach (Shot shot in _invaderShots)
            {
                if (RectsOverlap(new Rect(shot.Location.X, shot.Location.Y, Shot.ShotSize.Width, Shot.ShotSize.Height),
                    new Rect(_player.Location.X, _player.Location.Y, _player.Size.Width, _player.Size.Height)))
                {
                    invaderShotsToRemove.Add(shot);
                    _playerDied = DateTime.Now;
                    OnShipChanged(_player, _player.PlayerX, _player.PlayerY, PlayerDying);
                }
            }

            foreach (Shot shot in invaderShotsToRemove)
            {
                OnShotMoved(shot, true, false);
                _invaderShots.Remove(shot);
            }
        }

        // Checks if any invader collided w/ player
        public void CheckForPlayerCollisions()
        {
            foreach (Invader invader in _invaders)
            {
                if (RectsOverlap(new Rect(invader.Location.X, invader.Location.Y, Invader._invaderSize.Width, Invader._invaderSize.Height),
                    new Rect(_player.Location.X, _player.Location.Y, _player.Size.Width, _player.Size.Height)))
                {
                    _player.Die();
                    _playerDied = DateTime.Now;
                    OnShipChanged(_player, _player.PlayerX, _player.PlayerY, true);
                }
            }
        }

        // Checks if player shot hit any invaders
        public void CheckForInvaderCollisions()
        {
            List<Invader> invadersToRemove = new List<Invader>();
            List<Shot> playerShotsToRemove = new List<Shot>();

            foreach (Invader invader in _invaders)
            {
                foreach (Shot shot in _playerShots)
                {
                    if (RectsOverlap(new Rect(shot.Location.X, shot.Location.Y, Shot.ShotSize.Width, Shot.ShotSize.Height),
                        new Rect(invader.Location.X, invader.Location.Y, Invader._invaderSize.Width, Invader._invaderSize.Height)))
                    {
                        playerShotsToRemove.Add(shot);
                        invadersToRemove.Add(invader);
                    }
                }
            }

            foreach (Shot shot in playerShotsToRemove)
            {
                _playerShots.Remove(shot);
                OnShotMoved(shot, true, false);
            }

            foreach (Invader invader in invadersToRemove)
            {
                _invaders.Remove(invader);
                score += invader.InvaderScore;
                OnShipChanged(invader, invader.Location.X, invader.Location.Y, true);
            }
        }

        // Used for collision detection
        private static bool RectsOverlap(Rect r1, Rect r2)
        {
            r1.Intersect(r2);
            if (r1.Width > 0 || r1.Height > 0)
                return true;
            return false;
        }

        public void BulkMoveInvaders()
        {
            if (DateTime.Now - _lastUpdated > TimeSpan.FromMilliseconds(1000))
            {
                if (_invaderDirection == Direction.Right)
                {
                    var hitRightEdge =
                    from invader in _invaders
                    where invader.Location.X >= PlayAreaSize.Width - 25
                    select invader;

                    if (hitRightEdge.Count() != 0 && _justMovedDown == false)
                    {
                        foreach (Invader invader in _invaders)
                        {
                            invader.Location = invader.MoveDown(invader.Location.X, invader.Location.Y);
                            OnShipChanged(invader, invader.Location.X, invader.Location.Y, false);
                        }
                        _invaderDirection = Direction.Left;
                        _justMovedDown = true;
                    }
                    else
                    {
                        foreach (Invader invader in _invaders)
                        {
                            invader.Location = invader.MoveRight(invader.Location.X, invader.Location.Y);
                            OnShipChanged(invader, invader.Location.X, invader.Location.Y, false);
                        }
                        _justMovedDown = false;
                    }
                }

                else
                {
                    var hitLeftEdge =
        from invader in _invaders
        where invader.Location.X <= 5
        select invader;

                    if (hitLeftEdge.Count() != 0 && _justMovedDown == false)
                    {
                        foreach (Invader invader in _invaders)
                        {
                            invader.Location = invader.MoveDown(invader.Location.X, invader.Location.Y);
                            OnShipChanged(invader, invader.Location.X, invader.Location.Y, false);
                        }
                        _invaderDirection = Direction.Right;
                        _justMovedDown = true;
                    }
                    else
                    {
                        foreach (Invader invader in _invaders)
                        {
                            invader.Location = invader.MoveLeft(invader.Location.X, invader.Location.Y);
                            OnShipChanged(invader, invader.Location.X, invader.Location.Y, false);
                        }
                        _justMovedDown = false;
                    }
                }

                // Checks to see if any invaders hit bottom; if they did, 
                // set GameOver to false using EndGame();
                var hitBottom =
        from invader in _invaders
        where invader.Location.Y >= PlayAreaSize.Height - 20
        select invader;

                if (hitBottom.Count() != 0)
                    EndGame();

                _lastUpdated = DateTime.Now;
            }
        }

        public void InvadersFire()
        {
            // makes them fire at random, not all the time:
            int randomNumber = _random.Next(10);
            if (randomNumber < 9 - Wave && 9 - Wave >= 0)
            // the above && condition is insurance for when 
            // Wave surpasses 10 and returns a (-) number
            {
                return;
            }
            else
            {
                if (_invaderShots.Count <= 3 + Wave)
                {
                    // use LINQ to group the invaders by their Location.X and sort them descending. 
                    // Once it’s got those groups, it can choose a group at random, and use its Last() 
                    // method to find the invader at the bottom of the column.

                    double randomIndex = random.Next(12);

                    var invaderColumns =
                    from invader in _invaders
                    group invader by invader.Location.X
                        into columns
                        orderby columns.Key
                        select columns;

                    List<Invader> bottomInvaders = new List<Invader>();

                    foreach (var group in invaderColumns)
                    {
                        Invader bottomInvader = group.Last<Invader>();
                        bottomInvaders.Add(bottomInvader);
                    }

                    Invader firingInvader = bottomInvaders[random.Next(bottomInvaders.Count)];
                    Shot newShot = new Shot(new Point(firingInvader.Location.X + firingInvader.Size.Width / 1.3,
                        firingInvader.Location.Y + 30), Direction.Down, false);
                    _invaderShots.Add(newShot);
                    OnShotMoved(newShot, false, false);
                }
            }
        }

        // player firing logic
        public void FireShot(bool isBomb)
        {
            if (_playerShots.Count <= MaximumPlayerShots)
            {
                Shot newShot = new Shot(new Point(_player.Location.X + _player.Size.Width / 1.3, _player.Location.Y - 30), Direction.Up, isBomb);
                _playerShots.Add(newShot);
                OnShotMoved(newShot, false, isBomb);
            }
        }

        // moves all shots on screen and removes if necessary, 10x/second
        public void MoveShots()
        {
            List<Shot> playerShotsToRemove = new List<Shot>();
            List<Shot> invaderShotsToRemove = new List<Shot>();
            foreach (Shot shot in _playerShots)
            {
                if (shot.Location.Y > 0)
                {
                    shot.Move();
                    OnShotMoved(shot, false, shot.IsBomb);
                }
                else
                {
                    playerShotsToRemove.Add(shot);
                }
            }

            foreach (Shot shotToRemove in playerShotsToRemove)
            {
                _playerShots.Remove(shotToRemove);
                OnShotMoved(shotToRemove, true, shotToRemove.IsBomb);
            }

            foreach (Shot shot in _invaderShots)
            {
                if (shot.Location.Y < PlayAreaSize.Height)
                {
                    shot.Move();
                    OnShotMoved(shot, false, false);
                }
                else
                {
                    invaderShotsToRemove.Add(shot);
                }
            }

            foreach (Shot shotToRemove in invaderShotsToRemove)
            {
                _invaderShots.Remove(shotToRemove);
                OnShotMoved(shotToRemove, true, false);
            }
        }

        public void Twinkle()
        {
            // If you try to remove an object from a collection while you’re 
            // enumerating though it using foreach, it’ll throw an exception. 
            // Instead, use the LINQ ToList() extension method to make a 
            // copy of the collection first and loop through that instead.

            if (_random.Next(2) == 0)
            {
                CreateAStar();
            }
            else
            {
                if (_stars.Count > 50)
                {
                    Point starToRemove = _stars.ToList()[_random.Next(_stars.Count)];
                    _stars.Remove(starToRemove);
                    OnStarChanged(starToRemove, true);
                }
            }
        }
        private void CreateStars()
        {
            for (int i = 0; i < 50; i++)
            {
                CreateAStar();
            }
        }
        private void CreateAStar()
        {
            Point newStar = new Point(random.Next((int)PlayAreaSize.Width), random.Next((int)PlayAreaSize.Height));
            _stars.Add(newStar);
            OnStarChanged(newStar, false);
        }
        public void NextWave()
        {
            Wave++;
            _invaders.Clear();

// Populate _invaders in formation w/ nested for loop
            double locationX = 0;
            double locationY = 0;
            int invaderType = 0;

            for (int x = 0; x < 6; x++)
            {
                for (int i = 0; i < 11; i++)
                {
                    _invaders.Add(new Invader((InvaderType)invaderType, new Point(locationX, locationY)));
                    locationX += Invader._invaderSize.Width*1.4;
                }
                locationX = 0;
                locationY += Invader._invaderSize.Height * 1.4;
                if(invaderType < 4)
                invaderType++;
            }
        }
        public void MovePlayer(KeyEventArgs e)
        {
            Point newLocation = _player.Location;
            switch (e.Key)
            {
                case Key.Left:
                    _player.MovePlayer(Direction.Left, PlayAreaSize);
                    OnShipChanged(_player, _player.Location.X, _player.Location.Y, false);
                    break;
                case Key.Right:
                    _player.MovePlayer(Direction.Right, PlayAreaSize);
                    OnShipChanged(_player, _player.Location.X, _player.Location.Y, false);
                    break;
            }
        }

        public event EventHandler<ShipChangedEventArgs> ShipChanged;
        private void OnShipChanged(Ship shipThatChanged, double x, double y, bool killed)
        {
            if (ShipChanged != null)
            {
                ShipChanged(this, new ShipChangedEventArgs(shipThatChanged, x, y, killed));
            }
        }

        public event EventHandler<StarChangedEventArgs> StarChanged;
        private void OnStarChanged(Point starThatChanged, bool removed)
        {
            if (StarChanged != null)
            {
                StarChanged(this, new StarChangedEventArgs(starThatChanged, removed));
            }
        }

        public event EventHandler<ShotMovedEventArgs> ShotMoved;
        private void OnShotMoved(Shot shotThatMoved, bool removed, bool isBomb)
        {
            if (ShotMoved != null)
            {
                ShotMoved(this, new ShotMovedEventArgs(shotThatMoved, removed, isBomb));
            }
        }

        internal void UpdateAllShipsAndStars()
        {
            foreach (Invader invader in _invaders)
            {
                OnShipChanged(invader, invader.Location.X, invader.Location.Y, false);
            }

            foreach (Shot shot in _playerShots)
            {
                OnShotMoved(shot, false, false);
            }

            foreach (Shot shot in _invaderShots)
            {
                OnShotMoved(shot, false, false);
            }

            foreach (Point star in _stars)
            {
                OnStarChanged(star, false);
            }
        }
    }
}