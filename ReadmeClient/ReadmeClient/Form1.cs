using Readme.Model;
using System;
using System.ComponentModel;
using System.Windows.Forms;

namespace Readme
{
    public partial class Form1 : Form
    {
        private IConnection _connection;
        public Form1()
        {
            InitializeComponent();
        }

        private void btnGet_Click(object sender, EventArgs e)
        {
            if (_connection == null)
                _connection = new Connection();

            if (string.IsNullOrWhiteSpace(lblProject.Text) || string.IsNullOrWhiteSpace(lblLanguage.Text))
            {
                MessageBox.Show("Please provide project or language!", "Bad query", MessageBoxButtons.OK);
                return;
            }

            bgWorker.RunWorkerAsync();
        }
        private void bgWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            var answer = _connection.AskForReadme(tbLanguage.Text, tbProject.Text);

            if (answer)
                MessageBox.Show("yay");
            else
                MessageBox.Show("buu");
        }


    }
}
