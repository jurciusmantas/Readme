namespace Readme
{
    partial class Form1
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
            this.lblProject = new System.Windows.Forms.Label();
            this.tbProject = new System.Windows.Forms.TextBox();
            this.tbLanguage = new System.Windows.Forms.TextBox();
            this.lblLanguage = new System.Windows.Forms.Label();
            this.btnGet = new System.Windows.Forms.Button();
            this.lblBytesReceived = new System.Windows.Forms.Label();
            this.lblStatus = new System.Windows.Forms.Label();
            this.btnOpen = new System.Windows.Forms.Button();
            this.bgWorker = new System.ComponentModel.BackgroundWorker();
            this.SuspendLayout();
            // 
            // lblProject
            // 
            this.lblProject.AutoSize = true;
            this.lblProject.Location = new System.Drawing.Point(13, 13);
            this.lblProject.Name = "lblProject";
            this.lblProject.Size = new System.Drawing.Size(46, 13);
            this.lblProject.TabIndex = 0;
            this.lblProject.Text = "Project :";
            // 
            // tbProject
            // 
            this.tbProject.Location = new System.Drawing.Point(16, 30);
            this.tbProject.Name = "tbProject";
            this.tbProject.Size = new System.Drawing.Size(129, 20);
            this.tbProject.TabIndex = 1;
            // 
            // tbLanguage
            // 
            this.tbLanguage.Location = new System.Drawing.Point(164, 30);
            this.tbLanguage.Name = "tbLanguage";
            this.tbLanguage.Size = new System.Drawing.Size(129, 20);
            this.tbLanguage.TabIndex = 3;
            // 
            // lblLanguage
            // 
            this.lblLanguage.AutoSize = true;
            this.lblLanguage.Location = new System.Drawing.Point(161, 13);
            this.lblLanguage.Name = "lblLanguage";
            this.lblLanguage.Size = new System.Drawing.Size(61, 13);
            this.lblLanguage.TabIndex = 2;
            this.lblLanguage.Text = "Language :";
            // 
            // btnGet
            // 
            this.btnGet.Location = new System.Drawing.Point(16, 69);
            this.btnGet.Name = "btnGet";
            this.btnGet.Size = new System.Drawing.Size(277, 34);
            this.btnGet.TabIndex = 4;
            this.btnGet.Text = "Get Readme";
            this.btnGet.UseVisualStyleBackColor = true;
            this.btnGet.Click += new System.EventHandler(this.btnGet_Click);
            // 
            // lblBytesReceived
            // 
            this.lblBytesReceived.AutoSize = true;
            this.lblBytesReceived.Location = new System.Drawing.Point(16, 121);
            this.lblBytesReceived.Name = "lblBytesReceived";
            this.lblBytesReceived.Size = new System.Drawing.Size(88, 13);
            this.lblBytesReceived.TabIndex = 5;
            this.lblBytesReceived.Text = "Bytes Received :";
            // 
            // lblStatus
            // 
            this.lblStatus.AutoSize = true;
            this.lblStatus.Location = new System.Drawing.Point(16, 144);
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new System.Drawing.Size(0, 13);
            this.lblStatus.TabIndex = 6;
            // 
            // btnOpen
            // 
            this.btnOpen.Location = new System.Drawing.Point(16, 170);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(277, 34);
            this.btnOpen.TabIndex = 7;
            this.btnOpen.Text = "Open Readme";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Visible = false;
            // 
            // bgWorker
            // 
            this.bgWorker.DoWork += new System.ComponentModel.DoWorkEventHandler(this.bgWorker_DoWork);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(318, 224);
            this.Controls.Add(this.btnOpen);
            this.Controls.Add(this.lblStatus);
            this.Controls.Add(this.lblBytesReceived);
            this.Controls.Add(this.btnGet);
            this.Controls.Add(this.tbLanguage);
            this.Controls.Add(this.lblLanguage);
            this.Controls.Add(this.tbProject);
            this.Controls.Add(this.lblProject);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblProject;
        private System.Windows.Forms.TextBox tbProject;
        private System.Windows.Forms.TextBox tbLanguage;
        private System.Windows.Forms.Label lblLanguage;
        private System.Windows.Forms.Button btnGet;
        private System.Windows.Forms.Label lblBytesReceived;
        private System.Windows.Forms.Label lblStatus;
        private System.Windows.Forms.Button btnOpen;
        private System.ComponentModel.BackgroundWorker bgWorker;
    }
}

