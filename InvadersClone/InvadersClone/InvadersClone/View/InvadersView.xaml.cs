/*******************************************************************************************
* File:           InvadersView.cs                                                          *
*                                                                                          *
* Author:         Gregory Weiner                                                           *
* Version:        1.0 8.01.2012                                                            *
* Last Modified:  2.02.2013                                                                *
* License:        Free Software(GNU License Included)                                      *
* Purpose:        This is a clone of the classic space shooter game 'Invaders,'            *
*                 written from scratch in C# for the WPF platform. A real-time             *
*                 shooter game, the player scores points by destroying incoming            *
*                 alien invaders, and loses if the invaders collide with the player        *
*                 or reach the bottom of the screen.                                       *
*                                                                                          *
*                 This Application follows the model view viewmodel design pattern,        *
*                 in which the game logic occurs in the model layer (written in C#),       *
*                 the display and binding logic happens in the view layer (written in      *
*                 xaml), and the viewmodel is the pipeline that provides communication     *
*                 between the two aforementioned layers.This allows for better             *
*                 portability of the business logic, and better compartmentalization of    *
*                 code overall.                                                            *
*                                                                                          *
* Description:    This is the View Layer of the Program, responsible for display,          *
*                 written in C#.                                                           *
*                                                                                          *
* Input:          Arrow keys for movement, Space key to shoot, P to pause.                 *
*                                                                                          *
* Requirements:   Requires a functioning keyboard for input.                               *
*                 Runs in windowed mode.                                                   *
*                                                                                          *
* ******************************************************************************************/


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Timers;

namespace Invaders.View
{
    using ViewModel;

    public partial class InvadersView : Window
    {
        InvadersViewModel viewModel;
        public InvadersView()
        {
            InitializeComponent();
            viewModel = FindResource("viewModel") as InvadersViewModel;
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            viewModel.KeyInput(e);
        }

        private void playArea_Loaded(object sender, RoutedEventArgs e)
        {
            UpdatePlayAreaSize(playArea.RenderSize);
            RescaleUIText();
        }

        private void RescaleUIText()
        {
            Canvas.SetLeft(gameOverText, 50 * InvadersViewModel.Scale);
            Canvas.SetTop(gameOverText, 50 * InvadersViewModel.Scale);
            gameOverText.FontSize = 50 * InvadersViewModel.Scale;

            Canvas.SetLeft(shootToStart, 50 * InvadersViewModel.Scale);
            Canvas.SetTop(shootToStart, 50 * InvadersViewModel.Scale);
            shootToStart.FontSize = 20 * InvadersViewModel.Scale;

            Canvas.SetLeft(pausedText, 50 * InvadersViewModel.Scale);
            Canvas.SetTop(pausedText, 50 * InvadersViewModel.Scale);
            pausedText.FontSize = 50 * InvadersViewModel.Scale;
        }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            UpdatePlayAreaSize(new Size(e.NewSize.Width, e.NewSize.Height - 160));
            RescaleUIText();
        }

        private void UpdatePlayAreaSize(Size newPlayAreaSize)
        {
            double targetWidth;
            double targetHeight;
            if (newPlayAreaSize.Width > newPlayAreaSize.Height)
            {
                targetWidth = newPlayAreaSize.Height * 4 / 3;
                targetHeight = newPlayAreaSize.Height;
                double leftRightMargin = (newPlayAreaSize.Width - targetWidth) / 2;
                playArea.Margin = new Thickness(leftRightMargin, 0, leftRightMargin, 0);
            }
            else
            {
                targetHeight = newPlayAreaSize.Width * 3 / 4;
                targetWidth = newPlayAreaSize.Width;
                double topBottomMargin = (newPlayAreaSize.Height - targetHeight) / 2;
                playArea.Margin = new Thickness(0, topBottomMargin, 0, topBottomMargin);
            }
            playArea.Width = targetWidth;
            playArea.Height = targetHeight;
            viewModel.PlayAreaSize = playArea.RenderSize;
        }

    // I found out that when I initialized the InvadersViewModel as a StaticResource 
        // in the Xaml View page, the key input properties didn't update properly, but
        // when I initialize it in the code-behind here, they work. Any idea why?
        
        //private void playArea_Loaded(object sender, RoutedEventArgs e)
        //{
        //    UpdatePlayAreaSize(playArea.RenderSize);
        //}
        //private void pageRoot_SizeChanged(object sender, SizeChangedEventArgs e)
        //{
        //    UpdatePlayAreaSize(new Size(e.NewSize.Width, e.NewSize.Height - 160));
        //}
        //private void UpdatePlayAreaSize(Size newPlayAreaSize)
        //{
        //    double targetWidth;
        //    double targetHeight;
        //    if (newPlayAreaSize.Width > newPlayAreaSize.Height)
        //    {
        //        targetWidth = newPlayAreaSize.Height * 4 / 3;
        //        targetHeight = newPlayAreaSize.Height;
        //        double leftRightMargin = (newPlayAreaSize.Width - targetWidth) / 2;
        //        playArea.Margin = new Thickness(leftRightMargin, 0, leftRightMargin, 0);
        //    }
        //    else
        //    {
        //        targetHeight = newPlayAreaSize.Width * 3 / 4;
        //        targetWidth = newPlayAreaSize.Width;
        //        double topBottomMargin = (newPlayAreaSize.Height - targetHeight) / 2;
        //        playArea.Margin = new Thickness(0, topBottomMargin, 0, topBottomMargin);
        //    }
        //    playArea.Width = targetWidth;
        //    playArea.Height = targetHeight;
        //    viewModel.PlayAreaSize = playArea.RenderSize;
        //}    
    }
}
