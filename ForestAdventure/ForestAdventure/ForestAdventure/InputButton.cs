using System;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ForestAdventure
{
    public partial class InputButton : Button
    {
        protected override bool IsInputKey(Keys keyData)
        {
            if (keyData == Keys.Control)
            {
                return true;
            }
            else
            {
                return base.IsInputKey(keyData);
            }
        }
    }
}
