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
        private System.Windows.Forms.DataGridView dgvPlayers;
        
        private System.Windows.Forms.TextBox pidBox;
        private System.Windows.Forms.TextBox nameBox;
        private System.Windows.Forms.TextBox surnameBox;
        private System.Windows.Forms.TextBox dateBox;
        private System.Windows.Forms.TextBox genderBox;
        private System.Windows.Forms.TextBox sportIDBox;
        
        private System.Windows.Forms.Label pidLabel;
        private System.Windows.Forms.Label nameLabel;
        private System.Windows.Forms.Label surnameLabel;
        private System.Windows.Forms.Label dateLabel;
        private System.Windows.Forms.Label genderLabel;
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
            this.dgvPlayers = new System.Windows.Forms.DataGridView();
            this.pidBox = new System.Windows.Forms.TextBox();
            this.nameBox = new System.Windows.Forms.TextBox();
            this.surnameBox = new System.Windows.Forms.TextBox();
            this.dateBox = new System.Windows.Forms.TextBox();
            this.sportIDBox = new System.Windows.Forms.TextBox();
            this.pidLabel = new System.Windows.Forms.Label();
            this.nameLabel = new System.Windows.Forms.Label();
            this.surnameLabel = new System.Windows.Forms.Label();
            this.dateLabel = new System.Windows.Forms.Label();
            this.sportIDLabel = new System.Windows.Forms.Label();
            this.genderBox = new System.Windows.Forms.TextBox();
            this.genderLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dgvSports)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvPlayers)).BeginInit();
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
            // parentTable
            // 
            this.dgvSports.AllowUserToAddRows = false;
            this.dgvSports.AllowUserToDeleteRows = false;
            this.dgvSports.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvSports.Location = new System.Drawing.Point(13, 13);
            this.dgvSports.Margin = new System.Windows.Forms.Padding(4);
            this.dgvSports.Name = "parentTable";
            this.dgvSports.ReadOnly = true;
            this.dgvSports.RowHeadersWidth = 51;
            this.dgvSports.Size = new System.Drawing.Size(919, 225);
            this.dgvSports.TabIndex = 1;
            this.dgvSports.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.parentTable_click);
            // 
            // dgvPlayers
            // 
            this.dgvPlayers.AllowUserToAddRows = false;
            this.dgvPlayers.AllowUserToDeleteRows = false;
            this.dgvPlayers.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvPlayers.Location = new System.Drawing.Point(13, 293);
            this.dgvPlayers.Margin = new System.Windows.Forms.Padding(4);
            this.dgvPlayers.Name = "dgvPlayers";
            this.dgvPlayers.ReadOnly = true;
            this.dgvPlayers.RowHeadersWidth = 51;
            this.dgvPlayers.Size = new System.Drawing.Size(919, 269);
            this.dgvPlayers.TabIndex = 2;
            this.dgvPlayers.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.childTable_click);
            // 
            // pidBox
            // 
            this.pidBox.Location = new System.Drawing.Point(1192, 29);
            this.pidBox.Margin = new System.Windows.Forms.Padding(4);
            this.pidBox.Name = "pidBox";
            this.pidBox.Size = new System.Drawing.Size(204, 22);
            this.pidBox.TabIndex = 3;
            // 
            // nameBox
            // 
            this.nameBox.Location = new System.Drawing.Point(1192, 66);
            this.nameBox.Margin = new System.Windows.Forms.Padding(4);
            this.nameBox.Name = "nameBox";
            this.nameBox.Size = new System.Drawing.Size(204, 22);
            this.nameBox.TabIndex = 4;
            // 
            // surnameBox
            // 
            this.surnameBox.Location = new System.Drawing.Point(1192, 120);
            this.surnameBox.Margin = new System.Windows.Forms.Padding(4);
            this.surnameBox.Name = "surnameBox";
            this.surnameBox.Size = new System.Drawing.Size(204, 22);
            this.surnameBox.TabIndex = 5;
            // 
            // dateBox
            // 
            this.dateBox.Location = new System.Drawing.Point(1192, 170);
            this.dateBox.Margin = new System.Windows.Forms.Padding(4);
            this.dateBox.Name = "dateBox";
            this.dateBox.Size = new System.Drawing.Size(204, 22);
            this.dateBox.TabIndex = 6;
            // 
            // sportIDBox
            // 
            this.sportIDBox.Location = new System.Drawing.Point(1192, 253);
            this.sportIDBox.Margin = new System.Windows.Forms.Padding(4);
            this.sportIDBox.Name = "sportIDBox";
            this.sportIDBox.Size = new System.Drawing.Size(204, 22);
            this.sportIDBox.TabIndex = 8;
            // 
            // pidLabel
            // 
            this.pidLabel.AutoSize = true;
            this.pidLabel.Location = new System.Drawing.Point(1000, 29);
            this.pidLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.pidLabel.Name = "pidLabel";
            this.pidLabel.Size = new System.Drawing.Size(65, 17);
            this.pidLabel.TabIndex = 9;
            this.pidLabel.Text = "Player ID";
            // 
            // nameLabel
            // 
            this.nameLabel.AutoSize = true;
            this.nameLabel.Location = new System.Drawing.Point(1014, 71);
            this.nameLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.nameLabel.Name = "nameLabel";
            this.nameLabel.Size = new System.Drawing.Size(45, 17);
            this.nameLabel.TabIndex = 10;
            this.nameLabel.Text = "Name";
            // 
            // surnameLabel
            // 
            this.surnameLabel.AutoSize = true;
            this.surnameLabel.Location = new System.Drawing.Point(1014, 125);
            this.surnameLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.surnameLabel.Name = "surnameLabel";
            this.surnameLabel.Size = new System.Drawing.Size(65, 17);
            this.surnameLabel.TabIndex = 11;
            this.surnameLabel.Text = "Surname";
            // 
            // dateLabel
            // 
            this.dateLabel.AutoSize = true;
            this.dateLabel.Location = new System.Drawing.Point(1017, 173);
            this.dateLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.dateLabel.Name = "dateLabel";
            this.dateLabel.Size = new System.Drawing.Size(38, 17);
            this.dateLabel.TabIndex = 12;
            this.dateLabel.Text = "Date";
            // 
            // sportIDLabel
            // 
            this.sportIDLabel.AutoSize = true;
            this.sportIDLabel.Location = new System.Drawing.Point(1014, 253);
            this.sportIDLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.sportIDLabel.Name = "sportIDLabel";
            this.sportIDLabel.Size = new System.Drawing.Size(59, 17);
            this.sportIDLabel.TabIndex = 14;
            this.sportIDLabel.Text = "Sport ID";
            // 
            // genderBox
            // 
            this.genderBox.Location = new System.Drawing.Point(1192, 210);
            this.genderBox.Margin = new System.Windows.Forms.Padding(4);
            this.genderBox.Name = "genderBox";
            this.genderBox.Size = new System.Drawing.Size(204, 22);
            this.genderBox.TabIndex = 7;
            // 
            // genderLabel
            // 
            this.genderLabel.AutoSize = true;
            this.genderLabel.Location = new System.Drawing.Point(1017, 210);
            this.genderLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.genderLabel.Name = "genderLabel";
            this.genderLabel.Size = new System.Drawing.Size(56, 17);
            this.genderLabel.TabIndex = 13;
            this.genderLabel.Text = "Gender";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1756, 608);
            this.Controls.Add(this.pidBox);
            this.Controls.Add(this.pidLabel);
            this.Controls.Add(this.surnameBox);
            this.Controls.Add(this.surnameLabel);
            this.Controls.Add(this.dateBox);
            this.Controls.Add(this.dateLabel);
            this.Controls.Add(this.nameBox);
            this.Controls.Add(this.sportIDBox);
            this.Controls.Add(this.sportIDLabel);
            this.Controls.Add(this.deleteButton);
            this.Controls.Add(this.updateButton);
            this.Controls.Add(this.nameLabel);
            this.Controls.Add(this.dgvPlayers);
            this.Controls.Add(this.dgvSports);
            this.Controls.Add(this.insertButton);
            this.Controls.Add(this.genderBox);
            this.Controls.Add(this.genderLabel);
            this.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.form1_load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvSports)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvPlayers)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion
    }
}
