/**************8**************************************************************************
* File:           InvadersViewModel.cs                                                   *
*                                                                                        *
* Author:         Gregory Weiner                                                         *
* Version:        1.0 8.01.2012                                                          *
* Last Modified:  2.02.2013                                                              *
* License:        Free Software(GNU License Included)                                    *
* Purpose:        This is a clone of the classic space shooter game 'Invaders,'          *
*                 written from scratch in C# for the WPF platform. A real-time           *
*                 shooter game, the player scores points by destroying incoming          *
*                 alien invaders, and loses if the invaders collide with the player      *
*                 or reach the bottom of the screen.                                     *
*                                                                                        *
*                 * This Application follows the model view viewmodel design pattern,    *
*                 in which the game logic occurs in the model layer(written in C#),      *
*                 the display and binding logic happens in the view layer (written in    *
*                 xaml), and the viewmodel is the pipeline that provides communication   *
*                 between the two aforementioned layers.This allows for better           *
*                 portability of the business logic, and better compartmentalization of  *
*                 code overall.                                                          *
*                                                                                        *
* Description:    This is the ViewModel Layer of the Program, written in C#.             *
*                 Responsible for linking View and Model.                                *
*                                                                                        *
* Input:          Arrow keys for movement, Space key to shoot, P to pause.               *
*                                                                                        *
* Requirements:   Requires a functioning keyboard for input.                             *
*                 Runs in windowed mode.                                                 *
*                                                                                        *
******************************************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Invaders.ViewModel
{
    using View;
    using Model;
    using System.Collections.ObjectModel;
    using System.Collections.Specialized;
    using System.Windows;
    using DispatcherTimer = System.Windows.Threading.DispatcherTimer;
    using UIElement = System.Windows.UIElement;

    public class InvadersViewModel : INotifyPropertyChanged
    {
        private readonly ObservableCollection<UIElement> _sprites = 
    new ObservableCollection<UIElement>();
        public INotifyCollectionChanged Sprites { get { return _sprites; } }

        private readonly Dictionary<Invader, AnimatedImage> _invaders =
    new Dictionary<Invader, AnimatedImage>();        
        private readonly Dictionary<Point, StarControl> _starDictionary =
    new Dictionary<Point, StarControl>();
        private readonly List<StarControl> _starsToAdd =
    new List<StarControl>();
        private readonly Dictionary<Shot, AnimatedImage> _shots = 
    new Dictionary<Shot, AnimatedImage>();

        private readonly Dictionary<FrameworkElement, DateTime> _fadedStars =
    new Dictionary<FrameworkElement, DateTime>();
        private readonly Dictionary<FrameworkElement, DateTime> _shotInvaders =
    new Dictionary<FrameworkElement, DateTime>();

        private readonly List<FrameworkElement> _scanLines = 
    new List<FrameworkElement>();

        private InvadersModel _model;
        private DispatcherTimer _timer = new DispatcherTimer();

        public AnimatedImage playerControl = null;
        private bool _playerFlashing = false;

        public static double Scale { get; private set; }

        public Size PlayAreaSize
        {
            set
            {
                Scale = value.Width / 405;
                _model.UpdateAllShipsAndStars();
                RecreateScanLines();
            }
        }

        public bool GameOver
        {
            get { return _model.GameOver; }
        }
        public bool Paused
        {
            get { return _model.GamePaused; }
            private set { _model.GamePaused = value; }
        }
        public string Score
        {
            get { return _model.Score; }
        }

        private readonly ObservableCollection<object> _lives = 
            new ObservableCollection<object>();
        public INotifyCollectionChanged Lives {get {return _lives;}}

        public double PlayerLocationX { get; set; }
        public double PlayerLocationY { get; set; }

        public InvadersViewModel()
        {
            _model = new InvadersModel();
            Scale = 1;
            PopulateSprites();

            _timer.Interval = TimeSpan.FromMilliseconds(100);
            _timer.Tick += timer_Tick;
            _timer.Start();
            _model.StarChanged += StarChangedHandler;
            _model.ShipChanged += ShipChangedHandler;
            _model.ShotMoved += ShotMovedHandler;

            _model.EndGame();
        }

        public void StartGame()
        {
            Paused = false;
            foreach (var invader in _invaders.Values) _sprites.Remove(invader);
            foreach (var shot in _shots.Values) _sprites.Remove(shot);
            _model.StartGame();
            OnPropertyChanged("GameOver");
            _timer.Start();
        }

        public void KeyInput(KeyEventArgs e)
        {
            if (!Paused && !GameOver)
            {
                switch (e.Key)
                {
                    case Key.LeftCtrl:
                        _model.FireShot(true);
                        break;
                    case Key.P:
                        if (Paused == true)
                        {
                            _model.GamePaused = false;
                            OnPropertyChanged("Paused");
                        }
                        else
                        {
                            _model.GamePaused = true;
                            OnPropertyChanged("Paused");
                        }
                        break;
                    default:
                        _model.MovePlayer(e);
                        break;
                }
            }
            else
            {
                if (e.Key == Key.P)
                {
                    if (Paused == true)
                    {
                        _model.GamePaused = false;
                        OnPropertyChanged("Paused");
                    }
                    else
                    {
                        _model.GamePaused = true;
                        OnPropertyChanged("Paused");
                    }
                }
            }

            if (e.Key == Key.Space)
            {
                if (!GameOver)
                {
                    if (!Paused)

                        _model.FireShot(false);
                }
                else
                    StartGame();
            }
        }

        private void RecreateScanLines()
        {
            foreach (FrameworkElement scanLine in _scanLines)
                if (_sprites.Contains(scanLine))
                    _sprites.Remove(scanLine);
            _scanLines.Clear();

            // should make all rescaling values relative values, not set numbers
            for (int y = 0; y < 300; y += 2)
            {
                FrameworkElement scanLine = InvadersHelper.ScanLineFactory(y, 400, Scale);
                _scanLines.Add(scanLine);
                _sprites.Add(scanLine);
            }
        }
        public void PopulateSprites()
        {
            RecreateScanLines();

            foreach (Point star in _model._stars)
            {
                StarControl newStar = InvadersHelper.StarControlFactory(star, Scale) as StarControl;
                _starDictionary.Add(star, newStar);
              // Obsolete:
              // InvadersHelper.SetCanvasLocation(newStar, star.X, star.Y, Scale);
                _sprites.Add(newStar);

            }
        }
        void timer_Tick(object sender, object e)
        {
            _model.Twinkle();
            if (!Paused)
            {
                _model.Update();
                foreach (FrameworkElement starControl in _fadedStars.Keys.ToList())
                {
                    TimeSpan timeSinceRemoved = DateTime.Now - _fadedStars[starControl];
                    if (timeSinceRemoved > TimeSpan.FromMilliseconds(1000))
                    {
                        _fadedStars.Remove(starControl);
                        _sprites.Remove(starControl);
                    }
                }
                    
                foreach (FrameworkElement control in _shotInvaders.Keys.ToList())
                {
                    TimeSpan timeSinceLastShot = DateTime.Now - _shotInvaders[control];
                    if (timeSinceLastShot > TimeSpan.FromMilliseconds(2000))
                    {
                        _sprites.Remove(control);
                        _shotInvaders.Remove(control);
                    }
                }
                OnPropertyChanged("GameOver");
                OnPropertyChanged("Score");
             // No longer necessary:
             // OnPropertyChanged("Lives");
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged(string propertyName)
        {
            PropertyChangedEventHandler propertyChangedEvent = PropertyChanged;
            if (propertyChangedEvent != null)
            {
                propertyChangedEvent(this,
                  new PropertyChangedEventArgs(propertyName));
            }
        }

                private void ShipChangedHandler(object sender, ShipChangedEventArgs e)
        {
            if (!e.Killed) // if ship is not killed
            {
                if (e.ShipUpdated is Invader)
                {
                    Invader invader = e.ShipUpdated as Invader;
                    AnimatedImage invaderControl;

                    // set up preliminary data to create or alter invader sprites
                    List<string> invaderNames = new List<string>();
                    for (int i = 1; i < 5; i++)
                    {
                        string invaderName = "Assets/" + invader._invaderType.ToString() + i + ".png";
                        invaderNames.Add(invaderName);
                    }

                    if (!_invaders.ContainsKey(e.ShipUpdated as Invader))
                    {
                        invaderControl = InvadersHelper.InvaderControlFactory(invader, invaderNames, Scale) as AnimatedImage;
                        //_invaders.Add(invader, invaderControl);
                        _invaders[invader] = invaderControl;
                        _sprites.Add(invaderControl);
                    }
                    else
                    {
                        invaderControl = _invaders[e.ShipUpdated as Invader];
                        InvadersHelper.MoveElementOnCanvas(invaderControl, e.X*Scale, e.Y*Scale);
                        InvadersHelper.ResizeElement(invaderControl, invader.Size.Width * Scale, invader.Size.Height * Scale);
                    }
                }
                else // if ship is Player
                {
                    Player player = e.ShipUpdated as Player;

                    if (_playerFlashing)
                    {
                        playerControl.StopFlashing();
                        _playerFlashing = false;
                    }

                    if (playerControl == null)
                    {
                        List<string> playerImage = new List<string>();
                        playerImage.Add("Assets/player.png");
                        playerControl = InvadersHelper.PlayerControlFactory(player, playerImage, Scale) as AnimatedImage;
                        _sprites.Add(playerControl);
                    }
                    else
                    {
                        InvadersHelper.MoveElementOnCanvas(playerControl, e.X*Scale, e.Y*Scale);
                        InvadersHelper.ResizeElement(playerControl, player.Size.Width * Scale, player.Size.Height * Scale);
                    }
                }
            }
            else // if Ship is killed
            {
                if (e.ShipUpdated is Invader) // if ship is Invader
                {
                    AnimatedImage invaderControl;
                    Invader invader = e.ShipUpdated as Invader;

                    if (_invaders.ContainsKey(invader as Invader))
                    {
                        invaderControl = _invaders[e.ShipUpdated as Invader];
                        _invaders.Remove(invader as Invader);
                        _shotInvaders.Add(invaderControl, DateTime.Now);
                         invaderControl.FadeOut();
                         //// not sure where to put this resize element method
                         //InvadersHelper.ResizeElement(invaderControl, invader.Size.Width * Scale, invader.Size.Height * Scale,
                         //    invader.Location.X * Scale, invader.Location.Y * Scale, Scale);
                    }
                }
                else // if ship is Player
                {
                    playerControl.StartFlashing();
                    _playerFlashing = true;
                    //// not sure where to put this resize element method
                    //InvadersHelper.ResizeElement(playerControl, e.ShipUpdated.Size.Width * Scale,
                    //    e.ShipUpdated.Size.Height * Scale, e.ShipUpdated.Location.X * Scale, e.ShipUpdated.Location.Y * Scale, Scale);
                }
            }
        }        

        private void ShotMovedHandler(object sender, ShotMovedEventArgs e)
        {
            Shot shot = e.Shot;
            if (e.Removed)
            {
                AnimatedImage shotControl;
                if (_shots.ContainsKey(e.Shot))
                {
                    shotControl = _shots[e.Shot];
                    _sprites.Remove(shotControl);
                    _shots.Remove(e.Shot);
                }
            }

            else
            {
                AnimatedImage shotControl;

                if (!e.IsBomb)
                {
                    List<string> shotImages = new List<string>() 
            { "Assets/shot1.png", "Assets/shot2.png", "Assets/shot3.png", "Assets/shot4.png",
            };

                    if (!_shots.ContainsKey(e.Shot))
                    {
                        shotControl = InvadersHelper.ShotControlFactory(shot, shotImages, Scale) as AnimatedImage;
                        _shots[e.Shot] = shotControl;
                        //InvadersHelper.ResizeElement(shotControl, Shot.ShotSize.Width * Scale, Shot.ShotSize.Height * Scale);
                        _sprites.Add(shotControl);
                    }
                    else
                    {
                        shotControl = _shots[e.Shot];
                        //InvadersHelper.ResizeElement(shotControl, Shot.ShotSize.Width * Scale, Shot.ShotSize.Height * Scale);
                        InvadersHelper.MoveElementOnCanvas(shotControl, e.Shot.Location.X * Scale, e.Shot.Location.Y * Scale);
                    }
                }
                else
                {
                    List<string> bombImages = new List<string>() 
            { "Assets/bomb1.png", "Assets/bomb2.png", "Assets/bomb3.png", "Assets/bomb4.png",};

                    if (!_shots.ContainsKey(e.Shot))
                    {
                        shotControl = InvadersHelper.ShotControlFactory(shot, bombImages, Scale) as AnimatedImage;
                        _shots[e.Shot] = shotControl;
                        _sprites.Add(shotControl);
                    }
                    else
                    {
                        shotControl = _shots[e.Shot];
                        InvadersHelper.MoveElementOnCanvas(shotControl, e.Shot.Location.X * Scale, e.Shot.Location.Y * Scale);
                    }
                }
            }
        }

        private void StarChangedHandler(object sender, StarChangedEventArgs e)
        {
            Point star = e.StarThatChanged;
            if (e.Removed)
            {
                if (_starDictionary.ContainsKey(e.StarThatChanged))
                {
                    StarControl starControl = _starDictionary[e.StarThatChanged];
                    _starDictionary.Remove(e.StarThatChanged);
                    _fadedStars.Add(starControl, DateTime.Now);
                    starControl.FadeOut();
                    //// not sure where to put this resize element method
                    //InvadersHelper.ResizeElement(starControl, e.StarThatChanged.X * Scale, e.StarThatChanged.Y * Scale,
                    //    e.StarThatChanged.X * Scale, e.StarThatChanged.Y * Scale, Scale);
                }
            }
            else
            {
                StarControl newStar;
                if (_starDictionary.ContainsKey(e.StarThatChanged))
                {
                    newStar = _starDictionary[e.StarThatChanged];
                }
                else
                {
                    newStar = InvadersHelper.StarControlFactory(star, Scale) as StarControl;
                    _starDictionary[e.StarThatChanged] = newStar;
                    newStar.FadeIn();
                    _sprites.Add(newStar);
                                    }
                //InvadersHelper.SetCanvasLocation(newStar, e.StarThatChanged.X, e.StarThatChanged.Y, Scale);
                //// not sure where to put this resize element method
                //InvadersHelper.ResizeElement(newStar, e.StarThatChanged.X * Scale, e.StarThatChanged.Y * Scale,
                //    e.StarThatChanged.X * Scale, e.StarThatChanged.Y * Scale, Scale);
            }
        }
    }
    }