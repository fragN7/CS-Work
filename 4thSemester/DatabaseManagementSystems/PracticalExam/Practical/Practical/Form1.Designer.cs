using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;


namespace Practical
{
    partial class Form1 : Form
    {
        private System.Windows.Forms.Button insertButton;
        private System.Windows.Forms.Button updateButton;
        private System.Windows.Forms.Button deleteButton;

        private System.Windows.Forms.DataGridView dgvSports;
        private System.Windows.Forms.DataGridView dgvTeams;
        
        private System.Windows.Forms.TextBox teamIDBox;
        private System.Windows.Forms.TextBox nameBox;
        private System.Windows.Forms.TextBox membersBox;
        private System.Windows.Forms.TextBox startYearBox;
        private System.Windows.Forms.TextBox cityBox;
        private System.Windows.Forms.TextBox teamTypeIDBox;
        private System.Windows.Forms.TextBox sportIDBox;
        
        private System.Windows.Forms.Label teamIDLabel;
        private System.Windows.Forms.Label nameLabel;
        private System.Windows.Forms.Label membersLabel;
        private System.Windows.Forms.Label startYearLabel;
        private System.Windows.Forms.Label cityLabel;
        private System.Windows.Forms.Label teamTypeIDLabel;
        private System.Windows.Forms.Label sportIDLabel;


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
            this.insertButton = new System.Windows.Forms.Button();
            this.updateButton = new System.Windows.Forms.Button();
            this.deleteButton = new System.Windows.Forms.Button();
            this.dgvSports = new System.Windows.Forms.DataGridView();
            this.dgvTeams = new System.Windows.Forms.DataGridView();
            this.teamIDBox = new System.Windows.Forms.TextBox();
            this.nameBox = new System.Windows.Forms.TextBox();
            this.membersBox = new System.Windows.Forms.TextBox();
            this.startYearBox = new System.Windows.Forms.TextBox();
            this.cityBox = new System.Windows.Forms.TextBox();
            this.teamTypeIDBox = new System.Windows.Forms.TextBox();
            this.sportIDBox = new System.Windows.Forms.TextBox();
            this.teamIDLabel = new System.Windows.Forms.Label();
            this.nameLabel = new System.Windows.Forms.Label();
            this.membersLabel = new System.Windows.Forms.Label();
            this.startYearLabel = new System.Windows.Forms.Label();
            this.cityLabel = new System.Windows.Forms.Label();
            this.teamTypeIDLabel = new System.Windows.Forms.Label();
            this.sportIDLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dgvSports)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvTeams)).BeginInit();
            this.SuspendLayout();
            // 
            // insertButton
            // 
            this.insertButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.insertButton.Location = new System.Drawing.Point(1177, 357);
            this.insertButton.Margin = new System.Windows.Forms.Padding(4);
            this.insertButton.Name = "insertButton";
            this.insertButton.Size = new System.Drawing.Size(295, 50);
            this.insertButton.TabIndex = 0;
            this.insertButton.Text = "Insert";
            this.insertButton.UseVisualStyleBackColor = true;
            this.insertButton.Click += new System.EventHandler(this.insertButton_click);
            // 
            // updateButton
            // 
            this.updateButton.Location = new System.Drawing.Point(1000, 478);
            this.updateButton.Margin = new System.Windows.Forms.Padding(4);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(295, 50);
            this.updateButton.TabIndex = 11;
            this.updateButton.Text = "Update";
            this.updateButton.UseVisualStyleBackColor = true;
            this.updateButton.Click += new System.EventHandler(this.updateButton_click);
            // 
            // deleteButton
            // 
            this.deleteButton.Location = new System.Drawing.Point(1387, 478);
            this.deleteButton.Margin = new System.Windows.Forms.Padding(4);
            this.deleteButton.Name = "deleteButton";
            this.deleteButton.Size = new System.Drawing.Size(297, 50);
            this.deleteButton.TabIndex = 12;
            this.deleteButton.Text = "Delete";
            this.deleteButton.UseVisualStyleBackColor = true;
            this.deleteButton.Click += new System.EventHandler(this.deleteButton_click);
            // 
            // dgvSports
            // 
            this.dgvSports.AllowUserToAddRows = false;
            this.dgvSports.AllowUserToDeleteRows = false;
            this.dgvSports.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvSports.Location = new System.Drawing.Point(13, 13);
            this.dgvSports.Margin = new System.Windows.Forms.Padding(4);
            this.dgvSports.Name = "dgvSports";
            this.dgvSports.ReadOnly = true;
            this.dgvSports.RowHeadersWidth = 51;
            this.dgvSports.Size = new System.Drawing.Size(919, 225);
            this.dgvSports.TabIndex = 1;
            this.dgvSports.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.parentTable_click);
            // 
            // dgvTeams
            // 
            this.dgvTeams.AllowUserToAddRows = false;
            this.dgvTeams.AllowUserToDeleteRows = false;
            this.dgvTeams.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvTeams.Location = new System.Drawing.Point(13, 293);
            this.dgvTeams.Margin = new System.Windows.Forms.Padding(4);
            this.dgvTeams.Name = "dgvTeams";
            this.dgvTeams.ReadOnly = true;
            this.dgvTeams.RowHeadersWidth = 51;
            this.dgvTeams.Size = new System.Drawing.Size(919, 269);
            this.dgvTeams.TabIndex = 2;
            this.dgvTeams.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.childTable_click);
            // 
            // teamIDBox
            // 
            this.teamIDBox.Location = new System.Drawing.Point(1192, 29);
            this.teamIDBox.Margin = new System.Windows.Forms.Padding(4);
            this.teamIDBox.Name = "teamIDBox";
            this.teamIDBox.Size = new System.Drawing.Size(204, 22);
            this.teamIDBox.TabIndex = 3;
            // 
            // nameBox
            // 
            this.nameBox.Location = new System.Drawing.Point(1192, 66);
            this.nameBox.Margin = new System.Windows.Forms.Padding(4);
            this.nameBox.Name = "nameBox";
            this.nameBox.Size = new System.Drawing.Size(204, 22);
            this.nameBox.TabIndex = 4;
            // 
            // membersBox
            // 
            this.membersBox.Location = new System.Drawing.Point(1192, 120);
            this.membersBox.Margin = new System.Windows.Forms.Padding(4);
            this.membersBox.Name = "membersBox";
            this.membersBox.Size = new System.Drawing.Size(204, 22);
            this.membersBox.TabIndex = 5;
            // 
            // startYearBox
            // 
            this.startYearBox.Location = new System.Drawing.Point(1192, 170);
            this.startYearBox.Margin = new System.Windows.Forms.Padding(4);
            this.startYearBox.Name = "startYearBox";
            this.startYearBox.Size = new System.Drawing.Size(204, 22);
            this.startYearBox.TabIndex = 6;
            // 
            // cityBox
            // 
            this.cityBox.Location = new System.Drawing.Point(1192, 220);
            this.cityBox.Margin = new System.Windows.Forms.Padding(4);
            this.cityBox.Name = "cityBox";
            this.cityBox.Size = new System.Drawing.Size(204, 22);
            this.cityBox.TabIndex = 7;
            // 
            // teamTypeIDBox
            // 
            this.teamTypeIDBox.Location = new System.Drawing.Point(1192, 270);
            this.teamTypeIDBox.Margin = new System.Windows.Forms.Padding(4);
            this.teamTypeIDBox.Name = "teamTypeIDBox";
            this.teamTypeIDBox.Size = new System.Drawing.Size(204, 22);
            this.teamTypeIDBox.TabIndex = 8;
            // 
            // sportIDBox
            // 
            this.sportIDBox.Location = new System.Drawing.Point(1192, 320);
            this.sportIDBox.Margin = new System.Windows.Forms.Padding(4);
            this.sportIDBox.Name = "sportIDBox";
            this.sportIDBox.Size = new System.Drawing.Size(204, 22);
            this.sportIDBox.TabIndex = 9;
            // 
            // teamIDLabel
            // 
            this.teamIDLabel.AutoSize = true;
            this.teamIDLabel.Location = new System.Drawing.Point(1078, 32);
            this.teamIDLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.teamIDLabel.Name = "teamIDLabel";
            this.teamIDLabel.Size = new System.Drawing.Size(61, 17);
            this.teamIDLabel.TabIndex = 9;
            this.teamIDLabel.Text = "Team ID";
            // 
            // nameLabel
            // 
            this.nameLabel.AutoSize = true;
            this.nameLabel.Location = new System.Drawing.Point(1094, 71);
            this.nameLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.nameLabel.Name = "nameLabel";
            this.nameLabel.Size = new System.Drawing.Size(45, 17);
            this.nameLabel.TabIndex = 10;
            this.nameLabel.Text = "Name";
            // 
            // membersLabel
            // 
            this.membersLabel.AutoSize = true;
            this.membersLabel.Location = new System.Drawing.Point(1037, 120);
            this.membersLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.membersLabel.Name = "membersLabel";
            this.membersLabel.Size = new System.Drawing.Size(136, 17);
            this.membersLabel.TabIndex = 11;
            this.membersLabel.Text = "Number of Members";
            // 
            // startYearLabel
            // 
            this.startYearLabel.AutoSize = true;
            this.startYearLabel.Location = new System.Drawing.Point(1094, 170);
            this.startYearLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.startYearLabel.Name = "startYearLabel";
            this.startYearLabel.Size = new System.Drawing.Size(72, 17);
            this.startYearLabel.TabIndex = 12;
            this.startYearLabel.Text = "Start Date";
            // 
            // cityLabel
            // 
            this.cityLabel.AutoSize = true;
            this.cityLabel.Location = new System.Drawing.Point(1101, 223);
            this.cityLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.cityLabel.Name = "cityLabel";
            this.cityLabel.Size = new System.Drawing.Size(31, 17);
            this.cityLabel.TabIndex = 13;
            this.cityLabel.Text = "City";
            // 
            // teamTypeIDLabel
            // 
            this.teamTypeIDLabel.AutoSize = true;
            this.teamTypeIDLabel.Location = new System.Drawing.Point(1076, 275);
            this.teamTypeIDLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.teamTypeIDLabel.Name = "teamTypeIDLabel";
            this.teamTypeIDLabel.Size = new System.Drawing.Size(97, 17);
            this.teamTypeIDLabel.TabIndex = 14;
            this.teamTypeIDLabel.Text = "Team Type ID";
            // 
            // sportIDLabel
            // 
            this.sportIDLabel.AutoSize = true;
            this.sportIDLabel.Location = new System.Drawing.Point(1094, 325);
            this.sportIDLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.sportIDLabel.Name = "sportIDLabel";
            this.sportIDLabel.Size = new System.Drawing.Size(59, 17);
            this.sportIDLabel.TabIndex = 15;
            this.sportIDLabel.Text = "Sport ID";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1756, 608);
            this.Controls.Add(this.teamIDBox);
            this.Controls.Add(this.teamIDLabel);
            this.Controls.Add(this.membersBox);
            this.Controls.Add(this.membersLabel);
            this.Controls.Add(this.startYearBox);
            this.Controls.Add(this.startYearLabel);
            this.Controls.Add(this.nameBox);
            this.Controls.Add(this.sportIDBox);
            this.Controls.Add(this.sportIDLabel);
            this.Controls.Add(this.teamTypeIDBox);
            this.Controls.Add(this.teamTypeIDLabel);
            this.Controls.Add(this.cityBox);
            this.Controls.Add(this.cityLabel);
            this.Controls.Add(this.deleteButton);
            this.Controls.Add(this.updateButton);
            this.Controls.Add(this.nameLabel);
            this.Controls.Add(this.dgvTeams);
            this.Controls.Add(this.dgvSports);
            this.Controls.Add(this.insertButton);
            this.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.form1_load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvSports)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvTeams)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion
    }
}
