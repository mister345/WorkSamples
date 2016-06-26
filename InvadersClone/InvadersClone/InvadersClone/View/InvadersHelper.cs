using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Animation;
using System.Windows.Media;
using System.Windows.Shapes;

namespace Invaders.View
{
    using Model;

    static class InvadersHelper
    {
        // SOLVED problem: was not passing the INVADER object Size properties to 
        // this method; it takes them from the AnimatedImage control directly!
        internal static FrameworkElement InvaderControlFactory(Invader invader, List<string> imageNames, double scale)
        {
            AnimatedImage invaderControl = new AnimatedImage(imageNames, TimeSpan.FromMilliseconds(200));
            invaderControl.Width = invader.Size.Width * scale;
            invaderControl.Height = invader.Size.Width * scale;
            SetCanvasLocation(invaderControl, invader.Location.X * scale, invader.Location.Y * scale);
            return invaderControl;
        }

        internal static FrameworkElement ShotControlFactory(Shot shot, List<string> imageNames, double scale) 
        {
            AnimatedImage shotControl = new AnimatedImage(imageNames, TimeSpan.FromMilliseconds(100));
            shotControl.Width = Shot.ShotSize.Width * scale;
            shotControl.Height = Shot.ShotSize.Height * scale;
            SetCanvasLocation(shotControl, shot.Location.X * scale, shot.Location.Y * scale);
            return shotControl;
        }

        internal static FrameworkElement PlayerControlFactory(Player player, List<string> imageNames, double scale)
        {
            AnimatedImage playerControl = new AnimatedImage(imageNames, TimeSpan.FromMilliseconds(300));
            playerControl.Width = player.Size.Width * scale;
            playerControl.Height = player.Size.Height * scale;
            SetCanvasLocation(playerControl, player.Location.X * scale, player.Location.Y * scale);
            return playerControl;
        }

        internal static FrameworkElement StarControlFactory(Point star, double scale)
        {
            StarControl starControl = new StarControl();
            SetCanvasLocation(starControl, star.X * scale, star.Y * scale);
            Canvas.SetZIndex(starControl, -1000);
            return starControl;
        }

        public static FrameworkElement ScanLineFactory(int yPosition, double playAreaWidth, double scale)
        {
            Rectangle newScanLine = new Rectangle();
            newScanLine.Width = playAreaWidth * scale;
            newScanLine.Height = 2;
            newScanLine.Opacity = .1;
            newScanLine.Fill = new SolidColorBrush(Colors.White);
            SetCanvasLocation(newScanLine, 0, yPosition * scale);
            return newScanLine;
        }

        public static void SetCanvasLocation(UIElement control, double x, double y)
        {
            Canvas.SetLeft(control, x);
            Canvas.SetTop(control, y);
        }

        public static void MoveElementOnCanvas(UIElement uiElement, double toX, double toY)
        {
            double fromX = Canvas.GetLeft(uiElement);
            double fromY = Canvas.GetTop(uiElement);

            Storyboard storyboard = new Storyboard();

        // TODO: later customize these Timespans for different animated objects
            DoubleAnimation animationX = CreateDoubleAnimation(uiElement, fromX, toX, 
                new PropertyPath(Canvas.LeftProperty), TimeSpan.FromMilliseconds(50));
            DoubleAnimation animationY = CreateDoubleAnimation(uiElement, fromY, toY,
                new PropertyPath(Canvas.TopProperty), TimeSpan.FromMilliseconds(50));
            storyboard.Children.Add(animationX);
            storyboard.Children.Add(animationY);
            storyboard.Begin();
        }

        // possible issue here?
        public static DoubleAnimation CreateDoubleAnimation(UIElement uiElement,
        double from, double to, PropertyPath propertyToAnimate, TimeSpan timeSpan)
        {
            DoubleAnimation animation = new DoubleAnimation();
            Storyboard.SetTarget(animation, uiElement);
            Storyboard.SetTargetProperty(animation, propertyToAnimate);
            animation.From = from;

            animation.To = to;
            animation.Duration = timeSpan;
            return animation;
        }

        public static void ResizeElement(Control control, double width, double height)
        {
            control.Width = width;
            control.Height = height;
        }
    }
}
