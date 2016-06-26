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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Media.Animation;
using System.Reflection;

namespace Invaders.View
{
    /// <summary>
    /// Interaction logic for StarControl.xaml
    /// </summary>
    public partial class StarControl : UserControl
    {
        Random rnd;

        public StarControl()
        {
            InitializeComponent();
            SetSize();
            SetFill();
        }

        public void FadeIn()
        {
            Storyboard fadeInStoryboard = FindResource("fadeInStoryboard") as Storyboard;
            fadeInStoryboard.Begin();
        }
        public void FadeOut()
        {
            Storyboard fadeOutStoryboard = FindResource("fadeOutStoryboard") as Storyboard;
            fadeOutStoryboard.Begin();
        }

        public void SetSize()
        {
            rnd = new Random();
            int rndSize = rnd.Next(2, 8);
            starPolygon.Height = rndSize;
            starPolygon.Width = rndSize;
        }

        public void SetFill()
        {
            rnd = new Random();
            Brush result = Brushes.Transparent;
            Type brushesType = typeof(Brushes);
            PropertyInfo[] properties = brushesType.GetProperties();
            int random = rnd.Next(properties.Length);
            result = (Brush)properties[random].GetValue(null, null);
            starPolygon.Fill = result;
        }       
    }
}
