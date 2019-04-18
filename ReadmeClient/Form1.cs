using Readme.Model;
using System;
using System.ComponentModel;
using System.Windows.Forms;

namespace Readme
{
    public partial class Form1 : Form
    {
        private readonly IConnection _connection;
        public Form1()
        {
            InitializeComponent();
            _connection = new Connection();
            var answer = _connection.AskForReadme();
            if (answer)
                MessageBox.Show("yay");
            else
                MessageBox.Show("buu");
        }

        private void btnGet_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(lblProject.Text) || string.IsNullOrWhiteSpace(lblLanguage.Text))
            {
                MessageBox.Show("Please provide project or language!", "Bad query", MessageBoxButtons.OK);
                return;
            }

            bgWorker.RunWorkerAsync();
        }
        private void bgWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            var request = GetSearchArguments();
            var answer = _connection.AskForReadme();
            if (answer)
                MessageBox.Show("yay");
            else
                MessageBox.Show("buu");
        }

        private string GetSearchArguments()
        {
            var request = "GET /search/";
            if (!string.IsNullOrWhiteSpace(tbProject.Text))
                request += $"repositories?q={tbProject.Text}+";

            if (string.IsNullOrWhiteSpace(tbLanguage.Text))
                request += $"language:{tbLanguage.Text}";

            request += "&sort=stars&order=desc HTTP/1.1\r\n" + 
                "Host: api.github.com\r\n" +
                "Content-Length: 100\r\n" +
                "Content-Type: application/json\r\n";

            return request;
        }
    }
}
